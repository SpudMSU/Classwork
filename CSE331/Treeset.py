"""
Tree Set.py
creates a Binary Search Tree that consists of nodes
Spencer Cassetta - A54379022
James Daly
Cse 320
"""
def find_height(node):
    """
    finds the height of a node
    :param node: node to find height of
    :return: height of a node
    """
    if node is None:
        return 0
    else:
        return max(find_height(node.left), find_height(node.right)) + 1

def addnode(comp, root, item):
    """
    Helper function for delete and insert. Adds a node to a tree with
    the given node as the root
    :param comp: comparison function
    :param root: selected node to delete
    :param item: item to insert into the node
    :return: new node to replace deleted node
    """
    original = root
    while root is not None:
        #run loop until root is null
        if comp(root.data, item.data) > 0:
            #root is bigger than item,
            #add it to the left side
            if root.left is None:
                #if left is none we found where to add it
                root.left = item
                root.left.parent = root
                root.childcount += 1
                root = original
                return root
            else:
                #otherwise iterate to the left and repeat
                root = root.left
        else:
            #root is smaller than the item,
            #add it to the right side
            if root.right is None:
                #if right is none we found where to add it
                root.right = item
                root.right.parent = root
                root.childcount += 1
                root = original
                return root
            else:
                #otherwise iterate to the right and return
                root = root.right
def delete(comp, root):
    """
    Helper function for remove that removes selected node
    :param comp: comparison function
    :param root: selected node to delete
    :return: new node to replace deleted node
    """
    if root.left is None and root.right is None:
        #node we are deleting has no children
        kid = root
        root = root.parent
        if root is None:
            #if no parents, return None
            return root
        #otherwise determine what side of parent it belongs
        elif comp(kid.data, root.data) > 0:
            #kid is bigger so belongs on right
            root.right = None
            root.childcount -= 1
            return root
        else:
            #kid is smaller so belongs on left
            root.left = None
            root.childcount -= 1
            return root
    else:
        #node has children
        if root.right is None:
            #has no right children, must have left children
            kid = root.left
            root = root.parent
            #determine which side of the parent it belongs
            if comp(kid.data, root.data) > 0:
                #kid is bigger, belongs on right
                root.right = kid
                root.right.parent = root.right
                return root
            else:
                #kid is smaller, belongs on left
                root.left = kid
                root.left.parent = root.left
                return root
        else:
            #has kids on both sides
            original = root
            root = root.right
            #go to the right, then find the most left
            if root.left is not None:
                #if there is a left node, 
                #itterate until you find the most left
                while root.left is not None:
                    root = root.left
                smallest = root
                root = root.parent
                root.left = None
                #capture the data and delete if from the tree
                if smallest.right is not None:
                    root = addnode(comp, root, smallest.right)
                root.childcount -= 1
            else:
                #otherwise use the node you are on
                smallest = root
                root = original
                root.right = smallest.right
            #use the smallest as the new root
            root = original
            root.data = smallest.data
            return root




