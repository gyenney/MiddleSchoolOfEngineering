import re

while True:


    message_string = raw_input("Please enter a command:")

    print "You entered:",message_string

    m = re.match(r'(w+)/s+(/d+)',message_string)

    if m == None:
        print "There is no such command:", message_string
        continue
    else:
        print"The string matches a command."
        print"The match object is:",m

    command = m.group(1)
    value = m.group(2)


    print"Command:", command
    print"Value:",value            
