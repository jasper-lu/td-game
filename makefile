test:	test.o keyboard.o xterm_control.o structs.o
	gcc test.o keyboard.o xterm_control.o structs.o -o test
	
test.o:	test.c
	gcc -c test.c
	
keyboard.o: keyboard.c
	gcc -c keyboard.c

xterm_control.o: xterm_control.c
	gcc -c xterm_control.c

structs.o: structs.c
	gcc -c structs.c 
