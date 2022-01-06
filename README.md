# Inazuma Eleven GO Strikers 2013 Xtreme
This repository contains all of the code used in the Inazuma Eleven GO Strikers 2013 Xtreme game mod.

It uses a modified version of [Kamek](https://github.com/Treeki/Kamek) and [Syati](https://github.com/shibbo/Syati/) to be able to compile custom code and link to existing functions in the game.

# Requirements
- [CodeWarrior Special Edition](http://web.archive.org/web/20160602205749/http://www.nxp.com/products/software-and-tools/software-development-tools/codewarrior-development-tools/downloads/special-edition-software:CW_SPECIALEDITIONS). After installing it, you need `license.dat` from the installation root, and the DLL and EXE files inside `PowerPC_EABI_Tools/Command_Line_Tools`. You need to store them in a `cw` folder.
- [Kamek](https://github.com/Treeki/Kamek). After compiling it, store it in a `km` folder.
- Python 3.7

# Usage

Use the script in `/loader/` order to create a modified main.dol that will be able to load custom code.

To build the custom code, use the `build.py` script, it will create a `CustomCode.bin` file that will be placed in a `Code` folder at the root of your extracted game.


# TODO

- Complete the header files (some of them are very empty right now)
