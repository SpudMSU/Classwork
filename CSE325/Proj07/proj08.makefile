proj08: proj08.student.o
	g++ -pthread  proj08.student.o -o proj08
proj08.student.o: proj08.student.c
	g++ -Wall -pthread -c  proj08.student.c 
clean:
	rm -f proj08.student.orm -f proj08
