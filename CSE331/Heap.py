"""
Heap.py
creates a priority queue using a heap
Spencer Cassetta - A54379022
James Daly
Cse 320
"""

import math
class Heap:
    """
    A heap-based priority queue
    Items in the queue are ordered according to a comparison function
    """

    def __init__(self, comp):
        """
        Constructor
        :param comp: A comparison function determining the priority of the included elements
        """
        self.comp = comp
        self.arr = list()
        #to keep track of length
        self.length = 0
        # Added Members

    def __len__(self):
        return len(self.arr)

    def peek(self):
        """
        Finds the item of highest priority
        :return: The item item of highest priority
        """
        if self.length == 0:
            #if no elements raise error
            raise IndexError
        else:
            #otherwise return root node
            return self.arr[0]

    def insert(self, item):
        """
    	Adds the item to the heap
        :param item: An item to insert
        """
        i = len(self.arr)
        #add a null value to list
        self.arr.append(None)
        #if heap has elements in it
        if i > 0:
            while i > 0 and self.comp(item, self.arr[parent(i)]):
                #shift parents down to make room for element if element has higher priority
                self.arr[i] = self.arr[parent(i)]
                i = parent(i)
        #insert item in proper place
        self.arr[i] = item
        #increase length
        self.length += 1

    def extract(self):
        """
        Removes the item of highest priority
        :return: the item of highest priority
        """
        if self.length == 0:
            #if empty, raise error
            raise IndexError("Heap Underflow")
        #get value with highest priority
        root = self.arr[0]
        #set root to item with lowest priority
        self.arr[0] = self.arr[-1]
        #take out last item in list
        self.arr.pop()
        #decrease length
        self.length -= 1
        #reorganize the heap
        self.arr = heapify(self.comp, self.arr, 0)
        #return item with highest priority
        return root

    def extend(self, seq):
        """
    	Adds all elements from the given sequence to the heap
    	:param seq: An iterable sequence
    	"""
    	#insert all items in sequence into the heap
        for item in seq:
            self.insert(item)
            self.length += 1

    def replace(self, item):
        """
        Adds the item the to the heap and returns the new highest-priority item
    	Faster than insert followed by extract.
    	:param item: An item to insert
    	:return: The item of highest priority
    	"""
    	#insert items then extract
        self.insert(item)
        return self.extract()
        #meets runtime complexity because it meets specific cases in insert and extract

    def clear(self):
        """
    	Removes all items from the heap
        """
        #clear array
        self.arr.clear()
        self.length = 0

    def __iter__(self):
        yield from self.arr

    # Supplied methods

    def __bool__(self):
        """
        Checks if this heap contains items
        :return: True if the heap is non-empty
        """
        return not self.is_empty()

    def is_empty(self):
        """
        Checks if this heap is empty
        :return: True if the heap is empty
        """
        return (len(self.arr) == 0)

    def __repr__(self):
        """
        A string representation of this heap
        :return:
        """
        return 'Heap([{0}])'.format(','.join(str(item) for item in self))

    # Added methods


# Required Non-heap member function
def heapify(comp, arr, i):
    """
    helper funciton to make reorganize the heap after removing item at 0
    :param comp: A comparison function determining the priority of the included elements
    :param arr: part of a former heap
    :param i: index to element to reheap
    """
    #get the index's of the left and right children
    l = left(i)
    r = right(i)
    #assume root has largest priority
    prio = i
    #if left child has larger priority then set prio equal to it
    if l < len(arr) and comp(arr[l], arr[prio]):
        prio = l
    #if right child has larger priority, capture that value
    if r < len(arr) and comp(arr[r], arr[prio]):
        prio = r
    #if a element has higher priority than root,
    if prio != i:
        #swap elements and run function again
        arr[i], arr[prio] = arr[prio], arr[i]
        heapify(comp, arr, prio)
    return arr

def parent(index):
    """
    a helper function that determines the parent of a given element
    :param index: index to element
    :return: index to parent of element
    """
    return math.ceil(index/2) - 1
def left(index):
    """
    helper function to give left child of element
    :param index: index to element
    :return: index to left child
    """
    return index * 2 + 1
def right(index):
    """
    helper function to give right child of element
    :param index: index to element
    :return: index to right child
    """
    return index * 2 + 2
def find_median(seq):
    """
    Finds the median (middle) item of the given sequence.
    Ties are broken arbitrarily.
    :param seq: an iterable sequence
    :return: the median element
    """
    if not seq:
        raise IndexError
    #create 2 heaps, one that puts larger values with highest priority and one that puts smallest values with highest priority
    min_heap = Heap(lambda a, b: a < b)
    max_heap = Heap(lambda a, b: a > b)
    for ele in seq: #for every item in the sequence
        #if heaps are empty, set median to 0
        if min_heap.length == 0 and max_heap.length == 0:
            median = 0
        #otherwise determine length of each to determine where the median is
        elif min_heap.length < max_heap.length:
            median = max_heap.peek()
        elif min_heap.length > max_heap.length:
            median = min_heap.peek()
        #if both have same length, use average as median
        else:
            median = (min_heap.peek() + max_heap.peek())//2
        #if element is larger than median it belongs with the larger half of values
        if ele > median:
            min_heap.insert(ele)
        #otherwise it belongs in lower half of values
        else:
            max_heap.insert(ele)
        #if one heap is greater than the other by 2, extract value from larger heap and put it in the other
        if min_heap.length - 1 > max_heap.length:
            max_heap.insert(min_heap.extract())
        elif min_heap.length + 1 < max_heap.length:
            min_heap.insert(max_heap.extract())
    #after loop, find the final median
    if min_heap.length > max_heap.length:
        median = min_heap.peek()
    else:
        median = max_heap.peek()
    #and return it
    return median
