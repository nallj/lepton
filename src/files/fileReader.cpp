
#include "fileReader.h"

bool operator==(const char& ch, const specialTag& st) {
	return ch == static_cast<char>(st);
}


/* PUBLIC */

// Operations Functions //

void fileReader::parseContent() {

	// Clear out current body.
	file_body_.clear(); 

	std::ifstream in_file(input_file_.c_str());
	std::string line;
	bool comment_block = false;

	while (std::getline(in_file, line)) {

		// Handle comment blocks.
		if (
			comment_block ||
			(line.length() > 1 && line.at(0) == specialTag::long_comment && line.at(1) == specialTag::comment)
		) {

			// Is this the end of a comment block?
			comment_block = !(
				comment_block &&
				line.length() > 1 &&
				line.at(0) == specialTag::comment &&
				line.at(1) == specialTag::long_comment
			);

			file_body_.push_back( std::make_pair(lineType::comment, line) );
			continue;
		}

		// Check for single-line comment.
		if (line.length() > 0 && line.at(0) == specialTag::comment) {

			file_body_.push_back( std::make_pair(lineType::comment, line) );
			continue;
		}

		// Parsing not inhibited by comment block.
		if (line.length() == 0) {
			file_body_.push_back( std::make_pair(lineType::white, line) );

		} else {

			// Single line comment.
			//if (line.length() > 0 && line.at(0) == specialTag::comment)
				//continue;

			// Push non-disqualified line onto file body holder.
			file_body_.push_back( std::make_pair(lineType::unknown, line) );
		}


	}

	in_file.close();
}

void fileReader::parseEntries() {

	param_map_.clear();

	for (int i = 0; i < file_body_.size(); i++) {

		if (file_body_[i].first == lineType::unknown) {

			std::size_t pos = file_body_[i].second.find(':');

			// Presence of colon implies (but doesn't guarantee) an acceptable parameter.
			if (pos != std::string::npos) {

				std::string test_param = file_body_[i].second.substr(0, pos);
				std::string test_arg = file_body_[i].second.substr(pos + 1);

				boost::trim(test_arg);

				// Check for parameter with no argument.
				if (test_arg.length() == 0) { 

					std::cout << "ERROR: This is not a valid file. <Parameter with No Argument>\n\n";
					file_body_[i].first = lineType::invalid;

					// File format invalid; stop parsing.
					is_valid_ = false;
					break; 
				}

				// Check if acceptable parameter is present.
				if (
					std::find(
						acceptable_params_.begin(),
						acceptable_params_.end(),
						test_param
					) != acceptable_params_.end()	&&
					test_arg.length() != 0
				) {

					// Multimap parameter and value pairs - like a dictionary.
					std::pair<std::string, std::string> entry(test_param, test_arg);
					param_map_.insert(entry);

					// Parameter accepted; next input.
					file_body_[i].first = lineType::parameter;
					continue; 
				}
			}

			bool pass_regex = false;
			for (int j = 0; j < regex_args_.size(); j++) {

				boost::smatch match;

				if (boost::regex_match(file_body_[i].second, match, boost::regex{regex_args_[j]})) {

					file_body_[i].first = lineType::data;

 					// Regex match found; stop regex parsing.
					pass_regex = true;
					break;
				}
			}

			// Data accepted; next input.
			if (pass_regex) {
				continue; 
			}

			// Getting this far means the line contains neither parameter nor data.
			std::cout << "ERROR: This is not a valid file. <Line#" << i << " is Neither Parameter nor Data>\n\n";
			file_body_[i].first = lineType::invalid;
			is_valid_ = false;

			break;
		}

	} // /for (file body search)
}

void fileReader::printEntries() const {

	std::cout << "> PARAMETER MULTIMAP <\n";


	for (auto& it : param_map_) {
		std::cout << "MAP: " << it.first << "  \t=>\t" << it.second << "\n";
	}

	std::cout << "\n> DATA ENTRIES <" << "\n";
	for (int i = 0; i < file_body_.size(); i++) {
		if (file_body_[i].first == lineType::data) {
				std::cout << "DATA: " << file_body_[i].second << "\n";
		}
	}

}

// std::pair<bool, unsigned long> fileReader::findInFile(std::string line) {

// 	for (unsigned long i = 0; i < file_body_.size(); i++)
// 		if (file_body_[i].second.compare(line) == 0)
// 			return std::make_pair(true, i);

// 	return std::make_pair(false, 0);
// }

// bool fileReader::removeFromFile(std::string line) {

// 	std::pair<bool, unsigned long> finding_pair = findInFile(line);

// 	// Check for presence of line in file.
// 	if (finding_pair.first) {

// 		std::ofstream fout(input_file_);

// 		for (unsigned long i = 0; i < file_body_.size(); i++)
// 				if (i != finding_pair.second)
// 					fout << file_body_[i].second << "\n";

// 		fout.close();
// 		return true;

// 	} else std::cout << "\n\nError: Entry not found in file!\n\n";

// 	return false;
// }


// Accessor Methods //

bool fileReader::isFileValid() { return is_valid_; }

std::vector<std::string> fileReader::getData() {

	std::vector<std::string> data_body;

	for (unsigned long i = 0; i < file_body_.size(); i++) {
		if (file_body_[i].first == lineType::data) {
			data_body.push_back(file_body_[i].second);
		}
	}

	return data_body;
}
