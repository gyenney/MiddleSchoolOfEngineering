import smtplib

import re

def CheckCommandSyntax(txt_string):
    print "Checking command syntax."

    m = re.match(r'(\w+)-(\d+)', txt_string)

    if m == None:
        print "\t Not a valid command: ", txt_string
    else:
        command = m.group(1)
        level = m.group(2)

        print "\t Valid command: "
        print "\t\t Command: ", command
        print "\t\t Level: ", level

    print "Syntax check complete."

server = smtplib.SMTP ( "smtp.gmail.com", 587) # was 587
server.starttls()
server.login( 'middleschoolengineer1', '3n61n33r' )


print "" print
"====================================================================="
print "desk_txter is ready to send your messages."

while True:

    print ""
    print "Send a message: "
    email_address = raw_input ("\t To: ")
    message = raw_input("\t Message: ")
    print ""

    CheckCommandSyntax(message)

    print ""
    sendYN = raw_input("Do you wish to send your messgae (y/n)? ")


    if ( sendYN == 'y'):

        print ""
        print "Sending..."
        server.sendmail( 'middleschoolengineer1', email_address, message )
        print "your message has been sent. \n";
