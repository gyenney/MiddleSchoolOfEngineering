import boto3
from boto3.session import Session

session = Session( aws_access_key_id='AKIAI63546FLYAQUMQ3A',
                   aws_secret_access_key='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',
		   region_name='us-east-1')


sqs = session.resource('sqs')
queue = sqs.get_queue_by_name(QueueName='chatqueue1')

sender_name = raw_input ("Enter your Chat Id:")
receiver_name = raw_input ("Enter the Chat Id of the person you will chat with:")

print "\n"
print "Enter the following styring to end your chat session: __STOP__\n"
print "\n"

sequence_number = 0

while True:

    messages = queue.receive_messages(
        MessageAttributeNames = ['SenderName','ReceiverName'],
        )

    for message in messages:

        sender_name = ''

        if message.message_attributes is not None:
           # print"1"

            if message.message_attributes.get('ReceiverName') is not None:
                #print"2"

                if message.message_attributes.get('ReceiverName').get('StringValue') == receiver_name:
                    #print"3"
                    sender_name = message.message_attributes.get('SenderName').get('StringValue')
                    print sender_name, "said: ", message.body
                    message.delete()

    sequence_number += 1

    message = raw_input( "Enter your Message>")

    if message == "__Stop__":
        break

    response = queue.send_messages ( Entries = [
        {
            'Id' : str(sequence_number),
            'MessageBody' : str(message),
            'MessageAttributes' :
            {
                'SenderName' :
                {
                    'StringValue' : str(sender_name),
                    'DataType' : 'String'
                },
                'ReceiverName':
                {
                    'StringValue' : str(receiver_name),
                    'DataType' : 'String'
                }
            }
        }
    ])
print "\nChat session ended.\n"
print "Goodbye!\n"
