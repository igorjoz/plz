inputFile = open("teksty.txt", "r")
outputFile = open("anagramy.txt", "w")


def sumOfAsciiCode(string):
    hashSum = 0
    for letter in string:
        hashSum += ord(letter)
    # print(string, hashSum)
    return hashSum


def checkIfHashesAndLettersMatch(substringHash, patternHash, substring, sortedPattern, failedMatchesCounter, substractPatternLength):
    if substringHash == patternHash:
        sortedSubstring = sorted(substring)
        print(substring, sortedSubstring, sortedPattern)
        if sortedSubstring == sortedPattern:
            if substractPatternLength:
                anagramIndexes.append(i - patternLength + 1)
                print("APPENDED")
            else:
                anagramIndexes.append(i)
        else:
            failedMatchesCounter[0] += 1
            print("FAIL")


def createStringFromList(nums):
    string = ""
    for num in nums:
        string = string + str(num) + " "
    string = string.strip()
    return string


lines = list(map(lambda line: line.strip(), inputFile.readlines()))
# print(lines)

stringsQuantity, stringLength = list(map(lambda num: int(num), lines[0].split()))
strings = lines[2:]
print(strings)

pattern = lines[1]
sortedPattern = sorted(pattern)
patternLength = len(pattern)
print("stringsQuantity:", stringsQuantity)
print("stringLength:", stringLength)
print("pattern:", pattern)
print("sortedPattern:", sortedPattern)
print("patternLength: ", patternLength)

patternHash = 0
for letter in pattern:
    patternHash += ord(letter)
print("patternHash:", patternHash)

failedMatchesCounter = [0]
print("====================================")

# a)
rowAnagramIndexes = []
for string in strings:
    print(string)
    anagramIndexes = []
    substringHash = 0
    for i in range(patternLength):
        substringHash += ord(string[i])
    print("substringHash:", substringHash)
    checkIfHashesAndLettersMatch(substringHash, patternHash, string[0:3], sortedPattern, failedMatchesCounter, True)

    for i in range(patternLength, stringLength):
        substringHash -= ord(string[i - patternLength])
        substringHash += ord(string[i])
        # print(substringHash, patternHash)

        checkIfHashesAndLettersMatch(substringHash, patternHash, string[i - patternLength + 1: i + 1], sortedPattern, failedMatchesCounter, True)

    rowAnagramIndexes.append(anagramIndexes)
    if len(anagramIndexes) == 0:
        anagramIndexes.append(-1)
    print(anagramIndexes)
    outputFile.write(createStringFromList(anagramIndexes) + "\n")
    print("==================")
print(rowAnagramIndexes)
print("====================================")

# b)
colAnagramIndexes = []
cols = []
for i in range(stringLength):
    col = ""
    for j in range(stringsQuantity):
        col += strings[j][i]
        # substrings = []
    cols.append(col)
print(cols)

for col in cols:
    print(col)
    substrings = []
    anagramIndexes = []
    i = 0
    while i + patternLength <= len(col):
        substring = col[i:i + patternLength]
        substrings.append(substring)

        substringHash = sumOfAsciiCode(substring)
        checkIfHashesAndLettersMatch(substringHash, patternHash, substring, sortedPattern, failedMatchesCounter, False)
        i += 1
    print(substrings)

    if len(anagramIndexes) == 0:
        anagramIndexes.append(-1)
    colAnagramIndexes.append(anagramIndexes)
    print(anagramIndexes)
    outputFile.write(createStringFromList(anagramIndexes) + "\n")
    print("=========")

# c)
firstDiagonalAnagramsIndexes = []
secondDiagonalAnagramsIndexes = []

if stringsQuantity != stringLength:
    firstDiagonalAnagramsIndexes.append(-1)
    secondDiagonalAnagramsIndexes.append(-1)
else:
    firstDiagonal = ""
    secondDiagonal = ""
    for i in range(stringLength):
        firstDiagonal = firstDiagonal + strings[i][i]
        secondDiagonal = secondDiagonal + strings[i][stringLength - i - 1]
        print(strings[i][i], strings[i][stringLength - i - 1])
    print("DIAGONALS: ", firstDiagonal, secondDiagonal)

    # ======================

    # first diagonal
    substrings = []
    anagramIndexes = []
    i = 0
    while i + patternLength <= len(firstDiagonal):
        substring = firstDiagonal[i:i + patternLength]
        substrings.append(substring)

        substringHash = sumOfAsciiCode(substring)
        checkIfHashesAndLettersMatch(substringHash, patternHash, substring, sortedPattern, failedMatchesCounter, False)
        i += 1
    if len(anagramIndexes) == 0:
        anagramIndexes.append(-1)
    print(substrings)
    print(anagramIndexes)
    firstDiagonalAnagramsIndexes = anagramIndexes

    # second diagonal
    substrings = []
    anagramIndexes = []
    i = 0
    while i + patternLength <= len(secondDiagonal):
        substring = secondDiagonal[i:i + patternLength]
        substrings.append(substring)

        substringHash = sumOfAsciiCode(substring)
        checkIfHashesAndLettersMatch(substringHash, patternHash, substring, sortedPattern, failedMatchesCounter, False)
        i += 1
    if len(anagramIndexes) == 0:
        anagramIndexes.append(-1)
    print(substrings)
    print(anagramIndexes)
    secondDiagonalAnagramsIndexes = anagramIndexes

#      ===========================

outputFile.write(createStringFromList(firstDiagonalAnagramsIndexes) + "\n")
outputFile.write(createStringFromList(secondDiagonalAnagramsIndexes) + "\n")
print("==================")

# d)
if patternLength % 2 == 1:
    TShapeAnagramsCombinationsCounter = 0

    wingLengthOfTShape = patternLength // 2
    print("wingLengthOfTShape:", wingLengthOfTShape)
    print(rowAnagramIndexes)
    print(colAnagramIndexes)
    print("---")

    for rowIndex in range(len(rowAnagramIndexes) - wingLengthOfTShape):
        print(rowAnagramIndexes[rowIndex])
        currentRow = rowAnagramIndexes[rowIndex]
        for rowAnagramIndex in currentRow:
            if rowAnagramIndex + wingLengthOfTShape < len(colAnagramIndexes) and rowAnagramIndex >= 0:
                currentCol = colAnagramIndexes[rowAnagramIndex + wingLengthOfTShape]
                print(rowAnagramIndex, currentCol)
                if rowIndex + 1 < len(currentCol) and rowAnagramIndex in currentCol:
                    # print(rowAnagramIndex, currentCol[rowIndex + 1])
                    TShapeAnagramsCombinationsCounter += 1
                    print("TShapeAnagramsCombinationsCounter INCREMENTED", rowAnagramIndex, currentCol)

    outputFile.write(str(TShapeAnagramsCombinationsCounter) + "\n")
else:
    outputFile.write("-1" + "\n")
print("==================")

# e) output
print("failedMatchesCounter[0]:", failedMatchesCounter[0])
outputFile.write(str(failedMatchesCounter[0]) + "\n")

inputFile.close()
outputFile.close()

# TODO - refactor
# a) & b) - search for substrings & hash functions using the same function
# c) task - create separate function
