import smtplib
import re


def CheckCommandSyntax(txt_string):
    
    print "Checking command syntax."

    m = re.match(r'(\w+)-(\d+)',txt_string)
    
from_email_address=raw_input("Enter From email address:")
from_email_password=raw_input("Enter Password:")

server = smtplib.SMTP( "smtp.gmail.com", 587 ) # was 587
server.starttls()
server.login( from_email_address, from_email_password )
email_address = raw_input ("To: ")

print ""
print "=================================================="
print "SMS_driver is ready to send your messages."

while True:
    print ""
    

    #  Try sending txt messages to a mobile phone by sending to the sms gateway for the 
    #  service provider (AT&T, Verizon, etc.) or send to a regular email address.    #
    # AT&T SMS Gateway: your_>@txt.att.net
    
    
    command = raw_input("What would you like to do?: 1: GO 2: STOP 3: turnleft 4: turnright 5: STATUS..")

    sendYN = 'y'
    if (command == "1"):
        message = "GO"
    elif ( command == "2"):
        message = "STOP"
    elif ( command == "3"):
        message = "turnleft"
    elif ( command == "4"):
        message = "turnright"
    elif ( command == "5") :
        message = "STATUS"
    else:
        print " No such command"
        sendYN = 'n'
        



                
    print ""


    print ""
    #sendYN = raw_input("Do you wish to send your message (y/n)? ")

    if (sendYN == 'y'):
        print ""
        print "Sending..."
        print message
        server.sendmail( from_email_address, email_address, message )
        print "your message has been sent. \n";
