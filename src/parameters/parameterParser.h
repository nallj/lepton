#ifndef LEPTON_PARAMETER_PARSER_2_H
#define LEPTON_PARAMETER_PARSER_2_H

#include <utility>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "../files/specificFileReaders.h"

struct parsedFileContents {

  std::unordered_multimap<std::string, std::string> params_map;
  std::vector<std::string> data;
};

struct regionAndModuleCounts {

  unsigned sr_count_;
  unsigned rr_count_;
  std::vector<unsigned> sr_module_counts_;
  std::vector<unsigned> rr_module_counts_;

  regionAndModuleCounts() : sr_count_(0), rr_count_(0) {}
};

// Collection of functions that use the file handler to parse input files for relevant parameters.
struct parameterParser {

  parsedFileContents parseLeptonSpecificationFile(const std::string &spec_file_path) const;
  regionAndModuleCounts countRegionsAndModules(const std::string &app_file_path) const;
};

#endif
