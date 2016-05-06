#import the Regular Expression library.
import re
while True:

    # press ctrl-c to exit the infinite loop

    message_string = raw_input("Please enter a command: ")

    print "You entered: ", message_string

    m = re.match(r'(\w+)\s+(\d+)', message_string)
    print "m:  ", m
