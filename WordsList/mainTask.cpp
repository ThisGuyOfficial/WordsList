#include "mainTask.h"

void mainTask::push_back(int count, std::string& value)
{
	W.log("Called mainTask::push_back - adding new node to list with value " + value);
	Node* p = new Node(count, value);
	if (empty()) { head = p; end = p; return; }
	end->next = p;
	end = p;
}

bool mainTask::read()
{
	W.log("Called  mainTask::read()");
	std::ifstream in(pathtowl);
	char c;
	int i = 0;
	std::string res;
	if (in.is_open()) {
		while (in.good()) {
			in.get(c);
			if (c < 'A' || c>'Z')
			{
				if (i)
				{
					storedWords.push_back( res );
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
		return false;
	}
	in.close();
	W.log("mainTask::read() data sucessfully readed from file and parsed");
	std::sort(storedWords.begin(), storedWords.end());
	return true;
}

void mainTask::createList()
{
	W.log("Called mainTask::createList");
	if (result.empty()) { W.log("mainTask::createList exit with error: cannot create list - load data from file first"); return; }
	for (std::pair<int, std::string>& a : result)
		push_back(a.first, a.second);
	W.log("mainTask::createList list sucessfully created");
}

void mainTask::countMatches()
{
	W.log("Called mainTask::countMatches");
	auto first_m = storedWords.begin();
	while (first_m != storedWords.end())
	{
		auto next_word_m = std::find_if_not(first_m, storedWords.end(), [&first_m](const auto& val)
			{
				return val == *first_m;
			}
		);
		std::string expectsString{ *first_m };
		W.log("mainTask::countMatches founded match at "+expectsString);
		result.push_back({ std::distance(first_m, next_word_m), expectsString });
		first_m = next_word_m;
	}
	W.log("mainTask::countMatches data processed sucessfylly");
	createList();
}

bool mainTask::save()
{
	W.log("Called mainTask::save");
	if (result.empty()) { W.log("mainTask::save exit with error: no data to save"); return false; }
	std::ofstream out;
	out.open("ResultPairs.txt");
	if (out.is_open())
	{
		for (std::pair<int, std::string>& a : result)
			out << a.first << " " << a.second << '\n';
	}
	else { W.log("mainTask::save exit with error: cannot open oftream to ResultPairs.txt"); out.close(); return false; }
	W.log("mainTask::save all data sucessfully saved in file");
	out.close();
}

bool mainTask::changePath(std::string& val)
{
	if (val.empty()) return false;
	pathtowl = val + "\\WordsList.txt";
	return true;
}


