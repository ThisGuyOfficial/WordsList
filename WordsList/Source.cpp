#include "mainTask.h"

int main()
{
	mainTask n;
	
	n.read();
	n.countMatches();
	n.save();
	

	/*std::cout << "path: " << logg::path << '\n';
	logs::out << "this is a test\n";
	logs::out << "this is another test\n";
	logs::flush();
	std::cout << "\n--------------------\n" << std::ifstream(logg::path).rdbuf();

	logg::out << "this is the third test\n";
	logg::flush();
	std::cout << "\n--------------------\n" << std::ifstream(logg::path).rdbuf();*/
	return 0;
}