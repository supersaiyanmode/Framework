#include "QueueSender.h"
#include "ThreadLogger.h"

QueueSender::QueueSender(CMSServerConnection& c, const CMSDestination& d) :
            conn(c), destination(d){
        
}

QueueSender::~QueueSender() {

}

bool QueueSender::send(const CMSHeaderSet& custom, const std::string& message) {
    CMSHeaderSet standard;
    standard["direction"] = "forward";
    standard["category"] = GenericCMSMessage::CMSMessageTypeToStr(GenericCMSMessage::Queue);
    standard["destination"] = destination;
    GenericCMSMessage out(standard, custom, message);
    GenericCMSMessage ack;
    return conn.writeWithAck(out, ack);
}

bool QueueSender::send(const std::string& message) {
    return send(CMSHeaderSet(), message);
}
