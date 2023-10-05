/*
*   TCP Asynchronous Server boost.asio
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using ip::tcp;

class con_handler : public boost::enable_shared_from_this<con_handler>
{
private:
  tcp::socket sock;
  std::string message = "Hello From Server!";
  enum {max_length = 1024};
  char data[max_length];

public:
  typedef boost::shared_ptr<con_handler> pointer;
  con_handler(boost::asio::io_service &io_service) : sock(io_service){}         // constructor socket

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new con_handler(io_service));
  }

  tcp::socket &socket()                                                         // socket creation
  {
    return sock;
  }

  void start()
  {
    sock.async_read_some(
        boost::asio::buffer(data, max_length),
        boost::bind(&con_handler::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  
    sock.async_write_some(
        boost::asio::buffer(message, max_length),
        boost::bind(&con_handler::handle_write,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
  }

  void handle_read(const boost::system::error_code& err, size_t bytes_transferred)
  {
    if (!err)
    {
         std::cout << data << std::endl;
    }
    else 
    {
         std::cerr << "error: " << err.message() << std::endl;
         sock.close();
    }
  }

  void handle_write(const boost::system::error_code& err, size_t bytes_transferred)
  {
    if (!err)
    {
      std::cout << "Server sent Hello message!" << std::endl;
    }
    else
    {
      std::cerr << "error: " << err.message() << std::endl;
      sock.close();
    }
  }
};

class Server 
{
private:
   tcp::acceptor acceptor_;
   void start_accept()
    {
      con_handler::pointer connection = con_handler::create(acceptor_.get_executor());               // socket

      acceptor_.async_accept(connection->socket(),                                                       // asynchronous accept operation and wait for a new connection.
      boost::bind(&Server::handle_accept, this, connection,
      boost::asio::placeholders::error));
    }
public:

  Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234))    // constructor for accepting connection from client
  {
     start_accept();
  }
  void handle_accept(con_handler::pointer connection, const boost::system::error_code& err)
  {
    if (!err)
    {
      connection->start();
    }
    start_accept();
  }
};

int main(int argc, char *argv[])
{
  try
    {
      boost::asio::io_service io_service;  
      Server server(io_service);
      io_service.run();
    }
  catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }

  return 0;
}
