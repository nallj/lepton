#ifndef LEPTON_FILE_HANDLER_H
#define LEPTON_FILE_HANDLER_H

#include <boost/algorithm/string/trim.hpp> // trim
#include <boost/regex.hpp> // regex, regex_match, smatch
#include <fstream> // ifstream
#include <iostream> // cout
//#include <stdio.h> // 
#include <string> // string
#include <unordered_map> // unordered_map
#include <utility> // pair
#include <vector> // vector

enum class specialTag {
	comment = '#',
	long_comment = '/'
};
enum class lineType {
	unknown,
	white,
	comment,
	parameter,
	data,
	invalid
};

using line_t = std::pair<lineType, std::string>;
using file_body_t = std::vector<line_t>;

class fileReader {
	bool is_valid_;

	std::vector<std::string> acceptable_params_;
	std::vector<std::string> regex_args_;
	file_body_t file_body_;
	std::unordered_multimap<std::string, std::string> param_map_;

public:
	const std::string input_file_;

	fileReader(const std::string& input);

	// Desired paramters only.
	// fileReader(std::string input, std::vector<std::string> accept) :
	// 	is_valid_(true), input_file_(input), acceptable_params_(accept) {

	// 	parseContent(input);
	// 	parseEntries();
	// }

	// fileReader(std::string input, std::vector<std::string> accept, std::vector<std::string> regex) :
	// 	is_valid_(true), input_file_(input), acceptable_params_(accept), regex_args_(regex) {

	// 	parseContent(input);
	// 	parseEntries();
	// }

	// Desired paramters and data body regex.
	// fileReader(
	// 	std::string input,
	// 	std::vector<std::string> accept,
	// 	std::vector<std::string> regex
	// );

	void setAcceptableParams(const std::vector<std::string>& params);

	void setRegexArgs(const std::vector<std::string>& args);

	// Operations Functions //
	void parseContent();

	// Search for accepted parameters and regex matches for data body.
	void parseEntries(); 

	void printEntries() const;

	// TODO: needs line validation.

	// TODO: not finished.
	//std::pair<bool, unsigned long> findInFile(std::string line);

	// Todo: not finished.
	//bool removeFromFile(std::string line);


	// Accessor Methods //
	bool isFileValid();
	std::unordered_multimap<std::string, std::string> getParamsMap();
	std::vector<std::string> getData();
};

#endif
