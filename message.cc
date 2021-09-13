#include "message.h"


HEADER::HEADER(std::string line)
{
	int index = line.find_first_of(':');
	this->key = line.substr(0, index);
	this->val = line.substr(index + 2, line.length() - (index + 2));
}

HEADER::HEADER(std::string key, std::string val)
{
	this->key = key;
	this->val = val;
}

std::string HEADER::get()
{
	return std::string(this->key + ": " + this->val);
}


void HEADER::print()
{
	std::cout << this->key << ": " << this->val << std::endl;
}

static unsigned char requestParseType(std::string line)
{
	int queryIndex = line.find_first_of('/');
	std::string type = line.substr(0, queryIndex - 1);
	if (type == "GET")
		return ROUTE_GET;
	if (type == "POST")
		return ROUTE_POST;
	return 0;
}

static std::string getQuery(std::string line)
{
	int queryIndex = line.find_first_of('/');
	std::string query;
	for (int i = queryIndex; i < line.length() && line[i] != ' '; i++)
		query.push_back(line[i]);
	
	return query;
}

REQUEST::REQUEST(std::string req)
{
	std::stringstream ss(req);
	std::string line;

	std::getline(ss, line);
	this->type = requestParseType(line);
	this->query = getQuery(line);

	std::getline(ss, line);
	while (line != "\r" && line != "")
	{
		this->headers.push_back(HEADER(line));
		std::getline(ss, line);
	}
}

std::string REQUEST::findHeader(std::string key)
{
	for (HEADER h : this->headers)
	{
		if (h.key == key)
			return h.val;
	}

	return "";
}

RESPONSE::RESPONSE()
{

}

RESPONSE::RESPONSE(int code)
{
	this->code = code;
}

void RESPONSE::addHeader(HEADER h)
{
	this->headers.push_back(h);
}

void RESPONSE::addHeaders(std::vector<HEADER> headers)
{
	for (HEADER h : headers)
	{
		this->headers.push_back(h);
	}
}

std::string RESPONSE::get()
{
	std::ostringstream ss;
	ss << "HTTP/1.1 " << httpCode(this->code) << "\n";
	for (HEADER h : this->headers)
	{
		ss << h.get() << '\n';
	}
	ss << '\n';
	return ss.str();
}