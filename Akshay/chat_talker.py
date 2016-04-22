import boto3
from boto3.session import Session

session = Session( aws_access_key_id='AKIAI63546FLYAQUMQ3A',
                   aws_secret_access_key='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',
		   region_name='us-east-1')

sqs=session.resource('sqs')
queue=sqs.get_queue_by_name(QueueName='chatqueue1')


sender_name=raw_input("Enter your Chat ID:")
receiver_name=raw_input("Enter the Chat ID of the person you will chat with:")
print"\n"
print"Enter the following string to end your chat session:_STOP_\n"
print"\n"


sender_name=raw_input("Enter your Chat ID:")
receiver_name=raw_input("Enter the Chat ID of the person you will chat with:")
print"\n"
print"Enter the following string to end your

