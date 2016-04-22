import smtplib
import re


def CheckCommandSyntax(txt_string):
    
    print "Checking command syntax."

    m = re.match(r'(\w+)-(\d+)',txt_string)
    
from_email_address=raw_input("Enter From email address:")
from_email_password=raw_input("Enter Password")

server = smtplib.SMTP( "smtp.gmail.com", 587 ) # was 587
server.starttls()
server.login( 'middleschoolengineer1', '3n61n33r' )

print ""
print "=================================================="
print "desk_txter is ready to send your messages."

while True:
    print ""
    print"send a message:"
    email_address = raw_input ("\t To: ")
    message = raw_input("\t Message: ")
    print ""


    print ""
    sendYN = raw_input("Do you wish to send your message (y/n)? ")

    if (sendYN == 'y'):
        print ""
        print "Sending..."
        server.sendmail( 'middleschoolengineer1', email_address, message )
        print "your message has been sent. \n";
