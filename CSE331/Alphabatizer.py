"""
Project 1: Alphabetizer
Spencer Cassetta
cassett8 - A54379022
CSE 260 - James Daly
"""
class Person:
    """
    Class : Person
    has a first name, last name, and email.
    built in functionality for <,>,= operators
    """
    def __init__(self, first, last, email):
        self.first = first
        self.last = last
        self.email = email
    def __str__(self):
        return '{0} {1} <{2}>'.format(self.first, self.last, self.email)
    def __repr__(self):
        return '({0}, {1}, {2})'.format(self.first, self.last, self.email)
    def __eq__(self, other):
        return self.first == other.first and self.last == other.last and self.email == other.email

def order_first_name(a, b):
    """
    Orders two people by their first names
    :param a: a Person
    :param b: a Person
    :return: True if a comes before b alphabetically and False otherwise
    """
    # if a comes before b, then true
    if a.first < b.first:
        return True
    # if equal, compare with last name
    if a.first == b.first:
        return a.last < b.last
    # a does not come before b
    return False
def order_last_name(a, b):
    """
    Orders two people by their last names
    :param a: a Person
    :param b: a Person
    :return: True if a comes before b alphabetically and False otherwise
    """
    if a.last < b.last:
        return True
    # if equal, compare with first name
    if a.last == b.last:
        return a.first < b.first
    # a does not come before b
    return False

def is_alphabetized(roster, ordering):
    """
    Checks whether the roster of names is alphabetized in the given order
    :param roster: a list of people
    :param ordering: a function comparing two elements
    :return: True if the roster is alphabetized and False otherwise
    """
    # loop through roster
    for i in range(len(roster)-1):
        #if elements are equal, then continue
        if roster[i] == roster[i+1]:
            continue
        # if not in correct order,
        elif not ordering(roster[i], roster[i+1]):
            # then it is not sorted
            return False
    #made it all the way through list,
    # must be sorted
    return True
def merge(l, r, ordering):
    """
    takes 2 lists and merges them into new list in sorted order
    :param l: a list of elements
    :param r: a list of elements
    :param ordering: a function comparing two elements
    :return: a sorted list containing both elements of r and l
    :return: the number of comparisons made
    inspired by psuedocode
    """
    #declare variables, max length of lists,
    # and new list to store elements
    i, j, comp = 0, 0, 0
    n, m = len(l), len(r)
    new = []
    #loop through the lists as long as inbound
    while i < n and j < m:
        #else-if determines which element
        # is smaller and puts it in the new list first
        if ordering(l[i], r[j]):
            new.append(l[i])
            i += 1
        else:
            new.append(r[j])
            j += 1
        # a comparison was made
        comp += 1
    #finds list that didnt get iterated all the way
    # through and ammends the rest of it to the new list
    while j < len(r):
        new.append(r[j])
        j += 1
    while i < len(l):
        new.append(l[i])
        i += 1
    #return new list along with
    #number of comparisons made
    return (new, comp)


def mergesort(arr, ordering):
    """
        uses recursion to break array into smallest components
        and merge all of them in sorted order using the merge function
        :param arr: a list of elements
        :param ordering: a function comparing two elements
        :return: a sorted version of roster
        :return: the number of comparisons made
        inspired by psuedocode given in lecture
        """
    # if only 1 element,
    # then we are done breaking apart
    if len(arr) < 2:
        return (arr, 0)
    #breaks down list into smaller components
    #by breaking it into halves at a time
    #stores halves into l and r
    #stores comparisons made in comp1 and comp2
    l, comp1 = mergesort(arr[(len(arr) // 2):], ordering)
    r, comp2 = mergesort(arr[:(len(arr) // 2)], ordering)
    #sorts and merges all together using merge
    #stores new list in result
    #stores comparisons made by merge in comp
    result, comp = merge(l, r, ordering)
    #adds all comparisons together
    comp = comp + comp1 + comp2
    #returns the sorted list along with comparisons made
    return (result, comp)
def alphabetize(roster, ordering):
    """
    Alphabetizes the roster according to the given ordering
    :param roster: a list of people
    :param ordering: a function comparing two elements
    :return: a sorted version of roster
    :return: the number of comparisons made
    """
    # check if already sorted
    if is_alphabetized(roster, ordering):
        #if so, return right away
        return (list(roster), 0)
    # if not then do a mergesort,
    roster, comp = mergesort(roster, ordering)
    # return sorted list and # of comparisons
    return (list(roster), comp)
