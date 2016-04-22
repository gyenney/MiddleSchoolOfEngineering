import re

while True:

    # press ctrl-c to exit the infinite loop

    message_string = raw_input("Please enter a command: ")

    print "You entered: ", message_string


    # This is the regular expression pattern match
    #
    m = re.match(r'GO', message_string)

