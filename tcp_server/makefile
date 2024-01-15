tcp_server: main.o server.o
	g++ -o tcp_server main.o server.o

main.o: main.cpp server.h
	g++ -c main.cpp

server.o: server.cpp server.h
	g++ -c server.cpp

clean:
	rm -f tcp_server main.o server.o