#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

#include <httplib.h>

#include "client_server.h"

using namespace std::chrono_literals;

void ClientThreadFunc(bool& bStop)
{
	std::random_device rd;
	std::mt19937 rnd_eng(rd());
	std::uniform_int_distribution<int> dist;

	httplib::Client client(ServerAddress, ServerPort);
	client.set_keep_alive(true);
	client.set_tcp_nodelay(true);
	const auto timeout_ms = 250ms;
	client.set_connection_timeout(timeout_ms);
	client.set_read_timeout(timeout_ms);
	client.set_write_timeout(timeout_ms);

	while (!bStop)
	{
		const auto rnd_num = dist(rnd_eng);
		const auto res = client.Post("/post", std::to_string(rnd_num), "text/plain");
		if (res)
			std::cout << "Successfully posted " << rnd_num << std::endl;
		else
			std::cerr << "Failed to post data: " << res.error() << std::endl;

		std::this_thread::sleep_for(100ms);
	}
}

int main()
{
	bool bStop = false;
	std::thread t(&ClientThreadFunc, std::ref(bStop));

	std::cout << "Press enter key to stop client..." << std::endl;
	std::cin.get();
	std::cerr << "* Stopping client..." << std::endl;
	bStop = true;
	if (t.joinable())
		t.join();

	std::cerr << "* Client stopped. Exiting..." << std::endl;
	return 0;
}
