/*
*   TCP Client boost.asio
*/

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;

int main() 
{
     boost::asio::io_service io_service;                                                            
     tcp::socket socket(io_service);                                                                // socket creation
     socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));       // connection

     const string msg = "Hello from Client!\n";
     boost::system::error_code error;
     boost::asio::write(socket, boost::asio::buffer(msg), error);                                    // request/message from client
     if( !error )
     {
        std::cout << "Client sent hello message!" << std::endl;
     }
     else 
     {
        std::cout << "send failed: " << error.message() << std::endl;
     }

     boost::asio::streambuf receive_buffer;
     boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);                   // getting response from server
     if (error && error != boost::asio::error::eof)
     {
          std::cout << "receive failed: " << error.message() << std::endl;
     }
     else
     {
          const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
          std::cout << data << std::endl;
     }

     return 0;
}