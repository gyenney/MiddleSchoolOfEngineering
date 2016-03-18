import re

while True:

	message_string = raw_input("Please enter a command: ")
	
	print "You entered: ", message_string
	
	
	m = re.match(r'GO', message_string)
	
	print "m: ", m