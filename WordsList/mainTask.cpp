#include "mainTask.h"

void mainTask::push_back(std::string& value)
{
	Node* p = new Node(value);
	if (empty()) { head = p; end = p; return; }
	end->next = p;
	end = p;
}

void mainTask::read()
{
	std::ifstream in("WordsList.txt");
	char c;
	int i = 0;
	std::vector<std::string> storedWords;
	std::string res;
	if (in.is_open()) {
		while (in.good()) {
			in.get(c);
			if (c < 'a' || c>'z')
			{
				if (i)
				{
					storedWords.push_back(res);
					i = 0; 
					res.clear();
				}
				continue;
			}
			res += c;
			++i;
		}
	}
	if (!in.eof() && in.fail())
		std::cout << "error reading file\n";
	in.close();
	createList(storedWords);
}

void mainTask::createList(std::vector<std::string> storedWords)
{
	if (storedWords.empty()) { std::cout << "load data from file first\n"; return; }
	for (int i = 0; i < storedWords.size(); ++i)
	{
		push_back(storedWords[i]);
	}
}

void mainTask::countMatches()
{
	Node* first = head;
	int count = 0, pos=0;
	std::vector<std::pair<int, std::string>> res;
	while (first != nullptr)
	{
		result.push_back(std::pair<int, std::string>(1, first->val)); 
		first = first->next;
		++count;
	}
	first = head;
	std::sort(result.begin(), result.end(), [](const std::pair<int, std::string>& x, const std::pair<int, std::string>& y) 
		{
			if (x.second != y.second) {return x.second < y.second;}return x.first < y.first;
		});
	for (int i = 1; i < count-1; ++i)
	{
		if (result[i].second == result[i - 1].second)
		{
			result[i-1].first++;
			result.erase(result.begin() + i);
			--count; --i;

		}
	}
	std::sort(result.begin(), result.end());
}

void mainTask::save()
{
	if (result.empty()) { std::cout << "no data tot save"; return; }
	std::ofstream out;         
	out.open("ResultPairs.txt");     
	if (out.is_open())
	{
		for (const std::pair<int, std::string>& a : result)
			out << a.first << " " << a.second << '\n';
	}
	out.close();
}
