#include "http.h"


std::string httpCode(int code)
{
	switch (code)
	{
		case (200):
			return "200 OK";
		case (404):
			return "404 Not Found";

		default:
			return "501 Not Implemented";
	}
}