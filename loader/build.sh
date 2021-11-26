CW_PATH=../cw
CPPFILES="kamekLoader megane"

CC=$CW_PATH/mwcceppc
CFLAGS="-i . -I- -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0"

for i in $CPPFILES
do
	echo Compiling $i.cpp...
	$CC $CFLAGS -c -o $i.o $i.cpp
done

echo Linking...

../Kamek/bin/Debug/Kamek kamekLoader.o megane.o -static=0x80001900 -input-dol=main.dol -output-dol=main_kamek.dol