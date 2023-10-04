/*
*   TCP Server boost.asio
*/

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;

string read_(tcp::socket &socket)
{
    boost::asio::streambuf buf;                                             // buffer for data storage
    boost::asio::read_until(socket, buf, "\n" );                            // reading data from the socket until a newline character ('\n') 
    string data = boost::asio::buffer_cast<const char*>(buf.data());        // convert the content of streambuf into string
    return data;
}

void send_(tcp::socket &socket, const string &message)
{
    const string msg = message + "\n";                                      // new line is created
    boost::asio::write(socket, boost::asio::buffer(msg));                   // send buffer
}

int main()
{
    boost::asio::io_service io_service;                                     // asynchronous I/O in Boost.Asio
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));    // listen for new connection
    tcp::socket socket_(io_service);                                        // socket creation 
    acceptor_.accept(socket_);                                              // waiting for connection
    string message = read_(socket_);                                        // read operation
    std::cout << message <<std::endl;                                       // write operation

    send_(socket_, "Hello From Server!");
    std::cout << "Servent sent Hello message to Client!" << std::endl;
    
    return 0;
}