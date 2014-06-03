#if defined(TCP_SOCKET_TEST) || defined(ENABLE_ALL_TESTS)
#include <iostream>

#include "IO/Structure/Line/LineReader.h"
#include "IO/Structure/Line/LineWriter.h"
#include "IO/SocketIO/TCPServerSocket.h"
#include "IO/SocketIO/TCPClientSocket.h"

int main(int argc, char **argv){
    if (argc == 1){ //server
        TCPServerSocket sock(11001);
        sock.initialise();
        std::cout<<"Echo server up and running on port 11001\n";
        Connection con = sock.accept();
        std::cout<<"Connection accepted!\n";
        LineReader reader(con);
        LineWriter writer(con);
        while (true){
            std::string line = reader.readLine();
            std::cout<<"<< "<<line<<std::endl;
            if (line == "quit")
                break;
            writer.writeLine(line);
        }
    } else { //client
        Connection con = Connection::open("127.0.0.1", 11001);
        LineReader reader(con);
        LineWriter writer(con);
        while (true){
            std::string line;
            std::getline(std::cin, line);
            writer.writeLine(line);
            std::cout<<">> "<<reader.readLine()<<std::endl;
        }
    }
    return 0;
}
#endif
