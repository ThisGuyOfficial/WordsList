#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <algorithm>
#include <set>
#include "logger.h"

struct Node
{
	int ct;
	std::string val;
	Node* next;
	Node(int count, std::string& value) : ct(count), val(value), next(nullptr) {}
};

class mainTask
{

	Node* head;
	Node* end;
	logger W;
	std::vector<std::string> storedWords;
	std::vector<std::pair<int, std::string>>  result;
	std::string pathtowl = "WordsList.txt";

public:

	mainTask() : head(nullptr), end(nullptr) {}
	bool empty() { return head == nullptr; }
	void push_back(int,std::string&);
	bool read();
	void createList();
	void countMatches();
	bool save();
	bool changePath(std::string&);
	std::string& getPath() { return pathtowl; }
	std::string getLogPath() { return W.logFilePath(); }
	~mainTask()
	{
		Node* current = head;
		while (current != nullptr)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}


};

