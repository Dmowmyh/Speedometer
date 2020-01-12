all:
	g++ -g -o exe main.cpp Shader.cpp ResourceMgr.cpp Acceleration.cpp timercpp/timercpp.cpp -lGL -lGLU -lglut -lGLEW -lpthread
