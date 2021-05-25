#include <iostream>
#include <SDL.h>

#include "Game.h"

void start(int argc, char** argv) {

	// practica3 2000
	// practica3 localhost 2000
	Game g = Game();

	Uint16 port;
	const char* host = nullptr;
	if (argc == 2) {
		atoi(argv[1]);
		port = static_cast<Uint16>(atoi(argv[1]));
	}
	else if (argc == 3) {
		host = argv[1];
		port = static_cast<Uint16>(atoi(argv[2]));
	}
	else {
		throw "Unknown mode";
	}

	g.init(host, port);
	g.run();
}

int main(int ac, char **av) {

	//sdlutils_basic_demo();
	Game g = Game();

	try {	start(ac, av);	}
	catch (const std::string& e) {	// catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) {			// catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "No sé cual es el problema";
	}

	return 0;
}

