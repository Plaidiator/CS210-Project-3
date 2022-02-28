import re
import string

def allFrequency(v):
    # Open txt file
    grocFile = open("grocceryItems.txt", "r")
    grocDict = dict()  # Initialize dictionary

    for item in grocFile:
        item = item.strip() # Remove \n from all items
        item = item.lower() # Make all items lowercase

        if item in grocDict:
            grocDict[item] += 1 # Add to item already in dictionary
        else:
            grocDict[item] = 1  # Add item to dictionary
    
    # Print dictionary 
    for key in list (grocDict.keys()):
        print(key.capitalize(), ":", grocDict[key])

    grocFile.close()  # Close file
    return v

def itemFrequency(v):
    # Open txt file
    grocFile = open("grocceryItems.txt", "r")
    count = 0  # Initialize count variable

    # Similar function to above
    for item in grocFile:
        item = item.strip()
        item = item.lower()

        # If item name is the same as user input, increment count
        if item == v.lower():
            count += 1

    # Close file
    grocFile.close()
    
    return count

def itemGraph(v):
    # open file
    grocFile = open("grocceryItems.txt", "r")
    # create and write to frequency.dat file
    graph = open("frequency.dat", "w")
    grocDict = dict()

    # This for loop is identical to the loop in allFrequency function
    for item in grocFile:
        item = item.strip()
        item = item.lower()

        if item in grocDict:
            grocDict[item] += 1
        else:
            grocDict[item] = 1
    
    # Write item name and count like "item X"
    for key in list (grocDict.keys()):
        graph.write(str(key.capitalize()) + " " + str(grocDict[key]) + "\n")

    # Close files
    grocFile.close()
    graph.close()

    return v




