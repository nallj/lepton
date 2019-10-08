#ifndef LEPTON_DRACHMA_APP_FILE_READER_H
#define LEPTON_DRACHMA_APP_FILE_READER_H

#include <string> // string
#include <vector> // vector

#include "fileReader.h"

class drachmaAppFileReader : public fileReader {

public:
  drachmaAppFileReader(const std::string& input);
};

#endif
