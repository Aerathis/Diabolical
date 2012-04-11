OBJ = Player.o Loader.o Model.o World.o Renderer.o Entity.o Weather.o \
	  ../../../tools/xorshift.o Creators.o Object.o Brain.o

linux : CApp

clean :
	rm *.o

profile : CApp
	g++ -o CApp -I ../../../ExternalLibs/bullet/src -I ../../../ExternalLibs/SDL CApp.cpp $(OBJ) -L ../../../ExternalLibs/bullet/src/.libs/libBulletDynamics.a -L ../../../ExternalLibs/bullet/src/.libs/libBulletCollision.a -L ../../../ExternalLibs/bullet/src/.libs/libLinearMath.a `sdl-config --cflags --libs` -lGL -lBulletDynamics -lBulletCollision -lLinearMath -ltinyxml -pg

CApp : CApp.h CApp.cpp Map.h $(OBJ) 
	g++ -o CApp -I ../../../ExternalLibs/bullet/src -I ../../../ExternalLibs/SDL CApp.cpp $(OBJ) -L ../../../ExternalLibs/bullet/src/.libs/libBulletDynamics.a -L ../../../ExternalLibs/bullet/src/.libs/libBulletCollision.a -L ../../../ExternalLibs/bullet/src/.libs/libLinearMath.a `sdl-config --cflags --libs` -lGL -lBulletDynamics -lBulletCollision -lLinearMath -ltinyxml

CApp.exe : CApp.h CApp.cpp Player.o
	g++ -o CApp.exe -I ../../../ExternalLibs/bullet/src -I ../../../ExternalLibs/SDL \
	CApp.cpp ../../../ExternalLibs/bullet/src/.libs/libBulletDynamics.a \
	../../../ExternalLibs/bullet/src/.libs/libBulletCollision.a \
	../../../ExternalLibs/bullet/src/.libs/libLinearMath.a `sdl-config --cflags --libs` \
	-lopengl32

Player.o : Player.cpp Player.h
	g++ -c -I ../../../ExternalLibs/bullet/src Player.cpp

Loader.o : Loader.cpp Loader.h
	g++ -c Loader.cpp

Model.o : Model.cpp Model.h
	g++ -c Model.cpp 

World.o : World.cpp World.h
	g++ -c -I ../../../ExternalLibs/bullet/src World.cpp

Renderer.o : Renderer.cpp Renderer.h
	g++ -c -I ../../../ExternalLibs/SDL -I ../../../ExternalLibs/bullet/src Renderer.cpp

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
