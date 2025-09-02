import os
import platform
import subprocess
import argparse

BUILD_DIR = "build"

def run_command(command, cwd=None):
    """Run a shell command."""
    print(f"\n[RUN] {' '.join(command)}")
    result = subprocess.run(command, cwd=cwd)
    if result.returncode != 0:
        raise RuntimeError(f"Command failed: {' '.join(command)}")

def is_ninja_available():
    """Check if Ninja is available on the system."""
    try:
        subprocess.run(["ninja", "--version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
        return True
    except Exception:
        return False

def configure_and_build(build_type):
    """Configure and build the project."""
    system = platform.system()
    if system == "Windows":
        generator = "Visual Studio 17 2022"  # Possible to set any other version
    elif is_ninja_available():
        generator = "Ninja"
    else:
        generator = "Unix Makefiles"

    os.makedirs(BUILD_DIR, exist_ok=True)

    print(f"[INFO] Using generator: {generator}")
    print(f"[INFO] Build type: {build_type}")

    cmake_command = [
        "cmake",
        "-S", os.getcwd(),
        "-B", os.path.join(os.getcwd(), BUILD_DIR),
        "-G", generator,
        f"-DCMAKE_BUILD_TYPE={build_type}",
    ]
    run_command(cmake_command)

    build_command = [
        "cmake",
        "--build", os.path.join(os.getcwd(), BUILD_DIR),
        "--config", build_type,
    ]
    run_command(build_command)

def run_tests(build_type):
    """Run unit tests."""
    if not os.path.exists(BUILD_DIR):
        raise RuntimeError(f"Build directory '{BUILD_DIR}' does not exist. Cannot run tests.")
    run_command(["ctest", "--output-on-failure", "-C", build_type], cwd=BUILD_DIR)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Build and test the project.")
    parser.add_argument("--release", action="store_true", help="Build in Release mode")
    parser.add_argument("--debug", action="store_true", help="Build in Debug mode")
    parser.add_argument("--skip-tests", action="store_true", help="Skip running tests")
    args = parser.parse_args()

    build_type = "Debug"
    if args.release:
        build_type = "Release"
    elif args.debug:
        build_type = "Debug"

    try:
        configure_and_build(build_type)
        if not args.skip_tests:
            run_tests(build_type)
    except RuntimeError as e:
        print(f"[ERROR] {e}")
