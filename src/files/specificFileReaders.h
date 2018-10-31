#ifndef LEPTON_SPECIFIC_FILE_HANDLERS_H
#define LEPTON_SPECIFIC_FILE_HANDLERS_H

#include <string> // string
#include <vector> // vector

#include "fileReader.h"

class leptonSpecFileReader : public fileReader {

public:
    leptonSpecFileReader(const std::string& input) :
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

};

class drachmaAppFileReader : public fileReader {

public:
    drachmaAppFileReader(const std::string& input) :
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
};

#endif
