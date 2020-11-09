"""
Deque.py
creates a double-ended queue that consists of nodes
Spencer Cassetta - A54379022
James Daly
Cse 320
"""
class Node:
    """
    An element of a queue
    attribute: data - stores data passed
    attribute: next - points to next element in queue
    attribute: prev - last element in the queue
    """
    def __init__(self, data):
        """
        Initializes an element
        """
        self.data = data
        self.next = None
        self.prev = None
class Deque:
    """
    A double-ended queue
    """

    def __init__(self):
        """
        Initializes an empty Deque
        """
        nullNode = Node(None)
        #sets attributes equal to a dumby node
        self.head = nullNode
        self.tail = nullNode
        self.size = 0

    def __len__(self):
        """
        Computes the number of elements in the Deque
        :return: The size of the Deque
        """
        return self.size

    def peek_front(self):
        """
        Looks at, but does not remove, the first element
        :return: The first element
        """
        if self.size == 0:#if empty, return IndexError
            raise IndexError('queue went out of range')
        return self.head.data

    def peek_back(self):
        """
        Looks at, but does not remove, the last element
        :return: The last element
        """
        if self.size == 0:#if empty, return IndexError
            raise IndexError('queue went out of range')
        return self.tail.data

    def push_front(self, e):
        """
        Inserts an element at the front of the Deque
        :param e: An element to insert
        """
        #puts e into a node
        e = Node(e)
        if self.size > 0: #if not empty
        #we need to reassign the current
        #head and its attributes
            self.head.prev = e
            e.next = self.head
        else: #if empty,
        #e is tail aswell
            self.tail = e
        #e is put at head of queue
        self.head = e
        #increment size b/c we added a node to queue
        self.size += 1


    def push_back(self, e):
        """
        Inserts an element at the back of the Deque
        :param e: An element to insert
        """
        #puts e into a node
        e = Node(e)
        if self.size > 0: #if not empty
        #we need to reassign the current
        #tail and its attributes
            self.tail.next = e
            e.prev = self.tail
        else:#if empty,
        #e is head aswell
            self.head = e
        #e is put at tail of queue
        self.tail = e
        #increment size b/c we added a node to queue
        self.size += 1
    def pop_front(self):
        """
        Removes and returns the first element
        :return: The (former) first element
        """
        if self.size == 0: #if empty raise IndexError
            raise IndexError('queue went out of range')
        #otherwise take the node at the head
        front = self.head
        #reassign the head to next node
        self.head = self.head.next
        #decrease size because we removed current head
        self.size -= 1
        #return the data we just removed
        return front.data

    def pop_back(self):
        """
        Removes and returns the last element
        :return: The (former) last element
        """
        if self.size == 0: #if empty, raise IndexError
            raise IndexError('queue went out of range')
        #otherwise take the node at the tail
        back = self.tail
        #reassign the tail to the 2nd to last node
        self.tail = self.tail.prev
        #decrease size because we removed the current tail
        self.size -= 1
        #return the data we just removed
        return back.data

    def clear(self):
        """
        Removes all elements from the Deque
        """
        #set attributes to default values,
        #nodes are instantly lost
        self.size = 0
        self.head = None
        self.tail = None

    def __iter__(self):
        """
        Iterates over this Deque from front to back
        :return: An iterator
        """
        #put begining into n (n for node)
        #so we can read queue without modifying
        #the head or the tail
        n = self.head
        while n is not None:
            #yeild current nodes data
            yield n.data
            #move to next node
            n = n.next
    def extend(self, other):
        """
        Takes a Deque object and adds each of its elements to the back of self
        :param other: A Deque object
        """
        if self.size == 0:
            #if empty, dont run function
            pass
        for n in other:#for every node in other
            #if node is nothing we are done
            if n is None:
                break
            #otherwise add it to queue
            self.push_back(n)
    def drop_between(self, start, end):
        """
        Deletes elements from the Deque that within the range [start, end)
        :param start: indicates the first position of the range
        :param end: indicates the last position of the range(does not drop this element)
        """
        if start < 0 or start > end or end > self.size or self.size == 0:
            #if any of the above then function parameters are
            #not valid and raise an IndexError
            raise IndexError("function went out of bounds")
        #assign variable to head
        #because we want to just edit the nodes and not the
        #head or tail of function
        n = self.head
        index = 0
        while index < start and n is not None:
            #count up until we reach start
            index += 1
            n = n.next
        while index < end and n is not None:
            if n.prev is None:#nothing behind us,
            #must be only 1 node left that is within
            #end so clear the list and break
                self.clear()
                break
            #otherwise reassign node attributes to not include
            #current node in line
            n.prev.next = n.next
            n.next.prev = n.prev
            #decrease size because we removed a node
            self.size -= 1
            #increment the index
            index += 1
            #increment the node
            n = n.next
    def count_if(self, criteria):
        """
        counts how many elements of the Deque satisfy the criteria
        :param criteria: a bool function that takes an element of the Deque
        and returns true if that element matches the criteria and false otherwise
        """
        #variable for counted elements
        count = 0
        if self.size == 0:
            #if queue is empty, return 0
            return count
        #assign n to begining of list so we can itterate
        #without modifying the head or tail of queue
        n = self.head
        while n is not None:
            #while there is an element in node,
            #if it meets criteria count the element
            if criteria(n.data):
                count += 1
            #and increment the node
            n = n.next
        #return elements that met the criteria
        return count
    # provided functions
    def is_empty(self):
        """
        Checks if the Deque is empty
        :return: True if the Deque contains no elements, False otherwise
        """
        if self.size == 0:
            #if size is 0 it is empty
            return True
        #otherwise it is not
        return False
    def __repr__(self):
        """
        A string representation of this Deque
        :return: A string
        """
        return 'Deque([{0}])'.format(','.join(str(item) for item in self))
        
