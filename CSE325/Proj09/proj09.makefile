proj09: proj09.student.o
	g++ -pthread  proj09.student.o -o proj09
proj09.student.o: proj09.student.c
	g++ -Wall -pthread -c  proj09.student.c 
clean:
	rm -f proj09.student.orm -f proj09
