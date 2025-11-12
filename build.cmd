@echo off

del /f build\*.o bin\prog.exe

gcc -c lab2.6.c -Iincludes -o build/main.o
gcc -c func.c -Iincludes -o build/func.o

gcc build/main.o build/func.o -o bin\lab2.exe
bin\lab2.exe