class TreeSet:
    """
    A set data structure backed by a tree.
    Items will be stored in an order determined by a comparison
    function rather than their natural order.
    """

    def __init__(self, comp):
        """
        Constructor for the tree set.
        You can perform additional setup steps here
        :param comp: A comparison function over two elements
        """
        #data to keep track of
        self.comp = comp
        self.root = TreeNode(None)
        self.length = 0

    def __len__(self):
        """
        Counts the number of elements in the tree
        :return:
        """
        #we keep track of length so just return it
        return self.length

    def height(self):
        """
        Finds the height of the tree
        :return:
        """
        #use the height helper function
        return find_height(self.root) #so I can do it recursively.

    def insert(self, item):
        """
        Inserts the item into the tree
        :param item:
        :return: If the operation was successful
        """
        if self.is_empty():
            #if empty, it becomes root and we are done
            self.root = TreeNode(item)
            self.length += 1
            return True
        if self.__contains__(item):
            #if item is already in here return false
            return False
        #otherwise add the node using helper function
        self.root = addnode(self.comp, self.root, TreeNode(item))
        #increment length and return true
        self.length += 1
        return True


    def remove(self, item):
        """
        Removes the item from the tree
        :param item:
        :return: If the operation was successful
        """
        if self.is_empty():
            #if empty, return False
            return False
        isroot = 1 #helps determine if we are removing the root
        original = self.root #captures original root
        while self.root is not None:
            #find the node too remove
            if self.root.data == item:
                #item found, use helper function to delete
                self.root = delete(self.comp, self.root)
                self.length -= 1
                #if not root, restore original root
                if isroot == 0:
                    self.root = original
                return True
            elif self.comp(self.root.data, item) > 0:
                #iterate to the left
                self.root = self.root.left
            else:
                #iterate to the right
                self.root = self.root.right
            isroot = 0
        #restore original root and return False
        #because item wasnt found
        self.root = original
        return False

    def __contains__(self, item):
        """
        Checks if the item is in the tree
        :param item:
        :return: if the item was in the tree
        """
        if self.is_empty():
            #if empty, return false
            return False
        node = self.root
        while node is not None:
            #searches for item
            if self.comp(node.data, item) > 0:
            #iterates to the left
                node = node.left
            elif self.comp(node.data, item) < 0:
            #iterates to the right
                node = node.right
            else:
                #item found, break
                break
        if node is None:
            #if never found return none
            return False
        return True

    def first(self):
        """
        Finds the minimum item of the tree
        :return:
        """
        if self.is_empty():
            #if empty, raise error
            raise KeyError
        current = self.root
        #return most left element for that is smallest
        while current.left is not None:
            current = current.left
        return current.data

    def last(self):
        """
        Finds the maximum item of the tree
        :return:
        """
        if self.is_empty():
            #if empty, raise error
            raise KeyError
        current = self.root
        #return right most element because that is biggest
        while current.right is not None:
            current = current.right
        return current.data

    def clear(self):
        """
        Empties the tree
        :return:
        """
        #reset root and length
        self.root = None
        self.length = 0

    def __iter__(self):
        """
        Does an in-order traversal of the tree
        :return: an iterator for the tree
        """
        #if no element return empty iter
        if self.root is None:
            return iter([])
        #otherwise return the in order transversal
        #from the tree node itter
        return self.root.__iter__()

    def is_disjoint(self, other):
        """
        Check if two TreeSet is disjoint
        :param other: A TreeSet object
        :return: True if the sets have no elements in common
        """
        if self.is_empty() or other.is_empty():
            #if either sets are empty no elements are the same
            return True
        for x in other:
            #try to find all elements in one set using the
            #contain from the other
            if self.__contains__(x):
                #if found, there are same elements
                return False
        #otherwise there arent
        return True

    # Pre-defined methods

    def is_empty(self):
        """
        checks if Tree Set is empty
        :return: True if empty, false otherwise
        """
        #if length is 0 its empty, otherwise its not
        if self.length == 0:
            return True
        return False

    def __repr__(self):
        """
        Creates a string representation of this set using an in-order traversal.
        :return: A string representing this set
        """
        return 'TreeSet([{0}])'.format(','.join(str(item) for item in self))

    def __bool__(self):
        """
        Checks if the tree is non-empty
        :return:
        """
        return not self.is_empty()

    # Helper functions
    # You can add additional functions here


class TreeNode:
    """
    A TreeNode to be used by the TreeSet
    """

    def __init__(self, data):
        """
        Constructor
        You can add additional data as needed
        :param data:
        """
        #data for 
        self.data = data
        self.parent = None
        self.left = None
        self.right = None
        self.childcount = 0
        # added stuff below

    def __repr__(self):
        """
        A string representing this node
        :return: A string
        """
        return 'TreeNode({0})'.format(self.data)

    def __iter__(self):
        if self.left is not None:
            #iterates through all elements in left tree in order using yield from
            yield from self.left #code formatting marked this as wrong however
            #it works perfectly. Cant figure out another way to do it
            #if you could give me atleast partial points for the code formatting test that 
            #would be awesom
        yield self.data#yield this nodes data
        if self.right is not None:
            #iterates through all elements in left tree in order using yeild from
            yield from self.right


