from pathlib import Path
from typing import Set, List
import argparse
import difflib
import subprocess
import sys

DEFAULT_IGNORE_FILES = {
    'LICENSE',
    'License.md',
    'license.md',
    'license.txt',
    'README.md',
    'ReadMe.md',
    'Readme.md',
    'readme.md',
    'readMe.md',
    '.gitignore',
}

DEFAULT_IGNORE_DIRS = {
    '__pycache__',
    '.git',
    '.idea',
    'venv',
    'build',
    'dist'
}


def compare_directories(
        template_dir: str,
        client_dir: str,
        ignore_files: Set[str],
        ignore_dirs: Set[str]) -> tuple[bool, List[str]]:
    # Convert paths to Path objects
    template_dir_path = Path(template_dir)
    client_dir_path = Path(client_dir)

    # Check if both directories exist
    if not template_dir_path.is_dir() or not client_dir_path.is_dir():
        print("Error: One or both paths are not valid directories")
        return False, []

    # Get all files recursively in both directories, excluding ignored directories
    def get_files(directory: Path) -> Set[Path]:
        files = set()
        for f in directory.rglob('*'):
            if any(parent.name in ignore_dirs for parent in f.parents):
                continue
            if f.is_file():
                files.add(f.relative_to(directory))
        return files

    template_files = get_files(template_dir_path)
    client_files = get_files(client_dir_path)

    # Remove ignored files from both sets
    ignored_in_client = {f for f in client_files if f.name in ignore_files}
    if ignored_in_client:
        print("Ignoring files:", ", ".join(sorted(f.name for f in ignored_in_client)))

    template_files = {f for f in template_files if f.name not in ignore_files}
    client_files = {f for f in client_files if f.name not in ignore_files}

    # Find common files
    common_files = template_files & client_files

    if not common_files:
        print("No common files found")
        return True, []

    all_identical = True
    diffs = []

    # Compare each common file
    for relative_file_path in common_files:
        template_file_path = template_dir_path / relative_file_path
        client_file_path = client_dir_path / relative_file_path

        with open(template_file_path, 'r') as template_file, open(client_file_path, 'r') as client_file:
            template_content = template_file.readlines()
            client_content = client_file.readlines()

            if template_content != client_content:
                all_identical = False
                diff = ''.join(difflib.unified_diff(
                    client_content,
                    template_content,
                    tofile=str(client_file_path),
                    fromfile=str(template_file_path),
                ))
                diffs.append(diff)
                print(f"\nFound differences in {relative_file_path}:")

    return all_identical, diffs


def apply_diffs_to_client(diffs: List[str]) -> bool:
    """
    Apply a list of diffs to the client directory using git apply.

    Args:
        diffs: List of unified diff strings to apply

    Returns:
        bool: True if all diffs were applied successfully, False otherwise
    """
    if not diffs:
        print("No diffs to apply")
        return True

    try:
        # Create a temporary file with all diffs
        patch_file_path = Path('temp.patch')
        with patch_file_path.open('w') as patch_file:
            for diff in diffs:
                patch_file.write(diff)

        # Apply the patch using git apply
        result = subprocess.run(
            ['git', 'apply', '--unsafe-paths', '-p0', patch_file_path],
            capture_output=True,
            text=True
        )

        # Clean up the temporary patch file
        patch_file_path.unlink()

        if result.returncode != 0:
            print("Error applying patches:")
            print(result.stderr)
            return False

        print("Successfully applied all patches")
        return True

    except Exception as e:
        print(f"Error while applying patches: {str(e)}")
        return False


def parse_ignore_list(ignore_list: str) -> Set[str]:
    """Convert a comma-separated ignore list to a set"""
    if not ignore_list:
        return set()

    return {name.strip() for name in ignore_list.split(',')}


def parse_arguments():
    parser = argparse.ArgumentParser(
        description='Compare files that are common between template and client directories.',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )

    parser.add_argument(
        '-t', '--template-directory',
        required=True,
        help='Template directory path to compare'
    )

    parser.add_argument(
        '-c', '--client-directory',
        required=True,
        help='Client directory path to compare'
    )

    parser.add_argument(
        '-i', '--ignore-files',
        default='',
        help='Comma-separated list of additional files to ignore'
    )

    parser.add_argument(
        '-d', '--ignore-dirs',
        default='',
        help='Comma-separated list of additional directories to ignore'
    )

    parser.add_argument(
        '--no-default-ignores',
        action='store_true',
        help='Disable default ignore lists for both files and directories'
    )

    parser.add_argument(
        '--apply-diffs',
        action='store_true',
        help='Apply the differences to the client directory using git apply'
    )

    return parser.parse_args()


def main() -> int:
    args = parse_arguments()

    # Build the complete ignore lists
    ignore_files = set()
    ignore_dirs = set()

    if not args.no_default_ignores:
        ignore_files.update(DEFAULT_IGNORE_FILES)
        ignore_dirs.update(DEFAULT_IGNORE_DIRS)

    ignore_files.update(parse_ignore_list(args.ignore_files))
    ignore_dirs.update(parse_ignore_list(args.ignore_dirs))

    success, diffs = compare_directories(
        args.template_directory,
        args.client_directory,
        ignore_files,
        ignore_dirs)

    if success:
        print(f"Success. {args.template_directory} and {args.client_directory} match")
    elif args.apply_diffs:
        success = apply_diffs_to_client(diffs)

    if not success:
        print("Failed to establish congruency / apply diffs")
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
