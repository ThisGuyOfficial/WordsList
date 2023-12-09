#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <filesystem>

class logger
{
	std::ofstream filestr;
	const std::string path = logFilePath();;

public:
	std::string getTime();
	void log(const std::string&);
	std::string logFilePath();

	logger()
	{

		std::filesystem::path way = std::filesystem::current_path();
		way /= "logs/" + path;
		std::filesystem::create_directories(way.parent_path());
		filestr.open(way, std::ios::out );
		if (!filestr.good()) std::cout << "cannot create log file for session";
		log("Session started");
	}
	~logger()
	{
		log("Session ended");
		filestr.close();
	};
};

