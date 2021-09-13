#include "app.h"


Server::Server()
{
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == -1)
		std::cout << "err at socket create\n";
	int err = 0;
	int opt = 1;
	err = setsockopt(this->fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
	if (err != 0)
		std::cout << "err at sockopt\n";
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = htonl(INADDR_ANY);
	this->server.sin_port = htons(1234);
	err = bind(this->fd, (struct sockaddr*) &this->server, sizeof(this->server));
	if (err != 0)
		std::cout << "err at bind\n";
	err = listen(this->fd, 0);
	if (err != 0)
		std::cout << "err at listen\n";
}

int Server::acceptClient()
{
	int client = accept(this->fd, nullptr, nullptr);
	return client;
}



ROUTE::ROUTE(std::string path, std::function<void(REQUEST&, RESPONSE&)> func)
{
	this->path = path;
	this->func = func;
}

void ROUTE::execute(_req, _res)
{
	this->func(req, res);
}



void APP::get(std::string path, std::function<void(REQUEST&, RESPONSE&)> func)
{
	getRoutes.push_back(ROUTE(path, func));
}

ROUTE* APP::findRoute(std::string query)
{
	for (ROUTE& r : this->getRoutes)
	{
		if (r.path == query)
			return &r;
	}

	return nullptr;
}

void APP::startListening()
{
	while (true)
	{
		int clientfd = this->server.acceptClient();
		
		char* buf = (char*) std::calloc(1024, 1);
		recv(clientfd, buf, 1024, 0);
		
		std::string strbuf(buf);
		free(buf);

		REQUEST req(strbuf);
		RESPONSE res;

		ROUTE* route = this->findRoute(req.query);
		if (route == nullptr)
			res.code = 404;
		else
			route->execute(req, res);
		std::string respstr = res.get();
		send(clientfd, respstr.c_str(), respstr.length(), 0);
		shutdown(clientfd, SHUT_RDWR);
		close(clientfd);
	}
}
