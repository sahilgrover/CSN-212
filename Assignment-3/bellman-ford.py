from collections import defaultdict
import datetime as dt 
f1=open('./output.txt', 'w+')
class Graph:
 
    def __init__(self,vertices):
        self.V= vertices 
        self.graph = [] 

    #function to add edge from u to v with weight w
    def addEdge(self,u,v,w):
        self.graph.append([u, v, w])
         
    # function to print the solution
    def printArr(self, dist):
        f1.write("Vertex    Distance from Source\n")
        for i in range(self.V):
            f1.write(str(i)+"             "+str(dist[i])+ '\n')
     
    # The function that uses Bellman-Ford algorithm. 
    # The function detects negative weight cycle.
    def BellmanFord(self, src):
 
        # Step 1: Initialize distances from src to all other vertices as INFINITE
        dist = [float("Inf")] * self.V
        dist[src] = 0
 
 
        # Step 2: Relax all edges |V| - 1 times. A simple shortest path 
        # from src to any other vertex can have at-most |V| - 1 edges
        for i in range(self.V - 1):
            # Update dist value and parent index of the adjacent vertices
            for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                        dist[v] = dist[u] + w
 
        # Step 3: check for negative-weight cycles.  
        # If we get a shorter path, then there is a cycle.
        for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                        f1.write( "Graph contains negative weight cycle\n")
                        return
                         
        # print all distance
        self.printArr(dist)

with open("./input.txt") as f:
    lines = f.readlines()
t = (int)(lines[0].strip())
i = 1
for x in range(t):
    n1=dt.datetime.now()
    V,E = lines[i].strip().split()
    i += 1
    V = (int)(V)
    E =  (int)(E)
    g = Graph(V)
    src = (int)(lines[i].strip())
    i += 1
    for c in range(E):
        u,v,w = lines[i].strip().split()
        i += 1
        u,v,w = (int)(u),(int)(v),(int)(w)
        g.addEdge(u,v,w)
    g.BellmanFord(src)
    n2=dt.datetime.now()
    f1.write( "Time taken : " + str((n2-n1).microseconds) + " microseconds!!\n")