# The short paths problem with Dijkstra's algorithm, Min Heap and Graph structure.

## Content

1. Repo contents

2. Answers and Performance

3. How to compile

4. Discussions

## Repo Contents

1. `graph .c / .h` - contains the graph functions and interface

2. `minHeap .c / .h` -  contains the Min Heap functions and interface

3. `RList .c / .h` - contains a list structure for storing the results. Each list instance I used is of length 10, with each of their node contains the start and end vertex and the distance.

4.  `test_dij.c` - contains the main function, the `dijkstra` function, and the `result_paths` function which calculates the 10 longest "shortest paths" with the given graph, and return a list (``RList``) of length 10 and sorted by the distances.

## Answers and performance

### the small graph

```
start vertex 5995, end vertex 6278, distance 181
start vertex 4193, end vertex 6278, distance 181
start vertex 644, end vertex 6188, distance 181
start vertex 4568, end vertex 6278, distance 183
start vertex 644, end vertex 6187, distance 183
start vertex 3634, end vertex 6278, distance 184
start vertex 645, end vertex 6278, distance 184
start vertex 5720, end vertex 6278, distance 186
start vertex 644, end vertex 6290, distance 186
start vertex 644, end vertex 6278, distance 192
```

```
Time costs with 1 threads: 12.383723
```

```
Time costs with 30 threads: 1.768237
```

### the large graph

```
start vertex 40743, end vertex 36397, distance 101
start vertex 40743, end vertex 150246, distance 101
start vertex 26333, end vertex 36397, distance 101
start vertex 26333, end vertex 150246, distance 101
start vertex 100201, end vertex 139117, distance 102
start vertex 100201, end vertex 92762, distance 102
start vertex 41354, end vertex 36397, distance 102
start vertex 41354, end vertex 150246, distance 102
start vertex 100201, end vertex 36397, distance 103
start vertex 100201, end vertex 150246, distance 103
```

```
Time costs with 30 threads: 6916.204690
```

### Performance analysis

The whole process is expected to be a **O((V+E)Vlog(V))** process:

1. Each dijkstra function is **O((V+E)log(V))** because it contains V __dequeues__ and E __updates__. Each dequeue contains a log(V) process that perculate the root down (after one dequeue of the root, a leaf is moved to the root, and it should be soon moved down to an appropriate position). By "update" I mean updating the distance of each min heap node with data stored in each edges of the graph, so there are E times. And each update contains moving updated notes to the right position (log(V)).

2. Since the dijkstra function has to be applied with each vertex as the starting point, it is executed for V times.

The large graph contains 265214 vertices + 420045 edges, and the small graph contains 6301 vertices + 20777 edges. Based on the above analysis, the time costs of the large graph should be roughly 1500 times that of the small graph. However, in practive, the time costs of the large graph is about 3900 times that of the small graph (both with 30 threads). 
My guess is that it's partly because the time costs I calculated also contained the time for updating the final result list with the shortest paths calculated with each of the starting vertices. However, this should not have made much difference, since it's supposed to be a O(V) process, with each of the list only containing V nodes. 
Another possiblity with higher likelihood is that since 2 hours is a very long period, more noises are affecting the process (for example, screen lock of the computer).
Also, 30 threads may not be an optimal choice. I suppose that calling the threads and allocating tasks among them inside OpenMP implementation also contains time costs.

## How to compile

### STEP 1: Set parameters

The only parameter that needs to be set beforehead is the file name. Type it in the **line 10** of `test_dij.c`. The default is "graph1.txt".

### STEP2: How to compile

```
$make
$./test_dij 10 (the second parameter is the thread number. Can be any reasonable positive number. Default is 30)
```

## Disccussions

As is mentioned above, the main issue of my code is that the large graph costs me more time than in theory. Another issue could be that I attempted to integrate all the major calculations in one function (`result_paths`), which makes it hard to debug.