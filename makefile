all:
	gcc -o prog main.c project.c
debug:
	gcc -g -o prog main.c project.c
clean:
	rm -f prog