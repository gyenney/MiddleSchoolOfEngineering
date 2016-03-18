import smtplib
import re
server = smtplib.SMTP( "smtp.gmail.com" , 587 )  # was 587
server.starttls()
server.login( 'middleschoolengineer1', '3n61n33r' )
print ""
print "==============================================="
print "desk_txter is ready to send your messages."
while True:

    print""
    print "Send a message:"
    email_address = raw_input ("\To: ")
    message = raw_input("\t Message: ")
    print ""

    print ""
    sendYN=raw_input ("Do you wish to send your message (y/n)? ")

    if ( sendYN == 'y'):
        print""
        print "Sending..."
        server.sendmail( 'middleschoolengineer1', email_address, message)
        print "your message has ben sent.\n";
         
    
    
