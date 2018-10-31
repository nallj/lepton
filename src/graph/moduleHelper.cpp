#include "moduleHelper.h"

// void moduleHelper::buildRegionToAvailableModuleVectors(
//     region_to_avail_modules_t& available_sr_modules,
//     const sr_params_map_t& sr_params_map,
//     region_to_avail_modules_t& available_rr_modules,
//     const rr_params_map_t& rr_params_map
// ) {

//     // loop through each static region (ordered by region ID)
//     // for (unsigned i = 0; i < sr_params.size(); i++) {

//     //     std::vector<availableModule*> region_modules;

//     //     // loop through each static region module (ordered by module ID)
//     //     for (unsigned j = 0; j < sr_params[i].getModuleCount(); j++)
//     //         region_modules.push_back(new availableModule(i, j, true));

//     //     // store all of the modules for this static region
//     //     available_sr_modules.push_back(region_modules);
//     // }

//     // Loop through each static region.
//     for (auto& sr_it : sr_params_map) {

//         const unsigned sr_id = sr_it.first;
//         const auto sr_params = sr_it.second;

//         std::vector<availableModule*> region_modules;

//         // Loop through each static region module and create corresponding module objects.
//         for (auto& module_it : sr_params.getModuleIdToIpIdMap())
//             region_modules.push_back(new availableModule(sr_id, module_it.first, true));

//         // Store all of the modules for this static region.
//         available_sr_modules.push_back(region_modules);
//     }

//     // loop through each reconfigurable region (ordered by region ID)
//     // for (unsigned i = 0; i < rr_params.size(); i++) {

//     //     std::vector<availableModule*> region_modules;

//     //     // loop through each reconfigurable region module (ordered by module ID)
//     //     for (unsigned j = 0; j < rr_params[i].getModuleCount(); j++)
//     //         region_modules.push_back(new availableModule(i, j));

//     //     // store all of the modules for this reconfigurable region
//     //     available_rr_modules.push_back(region_modules);
//     // }

//     // Loop through each reconfigurable region.
//     for (auto &rr_it : rr_params_map) {

//         const unsigned rr_id = rr_it.first;
//         const auto rr_params = rr_it.second;

//         std::vector<availableModule*> region_modules;

//         // Loop through each reconfigurable region module and create corresponding module objects.
//         for (auto &module_it : rr_params.getModuleIdToIpIdsMap())
//             region_modules.push_back(new availableModule(rr_id, module_it.first));

//         // Store all of the modules for this reconfigurable region.
//         available_rr_modules.push_back(region_modules);
//     }

// }


region_to_avail_modules_t moduleHelper::buildSrToAvailableModuleMap(const sr_params_map_t& sr_params_map) const {

    region_to_avail_modules_t available_sr_modules_map;

    // Loop through each static region.
    for (auto& sr_it : sr_params_map) {

        const auto sr_id = sr_it.first;
        const auto sr_params = sr_it.second;

        auto empty_module_vector = std::vector<std::unique_ptr<availableModule>>();                                                                             

        // Insert new entry in SR to available modules map.
        auto new_entry = std::make_pair(sr_id, std::move(empty_module_vector));
        available_sr_modules_map.insert(std::move(new_entry));

        // Get reference to new entry.
        auto& sr_entry = available_sr_modules_map[sr_id];

        //std::vector<std::unique_ptr<availableModule>> region_modules;

        // Loop through each static region module and create corresponding module objects.
        for (auto& module_it : sr_params.getModuleIdToIpIdMap())
            //region_modules.push_back(new availableModule(sr_id, module_it.first, true));
            sr_entry.push_back(std::unique_ptr<availableModule>(new availableModule(sr_id, module_it.first, true)));

        // Store all of the modules for this static region.
        //available_sr_modules_map.push_back(region_modules);
    }

    return available_sr_modules_map;
}

