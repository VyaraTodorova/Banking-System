
#include <iostream>
#include "System.h"

int main()
{
	try {
		
		run();
	}
	catch (std::invalid_argument& ia)
	{
		std::cout << ia.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Invalid argument given" << std::endl;
	}
	


}

