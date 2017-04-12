CC=gcc -g
CFLAGS=-W -Wall -ansi -pedantic
EXEC1=progSDL
EXEC2=progTXT


all: $(EXEC1) $(EXEC2)


progSDL: ./obj/affichageSDL.o ./obj/position.o ./obj/protection.o ./obj/ensembleprotection.o ./obj/map.o ./obj/missile.o ./obj/scores.o ./obj/alien.o ./obj/vaisseau.o ./obj/ensemblealien.o ./obj/jeu.o ./obj/ensemblemissile.o ./obj/jeuSDL.o
	$(CC) -o ./bin/progSDL $^ -lSDL2-2.0 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


progTXT: ./obj/main.o ./obj/position.o ./obj/protection.o ./obj/ensembleprotection.o ./obj/map.o ./obj/missile.o ./obj/scores.o ./obj/alien.o ./obj/vaisseau.o ./obj/ensemblealien.o ./obj/jeu.o ./obj/ensemblemissile.o 
	$(CC) -o ./bin/progTXT $^ 


./obj/affichageSDL.o: ./src/affichageSDL.c ./src/position.h ./src/protection.h ./src/ensembleprotection.h ./src/map.h ./src/alien.h ./src/ensemblealien.h ./src/missile.h ./src/vaisseau.h ./src/scores.h ./src/jeu.h ./src/jeuSDL.h
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/main.o: ./src/main.c ./src/position.h ./src/protection.h ./src/ensembleprotection.h ./src/map.h ./src/alien.h ./src/ensemblealien.h ./src/missile.h ./src/vaisseau.h ./src/scores.h ./src/jeu.h ./src/jeuSDL.h
	$(CC) -o $@ -c $< $(CFLAGS)


./obj/position.o: ./src/position.c ./src/position.h
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/protection.o: ./src/protection.c ./src/position.h ./src/protection.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
./obj/ensembleprotection.o: ./src/ensembleprotection.c ./src/position.h ./src/ensembleprotection.h ./src/protection.h
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/map.o: ./src/map.c ./src/map.h 
	$(CC) -o $@ -c $< $(CFLAGS)	
	
./obj/missile.o: ./src/missile.c ./src/position.h ./src/missile.h
	$(CC) -o $@ -c $< $(CFLAGS)	
	
./obj/scores.o: ./src/scores.c ./src/scores.h 
	$(CC) -o $@ -c $< $(CFLAGS)	
	
./obj/alien.o: ./src/alien.c ./src/position.h ./src/alien.h
	$(CC) -o $@ -c $< $(CFLAGS)	
	
./obj/vaisseau.o: ./src/vaisseau.c ./src/position.h ./src/vaisseau.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
./obj/ensemblealien.o: ./src/ensemblealien.c ./src/position.h ./src/alien.h ./src/ensemblealien.h
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/ensemblemissile.o: ./src/ensemblemissile.c ./src/position.h ./src/missile.h ./src/ensemblemissile.h
	$(CC) -o $@ -c $< $(CFLAGS)	
	
./obj/jeu.o: ./src/jeu.c ./src/jeu.h ./src/protection.h ./src/ensembleprotection.h ./src/map.h ./src/alien.h ./src/ensemblealien.h ./src/missile.h ./src/ensemblemissile.h ./src/vaisseau.h ./src/scores.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
./obj/jeuSDL.o: ./src/jeuSDL.c ./src/jeuSDL.h ./src/protection.h ./src/ensembleprotection.h ./src/map.h ./src/alien.h ./src/ensemblealien.h ./src/missile.h ./src/ensemblemissile.h ./src/vaisseau.h ./src/scores.h ./src/jeu.h
	$(CC) -o $@ -c $< $(CFLAGS)
	



clean:
	rm -rf ../obj/*.o

mrproper: clean
	rm -rf ./obj/$(EXEC1) ./obj/$(EXEC2)
