
#include "debugHelper.h"

void debugHelper::debugCollectConfigParams(const allParamMaps& all_params) const {

    const auto& ip_params = all_params.ip_params_map;
    const auto& sr_params = all_params.sr_params_map;
    const auto& rr_params = all_params.rr_params_map;

    const auto& ordered_sr_params = std::map<unsigned, srParams>(sr_params.begin(), sr_params.end());
    const auto& ordered_rr_params = std::map<unsigned, rrParams>(rr_params.begin(), rr_params.end());

    std::cout << "\n==============================================================================\n"
              << " >>> Now printing 'DEBUG_COLLECT_CONFIG_PARAMS' Debug Data\n\n";


    for (unsigned i = 0; i < ip_params.size(); i++) {
        const auto& ip_param = ip_params.at(i);
        std::cout << "IP#" << i << " <" << ip_param.latency_ << ", " << ip_param.upper_tolerance_ << ", " << ip_param.lower_tolerance_ << ">\n";
    }

    std::cout << "\nTHERE ARE " << ordered_sr_params.size() << " SRs TOTAL with module counts = { ";
    for (auto& entry_it : ordered_sr_params)
        std::cout << entry_it.second.getModuleCount() << ", ";
    std::cout << " }\n";


    //for (unsigned i = 0; i < sr_params.size(); i++) {
    for (const auto& entry_it : ordered_sr_params) {

        const auto sr_id = entry_it.first;
        const auto& sr_param_it = entry_it.second;

        const auto module_count = sr_param_it.getModuleCount();
        std::cout << "> SR " << sr_id << " has " << module_count << " Modules with the following respective IPs = { ";

        for (const auto& module_it : sr_param_it.getModuleIdToIpIdMap())
            std::cout << "ip" << module_it.second << ", ";

        //for (unsigned j = 0; j < module_count; j++)
        //    std::cout << "ip" << sr_param_it.getIpIdForModule(j) << ", ";

        std::cout << " }\n";
    }

    std::cout << "\nTHERE ARE " << ordered_rr_params.size() << " RRs TOTAL with module counts = { ";
    for (auto& entry_it : ordered_rr_params)
        std::cout << entry_it.second.getModuleCount() << ", ";
    std::cout << " }\n";

    //for (unsigned i = 0; i < rr_params.size(); i++) {
    for (const auto& entry_it : ordered_rr_params) {
        
        const auto rr_id = entry_it.first;
        const auto& rr_param_it = entry_it.second;

        //for (unsigned j = 0; j < rr_param_it.getModuleCount(); j++) {
        for (const auto& module_it : rr_param_it.getModuleIdToIpIdsMap()) {

            const auto module_id = module_it.first;
            const auto& ip_ids = module_it.second;

            std::cout << ">> RR " << rr_id << ", Module " << module_id << " has ";

            //auto ip_ids = rr_param_it.getIpIdsForModule(j);
            std::cout << "[" << ip_ids.size() << "] { ";

            //for (int k = 0; k < ip_ids.size(); k++) {
            for (auto ip_id : ip_ids)
                std::cout << "ip" << ip_id << ", ";
            //}

            std::cout << "}\n";
        }
    }

    std::cout << "\n >>> Finished printing 'DEBUG_COLLECT_CONFIG_PARAMS' Debug Data"
              << "\n==============================================================================\n";
}

void debugHelper::debugFormGraphs(const std::vector<graph>& graphs) const {

    std::cout << "\n==============================================================================\n"
              << " >>> Now printing 'DEBUG_FORM_GRAPHS' Debug Data\n\n";

    for (unsigned i = 0; i < graphs.size(); i++) {

        std:: cout << "> This is graph # " << i << " and it has nodes:\n";

        const auto& current_graph = graphs.at(i);
        const auto all_nodes = current_graph.getAllNodes();

        for (const auto& node_it : all_nodes) {
            std::cout << "\t" << node_it->getNodeId() << " (type " << node_it->getTaskTypeId() << ")";

            auto successor_nodes = node_it->getSuccessorNodes();

            if (successor_nodes.size() > 0)
                std::cout << "\n\t\twith successor nodes: ";
            else
                std::cout << " <no successor nodes>";

            for (const auto successor_node_it : successor_nodes)
                std::cout << successor_node_it->getNodeId() << ", ";

            std::cout << "\n";
        }

        std:: cout << "  And has the following top nodes:\n";

        for (const auto& node_it : current_graph.getAllTopLevelNodes())
            std::cout << "\t" << node_it->getNodeId() << " (" << node_it->getTaskTypeId() << ")\n";
    }

    std::cout << "\n >>> Finished printing 'DEBUG_FORM_GRAPHS' Debug Data"
              << "\n==============================================================================\n";
}

void debugHelper::debugMarkGraphs(const std::vector<graph>& graphs) const {

    std::cout << "\n==============================================================================\n"
              << " >>> Now printing 'DEBUG_MARK_GRAPHS' Debug Data\n\n";

    for (unsigned i = 0; i < graphs.size(); i++) {

        std:: cout << "> This is graph # " << i << " and it has nodes:\n";

        const auto all_nodes = graphs.at(i).getAllNodes();
        for (const auto& node_it : all_nodes)
            std::cout << "\t" << node_it->getNodeId() << " (IP" << node_it->getIpId() << ")\n";
    }

    std::cout << "\n >>> Finished printing 'DEBUG_MARK_GRAPHS' Debug Data"
              << "\n==============================================================================\n";
}

void debugHelper::debugMapRegions(const std::vector<graph>& graphs) const {

    std::cout << "\n==============================================================================\n"
              << " >>> Now printing 'DEBUG_MAP_REGIONS' Debug Data\n\n";

    for (unsigned i = 0; i < graphs.size(); i++) {

        std:: cout << "> This is graph # " << i << " and it has nodes:\n";

        const auto all_nodes = graphs.at(i).getAllNodes();
        for (const auto& node_it : all_nodes) {
            std::cout << "\t" << node_it->getNodeId() << " (ip" << node_it->getIpId() << " mapped to ";

            // SR/RR

            std::cout << ")\n";
        }
    }

    std::cout << "\n >>> Finished printing 'DEBUG_MAP_REGIONS' Debug Data"
              << "\n==============================================================================\n";
}

void debugHelper::debugIpToRegions(const ip_to_capable_modules_map_t& ip_to_capable_modules_dictionary) const {

    std::cout << "\n==============================================================================\n"
              << " >>> Now printing 'DEBUG_IP_TO_REGIONS' Debug Data\n\n";

    // Print unsigned IP-to-module dictionary contents.
    for (auto dict_it = ip_to_capable_modules_dictionary.begin(); dict_it != ip_to_capable_modules_dictionary.end(); ++dict_it) {
        std::cout << "IP" << dict_it->first << " can be used in: { ";

        auto modules = dict_it->second;
        for (auto vect_it = modules->begin(); vect_it != modules->end(); ++vect_it)

            std::cout << ((*vect_it)->getIsStatic() ? "sr" : "rr")
                        << (*vect_it)->getRegionId()
                        << "m" << (*vect_it)->getModuleId() << ", ";

        std::cout << "}\n";
    }

    std::cout << "\n >>> Finished printing 'DEBUG_IP_TO_REGIONS' Debug Data"
              << "\n==============================================================================\n";
}