#include "mainTask.h"

void mainTask::push_back(std::string& value)
{
	W.log("Called mainTask::push_back - adding new node to list with value "+value);
	Node* p = new Node(value);
	if (empty()) { head = p; end = p; return; }
	end->next = p;
	end = p;
}

void mainTask::read()
{
	W.log("Called  mainTask::read()");
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
	{
		W.log("mainTask::read() exit with error: cannot open ifstream to WordsList.txt");
		in.close();
		return;
	}
	in.close();
	W.log("mainTask::read() data sucessfully readed from file and parsed");
	createList(storedWords);
}

void mainTask::createList(std::vector<std::string> storedWords)
{
	W.log("Called mainTask::createList");
	if (storedWords.empty()) { W.log("mainTask::createList exit with error: cannot create list - load data from file first"); return; }
	for (int i = 0; i < storedWords.size(); ++i)
	{
		push_back(storedWords[i]);
	}
	W.log("mainTask::createList list sucessfully created");
}

void mainTask::countMatches()
{
	W.log("Called function mainTask::countMatches()");
	Node* first = head;
	int count = 0, pos=0;
	std::vector<std::pair<int, std::string>> res;
	while (first != nullptr)
	{
		result.push_back(std::pair<int, std::string>(1, first->val)); 
		first = first->next;
		++count;
	}
	W.log("mainTask::countMatches() counted all elements and stored in   pair <int,string>");
	first = head;
	std::sort(result.begin(), result.end(), [](const std::pair<int, std::string>& x, const std::pair<int, std::string>& y) 
		{
			if (x.second != y.second) {return x.second < y.second;}return x.first < y.first;
		});
	W.log("mainTask::countMatches() elements sorted by second value in pair");
	for (int i = 1; i < count-1; ++i)
	{
		if (result[i].second == result[i - 1].second)
		{
			result[i-1].first++;
			result.erase(result.begin() + i);
			--count; --i;

		}
	}
	W.log("mainTask::countMatches() duplicate elements counted and removed (all strings unique)");
	std::sort(result.begin(), result.end());
	W.log("mainTask::countMatches() elements sorted");
}

void mainTask::save()
{
	W.log("Called mainTask::save");
	if (result.empty()) { W.log("mainTask::save exit with error: no data to save"); return; }
	std::ofstream out;         
	out.open("ResultPairs.txt");     
	if (out.is_open())
	{
		for (const std::pair<int, std::string>& a : result)
			out << a.first << " " << a.second << '\n';
	}
	else { W.log("mainTask::save exit with error: cannot open oftream to ResultPairs.txt");}
	W.log("mainTask::save all data sucessfully saved in file");
	out.close();
}

