### Bellman - Ford Algorithm

The Bellman–Ford algorithm is an algorithm that computes _shortest paths from a single source vertex to all of the other vertices_ in a weighted digraph.

##### Input format (in input file):

First line of input file contains the number of test cases.
First line of the input of each test case contains two integers: V - number of vertices and E - number of edges.
Second line contains single integer which specify the souce vertex: src
Next E lines specifies each edge of the graph with three integers : start, end, wt.
It defines directed edge from vertex start to vertex end with a weight wt.
src start and end all lie in [0,V-1].
(input.txt)

##### Output Format :

Output contains distance of each vertex from source and in the end prints the time elapsed in each test case. 
(output.txt)

##### Test cases :

The graphs in test cases are generated randomly using a C++ random test case gebnerator (testgen.cpp).

##### Images :

The directory includes two images - Table.jpg which is a table of size of graph against the running time in microseconds; and Chart.jpg, which has a line graph between running time and size of graph (in terms of V*E).