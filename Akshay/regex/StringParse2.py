import re
while True:

  #press ctrl-c to exit the infinite loop
  message_string=raw_input("Please enter a command:")
  print"You entered: ",message_string

  #This is the regular expresion pattrn match
  #
  m=re.match(r'GO', message_string)

  #See if your string matched the regular expression pattern or not.
  #None means it did not match.
  print"m: ", m
