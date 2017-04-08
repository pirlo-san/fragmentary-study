
all: graph list

graph:
	gcc graph.c test_graph.c test_main.c test_api.c -o testbin

list:
	gcc test_list.c -o testbin

clean:
	rm -f testbin *.o
