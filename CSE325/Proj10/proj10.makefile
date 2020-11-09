proj10: proj10.student.o
	g++ -pthread  proj10.student.o -o proj10
proj10.student.o: proj10.student.c
	g++ -Wall -pthread -c  proj10.student.c 
clean:
	rm -f proj09.student.orm -f proj10
