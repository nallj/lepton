#ifndef LEPTON_SR_PARAMS_H
#define LEPTON_SR_PARAMS_H

#include <iostream>
#include <unordered_map>
#include <vector>

class srParam;

using sr_module_ip_map_t = std::unordered_map<unsigned, unsigned>;
using sr_params_map_t = std::unordered_map<unsigned, srParam>;

// Container of parameters relating to a single SR (static region).  Keeps track of how many
// modules are present within the SR and which IP is set to each individual module.
class srParam {
	sr_module_ip_map_t module_id_to_ip_id_map_;

public:
	srParam();
	srParam(unsigned first_module_id, unsigned first_module_ip_id);

	void assignIpIdToModule(unsigned module_id, unsigned ip_id);
	unsigned getModuleCount() const;
	unsigned getIpIdForModule(unsigned module_id);
	sr_module_ip_map_t getModuleIdToIpIdMap() const;
};

#endif
