import re
while True:

  #press ctrl-c to exit the infinite loop
  message_string=raw_input("Please enter a command:")
  print"You entered: ",message_string

  m=re.match(r'(\w+)\s+(\d+)',message_string)

  #See if your string matched the regular expression pattern or not
  #If not, then go back to beginning of loop.
