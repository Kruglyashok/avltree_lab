#include <iostream>
#include <fstream>
#include "avl_tree.h"
#include <cstring>
#include <string>

void swapRec(Record& lhs, Record& rhs)
{
	Record tmp{};
	tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}


void sortByPublishers(std::vector<Record>& res)
{
	for (auto i{ 0U }; i < res.size() - 1; ++i)
		for (auto j{ 0U }; j < res.size() - i - 1; ++j)
			if (strcmp(res[j].title, res[j + 1].title) > 0)
			{
				swapRec(res[j], res[j + 1]);
			}
}
int main()
{
	AVLTree tree("BASE1.dat");
	char control = 'a';
	std::string publisher;
	while (control != 'q') {
		std::cout << "\nto display tree press d";
		std::cout << "\nto find records in tree by year press f";
		std::cout << "\nto find publishers and their count press m";
		std::cout << "\nto escape press q\n";
		std::cin >> control;
		uint16_t from, to;
		std::vector<Record> recs{};
		std::unordered_map<std::string, int> map{};
		auto print_key_value = [](std::string const& key, int const& value) {
			std::cout << "Publisher:[" << key << "] Number of publications:[" << value << "]\n";
		};
		switch (control)
		{
		case'd':
			tree.display();
			break;
		case 'f':
			std::cout << "\nselect range for years of books to find:\n";
			std::cin >> from >> to;
			std::cin.ignore();
			std::cout << "\nselect publisher of books to find:\n";
			std::getline(std::cin, publisher);
			recs = tree.getRecByYear(from, to, publisher);
			if (recs.size() > 0) 
			{
				sortByPublishers(recs);
				std::for_each(recs.begin(), recs.end(), [](Record rec) {
					std::cout << rec.auth << " " << rec.name << " "
						<< rec.title << " " << rec.year << " " << rec.pages << std::endl; });
			}
			break;
		case 'm':
			map.clear();
			map = tree.getPublishers();
			std::cout << "Iterate and print keys and values of unordered_map, being\n"
				"explicit with the type of the iterator, n:\n";
			for (const std::pair<const std::string, int>& n : map) {
				print_key_value(n.first, n.second);
			}
			std::cout << "\n";
			break;
		case 'q':
			break;
		default:
			break;
		}
	}
	return 0;
}