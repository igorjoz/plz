inputFile = open("normalizacja.txt", "r")
outputFile = open("wynik.txt", "w")


def convertToNormalizedFormat(num):
    negative = False

    if num < 0:
        negative = True
        num = -num

    powCounter = 0
    if num > 1:
        while num >= 10:
            powCounter += 1
            num /= 10
    else:
        while num < 1:
            powCounter -= 1
            num *= 10

    # print(num, powCounter, int(num - (num % 1)), round(num % 1, 10), 10 ** powCounter)

    if negative:
        num = -num
    if num % 1 == 0:
        num = int(num)
    num = round(num, 10)

    print(normalizedFormatString(num, powCounter))
    return [num, powCounter]


def normalizedFormatString(num, powCounter):
    string = ""
    if str(num)[0] == "-":
        string += "(" + str(num) + ")"
    else:
        string = str(num)
    string += "*" + "10(" + str(powCounter) + ")"
    return string


def printAndWriteCurrentState(normalizedFormatStrings, operations):
    string = normalizedFormatStrings[0]
    stringIndex = 1
    operationIndex = 0
    print(normalizedFormatStrings, operations)
    while operationIndex < len(operations):
        string += (operations[operationIndex] + normalizedFormatStrings[stringIndex])
        stringIndex += 1
        operationIndex += 1
    print(string, normalizedFormatStrings, operations)
    outputFile.write(string + "\n")


lines = inputFile.readlines()
lines = list(map(lambda line: line.strip(), lines))

operationsQuantity = int(lines[0])
nums = list(map(lambda num: float(num), lines[1].split()))
inputNums = list(map(lambda num: float(num), lines[1].split()))
inputOperations = lines[2].split()
operations = lines[2].split()
print("operationsQuantity:", operationsQuantity)
print(nums)
print(operations)
print("================")

normalizedFormatNums = []
normalizedFormatStrings = []
for num in inputNums:
    normalizedFormatNum = convertToNormalizedFormat(num)
    normalizedFormatNums.append(normalizedFormatNum)
    normalizedFormatStrings.append(normalizedFormatString(normalizedFormatNum[0], normalizedFormatNum[1]))

print(normalizedFormatNums)
print(normalizedFormatStrings)
print("========")

printAndWriteCurrentState(normalizedFormatStrings, operations)

# multiplication & division
numIndex = 0
operationIndex = 0
while operationIndex < len(operations):
    operation = operations[operationIndex]
    num1 = normalizedFormatNums[numIndex]
    num2 = normalizedFormatNums[numIndex + 1]

    if operation == '+' or operation == '-':
        operationIndex += 1
        numIndex += 1
    else:

        if operation == '*':
            result = (num1[0] * 10 ** num1[1]) * (num2[0] * 10 ** num2[1])
        if operation == '/':
            result = (num1[0] * 10 ** num1[1]) / (num2[0] * 10 ** num2[1])
        normalizedFormatNums[numIndex] = convertToNormalizedFormat(result)
        normalizedFormatStrings[numIndex] = normalizedFormatString(normalizedFormatNums[numIndex][0], normalizedFormatNums[numIndex][1])

        print(num1, operation, num2, normalizedFormatNums[numIndex])
        operations.pop(operationIndex)
        normalizedFormatNums.pop(numIndex + 1)
        normalizedFormatStrings.pop(numIndex + 1)
        print(operations, normalizedFormatNums)
        printAndWriteCurrentState(normalizedFormatStrings, operations)
        print("---")
print("========")

# addition & subtraction
numIndex = 0
operationIndex = 0
while operationIndex < len(operations):
    operation = operations[operationIndex]
    num1 = normalizedFormatNums[numIndex]
    num2 = normalizedFormatNums[numIndex + 1]

    if operation == '+':
        result = (num1[0] * 10 ** num1[1]) + (num2[0] * 10 ** num2[1])
    if operation == '-':
        result = (num1[0] * 10 ** num1[1]) - (num2[0] * 10 ** num2[1])
    normalizedFormatNums[numIndex] = convertToNormalizedFormat(result)
    normalizedFormatStrings[numIndex] = normalizedFormatString(normalizedFormatNums[numIndex][0], normalizedFormatNums[numIndex][1])

    print(num1, operation, num2, normalizedFormatNums[numIndex])
    operations.pop(operationIndex)
    normalizedFormatNums.pop(numIndex + 1)
    normalizedFormatStrings.pop(numIndex + 1)
    print(operations, normalizedFormatNums)
    printAndWriteCurrentState(normalizedFormatStrings, operations)
    print("---")

inputFile.close()
outputFile.close()
