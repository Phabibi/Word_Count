all: Main

Main: src/Writer.cpp src/Reader.cpp main.cpp 
	g++ -std=c++11 main.cpp  -o  main	

clean:
	rm -f main *.o