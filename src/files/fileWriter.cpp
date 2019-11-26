#include "fileWriter.h"

fileWriter::fileWriter(const std::string& input) :
	input_file_(input) {}


void fileWriter::deleteIfExists() const {
	remove(input_file_.c_str());
}

void fileWriter::addSingleLineToEof(const std::string& line) const {

	std::ofstream input_file;
	input_file.open(input_file_.c_str(), std::ios_base::app);

	input_file << line << "\n";
	input_file.close();
}

void fileWriter::addMultipleLinesToEof(const std::vector<std::string>& lines) const {

  std::ofstream input_file;
	input_file.open(input_file_.c_str(), std::ios_base::app);

	for (const auto& line : lines) {
		input_file << line << "\n";
	}

	input_file.close();
}
