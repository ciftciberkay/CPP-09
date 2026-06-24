#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {
	loadData("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates) {
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		_rates = other._rates;
	return *this;
}

void BitcoinExchange::run(const std::string &file) const {
	std::ifstream input(file.c_str());
	if (!input)
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(input, line);
	while (std::getline(input, line))
		processLine(line);
}

void BitcoinExchange::loadData(const std::string &file) {
	std::ifstream input(file.c_str());
	if (!input)
		throw std::runtime_error("Error: could not open database.");

	std::string line;
	std::getline(input, line);
	while (std::getline(input, line)) {
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = line.substr(0, comma);
		double rate;
		if (parseNumber(line.substr(comma + 1), rate) && validDate(date))
			_rates[date] = rate;
	}
}

void BitcoinExchange::processLine(const std::string &line) const {
	std::string::size_type sep = line.find(" | ");
	if (sep == std::string::npos) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, sep);
	std::string valueText = line.substr(sep + 3);
	double value;
	if (!validDate(date) || !parseNumber(valueText, value)) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	if (value < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000) {
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
	if (it == _rates.end() || it->first != date) {
		if (it == _rates.begin()) {
			std::cout << "Error: bad input => " << date << std::endl;
			return;
		}
		--it;
	}
	std::cout << date << " => " << valueText << " = " << value * it->second << std::endl;
}

bool BitcoinExchange::parseNumber(const std::string &text, double &value) {
	char *end = NULL;
	value = std::strtod(text.c_str(), &end);
	return end != text.c_str() && *end == '\0';
}

bool BitcoinExchange::validDate(const std::string &date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (std::size_t i = 0; i < date.size(); ++i) {
		if (i != 4 && i != 7 && !std::isdigit(date[i]))
			return false;
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year < 0 || month < 1 || month > 12)
		return false;
	int maxDay = days[month - 1];
	if (month == 2 && isLeap(year))
		maxDay = 29;
	return day >= 1 && day <= maxDay;
}

bool BitcoinExchange::isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
