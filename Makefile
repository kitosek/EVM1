all:checkdir bin/prog 

bin/prog:build/myTerm.o build/Term.o build/SimpleComputer.o 
	gcc build/myTerm.o build/Term.o build/SimpleComputer.o -o bin/prog

build/myTerm.o:src/myTerm.c
	gcc -c src/myTerm.c -o build/myTerm.o -Wall 

build/Term.o:src/Term.c
	gcc -c src/Term.c -o build/Term.o -Wall 

build/SimpleComputer.o:src/SimpleComputer.c
	gcc -c src/SimpleComputer.c -o build/SimpleComputer.o -Wall 

checkdir:
	@if [ -d bin  ];then echo ; else mkdir bin;fi
	@if [ -d build  ];then echo ; else mkdir build;fi
