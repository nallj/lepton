#ifndef LEPTON_FILE_WRITER_H
#define LEPTON_FILE_WRITER_H

#include <stdio.h> // remove
#include <fstream> // ofstream
#include <string> // c_str, string
#include <vector> // vector

class fileWriter {
  const std::string input_file_;

public:
	fileWriter(const std::string& input) :
		input_file_(input) {}


	void deleteIfExists() const {
    remove(input_file_.c_str());
  }

	void addSingleLineToEof(const std::string& line) const;
	void addMultipleLinesToEof(const std::vector<std::string>& lines) const;
};

#endif
