#ifndef LEPTON_RR_PARAMS_H
#define LEPTON_RR_PARAMS_H

#include <iostream>
#include <unordered_map>
#include <vector>

class rrParam;

using rr_module_ip_map_t = std::unordered_map<unsigned, std::vector<unsigned>>;
using rr_params_map_t = std::unordered_map<unsigned, rrParam>;

// Container of parameters relating to a single RR (i.e. reconfigurable region).  Keeps track of
// how many modules are present within the RR and which IPs can be supported by each individual
// module.
class rrParam {
	rr_module_ip_map_t module_id_to_ip_ids_map_;

public:
	rrParam();
	rrParam(unsigned first_module_id, std::vector<unsigned> first_module_ip_ids) ;

	void assignIpsToModule(unsigned module_id, std::vector<unsigned> ip_ids);
	void addModuleIpPair(unsigned module_id, unsigned ip_id);
	unsigned getModuleCount() const;
	std::vector<unsigned> getIpIdsForModule(unsigned module_id) const;
	rr_module_ip_map_t _getModuleIdToIpIdsMap() const;
};

#endif
