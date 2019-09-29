#include "moduleHelper.h"

region_to_avail_modules_t moduleHelper::buildSrToAvailableModuleMap(
  const sr_params_map_t &sr_params_map
) const {

  region_to_avail_modules_t available_sr_modules_map;

  // Loop through each static region.
  for (auto &sr_it : sr_params_map) {

    const auto sr_id = sr_it.first;
    const auto sr_params = sr_it.second;

    auto empty_module_vector = std::vector<std::shared_ptr<availableModule>>();

    // Insert new entry in SR to available modules map.
    auto new_entry = std::make_pair(sr_id, std::move(empty_module_vector));
    available_sr_modules_map.insert(std::move(new_entry));

    // Get reference to new entry.
    auto &sr_entry = available_sr_modules_map[sr_id];

    //std::vector<std::shared_ptr<availableModule>> region_modules;

    // Loop through each static region module and create corresponding module objects.
    for (auto &module_it : sr_params.getModuleIdToIpIdMap()) {
      //region_modules.push_back(new availableModule(sr_id, module_it.first, true));
      sr_entry.push_back(std::shared_ptr<availableModule>(new availableModule(sr_id, module_it.first, true)));
    }
    // Store all of the modules for this static region.
    //available_sr_modules_map.push_back(region_modules);
  }

  return available_sr_modules_map;
}

region_to_avail_modules_t moduleHelper::buildRrToAvailableModuleMap(
  const rr_params_map_t &rr_params_map
) const {

  region_to_avail_modules_t available_rr_modules_map;

  // Loop through each reconfigurable region.
  for (auto &rr_it : rr_params_map) {

    const unsigned rr_id = rr_it.first;
    const auto rr_params = rr_it.second;

    auto empty_module_vector = std::vector<std::shared_ptr<availableModule>>();

    // Insert new entry in RR to available modules map.
    auto new_entry = std::pair<unsigned, std::vector<std::shared_ptr<availableModule>>>(
      rr_id,
      std::move(empty_module_vector)
    );
    available_rr_modules_map.insert(std::move(new_entry));

    // Get reference to new entry.
    auto &rr_entry = available_rr_modules_map[rr_id];

    //std::vector<std::shared_ptr<availableModule>>> region_modules;

    // Loop through each reconfigurable region module and create corresponding module objects.
    for (auto &entry_it : rr_params._getModuleIdToIpIdsMap()) {

      //auto module_id = entry_it.first;
      //auto ip_ids = entry_it.second;

      //region_modules.push_back(new availableModule(rr_id, module_it.first));
      //for (auto& module_it : entry_it.second) {
      //unsigned mod_id = module_it.first;
      rr_entry.push_back(std::shared_ptr<availableModule>(new availableModule(rr_id, entry_it.first)));
    }

    // Store all of the modules for this reconfigurable region.
    //available_rr_modules.push_back(region_modules);
  }

  return available_rr_modules_map;
}

void moduleHelper::buildIpToSrModuleMap(
  const sr_params_map_t &sr_params_map,
  region_to_avail_modules_t &available_sr_modules,
  ip_to_capable_modules_map_t &containing_map
) const {

  // Loop through each static region.
  for (const auto &sr_entry : sr_params_map) {

    auto sr_id = sr_entry.first;
    const auto sr_module_ip_ids = sr_entry.second.getModuleIdToIpIdMap();

    // Loop through each static module.
    for (auto &module_entry : sr_module_ip_ids) {

      auto ip_id = module_entry.first;
      auto target_available_sr_module = available_sr_modules[sr_id][ip_id];

      auto find_it = containing_map.find(ip_id);
      if (find_it == containing_map.end()) {

        std::vector<std::shared_ptr<availableModule>> single_sr_module_list;
        single_sr_module_list.push_back(target_available_sr_module);

        // Create the first entry relating to this IP.
        containing_map.insert(std::make_pair(ip_id, single_sr_module_list));
      } else {
        auto &sr_module_list = find_it->second;
        sr_module_list.push_back(target_available_sr_module);
      }
    }
  }

  // if (DEBUG_IP_TO_REGIONS) {
  //     auto debug_helper = debugHelper();
  //     debug_helper.debugIpToRegions(containing_map);
  // }
}

void moduleHelper::buildIpToRrModuleMap(
  const rr_params_map_t &rr_params_map,
  region_to_avail_modules_t &available_rr_modules,
  ip_to_capable_modules_map_t &containing_map
) const {

  // Loop through each region.
  for (const auto &rr_entry : rr_params_map) {

    const auto rr_id = rr_entry.first;
    const auto &rr_module_ip_ids = rr_entry.second._getModuleIdToIpIdsMap();

    // Loop through each module (ordered by module ID).
    for (auto &module_entry : rr_module_ip_ids) {

      const auto module_id = module_entry.first;
      auto ip_ids = rr_module_ip_ids.at(module_id);
      auto target_available_rr_module = available_rr_modules[rr_id][module_id];

      // Loop through each IP that can be programmed for this module.
      for (const auto ip_id : ip_ids) {

        auto find_it = containing_map.find(ip_id);
        if (find_it == containing_map.end()) {

          std::vector<std::shared_ptr<availableModule>> single_rr_module_list;
          single_rr_module_list.push_back(target_available_rr_module);

          // Create the first entry relating to this IP.
          containing_map.insert(std::make_pair(ip_id, single_rr_module_list));
        } else {
          auto &rr_module_list = find_it->second;
          rr_module_list.push_back(target_available_rr_module);
        }
      }
    }
  }

  if (DEBUG_IP_TO_REGIONS) {
    auto debug_helper = debugHelper();
    debug_helper.debugIpToRegions(containing_map);
  }
}
