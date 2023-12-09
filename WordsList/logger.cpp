#include "logger.h"

void logger::log(const std::string& msg)
{
	filestr << "[" + getTime() + "] " + msg<<'\n';
}

std::string logger::getTime()
{
    return std::string(std::format("{:%F %H %M %S}", std::chrono::system_clock::now()));
}

std::string logger::logFilePath()
{
    return getTime() + "_f.log";
}