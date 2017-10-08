#include "MyErrors.h"

namespace EmGine{

void fatalError(std::string errorString){

	std::cout << "ERROR: " << errorString << "\n" << "Enter any key to quit...";
	std::cin.get();
	SDL_Quit();
	exit(1);
}

}