all: test_dij

test_dij: test_dij.c RList.c minHeap.c graph.c
	gcc -fopenmp test_dij.c RList.c minHeap.c graph.c -o test_dij

clean:
	rm test_dij