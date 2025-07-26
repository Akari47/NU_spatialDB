spatialdb: main_menu.o database.o page.o
	gcc -lm -o spatialdb main_menu.o database.o page.o

main_menu.o: main_menu.c database.h page.h item.h
	gcc -c main_menu.c

page.o: page.c page.h item.h
	gcc -c page.c

database.o: database.c database.h item.h readline.o
	gcc -c database.c

readline.o: readline.c readline.h
	gcc -c readline.c
clean:
	rm -f *.o spatialdb