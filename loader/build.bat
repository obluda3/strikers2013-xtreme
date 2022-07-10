..\cw\mwcceppc -i . -I- -i ../includes/Kamek -i ../includes/ -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o kamekLoader.o kamekLoader.cpp
..\cw\mwcceppc -i . -I- -i ../includes/Kamek -i ../includes/ -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o loader.o loader.cpp

..\km\Kamek kamekLoader.o loader.o -static=0x804EACD0 -input-dol=main.dol -output-dol=main_kamek.dol

