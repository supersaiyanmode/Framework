#include <iostream>
#include <sstream>
#include <string>

#include "CMSServer.h"

#include "QueueReceiver.h"
#include "QueueSender.h"
#include "TopicSubscriber.h"
#include "TopicPublisher.h"
#include "CMSServerConnection.h"

#include "ThreadLogger.h"
#include "Thread.h"
#include "StringUtils.h"
#include "OptParse.h"

//TODO:
//1. Move RegistrationData out to a new class with RWLocks
//2. Like MessageProcessor, have BridgeProcessor as well



//TODO:
//1. Move RegistrationData out to a new class with RWLocks
//2. Like MessageProcessor, have BridgeProcessor as well


class MyCMSServer: public CMSServer {
	Thread<MyCMSServer, int>* thread;
public:
    MyCMSServer(int p): CMSServer(p){
        CMSServer::initialise();
        thread = Thread<MyCMSServer, int>::createThread(this, &MyCMSServer::serve);
        thread->start(0);
    }
    
    bool onConnection(const Connection& c) const{
        tlog("Remote client connected from "<<c.remoteAddressStr());
        return true;
    }
    
    void onDisconnection(const Connection& c) const {
        tlog("Remote client disconnected: "<<c.remoteAddressStr());
    }
    
    bool onReceiverRegistrationRequest() {
        tlog("Registration request");
        return true;
    }
    
    bool onReceiverUnregistrationRequest() {
        tlog("Unregistration request");
        return true;
    }
    
    void serve(int){
        CMSServer::serve();
    }
};

class MyQueueReceiver: public QueueReceiver {
public:
    MyQueueReceiver(CMSServerConnection& conn, const std::string& dest):
            QueueReceiver(conn, dest){
        tlog("QueueReceiver initialised. Receiver ID: "<<id());
    }
    
    void onMessage(GenericCMSMessage& msg){
        tlog("Got ["<<(std::string)destination()<<"]: "<<msg.message());
    }
};

class MyQueueSender : public QueueSender {
public:
    MyQueueSender(CMSServerConnection& conn, const std::string& dest):
            QueueSender(conn, dest){
        tlog("QueueSender initialised!");
    }
    
    void send(std::string m){
        QueueSender::send(m);
    }
};

class MyTopicSubscriber: public TopicSubscriber {
public:
    MyTopicSubscriber(CMSServerConnection& conn, const std::string& dest):
            TopicSubscriber(conn, dest){
        tlog("TopicSubscriber initialised. Receiver ID: "<<id());
    }
    
    void onMessage(GenericCMSMessage& msg){
        tlog("Got ["<<(std::string)destination()<<"]: "<<msg.message());
    }
};

class MyTopicPublisher : public TopicPublisher {
public:
    MyTopicPublisher(CMSServerConnection& conn, const std::string& dest):
            TopicPublisher(conn, dest){
        tlog("TopicPublisher initialised!");
    }
    
    void publish(std::string m){
        TopicPublisher::publish(m);
    }
};

OptParseData OPTPARSE_DATA[] = {
    {"p", "port", "The port to bind on."},
    {"s", "server", "<server-ip>:<port>"},
    {"c", "conf", "The configuration file (optional)"}
};

int main(int argc, char ** argv){
    OptParse parser(OPTPARSE_DATA, sizeof(OPTPARSE_DATA)/sizeof(*OPTPARSE_DATA));
    if (!parser.parse(argc, argv)) {
        std::cerr<<"Invalid command line arguments\n";
        parser.displayHelp();
        return 1;
    }
    if (parser["port"] != "") {
        std::stringstream ss(parser["port"]);
        int port;
        if (!(ss>>port) && port > 65535) {
            std::cout<<"Not a valid port number.\n";
            parser.displayHelp();
            return 1;
        }
        MyCMSServer server(port);
        
        tlog ("Server started on port "<<(long)port);
        std::string line;
        while (std::cin>>line){
            if (line == "quit")
                break;
            else if (line=="bridge"){
                std::string from, to;
                int isQueue;
                std::cin>>from>>to>>isQueue;
                tlog("Bridge added: "<<server.addBridge(from, to, !!isQueue));
            }
            else
                tlog("Unrecognised command.");
        }
    } else if (parser["server"] != ""){
        std::string serverStr = parser["server"];
        std::vector<std::string> split = StringUtils::splitAny(serverStr, ":", true);
        if (split.size() != 2) {
            std::cerr<<"Invalid Server IP\n";
            parser.displayHelp();
            return 1;
        }
        std::stringstream ss(parser["port"]);
        int port;
        if (!(ss>>port) && port > 65535) {
            std::cout<<"Not a valid port number.\n";
            parser.displayHelp();
            return 1;
        }
        CMSServerConnection* conn = CMSServerConnection::createCMSServerConnection(
            split[0], port);
        tlog ("Connected to Server at "<<argv[1]<<" on port "<<(long)port);
        std::vector<CMSClient*> receivers;
        std::string command, opt1, opt2;
        while (conn->readable() && conn->writable()){
            (std::cout<<"> ").flush();
            std::cin>>command;
            if (command == "quit")
                break;
            else if (command == "receive"){
                std::cin>>opt1;
                CMSClient* r = new MyQueueReceiver(*conn, opt1);
                receivers.push_back(r);
            } else if (command == "send"){
                std::cin>>opt1;
                MyQueueSender s(*conn, opt1);
                std::cin>>command;
                s.send(StringUtils::trim(command));
            } else if (command == "publish"){
                std::cin>>opt1;
                MyTopicPublisher s(*conn, opt1);
                std::cin>>command;
                s.publish(StringUtils::trim(command));
            } else if (command == "subscribe") {
                std::cin>>opt1;
                CMSClient* r = new MyTopicSubscriber(*conn, opt1);
                receivers.push_back(r);
            } 
            else
                tlog("Unrecognised command!");
        }
        for (std::vector<CMSClient*>::iterator it=receivers.begin();
                    it != receivers.end(); it++){
            delete *it;
        }
        delete conn;
    } else {
        parser.displayHelp();
    }
    return 0;
}
