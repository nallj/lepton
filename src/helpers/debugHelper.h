#ifndef LEPTON_DEBUG_HELPER_H
#define LEPTON_DEBUG_HELPER_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "../core/availableModule.h"
#include "../graph/graph.h"
#include "../graph/graphNode.h"
#include "../parameters/parameterBuilder.h"
// #include "../parameters/parameters.h"

struct allParamMaps;

struct debugHelper {

  // Debug parameterBuilder.
  static void debugCollectConfigParams(const allParamMaps& all_params);

  // Debug graphHandler.
  static void debugFormGraphs(const graphs_t &graphs);
  static void debugMarkGraphs(const graphs_t &graphs);

  // Debug graphMapper.
  static void debugMapRegions(const graphs_t &graphs);

  // Debug moduleHelper.
  static void debugIpToRegions(const ip_to_capable_modules_map_t& ip_to_capable_modules_dictionary);
};

#endif
