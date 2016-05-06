# Python txt messager.

import smtplib

print "Library loaded\n"

server = smtplib.SMTP( "smtp.gmail.com", 587 )  # was 587

print "Starting tls session..."
server.starttls()
print "done.\n";

print "Logging in to server..."
server.login( 'middleschoolengineer1', '3n61n33r' )
print "done.\n";

print "Sending txt..."
server.sendmail( 'middleschoolengineer1', '8057954135@vtext', 'hi mom you cat reply because im texting you on a computer program so hi')
print "done.\n";

hi  
