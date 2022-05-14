sim: sim.o body.o vec3.o
	g++ -o sim.exe sim.o body.o vec3.o

body.o: body.cpp
	g++ -c body.cpp

sim.o: sim.cpp
	g++ -c sim.cpp

vec3.o: vec3.cpp
	g++ -c vec3.cpp

clean:
	cmd /K "del *.o *.exe & exit"

