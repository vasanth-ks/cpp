import collections

def numberOfDeletions(a, b):
    numDeletions = 0
    '''
        Convert the string to a dictionary containing number of occurrences of
        each character
    '''
    dictA = collections.Counter(a)
    dictB = collections.Counter(b)

    # Get the keys in the dictionary and convert it to lists to iterate over them
    listA = dictA.keys()
    listB = dictB.keys()

    for la in listA:
        if la in listB:
            if dictA[la] != dictB[la]:
                '''
                Number of times this character occuring in both the strings is 
                different. So, delete it from both the strings.
                '''
                numDeletions += abs(dictA[la] - dictB[la])
            '''
            This character is either counted for deletion or it occurs equal
            number of times in both the strings. So, delete it.
            '''
            del dictA[la]
            del dictB[la]
    '''
        These lists contain the characters that are not common to both the strings.
        Convert these characters to list and iterate over them to get the count
        their occurrences and include them for deletion.
    '''
    listA = dictA.keys()
    listB = dictB.keys()
    for la in listA:
        numDeletions += dictA[la]
    for lb in listB:
        numDeletions += dictB[lb]

    return numDeletions

a = raw_input().strip()
b = raw_input().strip()

print(numberOfDeletions(a, b))
