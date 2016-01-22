#chat_listener.py
#Author: Greg Yeney
#
import boto3
from boto3.session import Session

session = Session( aws_access_key_id='AKIAI63546FLYAQUMQ3A',
                   aws_secret_access_key='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',
		   region_name='us-east-1')
sqs = session.resource('sqs')
queue = sqs.get_queue_by_name(QueueName='chatqueue1')

receiver_namer = raw_input("Enter your Chat Id:")

print "Pollfor messages./n";

while 1 :

    messages = queue.receive_messages(
        MessageAttributeNames =
