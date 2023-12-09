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
	const std::string path = logFilePath();
	std::string savedPath;

public:
	std::string getTime();
	void log(const std::string&);
	std::string logFilePath();
	std::string sp() { return savedPath; }

	logger()
	{

		std::filesystem::path way = std::filesystem::current_path();
		way /= "logs/" + path;
		std::filesystem::create_directories(way.parent_path());
		filestr.open(way, std::ios::out );
		if (!filestr.good()) { log("cannot create log file for session"); return; }
		savedPath = way.string();
		log("Session started");
	}
	~logger()
	{
		log("Session ended");
		filestr.close();
	};
};

