"""
Spencer Cassetta
LIS.py
functions using sequences
"""

def verify_subseq(seq, subseq):
    """
    :param seq: a sequence given to the function
    :param subseq: a subsequence given to the function
    :return: whether or not subseq is a subsequence of seq
    """
    i = 0 #i set to 0 at start. Nested loop starts where it left off the previous time
    #goes through all elements in the subsequence
    for x in subseq:
        found = False #bool to tell if it was found by upcoming loop
        while i < len(seq): #run until i goes out of bounds
            if seq[i] == x:
                #item found, break
                found = True
                break
            #otherwise increment i
            i += 1
        if not found:
            #if it wasnt found then its not a subsequence, return false
            return False
    #otherwise return true
    return True

def verify_increasing(seq):
    """
    :param seq: a sequence given to the function
    :return: whether or not it is an increasing subsequence
    """
    #pretty self explanatory, ensures seq[i]>seq[i-1] and is therefore increasing
    for i in range(1, len(seq)):
        if seq[i] <= seq[i - 1]:
            return False
    return True


def find_lis(seq):
    """
    :param seq: a sequence given to the function
    :return: result: a list representing longest possible increasing sequence within seq
    """
    smalls = list() #list that holds indexes of smallest values that could be used
    prev = list() #list to store previous indexes of elements of the subsequence

    #fill an the empty lists with size seq
    for i in range(0, len(seq)):
        smalls.append(None)
        prev.append(None)

    #we know theres a subsequence of atleast 1
    longst = 1
    smalls.insert(0, 0)


    index = 1
    #loop over the sequence starting at the second element
    while index < len(seq):
        #binary search for lowest possible element between 0 and longest

        low = 0
        high = longst
        if seq[smalls[high - 1]] >= seq[index]:
            #if element near upperbounds is bigger than the element of sequence we are on, then search the lowerbounds

            #now we need to find the best element in the lower region as well as set parameters for future search
            while high - low > 1:
                #while low is atleast 1 less than high,


                middle = (high + low) // 2
                #check if the middle value in the small list is bigger or equal to the element we are on
                if seq[smalls[middle - 1]] >= seq[index]:
                    #if so, lower the high end to the middle, its in the lowerbounds of the small list
                    high = middle
                else:
                    #otherwise its in the upperbounds, set the middle to the new low
                    low = middle
            temp = low
        else:
            #otherwise it is the highest possible element
            temp = high
        #add the next small item in the list to the sequence
        prev[index] = smalls[temp - 1]

        #redefine the longst
        if temp == longst: #if item was found in upperbounds then increment longest and update the small list
            longst += 1
            smalls[temp] = index
        elif seq[index] < seq[smalls[temp]]: #if binary search was performed and item found is bigger than element we are on save it to the smalls list for later
            smalls[temp] = index
        #increment the index
        index += 1

    #result is just the elements referenced by previous list
    i = smalls[longst - 1]
    result = list()
    j = 0
    while j < longst:
        #adds the sequence to result in reverse order
        result.append(seq[i])
        i = prev[i]
        j += 1
    #makes the result in the right order
    result.reverse()
    return result
    
