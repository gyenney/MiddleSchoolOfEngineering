import smtplib
import re

def CheckCommandSyntax(txt_string):
    print "Checking command syntax"

    m = re.match(r' (\w+)-(\d+)', txt_string)

    if m == None:
        print "/t Not a valid command", txt_string
    else:
        command = m.group (1)
        level = m.group(2)

        print "/t Valid command: ", command
        print "/t/t Command: ", level
        print "/t/t Level: ", level

print "Syntax check complete"

server = smtplib.SMTP( "smtp.gmail.com", 587)
server.starttls()
server.login('middleschoolengineer1', 'm1ddl35ch001')

print ""
print "============================================================="
print "desktxter is ready for use"

while True:
    print ""
    print "Send a message: "
    email_address = raw_input ("\t To: ")
    message = raw_input("\t Message: ")
    print ""

    sendYN = raw_input("Do you wish to send your message (y/n)? ")

    if (sendYN == 'y'):
        print ""
        print "Sending..."
        server.sendmail( 'middleschoolengineer1', email_address, message )
        print "message sent"

        


    
