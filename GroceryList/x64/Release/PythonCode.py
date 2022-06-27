import re
import string
import os

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v   

def readData(userString = ""):
    # create empty list and dictionary
    wordDict = {}
    wordList = []
    # open the file to read
    f = open("Input.txt" , "r")
    # loop through the file and collect all the lines
    for i in f:
        i = i.split()
        for j in i:
            wordList.append(j) # append the extracted words to a list
    # close the file
    f.close()
    # populate the the dictionary with items as key and frequency as values.
    for words in wordList:
        wordDict[words] = wordList.count(words)
    # check if method received an argument
    if (len(userString) > 0):
        # convert userString to uppercase
        userString = userString[0].upper() + userString[1:]
        # check if item exist in the list
        if userString not in wordList:
            print(f"{userString} does not exist in the list.")
            return 0
        else:
            # print the item frequency
            print(f"{userString} has {wordDict[userString]} entries")     
            return 0
    # if no argument was passed, print the list of items with frequncies.
    else:
        for k , v in wordDict.items():
            print(f"{k} - {v}")        
    return wordDict   

def plotData():
    # create empty list and dictionary
    wordDict = {}
    wordList = []
    # open the file to read
    f = open("Input.txt" , "r")
    # loop through the file and collect all the lines
    for i in f:
        i = i.split()
        for j in i:
            wordList.append(j) # append the extracted words to a list
    # populate the the dictionary with items as key and frequency as values.
    for words in wordList:
        wordDict[words] = wordList.count(words)
    # close the file
    f.close()
    # sort the dictionary by the value from smallest to largest
    sortDict = {k: v for k, v in sorted(wordDict.items(), key=lambda v:v[1])}
    # open the file and write the data to the file
    with open("frequency.dat", 'w') as f: 
        for key, value in sortDict.items(): 
            f.write('%s %s\n' % (key, value))
    return 0