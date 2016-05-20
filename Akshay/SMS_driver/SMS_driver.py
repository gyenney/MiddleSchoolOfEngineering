import smtplib
import re


def CheckCommandSyntax(txt_string):
    
    print "Checking command syntax."

    m = re.match(r'(\w+)-(\d+)',txt_string)
    
from_email_address=raw_input("Enter From email address:")
from_email_password=raw_input("Enter Password")

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
    #  service provider (AT&T, Verizon, etc.) or send to a regular email address.
    # 
    #  Examples: 
    #     Txt Message thru AT&T SMS Gateway:  your_mobile_phone_number>@txt.att.net
    #     Normal Email:  your_address@gmail.com
    #
    # AT&T SMS Gateway:  your_mobile_phone_number>@txt.att.net
    
    
    message = raw_input("Message: ")
    print ""


    print ""
    sendYN = raw_input("Do you wish to send your message (y/n)? ")

    if (sendYN == 'y'):
        print ""
        print "Sending..."
        server.sendmail( from_email_address, email_address, message )
        print "your message has been sent. \n";
