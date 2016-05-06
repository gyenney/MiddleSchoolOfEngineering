import smtplib
import re

def CheckCommandSyntax(txt_string) :

    print "Checking command syntax..."

    m = re.match(r'(\w+)(\d+)', txt_string)

    if m == None:
        print"\t Not a valid command: ", txt_string

    else:
        command = m.group(1)
        level = m.group(2)

        print"\tValid command:"
        print"\t\t Command: ", command
        print"\t\t Value:   ", value

    print "Syntax check complete."


from_email_address = raw_input("Enter From email address: ")
from_email_password = raw_input("Enter Password: ")
    
        
server = smtplib.SMTP("smtp.gmail.com", 587 ) 
server.starttls()
server.login('middleschoolengineer1', 'm1ddl35ch001')

print ""
print"======================================"
print"desk_txter is ready to send your messages."


while True:
    print""
    print"Send a message:"
    email_address = raw_input("\t To:")
    message = raw_input("\t Mezssage:")
    print""

    CheckCommandSyntax(message)

    print""
    sendYN = raw_input("Do you wish to send your message (Y/N? ")
    if(sendYN == 'Y'):

        print"Sending..."
        server.sendmail('middleschoolengineer1', email_address, message)
        print"Your message has been sent.\n";

