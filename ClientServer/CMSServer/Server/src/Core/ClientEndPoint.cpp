#include "Core/ClientEndPoint.h"
#include "ThreadLogger.h"

ClientEndPoint::ClientEndPoint(Connection& c, MessageProcessor& mp, BridgeProcessor& bp): 
                active(true), conn(c), messageProcessor(mp), bridgeProcessor(bp) {
    queue = SynchronisedQueue<GenericCMSMessage>::createSynchronisedQueue();
    outThread = Thread<ClientEndPoint, int>::createThread(this, &ClientEndPoint::processOutgoing);
    outThread->start(0);
}

ClientEndPoint::~ClientEndPoint(){
    //inform MessageProcessor
    messageProcessor.removeClient(this);
    
    active = false;
    conn.close();
    outThread->join();
    delete outThread;
    delete queue;
}

void ClientEndPoint::addOutboundMessage(GenericCMSMessage& msg){
	queue->push(msg);
}

void ClientEndPoint::processOutgoing(int){
    while (active && conn.writable() && *queue) {
        GenericCMSMessage msg;
        if (!queue->timedPop(msg, 50000))
            continue;
        if (conn.write(msg.str()) <= 0){
            conn.closeWriting();
            break;
        }
    }
}

void ClientEndPoint::processIncoming(int){
    while (active && conn.readable()) {
        GenericCMSMessage msg;
        if (!GenericCMSMessage::parse(conn, msg)) {
            continue; //would break if !conn.readable(); else ignore current message and go on!
        }
        
        //Register Session
        //Send back acknowledgement
        
        if (msg.isForward()) {
            GenericCMSMessage ackMsg;
            ackMsg.updateStandardHeader("receiver-id", "<SERVER>");
            ackMsg.updateStandardHeader("acknowlegdement-for-local-message-id", 
                msg.getStandardHeader("local-message-id"));
            ackMsg.updateStandardHeader("category",
                msg.getStandardHeader("category"));
            ackMsg.updateStandardHeader("direction","backward");
            std::string resultStr;
            switch (msg.category()) {
				//A Queue Message, from a QueueSender
                case GenericCMSMessage::Queue: {
                    bool result;
                    resultStr = (result=messageProcessor.processQueueMessage(msg))?
                        "SUCCESS":"Error sending Queue Message";
                    if (result) {
                        bridgeProcessor.processMessage(msg, messageProcessor);
                    }
                    break;
                }
                
				//A topic Message, from a TopicSender
                case GenericCMSMessage::Topic: {
                    bool result;
                    resultStr = (result=messageProcessor.processTopicMessage(msg))?
                        "SUCCESS":"Error sending Topic Message";
                    if (result) {
                        bridgeProcessor.processMessage(msg, messageProcessor);
                    }
                    break;
                }
				
                //A Message to register Queue/Topic Listener
                case GenericCMSMessage::Register: {
                    resultStr = messageProcessor.registerReceiver(
                                this,
								msg.getStandardHeader("receiver-id"),
                                msg.getStandardHeader("destination"))?
                                    "SUCCESS":"Error registering";
                    break;
                }
                
				//A message to unregister Queue/Topic Listener
                case GenericCMSMessage::UnRegister: {
                    resultStr = messageProcessor.unregisterReceiver(this,
								msg.getStandardHeader("receiver-id"))?
                                    "SUCCESS":"Error unregistering";
                    break;
                }
            }
            
            if (resultStr == "SUCCESS")
                ackMsg.updateStandardHeader("acknowledgement-result", "SUCCESS");
            else{
                ackMsg.updateStandardHeader("acknowledgement-result", "ERROR");
                ackMsg.updateStandardHeader("acknowledgement-error-description", resultStr);
            }
            
            addOutboundMessage(ackMsg);
        } else { 
            //implicit that its backward (ACK)
            //GenericCMSMessage::parse(..) must validate value too - TODO!
            
        }
        //std::cout<<"Got:\n"<<msg.str()<<std::endl;
    }
    conn.closeReading();
    active = false;
}