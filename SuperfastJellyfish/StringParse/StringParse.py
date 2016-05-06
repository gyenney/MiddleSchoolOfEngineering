#  MoreInfo:  https://docs.python.org/2/howto/regex.html#regex-howto           #
#  I copied and pasted this for later referance                                #
#  Common Patterns which can be matched:                                       #
#                                                                              #
#  \d  Matches any decimal digit                                               #
#  \D  Matches any non-digit character                                         #
#  \s  Matches any whitespace character                                        #
#  \S  Matches any non-whitespace character                                    #
#  \w  Matches any alphanumeric character                                      #
#  \W  Matches any non-alphanumeric character                                  #
#                                                                              #
#   *  means: match zero or more of the preceding patterns                     #
#   +  means:  match 1 or more of the preceeding patterns                      #
#                                                                              #
################################################################################
import re
while True:

    message_string = raw_input("Please enter a command: ")
    print "You entered: ", message_string

    m = re.match(r'(\w+)\s+(\d+)', message_string)
    if m == None:
        print "No such command: ", message_string
        continue
    else:
        print "The string matches a command."
        print "The match object is: ", m

    command = m.group(1)
    value = m.group(2)

    print "Command: ", command
    print "Value: ", value
    