region_to_avail_modules_t moduleHelper::buildRrToAvailableModuleMap(const rr_params_map_t& rr_params_map) const {

    region_to_avail_modules_t available_rr_modules_map;
    
    // Loop through each reconfigurable region.
    for (auto& rr_it : rr_params_map) {

        const unsigned rr_id = rr_it.first;
        const auto rr_params = rr_it.second;

        auto empty_module_vector = std::vector<std::unique_ptr<availableModule>>();

        // Insert new entry in RR to available modules map.
        auto new_entry = std::pair<unsigned, std::vector<std::unique_ptr<availableModule>>>(rr_id, std::move(empty_module_vector));
        available_rr_modules_map.insert(std::move(new_entry));

        // Get reference to new entry.
        auto& rr_entry = available_rr_modules_map[rr_id];

        //std::vector<availableModule*> region_modules;

        // Loop through each reconfigurable region module and create corresponding module objects.
        for (auto& entry_it : rr_params.getModuleIdToIpIdsMap())

            //auto module_id = entry_it.first;
            //auto ip_ids = entry_it.second;

            //region_modules.push_back(new availableModule(rr_id, module_it.first));
            //for (auto& module_it : entry_it.second) {
                //unsigned mod_id = module_it.first;
                rr_entry.push_back(std::unique_ptr<availableModule>(new availableModule(rr_id, entry_it.first)));
            //}

        // Store all of the modules for this reconfigurable region.
        //available_rr_modules.push_back(region_modules);
    }

    return available_rr_modules_map;
}
/*
ip_to_capable_modules_map_t moduleHelper::buildIpToSrModuleMap(
    const sr_params_map_t& sr_params_map,
    region_to_avail_modules_t& available_sr_modules
) const {

    ip_to_capable_modules_map_t ip_to_capable_modules_map;

    // Loop through each region (ordered by region ID).
    //for (unsigned i = 0; i < sr_params_map.size() || i < rr_params_map.size(); i++) {
    for (const auto& sr_entry : sr_params_map) {

        const auto sr_module_ip_ids = sr_entry.second.getModuleIdToIpIdMap();

        // Loop through each module (ordered by module ID).
        //for (int j = 0; j < sr_module_ip_ids.size(); j++) {
        for (auto& module_entry : sr_module_ip_ids) {

            auto ip_id = module_entry.first;
            auto target_available_sr_module = available_sr_modules[i][j];

            auto find_it = ip_to_capable_modules_map.find(ip_id);
            if (find_it == ip_to_capable_modules_map.end()) {

                auto single_sr_module_list = new std::vector<availableModule*>();
                single_sr_module_list->push_back(target_available_sr_module);

                // Create the first entry relating to this IP.
                ip_to_capable_modules_map.insert(std::pair<unsigned, std::vector<availableModule*>*>(ip_id, single_sr_module_list));

            } else {
                auto sr_module_list = find_it->second;
                sr_module_list->push_back(target_available_sr_module);
            }


        } // for: j (all modules in a single region)
    } // for: i (all regions)


    if (DEBUG_IP_TO_REGIONS) {
        auto debug_helper = debugHelper();
        debug_helper.debugIpToRegions(ip_to_capable_modules_map);
    }

    return ip_to_capable_modules_map;
}

ip_to_capable_modules_map_t moduleHelper::buildIpToRrModuleMap(
    const rr_params_map_t& rr_params_map,
    region_to_avail_modules_t& available_rr_modules
) const {

    ip_to_capable_modules_map_t ip_to_capable_modules_map;

    // Loop through each region (ordered by region ID).
    //for (unsigned i = 0; i < sr_params_map.size() || i < rr_params_map.size(); i++) {
    for () {

        bool remaining_srs = (i < sr_params_map.size());
        bool remaining_rrs = (i < rr_params_map.size());

        sr_module_ip_map_t sr_module_ip_ids;
        rr_module_ip_map_t rr_module_ip_ids;

        if (remaining_srs)
            sr_module_ip_ids = sr_params_map.at(i).getModuleIdToIpIdMap();

        if (remaining_rrs)
            rr_module_ip_ids = rr_params_map.at(i).getModuleIdToIpIdsMap();

        // Loop through each module (ordered by module ID).
        for (int j = 0; j < sr_module_ip_ids.size() || j < rr_module_ip_ids.size(); j++) {

            bool remaining_sr_modules = (j < sr_module_ip_ids.size());
            bool remaining_rr_modules = (j < rr_module_ip_ids.size());

            // There are modules remaining in this static region.
            if (remaining_sr_modules) {

                unsigned ip_id = sr_module_ip_ids.at(j);
                auto target_available_sr_module = available_sr_modules[i][j];

                auto find_it = ip_to_capable_modules_map.find(ip_id);
                if (find_it == ip_to_capable_modules_map.end()) {

                    auto single_sr_module_list = new std::vector<availableModule*>();
                    single_sr_module_list->push_back(target_available_sr_module);

                    // Create the first entry relating to this IP.
                    ip_to_capable_modules_map.insert(std::pair<unsigned, std::vector<availableModule*>*>(ip_id, single_sr_module_list));

                } else {
                    auto sr_module_list = find_it->second;
                    sr_module_list->push_back(target_available_sr_module);
                }

            }

            // There are modules remaining in this reconfigurable region.
            if (remaining_rr_modules) {

                auto ip_ids = rr_module_ip_ids.at(j);
                auto target_available_rr_module = available_rr_modules[i][j];

                // Loop through each IP that can be programmed for this module.
                for (unsigned k = 0; k < ip_ids.size(); k++) {

                    unsigned ip_id = ip_ids[k];

                    auto find_it = ip_to_capable_modules_map.find(ip_id);
                    if (find_it == ip_to_capable_modules_map.end()) {

                        auto single_rr_module_list = new std::vector<availableModule*>();
                        single_rr_module_list->push_back(target_available_rr_module);

                        // Create the first entry relating to this IP.
                        ip_to_capable_modules_map.insert(std::pair<unsigned, std::vector<availableModule*>*>(ip_id, single_rr_module_list));

                    } else {
                        auto rr_module_list = find_it->second;
                        rr_module_list->push_back(target_available_rr_module);
                    }

                } // for: k (all IPs for one module)
            }

        } // for: j (all modules in a single region)
    } // for: i (all regions)


    if (DEBUG_IP_TO_REGIONS) {
        auto debug_helper = debugHelper();
        debug_helper.debugIpToRegions(ip_to_capable_modules_map);
    }

    return ip_to_capable_modules_map;
}*/

