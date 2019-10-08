#include "leptonSpecFileReader.h"

leptonSpecFileReader::leptonSpecFileReader(const std::string& input) :
  fileReader(input) {

  // Acceptable parameters from Lepton specification files.
  std::vector<std::string> lepton_simple_params {
      "tgff file",
      "drachma app file"
  };
  std::vector<std::string> lepton_regex_params {
      "\\bip\\d+\\b \\blatency\\b[:] \\d+",
      "\\bip\\d+\\b \\bupper tolerance\\b[:] \\d+",
      "\\bip\\d+\\b \\blower tolerance\\b[:] \\d+",
      "\\bsr\\d+\\b \\bmodule \\d+\\b[:]\\s*ip\\d+",
      "\\brr\\d+\\b \\bmodule \\d+\\b[:]\\s*\\{\\s*ip\\d+\\s*(,\\s*ip\\d+)*\\s*\\}"
  };

  setAcceptableParams(lepton_simple_params);
  setRegexArgs(lepton_regex_params);

  parseContent();
  parseEntries();
}
