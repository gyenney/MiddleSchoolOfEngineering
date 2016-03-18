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
server.sendmail( 'middleschoolengineer1', '(469)-955-9292@txt.att.net', 'Hello, From python!' )
print "done.\n";

