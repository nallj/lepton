#include "drachmaAppFileReader.h"

drachmaAppFileReader::drachmaAppFileReader(const std::string& input) :
  fileReader(input) {

  // Acceptable parameters from Drachma application files.
  std::vector<std::string> drachma_app_params {
    "name",
    "icap width",
    "icap speed",
    "prc speed",
    "static region speed"
  };
  std::vector<std::string> drachma_app_regex {
    "\\bsr\\d+ \\bmodule count\\b[:] \\d+",
    "\\brr\\d+\\b \\bbitstream size\\b[:] \\d+",
    "\\brr\\d+\\b \\bmodule \\d+ speed\\b[:] \\d+[.]\\d{1,2}"
  };

  setAcceptableParams(drachma_app_params);
  setRegexArgs(drachma_app_regex);

  parseContent();
  parseEntries();
}