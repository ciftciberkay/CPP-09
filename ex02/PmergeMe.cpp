#include "PmergeMe.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _list(other._list) {
}

PmergeMe::~PmergeMe() {
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other) {
		_vector = other._vector;
		_list = other._list;
	}
	return *this;
}

void PmergeMe::run(int argc, char **argv)
{
	if (argc < 2)
		throw std::runtime_error("Error");
	for (int i = 1; i < argc; ++i)
	{
		int value = parsePositive(argv[i]);
		_vector.push_back(value);
		_list.push_back(value);
	}
	printRange("Before:", _vector);
	std::clock_t startVector = std::clock();
	sortVector(_vector);
	std::clock_t endVector = std::clock();
	std::clock_t startList = std::clock();
	sortList(_list);
	std::clock_t endList = std::clock();
	printRange("After:", _vector);
	double vecTime = (endVector - startVector) * 1000000.0 / CLOCKS_PER_SEC;
	double listTime = (endList - startList) * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size()
			  << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _list.size()
			  << " elements with std::list : " << listTime << " us" << std::endl;
}

int PmergeMe::parsePositive(const std::string &text)
{
	char *end = NULL;
	long value = std::strtol(text.c_str(), &end, 10);
	if (end == text.c_str() || *end != '\0' || value <= 0
		|| value > std::numeric_limits<int>::max())
		throw std::runtime_error("Error");
	return static_cast<int>(value);
}

void PmergeMe::printRange(const std::string &label, const std::vector<int> &values)
{
	std::cout << label;
	for (std::vector<int>::const_iterator it = values.begin(); it != values.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void PmergeMe::sortVector(std::vector<int> &values)
{
	if (values.size() < 2)
		return;
	std::vector<Pair> pairs;
	bool hasOdd = values.size() % 2;
	int odd = hasOdd ? values.back() : 0;
	for (std::size_t i = 0; i + 1 < values.size(); i += 2)
	{
		Pair pair;
		pair.big = values[i] > values[i + 1] ? values[i] : values[i + 1];
		pair.small = values[i] > values[i + 1] ? values[i + 1] : values[i];
		pairs.push_back(pair);
	}
	sortVectorPairs(pairs);
	values.clear();
	for (std::vector<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
		values.push_back(it->big);
	for (std::vector<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
		insertVector(values, it->small);
	if (hasOdd)
		insertVector(values, odd);
}

void PmergeMe::sortVectorPairs(std::vector<Pair> &pairs)
{
	if (pairs.size() < 2)
		return;
	std::vector<Pair> winners;
	std::vector<Pair> losers;
	bool hasOdd = pairs.size() % 2;
	Pair odd;
	if (hasOdd)
		odd = pairs.back();
	for (std::size_t i = 0; i + 1 < pairs.size(); i += 2)
	{
		if (pairs[i].big > pairs[i + 1].big)
		{
			winners.push_back(pairs[i]);
			losers.push_back(pairs[i + 1]);
		}
		else
		{
			winners.push_back(pairs[i + 1]);
			losers.push_back(pairs[i]);
		}
	}
	sortVectorPairs(winners);
	pairs = winners;
	for (std::vector<Pair>::const_iterator it = losers.begin(); it != losers.end(); ++it)
		insertVectorPair(pairs, *it);
	if (hasOdd)
		insertVectorPair(pairs, odd);
}

void PmergeMe::insertVector(std::vector<int> &values, int value)
{
	std::vector<int>::iterator it = values.begin();
	while (it != values.end() && *it < value)
		++it;
	values.insert(it, value);
}

void PmergeMe::insertVectorPair(std::vector<Pair> &pairs, const Pair &value)
{
	std::vector<Pair>::iterator it = pairs.begin();
	while (it != pairs.end() && it->big < value.big)
		++it;
	pairs.insert(it, value);
}

void PmergeMe::sortList(std::list<int> &values)
{
	if (values.size() < 2)
		return;
	std::list<Pair> pairs;
	std::list<int>::iterator it = values.begin();
	while (it != values.end())
	{
		int first = *it++;
		if (it == values.end())
		{
			Pair odd;
			odd.big = first;
			odd.small = first;
			pairs.push_back(odd);
			break;
		}
		int second = *it++;
		Pair pair;
		pair.big = first > second ? first : second;
		pair.small = first > second ? second : first;
		pairs.push_back(pair);
	}
	bool hasOdd = values.size() % 2;
	int odd = pairs.back().big;
	if (hasOdd)
		pairs.pop_back();
	sortListPairs(pairs);
	values.clear();
	for (std::list<Pair>::const_iterator pit = pairs.begin(); pit != pairs.end(); ++pit)
		values.push_back(pit->big);
	for (std::list<Pair>::const_iterator pit = pairs.begin(); pit != pairs.end(); ++pit)
		insertList(values, pit->small);
	if (hasOdd)
		insertList(values, odd);
}

void PmergeMe::sortListPairs(std::list<Pair> &pairs)
{
	if (pairs.size() < 2)
		return;
	std::list<Pair> winners;
	std::list<Pair> losers;
	std::list<Pair>::iterator it = pairs.begin();
	while (it != pairs.end())
	{
		Pair first = *it++;
		if (it == pairs.end())
		{
			losers.push_back(first);
			break;
		}
		Pair second = *it++;
		if (first.big > second.big)
		{
			winners.push_back(first);
			losers.push_back(second);
		}
		else
		{
			winners.push_back(second);
			losers.push_back(first);
		}
	}
	sortListPairs(winners);
	pairs = winners;
	for (std::list<Pair>::const_iterator lit = losers.begin(); lit != losers.end(); ++lit)
		insertListPair(pairs, *lit);
}

void PmergeMe::insertList(std::list<int> &values, int value)
{
	std::list<int>::iterator it = values.begin();
	while (it != values.end() && *it < value)
		++it;
	values.insert(it, value);
}

void PmergeMe::insertListPair(std::list<Pair> &pairs, const Pair &value)
{
	std::list<Pair>::iterator it = pairs.begin();
	while (it != pairs.end() && it->big < value.big)
		++it;
	pairs.insert(it, value);
}
