prog:quiz.o main.o
	gcc quiz.o main.o -o prog -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
quiz.o:quiz.c
	gcc -c quiz.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx 
main.o:main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf	