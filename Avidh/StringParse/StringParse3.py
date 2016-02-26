import re

while True:

    input = raw_input("Enter If You Dare: ")
    print "You entered: ", input

    match = re.match(r'(\w+)\s+(\d+)', input)

    if match == None:
        print "You are a disgrace to the family"
        continue
    else:
        print "The string matches command"
        print "The match is: ", match

    command = match.group(1)
    val = m.groupt(2)

    print "Command: ", command
    print "Value: ", value

                      
