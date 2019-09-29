#ifndef LEPTON_PARAMETERS_H
#define LEPTON_PARAMETERS_H

#include <iostream>
#include <unordered_map>
#include <vector>

struct ipParams;
struct srParams;
struct rrParams;

using sr_module_ip_map_t = std::unordered_map<unsigned, unsigned>;
using rr_module_ip_map_t = std::unordered_map<unsigned, std::vector<unsigned>>;
using ip_params_map_t = std::unordered_map<unsigned, ipParams>;
using sr_params_map_t = std::unordered_map<unsigned, srParams>;
using rr_params_map_t = std::unordered_map<unsigned, rrParams>;

// Container of parameters relating to a single type of IP (i.e. intellectual property).
struct ipParams {
	unsigned latency_;
	unsigned upper_tolerance_;
	unsigned lower_tolerance_;
};

// Container of parameters relating to a single SR (i.e. static region).  Keeps track of how many
// modules are present within the SR and which IP is set to each individual module.
class srParams {
	sr_module_ip_map_t module_id_to_ip_id_map_;

public:
	srParams() {}

	// Use when the first module-IP pair is known.
	srParams(unsigned first_module_id, unsigned first_module_ip_id) {

		module_id_to_ip_id_map_.insert(std::pair<unsigned, unsigned>(first_module_id, first_module_ip_id));
	}


	void assignIpIdToModule(unsigned module_id, unsigned ip_id) {
		module_id_to_ip_id_map_[module_id] = ip_id;
	}

	unsigned getModuleCount() const {
		return module_id_to_ip_id_map_.size();
	}

	// Used exclusively within debugging code.
	unsigned getIpIdForModule(unsigned module_id) {
		return module_id_to_ip_id_map_[module_id];
	}

	sr_module_ip_map_t getModuleIdToIpIdMap() const {
		return module_id_to_ip_id_map_;
	}
};

// Container of parameters relating to a single RR (i.e. reconfigurable region).  Keeps track of
// how many modules are present within the RR and which IPs can be supported by each individual
// module.
class rrParams {
	rr_module_ip_map_t module_id_to_ip_ids_map_;

public:
	rrParams() {}

	// Use when the first module-IPs pair is known.
	rrParams(unsigned first_module_id, std::vector<unsigned> first_module_ip_ids) {

		module_id_to_ip_ids_map_.insert(std::pair<unsigned, std::vector<unsigned>>(first_module_id, first_module_ip_ids));
	}


	void assignIpsToModule(unsigned module_id, std::vector<unsigned> ip_ids) {
		
		//module_id_to_ip_ids_map_[module_id] = ip_ids;

		if (keyInMap(module_id_to_ip_ids_map_, module_id)) {

			std::cout << "   assignIpsToModule ASSIGN " << module_id << " with " << module_id_to_ip_ids_map_.size() << " things\n";
			module_id_to_ip_ids_map_[module_id] = ip_ids;
			std::cout << "                now with " << module_id_to_ip_ids_map_.size() << " things\n";
		} else {
			std::cout << "   assignIpsToModule NEW " << module_id << " with " << module_id_to_ip_ids_map_.size() << " things\n";
			module_id_to_ip_ids_map_.insert(std::pair<unsigned, std::vector<unsigned>>(module_id, ip_ids));
			std::cout << "                now with " << module_id_to_ip_ids_map_.size() << " things\n";
		}

	}

	void addModuleIpPair(unsigned module_id, unsigned ip_id) {

		if (keyInMap(module_id_to_ip_ids_map_, module_id)) {
			module_id_to_ip_ids_map_[module_id].push_back(ip_id);
		} else {
			auto ip_ids = std::vector<unsigned>();
			ip_ids.push_back(ip_id);
			module_id_to_ip_ids_map_.insert(std::pair<unsigned, std::vector<unsigned>>(module_id, ip_ids));
		}
	}

	unsigned getModuleCount() const {
		return module_id_to_ip_ids_map_.size();
	}

	// Used exclusively within debugging code.
	std::vector<unsigned> getIpIdsForModule(unsigned module_id) const {
		return module_id_to_ip_ids_map_.at(module_id);
	}

	// Underscored: Consider forbidding use outside of debugging.
	rr_module_ip_map_t _getModuleIdToIpIdsMap() const {
		return module_id_to_ip_ids_map_;
	}


	template<typename TKey, typename TVal>
	bool keyInMap(const std::unordered_map<TKey, TVal>& map, const TKey& key) {
		return map.find(key) != map.end();
	}

};

#endif
