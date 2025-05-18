hepsi: derle basla

derle:
	gcc -I ./include/ -o ./lib/Times.o -c ./src/Times.c
	gcc -I ./include/ -o ./lib/Person.o -c ./src/Person.c
	gcc -I ./include/ -o ./lib/Planet.o -c ./src/Planet.c
	gcc -I ./include/ -o ./lib/RockPlanet.o -c ./src/RockPlanet.c
	gcc -I ./include/ -o ./lib/IceGiantPlanet.o -c ./src/IceGiantPlanet.c
	gcc -I ./include/ -o ./lib/GasGiantPlanet.o -c ./src/GasGiantPlanet.c
	gcc -I ./include/ -o ./lib/DwarfPlanet.o -c ./src/DwarfPlanet.c
	gcc -I ./include/ -o ./lib/Spaceship.o -c ./src/Spaceship.c
	gcc -I ./include/ -o ./lib/FileReading.o -c ./src/FileReading.c
	gcc -I ./include/ -o ./lib/Simulation.o -c ./src/Simulation.c
	gcc -I ./include/ -o ./bin/Test ./lib/Times.o ./lib/Person.o ./lib/Planet.o ./lib/RockPlanet.o ./lib/IceGiantPlanet.o ./lib/GasGiantPlanet.o ./lib/DwarfPlanet.o ./lib/Spaceship.o ./lib/FileReading.o ./lib/Simulation.o ./src/main.c

basla:
	./bin/Test