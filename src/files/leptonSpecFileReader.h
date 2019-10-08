#ifndef LEPTON_SPEC_FILE_READER_H
#define LEPTON_SPEC_FILE_READER_H

#include <string> // string
#include <vector> // vector

#include "fileReader.h"

class leptonSpecFileReader : public fileReader {

public:
  leptonSpecFileReader(const std::string& input);
};

#endif
