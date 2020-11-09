proj07: proj07.student.o
	g++ -pthread  proj07.student.o -o proj07
proj07.student.o: proj07.student.c
	g++ -Wall -pthread -c  proj07.student.c 
clean:
	rm -f proj07.student.orm -f proj07
