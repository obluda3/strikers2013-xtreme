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

def delete_encoded(tasks):
    for task in tasks:
        source_path, build_path = task
        os.remove(source_path)

debug = False
if(len(sys.argv) > 1):
	debug = True

log("Building Strikers 2013 Xtreme")

if not os.path.exists("cw/mwcceppc.exe"):
    err("CodeWarrior compiler not found.")
if not os.path.exists("km/Kamek.exe"):
    err("Kamek linker not found.")

command = ""
if debug:
	command = "cw\mwcceppc.exe " + "-I- -i ./includes/ -i ./includes/Kamek/ -i ./source/ -Cpp_exceptions off -enc SJIS -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -d DEBUG -c -o "
else:
	command = "cw\mwcceppc.exe " + "-I- -i ./includes/ -i ./includes/Kamek/ -i ./source/ -Cpp_exceptions off -enc SJIS -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o "
asm_cmd = "cw\mwasmeppc.exe "  + "-I- -i ./includes/ -i ./includes/Kamek/ -c -o "

# Clean the entire build folder first if it exists
if os.path.exists("build"):
    shutil.rmtree("build", ignore_errors=True)

# Fetch all source C++ files that need to be compiled
tasks = list()
asm_tasks = list()

for root, dirs, files in os.walk("source"):
    for file in files:
        if file.endswith(".cpp"):
            default_source_path = os.path.join(root, file)
            converted_path = default_source_path + "_conv.cpp"
            with open(default_source_path, mode="r", encoding="utf8") as fd:
                content = fd.read()
            with open(converted_path, mode="w", encoding="shift-jis") as fd:
                try:
                    fd.write(content)
                except:
                    print(content)
            build_path = default_source_path.replace("source", "build").replace(".cpp", ".o")

            os.makedirs(os.path.dirname(build_path), exist_ok=True)

            tasks.append((converted_path, build_path))
        elif file.endswith(".S"):
            source_path = os.path.join(root, file)
            build_path = source_path.replace("source", "build").replace(".S", ".o")

            os.makedirs(os.path.dirname(build_path), exist_ok=True)

            asm_tasks.append((source_path, build_path))

if len(tasks) < 1 and len(asm_tasks) < 1:
    err("No C++/asm files to compile!")


# Process all compile tasks
for task in tasks:
    source_path, build_path = task

    log(f"Compiling {source_path}...")

    if subprocess.call(f"{command} {build_path} {source_path}", shell=True) != 0:
        delete_encoded(tasks)
        err("Compiler error.")

for a_task in asm_tasks:
    source_path, build_path = a_task
    log(f"Assembling {source_path}...")

    if subprocess.call(f"{asm_cmd} {build_path} {source_path}", shell=True) != 0:
        delete_encoded(tasks)
        err("Assembler error.")

# Link all object files and create the CustomCode binary
log("Linking...")

object_files = " ".join([task[1] for task in tasks])
asm_obj_files = " ".join([a_task[1] for a_task in asm_tasks])

kamek_cmd = f"km\Kamek.exe {object_files} {asm_obj_files} -externals=symbols.txt -output-kamek=CustomCode.bin"

if subprocess.call(kamek_cmd, shell=True) != 0:
    delete_encoded(tasks)
    err("Linking failed.")

# Remove all useless "d" files
for f in glob.glob("*.d"):
    os.remove(f)

# Remove encoding-corrected files
delete_encoded(tasks)

log("Done!")