// void moduleHelper::buildIpToModuleDictionaries(
//     ip_to_capable_modules_map_t& ip_to_capable_modules_dictionary,
//     const sr_params_map_t& sr_params_map,
//     region_to_avail_modules_t& available_sr_modules,
//     const rr_params_map_t& rr_params_map,
//     region_to_avail_modules_t& available_rr_modules
// ) {

//     // Loop through each region (ordered by region ID).
//     for (unsigned i = 0; i < sr_params_map.size() || i < rr_params_map.size(); i++) {

//         bool remaining_srs = (i < sr_params_map.size());
//         bool remaining_rrs = (i < rr_params_map.size());

//         sr_module_ip_map_t sr_module_ip_ids;
//         rr_module_ip_map_t rr_module_ip_ids;

//         if (remaining_srs)
//             sr_module_ip_ids = sr_params_map.at(i).getModuleIdToIpIdMap();

//         if (remaining_rrs)
//             rr_module_ip_ids = rr_params_map.at(i).getModuleIdToIpIdsMap();

//         // Loop through each module (ordered by module ID).
//         for (int j = 0; j < sr_module_ip_ids.size() || j < rr_module_ip_ids.size(); j++) {

//             bool remaining_sr_modules = (j < sr_module_ip_ids.size());
//             bool remaining_rr_modules = (j < rr_module_ip_ids.size());

//             // There are modules remaining in this static region.
//             if (remaining_sr_modules) {

//                 unsigned ip_id = sr_module_ip_ids.at(j);
//                 auto target_available_sr_module = available_sr_modules[i][j];

//                 auto find_it = ip_to_capable_modules_dictionary.find(ip_id);
//                 if (find_it == ip_to_capable_modules_dictionary.end()) {

//                     auto single_sr_module_list = new std::vector<availableModule*>();
//                     single_sr_module_list->push_back(target_available_sr_module);

//                     // Create the first entry relating to this IP.
//                     ip_to_capable_modules_dictionary.insert(std::pair<unsigned, std::vector<availableModule*>*>(ip_id, single_sr_module_list));

//                 } else {
//                     auto sr_module_list = find_it->second;
//                     sr_module_list->push_back(target_available_sr_module);
//                 }

//             }

//             // There are modules remaining in this reconfigurable region.
//             if (remaining_rr_modules) {

//                 auto ip_ids = rr_module_ip_ids.at(j);
//                 auto target_available_rr_module = available_rr_modules[i][j];

//                 // Loop through each IP that can be programmed for this module.
//                 for (unsigned k = 0; k < ip_ids.size(); k++) {

//                     unsigned ip_id = ip_ids[k];

//                     auto find_it = ip_to_capable_modules_dictionary.find(ip_id);
//                     if (find_it == ip_to_capable_modules_dictionary.end()) {

//                         auto single_rr_module_list = new std::vector<availableModule*>();
//                         single_rr_module_list->push_back(target_available_rr_module);

//                         // Create the first entry relating to this IP.
//                         ip_to_capable_modules_dictionary.insert(std::pair<unsigned, std::vector<availableModule*>*>(ip_id, single_rr_module_list));

//                     } else {
//                         auto rr_module_list = find_it->second;
//                         rr_module_list->push_back(target_available_rr_module);
//                     }

//                 } // for: k (all IPs for one module)
//             }

//         } // for: j (all modules in a single region)
//     } // for: i (all regions)


//     if (DEBUG_IP_TO_REGIONS) {
//         auto debug_helper = debugHelper();
//         debug_helper.debugIpToRegions(ip_to_capable_modules_dictionary);
//     }
// }