#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Logger.h"

void handle_client(boost::asio::ip::tcp::socket& socket, Logger& logger) {
    try {
        while (true) {
            char data[512];
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);

            std::string message(data, length);
            std::cout << "Received: " << message << std::endl;
            logger.log_message("Received: " + message);  
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main() {
    Logger logger("log.txt");  

    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handle_client, std::move(socket), std::ref(logger)).detach();
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
