#ifndef LEPTON_DEBUG_HELPER_H
#define LEPTON_DEBUG_HELPER_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "availableModule.h"
#include "graph/graph.h"
#include "graph/graphNode.h"
#include "parameters/parameterBuilder.h"
#include "parameters/parameters.h"

struct allParamMaps;

struct debugHelper {

    // Debug parameterBuilder.
    void debugCollectConfigParams(const allParamMaps& all_params) const;

    // Debug graphHandler.
    void debugFormGraphs(const std::vector<std::shared_ptr<graph>>& graphs) const;
    void debugMarkGraphs(const std::vector<std::shared_ptr<graph>>& graphs) const;

    // Debug graphMapper.
    void debugMapRegions(const std::vector<std::shared_ptr<graph>>& graphs) const;

    // Debug moduleHelper.
    void debugIpToRegions(const ip_to_capable_modules_map_t& ip_to_capable_modules_dictionary) const;
};

#endif
