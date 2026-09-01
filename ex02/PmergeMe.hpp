#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <ctime>
# include <list>
# include <stdexcept>
# include <string>
# include <vector>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &other);
	void run(int argc, char **argv);

private:
	struct Pair
	{
		int big;
		int small;
	};
	std::vector<int> _vector;
	std::list<int> _list;
	static int parsePositive(const std::string &text);
	static void printRange(const std::string &label, const std::vector<int> &values);
	static void sortVector(std::vector<int> &values);
	static void sortVectorPairs(std::vector<Pair> &pairs);
	static void insertVector(std::vector<int> &values, int value);
	static void insertVectorPair(std::vector<Pair> &pairs, const Pair &value);
	static void sortList(std::list<int> &values);
	static void sortListPairs(std::list<Pair> &pairs);
	static void insertList(std::list<int> &values, int value);
	static void insertListPair(std::list<Pair> &pairs, const Pair &value);
};

#endif
