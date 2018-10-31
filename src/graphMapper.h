#ifndef LEPTON_GRAPH_MAPPER_H
#define LEPTON_GRAPH_MAPPER_H

#include <deque>
#include <functional> // std::function
#include <iostream>
#include <limits>
#include <map>
#include <utility>
#include <vector>

#include <boost/algorithm/string/trim.hpp>

#include "applicationTrace.h"
#include "availableModule.h"
#include "fileReader.h"
#include "graphNode.h"
#include "mapper.h"
#include "parameters/parameterParser.h"
#include "parameters/parameters.h"



class graphMapper {

	public:
		graphMapper(std::string input_file);

	private:
		void countRegionsAndModules(fileReader app_file_handler);

		void collectAllParamMapsFromConfigFile(
			std::vector<std::string> &param_data,
			std::vector<ipParams> &ip_params,
			std::vector<srParams> &sr_params,
			std::vector<rrParams> &rr_params
		);

		void formGraphsFromTgffFile(std::string input_file, std::vector<graph*> &graphs);
		void markGraphTasksWithIps(std::vector<graph*> &graphs, unsigned ip_count);
		void markGraphTasksWithIpsRecursive(graphNode* node, unsigned ip_count);
		void mapRegionsToGraphNodesAndProduceTraces(
			std::vector<graph*> &graphs,
			std::vector<srParams> &sr_params,
			std::vector<rrParams*> &rr_params,
			std::vector<ipParams> &ip_params,
			bool use_random_else_least_cost
		);


		std::string input_file_;

		std::vector<std::string> t2d_simple_params_ {
			"tgff file",
			"drachma app file"
			//"region to ip mapping"
		};
		std::vector<std::string> t2d_regex_params_ {
			"\\bip\\d+\\b \\blatency\\b[:] \\d+",
			"\\bip\\d+\\b \\bupper tolerance\\b[:] \\d+",
			"\\bip\\d+\\b \\blower tolerance\\b[:] \\d+",
			"\\bsr\\d+\\b \\bmodule \\d+\\b[:]\\s*ip\\d+",
			"\\brr\\d+\\b \\bmodule \\d+\\b[:]\\s*\\{\\s*ip\\d+\\s*(,\\s*ip\\d+)*\\s*\\}"
		};

		// unaltered, takes from 'wallet.h'
		std::vector<std::string> application_params_ {
			"name",
			"icap width",
			"icap speed",
			"prc speed",
			"static region speed"
		};
		std::vector<std::string> application_regex_ {
			"\\bsr\\d+ \\bmodule count\\b[:] \\d+",
			"\\brr\\d+\\b \\bbitstream size\\b[:] \\d+",
			"\\brr\\d+\\b \\bmodule \\d+ speed\\b[:] \\d+[.]\\d{1,2}"
		};

		unsigned sr_count_;
		std::vector<unsigned> sr_module_counts_;

		unsigned rr_count_;
		std::vector<unsigned> rr_module_counts_;
};

#endif
