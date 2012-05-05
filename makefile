OBJ = Diabolical.o Model.o World.o Entity.o Weather.o Renderer.o \
	  ../../../tools/xorshift.o Creators.o Object.o Brain.o Structure.o \
	  DudeGroup.o

linux : CApp

clean :
	rm *.o

Main : main.cpp main.h Input.h Map.h $(OBJ)
	g++ -o Main main.cpp $(OBJ) -lGL -lX11

Diabolical.o : Diabolical.cpp Diabolical.h
	g++ -c Diabolical.cpp

Player.o : Player.cpp Player.h
	g++ -c -I ../../../ExternalLibs/bullet/src Player.cpp

Loader.o : Loader.cpp Loader.h
	g++ -c Loader.cpp

Model.o : Model.cpp Model.h
	g++ -c Model.cpp 

World.o : World.cpp World.h
	g++ -c -I ../../../ExternalLibs/bullet/src World.cpp

Renderer.o : Renderer.cpp Renderer.h
	g++ -c Renderer.cpp

Entity.o : Entity.h Entity.cpp Brain.o
	g++ -c -I ../../../ExternalLibs/bullet/src Entity.cpp

Dude.o : Dude.h Dude.cpp
	g++ -c Dude.cpp

Weather.o : Weather.h Weather.cpp
	g++ -c Weather.cpp

Creators.o : Creators.h Creators.cpp
	g++ -c Creators.cpp

Object.o : Object.h Object.cpp
	g++ -c Object.cpp

Brain.o : Brain.cpp Brain.h
	g++ -c Brain.cpp

Structure.o : Structure.h Structure.cpp Object.h Object.cpp
	g++ -c Structure.cpp

DudeGroup.o : DudeGroup.h DudeGroup.cpp
	g++ -c DudeGroup.cpp
