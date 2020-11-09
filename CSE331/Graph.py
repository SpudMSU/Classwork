"""
Graph.py
CSE 331
Spencer Cassetta
"""
import math
class Vertice:
    """
    Class to store vertices in
    """
    def __init__(self, n):
        """
        initializer
        :param n: order of graph
        """
        self.edges = [None] * n
        self.size = 0
        self.neighbors = set()

class Fifo:
    """
    class for a FIFO queue found online
    source:https://www.oreilly.com/library/view/python-cookbook/0596001673/ch17s15.html
    """
    def __init__(self):
        """
        initializer for FIFO
        """
        self.first = None
        self.last = None
        self.size = 0 #added to keep track of size

    def append(self, data):
        """
        insertion method for FIFO
        """
        self.size += 1
        node = [data, None]  # [payload, 'pointer'] "pair"
        if self.first is None:
            self.first = node
        else:
            self.last[1] = node
        self.last = node

    def pop(self):
        """
        pop method for FIFO
        returns first element added to the queue
        and removes it
        """
        if self.first is None:
            raise IndexError
        self.size -= 1
        node = self.first
        self.first = node[1]
        return node[0]

class Graph:
    """
    Class for a graph
    """
    def __init__(self, n):
        """
        Constructor
        :param n: Number of vertices
        """
        self.order = n
        self.size = 0
        self.verts = [None] * n
        self.adj = [[0] * n for i in range(n)] #initializes a empty 2d adjacency matrix
        for i in range(0, n):
            self.verts[i] = Vertice(n)

    def insert_edge(self, u, v, w):
        """
        connects given vertexes with given weight
        :param u: first vertex
        :param v: second vertex
        :param w: weight of edge between vertexes
        """
        if self.verts[u].edges[v] is None:
            #if vertexes are not already connected
            #adjust the size variables accordingly
            self.verts[u].size += 1
            self.verts[v].size += 1
            self.size += 1
        #add the verts to eachothers connections and key lists
        self.verts[v].edges[u] = w
        self.verts[u].edges[v] = w
        self.verts[v].neighbors.add(u)
        self.verts[u].neighbors.add(v)
        #then add them to the adjacency matrix
        self.adj[u][v] = w
        self.adj[v][u] = w

    def degree(self, v):
        """
        function to return number of vertices
        :return: number of vertices, aka the degree of the graph
        """
        return self.verts[v].size

    def are_connected(self, u, v):
        """
        function to tell if 2 vertices are connected
        :return: True/False depending if the vertices are connected
        """
        if self.verts[u].edges[v] is not None:
            #if its on ones connection list then they are connected
            return True
        #otherwise they are not
        return False

    def is_path_valid(self, path):
        """
        function to tell if a given path is valid
        :param path: list of vertices in order of path
        :return: True/False depending if the vertices in path are connected
        """
        i = 0
        while i <= len(path)-2: #itterates through all the vertices in the path
            if self.verts[path[i]].edges[path[i+1]] is None:
                #if the vertice next is in not in its connections list path is invalid
                return False
            i += 1
        #if all connections are valid, path is valid
        return True

    def edge_weight(self, u, v):
        """
        function that gives weight of edge between vertices
        :param u: a given vertice
        :param v: other given vertice
        :return: weight of the edge the 2 vertices share
        """
        if self.verts[u].edges[v] is not None:
            #if they are connected return the stored value
            return self.verts[u].edges[v]
        #if they arent connected weight is infinity
        return math.inf

    def path_weight(self, path):
        """
        function to calculate weight of path
        :param path: list of vertices in order of path taken
        :return: total weight of the given path
        """
        if not self.is_path_valid(path):
            #if path is invalid path weight is infinity
            return math.inf
        weight = 0
        i = 0
        while i <= len(path) - 2:
            #if it is valid sum all the edges in the path
            weight += self.verts[path[i]].edges[path[i+1]]
            i += 1
        #then return the sum
        return weight

    def does_path_exist(self, u, v):
        """
        uses a BFS to tell if a path exists in the graph
        :param u: starting vertice
        :param v: ending vertice
        :return: True/False depending on if the path exists
        """
        seen = set() #initilize a set of visited elements
        i = 0
        q = Fifo() #initilize a fifo queue
        q.append(u) #qdd u to the queue
        seen.add(u) #aswell as the visited list
        #check if vertices are in the graph
        if v > len(self.verts) - 1 or self.verts[v] is None:
            raise IndexError
        elif u > len(self.verts) - 1 or self.verts[u] is None:
            raise IndexError
        #checks if the two vertices are the same
        if v == u:
            #if so, there is a path for obvious reasons
            return True
        while q.size > 0:
            #while there are items in the queue set the current element to be the next item in the queue and remove it from the queue
            u = q.pop()
            if v == u:
                #if this is the vertex we are looking for return true because there is a path
                return True
            for i in self.verts[u].neighbors:
                #otherwise go through all the neighbors of the vertice and add them to the queue if they have not been already
                if i not in seen:
                    q.append(i)
                    #add it to the queue and seen set
                    seen.add(i)
        #if end vertice was never found then there is no path
        return False


    def find_min_weight_path(self, u, v):
        """
        function that uses Dijesktras algorithm to find minimum path to one vertice from another
        inspired by Pathfinding d2l lecture
        :param u: starting vertice
        :param v: ending vertice
        :return: lowest possible weight path between u and v
        """
        #check if vertices are in the graph
        if v > len(self.verts) - 1 or self.verts[v] is None:
            raise IndexError
        elif u > len(self.verts) - 1 or self.verts[u] is None:
            raise IndexError
        #check if a path exists
        if not self.does_path_exist(u, v):
            raise ValueError
        #check if first vertice is the same as the end point
        if v == u:
            #if so, itself is the path
            return [u]
        #distance values for all items in graph, they are infinity until recaclulated by algorithm
        dist = {vert:math.inf for vert in range(0, self.order)}
        #initilize a list of all unvisited vertices
        unseen = set(i for i in range(0, self.order))
        #initilize a list representing the path taken
        path = [u]
        while u != v:
            #while the current element is not the endpoint run algorithm
            #find the minimum neighbor that hasnt been visited yet
            smallest = math.inf
            ind = None
            for x in self.verts[u].neighbors:
                if x == v:
                    #if endpoint is the neighbor, go to it to finish the path
                    smallest = self.verts[u].edges[x]
                    ind = x
                    break
                if self.verts[u].edges[x] < smallest and x in unseen:
                    #if x is the cheapest neighbor then store it
                    smallest = self.verts[u].edges[x]
                    ind = x
            u = ind #set u equal to the cheapest neighbor
            unseen.remove(u) #remove it from the unseen list
            path.append(u) #add it to the path we have taken
            if u == v:
                #if we are on the endpoint, return the path because we are finished
                return path
            for i in self.verts[u].neighbors:
                #otherwise go through all the neighbors and recalculate their distance values
                if dist[u] + self.edge_weight(u, i) < dist[i]:
                    dist[i] = dist[u] +self.edge_weight(u, i)
        #loop ended meaning we have reached endpoint, return the path
        return path

    def is_bipartite(self):
        """
        function to tell if graph is a bipartite
        :return: True/False depending on if it is a bipartite
        """
        #initializes a list of colors for every element in the graph
        colors = [-1] * self.order
        #initialize a queue
        queue = []
        #itterate through adjacency matrix to find a random edge that exists
        for x in range(0, self.order):
            for y in range(0, self.order):
                if self.adj[x][y]:
                    #if loop exists, use it as the source
                    source = x
                    break
            if source == x:
                #if source was set to x, we are done
                break
        #assign a "color" to the source
        colors[source] = 1
        #add it to the queue
        queue.append(source)
        while queue:
            #while the queue is not empty,
            #get an arbiterary element from it
            x = queue.pop()
            if self.adj[x][x] == 1:
                #if something points to itself, it is not a bipartite
                return False
            for y in range(self.order):
                #for every edge connected to the vertice pulled from the queue,
                if self.adj[x][y] and colors[y]:
                    #if an edge exists here and is not colored,
                    #add it too the queue
                    queue.append(y)
                    #set its color to the opposite of x's color since it is adjacent
                    colors[y] = 1 - colors[x]
                elif self.adj[x][y] and colors[y] == colors[x]:
                    #if 2 vertices that share an edge of same color exist, it is not bipartite
                    return False
        #reason to not be bipartite wasnt found, must be bipartite
        return True
