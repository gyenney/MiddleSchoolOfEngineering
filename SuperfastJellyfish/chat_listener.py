import boto3
from boto3.session import Session


session = Session( aws_access_key_id='AKIAI63546FLYAQUMQ3A',
                   aws_secret_access_key='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',
		   region_name='us-east-1')

sqs = session.resource('sqs')
queue = sqs.get_queue_by_name(QueueName='chatqueue1')

receiver_name = raw_input('Enter your Chat Id: ')

print "Poll for messages.\n";

while 1 :

    messages = queue.recieve_messages(
        MessageAttributeNames = ['SenderName','ReceiverName'],
        )
    for message in messages:

        sender_name = ''

        if message.message_attributes is not None :
            if message.message_attributes.get('ReceiverName') is not None :
                if message.message_attribute.get('ReceiverName').get('StringValue') == receiver_name :

                    sender_name = message.message_attributes.get('SenderName').get('StringValue')
                    print sender_name, "said: ", message.body
                    message.delete()
print "Done with infinet while loop.\n";
