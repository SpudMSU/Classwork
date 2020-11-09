proj11.client: proj11.client.o
	g++ -pthread  proj11.client.o -o proj11.client
proj11.client.o: proj11.client.c
	g++ -Wall -pthread -c proj11.client.c
clean:
	rm -f proj11.client.orm -f proj11.client