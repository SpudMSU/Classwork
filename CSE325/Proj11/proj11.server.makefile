proj11.server: proj11.server.o
	g++ -pthread  proj11.server.o -o proj11.server
proj11.server.o: proj11.server.c
	g++ -Wall -pthread -c proj11.server.c
clean:
	rm -f proj11.server.orm -f proj11.server
