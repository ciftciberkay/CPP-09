#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <cctype>
# include <map>
# include <stdexcept>
# include <string>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &other);
	void run(const std::string &file) const;

private:
	std::map<std::string, double> _rates;
	void loadData(const std::string &file);
	void processLine(const std::string &line) const;
	static bool parseNumber(const std::string &text, double &value);
	static bool validDate(const std::string &date);
	static bool isLeap(int year);
};

#endif
