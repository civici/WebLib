#pragma once

#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <functional>

#include "message.h"

class Server
{
public:
	int fd;
	struct sockaddr_in server;
	
	Server();
	int acceptClient();
};

class ROUTE
{
public:
	std::string path;
	std::function<void(REQUEST&, RESPONSE&)> func;

	ROUTE(std::string path, std::function<void(REQUEST&, RESPONSE&)> func);
	void execute(_req, _res);
};

class APP
{
public:
	Server server;
	std::vector<ROUTE> getRoutes;
	std::vector<ROUTE> postRoutes;



	void get(std::string path, std::function<void(REQUEST&, RESPONSE&)> func);
	ROUTE* findRoute(std::string query);
	void startListening();
};