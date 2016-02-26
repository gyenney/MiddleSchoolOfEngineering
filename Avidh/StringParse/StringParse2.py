import re

while True:

    rawInput = raw_input("Enter Command: ")

    print "You entered: ", rawInput

    match = re.match(r'GO', rawInput)

    print"Match: ", match

    
