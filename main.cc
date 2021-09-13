#include "http.h"
#include "app.h"
#include "message.h"


int main()
{
	APP a;
	a.get("/", [](_req, _res) -> void {
		std::cout << "get executed " << req.query << std::endl;
		res.code = 200;
	});
	a.get("/test", [](_req, _res) -> void {
		std::cout << "second\n";
		res.code = 200;
	});
	a.startListening();
	return 0;
}