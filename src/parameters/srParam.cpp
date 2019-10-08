#include "srParam.h"

srParam::srParam() { }

// Use when the first module-IP pair is known.
srParam::srParam(unsigned first_module_id, unsigned first_module_ip_id) {
  module_id_to_ip_id_map_.insert(std::pair<unsigned, unsigned>(first_module_id, first_module_ip_id));
}


void srParam::assignIpIdToModule(unsigned module_id, unsigned ip_id) {
  module_id_to_ip_id_map_[module_id] = ip_id;
}

unsigned srParam::getModuleCount() const {
  return module_id_to_ip_id_map_.size();
}

// Used exclusively within debugging code.
unsigned srParam::getIpIdForModule(unsigned module_id) {
  return module_id_to_ip_id_map_[module_id];
}

sr_module_ip_map_t srParam::getModuleIdToIpIdMap() const {
  return module_id_to_ip_id_map_;
}
