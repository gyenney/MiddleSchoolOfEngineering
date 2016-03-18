import smtplib
print "Library loaded\"
sever = smtplib.SMTP("smtp.gmail.com", 587)

print "Starting tls session..."
server.starttls()
print "done.\n";

print "Logging in to sever..."
sever.login('middleschoolengineer1', '3n61n33r')
print "done.\n";

print "Sending txt..."
sever.sendmail('middleschoolengineer1', '<your_mobile_phone_number>@txt.att.net', 'Hello, From Python!')
print "done.\n"
