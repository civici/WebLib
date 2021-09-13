#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "http.h"

#define ROUTE_GET 0
#define ROUTE_POST 1

#define _req REQUEST& req
#define _res RESPONSE& res


class HEADER
{
public:
	std::string key;
	std::string val;

	HEADER(std::string line);
	HEADER(std::string key, std::string val);

	std::string get();
	void print();
};


class HEADERLIST
{
public:
	std::vector<HEADER> data;

	
};


class REQUEST
{
public:
	unsigned char type;
	std::string query;
	std::vector<HEADER> headers;

	REQUEST(std::string req);
	std::string findHeader(std::string key);
};


class RESPONSE
{
public:
	int code;
	std::vector<HEADER> headers;
	std::string body;

	RESPONSE();
	RESPONSE(int code);

	void addHeader(HEADER h);
	void addHeaders(std::vector<HEADER> headers);
	std::string get();
};