game:	game.o keyboard.o xterm_control.o 
	gcc game.o keyboard.o xterm_control.o -o game

game.o:	game.c
	gcc -c game.c
	
keyboard.o: keyboard.c
	gcc -c keyboard.c

xterm_control.o: xterm_control.c
	gcc -c xterm_control.c
