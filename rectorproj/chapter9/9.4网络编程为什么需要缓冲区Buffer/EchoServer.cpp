#include "EchoServer.h"

EchoServer::EchoServer(const std::string &ip,const uint16_t port)
{

}

EchoServer::~EchoServer()
{

}

void EchoServer::start()
{

}

void EchoServer::HandleNewConnection(Socket *clientsock)
{
    std::cout << "New connection come in" << std::endl;
}


void EchoServer::HandleClose(Connection *conn)
{

}

void EchoServer::HandleError(Connection *conn)
{

}

void EchoServer::HandleMessage(Connection *conn)
{

}

