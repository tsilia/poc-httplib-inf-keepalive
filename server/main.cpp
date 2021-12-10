#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <httplib.h>

#include "client_server.h"

using namespace std::chrono_literals;

void ServerThreadFunc(httplib::Server& server)
{
	if (!server.listen(ServerAddress.c_str(), ServerPort))
	{
		std::cerr << "Failed to start server!" << std::endl;
		return;
	}
}

int main()
{
	httplib::Server server;
	server.Post("/post", [](const httplib::Request& req, httplib::Response& res){ std::cout << req.body << std::endl; });
	server.set_read_timeout(250ms);
	server.set_write_timeout(250ms);
	server.set_keep_alive_max_count(std::numeric_limits<size_t>::max());	// we need to keep the connection as long as it's possible

	std::thread t(&ServerThreadFunc, std::ref(server));

	std::cout << "Press enter key to stop server..." << std::endl;
	std::cin.get();
	std::cerr << "* Stopping server..." << std::endl;
	server.stop();
	if (t.joinable())
		t.join();

	std::cerr << "* Server stopped. Exiting..." << std::endl;
	return 0;
}
