# From https://github.com/shibbo/Syati
import datetime
import os
import glob
import shutil
import subprocess
import sys

def err(message: str):
    print(f"Error: {message}")
    sys.exit(1)

def log(message: str):
	    print("[{}] {}".format(datetime.datetime.now(), message))

debug = False
if(len(sys.argv) > 1):
	debug = True

log("Building Strikers 2013 Xtreme")

if not os.path.exists("cw/mwcceppc.exe"):
    err("CodeWarrior compiler not found.")
if not os.path.exists("km/Kamek.exe"):
    err("Kamek linker not found.")

command = "cw\mwcceppc.exe " + "-I- -i ./includes/ -i ./includes/Kamek/ -i ./source/ -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 "
if debug:
	command += "-d DEBUG "
command += "-c -o "

# Clean the entire build folder first if it exists
if os.path.exists("build"):
    shutil.rmtree("build", ignore_errors=True)

# Fetch all source C++ files that need to be compiled
tasks = list()
asm_tasks = list()

for root, dirs, files in os.walk("source"):
    for file in files:
        if file.endswith(".cpp"):
            source_path = os.path.join(root, file)
            build_path = source_path.replace("source", "build").replace(".cpp", ".o")

            os.makedirs(os.path.dirname(build_path), exist_ok=True)

            tasks.append((source_path, build_path))

if len(tasks) < 1 and len(asm_tasks) < 1:
    err("No C++/asm files to compile!")


# Process all compile tasks
for task in tasks:
    source_path, build_path = task

    log(f"Compiling {source_path}...")

    if subprocess.call(f"{command} {build_path} {source_path}", shell=True) != 0:
        err("Compiler error.")

# Link all object files and create the CustomCode binary
log("Linking...")

object_files = " ".join([task[1] for task in tasks])

kamek_cmd = f"km\Kamek.exe {object_files} -externals=symbols.txt -output-kamek=CustomCode.bin"

if subprocess.call(kamek_cmd, shell=True) != 0:
    err("Linking failed.")

# Remove all useless "d" files
for f in glob.glob("*.d"):
    os.remove(f)

log("Done!")