
#include "parameterParser.h"


parsedFileContents parameterParser::parseLeptonSpecificationFile(const std::string& spec_file_path) const {

	// Read in the Lepton specification file.
	//auto file_handler = fileReader(spec_file_path, lepton_simple_params, lepton_regex_params);
	auto file_handler = leptonSpecFileReader(spec_file_path);

	if (!file_handler.isFileValid()) {
		throw std::invalid_argument("Supplied Lepton specification file is either corrupt or has an invalid structure.");
	}

	// Assembly the parameters before returning.
	parsedFileContents parsed_file_contents = { file_handler.getParamsMap(), file_handler.getData() };

	// Return the assembled parameters.
	//return std::pair<std::unordered_multimap<std::string, std::string>, std::vector<std::string>>();
	return parsed_file_contents;
}

regionAndModuleCounts parameterParser::countRegionsAndModules(const std::string& app_file_path) const {

	// Read the Drachma application file for how many static/reconfigurable regions will be present.
	//auto file_handler = fileReader(app_file_path, application_params, application_regex);
	auto file_handler = drachmaAppFileReader(app_file_path);

    if (!file_handler.isFileValid()) {
		throw std::invalid_argument("Supplied Drachma application file is either corrupt or has an invalid structure.");
	}

	regionAndModuleCounts counts;
	std::vector<unsigned>::iterator it;

	unsigned region_id_end_index, region_id, region_id_plus_1, current_rr_module_count;
	std::string region_id_str, module_id_str;
	unsigned module_id_start_index, module_id_end_index, module_id, module_id_plus_1;

	// Start parsing the arbitrary amounts of static and reconfigurable regions.
	std::vector<std::string> dynamically_declared_params = file_handler.getData();
	for (int i = 0; i < dynamically_declared_params.size(); i++) {

		// Get the parameter and the corresponding argument.
		std::string param = dynamically_declared_params[i].substr(0, dynamically_declared_params[i].find(":"));
		std::string arg = dynamically_declared_params[i].substr(dynamically_declared_params[i].find(":") + 2);

		// Handle static region parameters.
		if (param.substr(0, 2) == "sr") {

			region_id_end_index = param.find(" ");
			region_id_str = param.substr(2, region_id_end_index - 2);

			region_id = std::stoul(region_id_str);
			region_id_plus_1 = region_id + 1;

			// Record count based off of largest static region ID that is found.
			if (region_id_plus_1 > counts.sr_count_) {
				counts.sr_count_ = region_id_plus_1;
			}

			it = counts.sr_module_counts_.begin() + region_id;
			counts.sr_module_counts_.insert(it, std::stoul(arg));
		}

		// Handle reconfigurable region parameters.
		if (param.substr(0, 2) == "rr") {

			region_id_end_index = param.find(" ");
			region_id_str = param.substr(2, region_id_end_index - 2);

			region_id = std::stoul(region_id_str);
			region_id_plus_1 = region_id + 1;

			// Record region count based off of largest reconfigurable region ID that is found.
			if (region_id_plus_1 > counts.rr_count_) {
				counts.rr_count_ = region_id_plus_1;
			}

			// If an entry has not been added for this RR, add one first before proceeding.
			if (counts.rr_module_counts_.size() < region_id_plus_1) {

				it = counts.rr_module_counts_.begin() + region_id;
				counts.rr_module_counts_.insert(it, 0);
			}

			current_rr_module_count = counts.rr_module_counts_.at(region_id);

			// Ignore lines concerning bitstream width.
			if (param.substr(region_id_end_index + 1, 3) != "bit") {

				module_id_start_index = param.find("module") + 7;
				module_id_end_index = param.find(" ", module_id_start_index);

				module_id_str = param.substr(module_id_start_index, module_id_end_index - module_id_start_index);

				module_id = std::stoul(module_id_str);
				module_id_plus_1 = module_id + 1;

				// Record module count based off of largest module ID that is found.
				if (current_rr_module_count < module_id_plus_1) {
					counts.rr_module_counts_.at(region_id) = module_id_plus_1;
				}
			}
		}

	}

	return counts;
}
