#chat_talker.py
#
#Author: Greg Yenney

import boto3
from boto3.session import Session

session = Session( aws_access_key_id='AKIAI63546FLYAQUMQ3A',
                   aws_secret_access_key='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',
		   region_name='us-east-1')
sqs = session.resource('sqs')
queue = sqs.get_queue_by_name(QueueName='chatqueue1')

#Python Dictionary or Map is a special array of name : value pairs.
# inside braces {}
#
#e.g dictionary = { 'name1' : 'value1','name2' : 'value2'}
#
#you can nest dictionaries inside of dictionaries:
#dictionary ={ 'name1':'value1','name2': {'name3':'value3'}}
#
#the "value" for name2 is the dictionary which contains name3, value3.
#
#A message being sent to the AWS queue is in the form of a dictionary

sender_name = raw_input("Enter your Chat ID: ")
receiver_name = raw_input("Enter the Chat ID of the person you will chat with: ")
print "\n"
print "Enter the following string to end your chat sessions: __STOP__ \n"
print "\n"

sequence_number = 0

while True:

    message = raw_input("Enter your Message>")

    if message == "__STOP__":
        break


    response = queue.send_messages( Entries = [
        {
            'ID' : str(sequence_number),
            'MessageBody':str(message),
            'MessageAttributes':
            {
                'SenderName':
                {
                    'StringValue':str(sender_name),
                    'DataType':'String'

                },
                'ReceiverName':
                {
                    'StringValue':str(receiver_name),
		    'DataType':'String'
                }
            }
        }
    ])
			
		
	


print "\nChat session ended.\n"
print "Goodbye!\n"
