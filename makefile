all:
	gcc -o prog main.c project.c listArrayList.c mapArrayList.c utils.c date.c patient.c listElem.c mapElem.c region.c
debug:
	gcc -g -o prog main.c project.c listArrayList.c mapArrayList.c utils.c date.c patient.c listElem.c mapElem.c region.c
clean:
	rm -f prog