#include "rrParam.h"

template<typename TKey, typename TVal>
bool keyInMap(const std::unordered_map<TKey, TVal>& map, const TKey& key) {
	return map.find(key) != map.end();
}

rrParam::rrParam() {}

// Use when the first module-IPs pair is known.
rrParam::rrParam(unsigned first_module_id, std::vector<unsigned> first_module_ip_ids) {

	module_id_to_ip_ids_map_.insert(std::pair<unsigned, std::vector<unsigned>>(first_module_id, first_module_ip_ids));
}


void rrParam::assignIpsToModule(unsigned module_id, std::vector<unsigned> ip_ids) {
	
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

void rrParam::addModuleIpPair(unsigned module_id, unsigned ip_id) {

	if (keyInMap(module_id_to_ip_ids_map_, module_id)) {
		module_id_to_ip_ids_map_[module_id].push_back(ip_id);
	} else {
		auto ip_ids = std::vector<unsigned>();
		ip_ids.push_back(ip_id);
		module_id_to_ip_ids_map_.insert(std::pair<unsigned, std::vector<unsigned>>(module_id, ip_ids));
	}
}

unsigned rrParam::getModuleCount() const {
	return module_id_to_ip_ids_map_.size();
}

// Used exclusively within debugging code.
std::vector<unsigned> rrParam::getIpIdsForModule(unsigned module_id) const {
	return module_id_to_ip_ids_map_.at(module_id);
}

// Underscored: Consider forbidding use outside of debugging.
rr_module_ip_map_t rrParam::_getModuleIdToIpIdsMap() const {
	return module_id_to_ip_ids_map_;
}
