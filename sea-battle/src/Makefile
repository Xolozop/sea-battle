all: main.o exceptions.o ship.o shipManager.o field.o skill.o doubleAtack.o scanner.o shelling.o skillManager.o
	g++ main.o exceptions.o ship.o shipManager.o field.o skill.o doubleAtack.o scanner.o shelling.o skillManager.o -o lb

main.o: main.cpp field.h shipManager.h ship.h skill.h doubleAtack.h
	g++ -lstdc++ -c main.cpp

ship.o: ship.cpp ship.h
	g++ -c ship.cpp

shipManager.o: shipManager.cpp shipManager.h ship.h
	g++ -c shipManager.cpp

field.o: field.cpp field.h shipManager.h ship.h
	g++ -c field.cpp

skill.o: skill.cpp field.h skill.h
	g++ -c skill.cpp

doubleAtack.o: doubleAtack.cpp doubleAtack.h
	g++ -c doubleAtack.cpp

scanner.o: scanner.cpp scanner.h
	g++ -c scanner.cpp

shelling.o: shelling.cpp shelling.h
	g++ -c shelling.cpp

skillManager.o: skillManager.cpp skillManager.h skill.h doubleAtack.h scanner.h shelling.h
	g++ -c skillManager.cpp

eceptions.o: exceptions.cpp exceptions.h
	g++ -c exceptions.cpp

clean:
	rm -f ./*.o lb
