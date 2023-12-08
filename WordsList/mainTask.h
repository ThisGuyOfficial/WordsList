#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <algorithm>

struct Node
{
	std::string val;
	Node* next;
	Node(std::string& value) : val(value), next(nullptr) {}
};

class mainTask
{
	
	Node* head;
	Node* end;
	std::vector<std::pair<int, std::string>> result;

public:

	mainTask() : head(nullptr), end(nullptr) {}
	bool empty() { return head == nullptr; }
	void push_back(std::string&);
	void read();
	void createList(std::vector<std::string>);
	void countMatches();
	void save();
	
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

