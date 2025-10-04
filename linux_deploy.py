import os
import shutil
import subprocess
import urllib.request


QT_DIR = "/home/alexander/Qt/6.9.2/gcc_64"  # Qt install directory
BUILD_DIR = "ExpanderUi/build/Desktop_Qt_6_9_2-Release"
APP_BINARY = os.path.join(BUILD_DIR, "IntExp")  # Created by QtCreator build
APPDIR_DIR = os.path.join(BUILD_DIR, "AppDir")  # Created by linuxdeployqt6.py
SOURCE_SO_DIR = BUILD_DIR
TARGET_SO_DIR = os.path.join(APPDIR_DIR, "lib")
METAINFO_DIR = os.path.join(APPDIR_DIR, "usr/share/metainfo")

DESKTOP_FILE = "ExpanderUi/IntExp.desktop"
ICON_FILE = "ExpanderUi/IntExp.svg"
ICON_FILE2 = "ExpanderUi/IntExp.png"
APPRUN_FILE = "ExpanderUi/AppRun"
APPDATAXML_FILE = "ExpanderUi/IntExp.appdata.xml"
APPIMAGETOOL_PATH = "/home/alexander/tools/appimagetool-x86_64.AppImage"


def deploy_qt_app(build_dir):
    os.makedirs(build_dir, exist_ok=True)
    script_url = "https://raw.githubusercontent.com/gavv/linuxdeployqt6.py/main/linuxdeployqt6.py"
    script_path = os.path.join(build_dir, "linuxdeployqt6.py")

    # Download the script
    print(f"Downloading {script_url}...")
    urllib.request.urlretrieve(script_url, script_path)
    print(f"Saved to {script_path}")

    # Ensure it's executable
    os.chmod(script_path, 0o755)

    # Run the deployment command
    cmd = [
        "python3", "linuxdeployqt6.py",
        "-force",
        "-qtdir", QT_DIR,
        "-out-dir=./AppDir",
        "-out-lib-dir=./AppDir/lib",
        "-out-plugins-dir=./AppDir/plugins",
        "-qmlscandir=./ExpanderUi",
        "-verbose=2",
        "./IntExp"
    ]
    print("Running:", " ".join(cmd))
    subprocess.run(cmd, cwd=build_dir, check=True)


def copy_lib_dependencies(file_path, target_dir, only_not_founds=False):
    # Parse ldd output and copy non-system libraries
    ldd_output = subprocess.check_output(["ldd", file_path], text=True).splitlines()

    for line in ldd_output:
        parts = line.strip().split("=>")
        if len(parts) < 2:
            continue

        lib_name = parts[0].strip()  # The name the loader expects, e.g., libQt6Xml.so.6
        lib_path = parts[1].split("(")[0].strip()

        if not lib_path or not os.path.exists(lib_path):
            if lib_path and lib_path.strip() == "not found":
                # Search in your Qt lib folder
                lib_path = os.path.join(QT_DIR, "lib", lib_name)
                if os.path.islink(lib_path):
                    target = os.readlink(lib_path)
                    lib_path = os.path.abspath(os.path.join(os.path.dirname(lib_path), target))

                if not os.path.exists(lib_path):
                    raise RuntimeError(f"Unhandled lib: {line}")
            else:
                raise RuntimeError(f"Unhandled lib: {line}")
        else:
            if only_not_founds:
                continue

        # Copy the real file and rename it to match the loader name
        dest_path = os.path.join(target_dir, lib_name)

        if not os.path.exists(dest_path):
            print(f"Copying library: {lib_path} -> {dest_path}")
            shutil.copy(lib_path, dest_path)
        else:
            pass
            # print(f"Library already present, skip copy!")


def copy_all_libs(dir_path, target_dir):
    os.makedirs(target_dir, exist_ok=True)  # Ensure target directory exists

    for f in os.listdir(dir_path):
        full_path = os.path.join(dir_path, f)
        if os.path.isfile(full_path) and (f.endswith(".so") or ".so." in f):
            target_file = os.path.join(target_dir, f)
            if not os.path.exists(target_file):
                shutil.copy(full_path, target_file)
                print(f"Copied {full_path} -> {target_file}")


if __name__ == "__main__":
    deploy_qt_app(BUILD_DIR)

    # Search and copy "not found" libs (not found by ldd, therefore not copied by linuxdeployqt6.py)
    copy_lib_dependencies(APP_BINARY, TARGET_SO_DIR, only_not_founds=True)

    # Copy shared project libs (not copied by linuxdeployqt6.py)
    copy_all_libs(SOURCE_SO_DIR, TARGET_SO_DIR)

    # Run app (for testing)
    cmd = [
        "./IntExp"
    ]
    print("Running:", " ".join(cmd))
    subprocess.run(cmd, cwd=APPDIR_DIR, check=True)

    # Copy files
    # desktop_file = os.path.join(APPDIR_DIR, "com.almcoding.InterfaceExpander.desktop")
    shutil.copy(DESKTOP_FILE, APPDIR_DIR)
    shutil.copy(ICON_FILE, APPDIR_DIR)
    shutil.copy(ICON_FILE2, APPDIR_DIR)
    os.chmod(APPRUN_FILE, 0o755)
    shutil.copy(APPRUN_FILE, APPDIR_DIR)
    os.makedirs(METAINFO_DIR, exist_ok=True)
    # appdataxml_file = os.path.join(METAINFO_DIR, "com.almcoding.InterfaceExpander.appdata.xml")
    # shutil.copy(APPDATAXML_FILE, METAINFO_DIR)

    # Build AppImage
    cmd = [APPIMAGETOOL_PATH, "-v", "./AppDir"]
    print("Running:", " ".join(cmd))
    subprocess.run(cmd, cwd=BUILD_DIR, check=True)
