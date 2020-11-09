class HashMap:
    def __init__(self, load_factor=.5):
        # You may change the default maximum load factor
        self.max_load_factor = load_factor
        self.members = set()
        self.size = int(10)
        self.arr = [None] * self.size
        self.item_count = 0
        self.grown = 0
        # Other initialization code can go here


    def __len__(self):
        return self.item_count

    def hashfunc1(self, index, i):
        #hashing method found online
        primenums = [37, 41, 43, 53, 59, 19]
        #uses prime numbers, multiplication, and addition with a changing variable to enhance chance of
        #returning unique index's
        return ((i * (i + (hash(index) % primenums[i % 6]))) + hash(index) % (self.size//2)) % (self.size//2)

    def hashfunc2(self, index, i):
        #hashing method
        primenums = [3, 5, 11, 13, 17, 31]
        #uses prime numbers, multiplication, and addition with a changing variable to enhance chance of
        #returning unique index's
        return ((i * (i + (hash(index) % primenums[i % 6])))+ (hash(index) % self.size)%primenums[(i+1)%6]) % self.size


    def buckets(self):
        return self.size

    def load(self):
        return (self.item_count)/(self.size)

    def __contains__(self, key):
        return key in self.members

    def __getitem__(self, key):
        if key not in self.members:
            raise KeyError("Not in hashmap")
        index = self.hashfunc2(key, 0)
        i=0
        while True:
            if self.arr[index] is None:
                index = self.hashfunc1(key, i)
            elif self.arr[index][0] == key:
                return self.arr[index][1]
            index = self.hashfunc1((key), i)
            if self.arr[index] is None:
                i +=1
                index = self.hashfunc2(key, i)
            elif self.arr[index][0] == key:
                return self.arr[index][1]
            else:
                i += 1
                index = self.hashfunc2((key), i)

    def __setitem__(self, key, value):
        index = self.hashfunc2(key, 0)
        item = (key, value)
        i = 0
        while True:
            if self.arr[index] is None:
                self.members.add(key)
                self.item_count += 1
                self.arr[index] = item
                break
            if self.arr[index][0] == key:
                self.arr[index] = item
                break
            index = index = self.hashfunc1((key), i)
            if self.arr[index] is None:
                self.members.add(key)
                self.item_count += 1
                self.arr[index] = item
                break
            if self.arr[index][0] == key:
                self.arr[index] = item
                break
            else:
                i += 1
                index = self.hashfunc2((key), i)
        if self.load() > self.max_load_factor:
            self.grow()

    def grow(self, shrinking=False):
            mp = HashMap()
            mp.arr = [None] * self.size * 2
            mp.size = self.size*2
            for items in self.members:
                mp.__setitem__(items, self.__getitem__(items))
            self.size *= 2
            self.arr = mp.arr

    def __delitem__(self, key):
        if key not in self.members:
            raise KeyError("Not in hashmap")
        index = self.hashfunc2(key, 0)
        i = 0
        while True:
            if self.arr[index] is None:
                index = self.hashfunc1(key, i)
            elif self.arr[index][0] == key:
                self.arr[index] = None
                self.members.remove(key)
                self.item_count -= 1
                break
            index = self.hashfunc1((key), i)
            if self.arr[index] is None:
                i += 1
                index = self.hashfunc2(key, i)
            elif self.arr[index][0] == key:
                self.arr[index] = None
                self.members.remove(key)
                self.item_count -= 1
                break
            else:
                i += 1
                index = self.hashfunc2((key), i)
        if self.load() <= .05 and self.size > 10:
            self.shrink()

    def shrink(self):
        mp = HashMap()
        mp.size = self.size // 2
        mp.arr = [None] * (self.size // 2)
        for items in self.members:
            mp.__setitem__(items, self.__getitem__(items))
        self.size = self.size // 2
        self.arr = mp.arr

    def __iter__(self):
        for items in self.members:
            yield (items,self.__getitem__(items))

    def clear(self):
        self.arr = [None] * 10
        self.size = 10
        self.item_count = 0
        self.members = set()


    def keys(self):
        return self.members
    # supplied methods

    def __repr__(self):
        """
        A string representation of this map
        :return: A string representing this map
        """
        return '{{{0}}}'.format(','.join('{0}:{1}'.format(k, v) for k, v in self))

    def __bool__(self):
        """
        Checks if there are items in the map
        :return True if the map is non-empty
        """
        return not self.is_empty()

    def is_empty(self):
        if self.item_count == 0:
            return True
        return False

    # Helper functions can go here


# Required Function
def year_count(input_hashmap):
    """
    Function to count the number of students born in the given year
    :input: A HashMap of student name and its birth year
    :returns: A HashMap of the year and the number of students born in that year
    """
    seen = list()
    output = HashMap()
    students = input_hashmap
    for items in students.members:
        items = students[items]
        seen.append(items)
        output[items] = seen.count(items)
    return output
