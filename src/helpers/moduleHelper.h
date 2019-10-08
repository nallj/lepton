#ifndef MODULE_HELPER_H
#define MODULE_HELPER_H

#include <memory>        // shared_ptr
#include <unordered_map> // unordered_map
#include <utility>       // make_pair, move
#include <vector>        // vector

#include "debugHelper.h"
#include "../core/availableModule.h"
// #include "../parameters/parameters.h"
#include "../parameters/srParam.h"
#include "../parameters/rrParam.h"

// Debug message controls.
#define DEBUG_IP_TO_REGIONS false

struct moduleHelper {

  // void buildRegionToAvailableModuleVectors(
  //     region_to_modules_map_t& available_sr_modules,
  //     const sr_params_map_t& sr_params_map,
  //     region_to_modules_map_t& available_rr_modules,
  //     const rr_params_map_t& rr_params_map
  // );

  static region_to_modules_map_t buildSrToAvailableModuleMap(const sr_params_map_t &sr_params_map);
  static region_to_modules_map_t buildRrToAvailableModuleMap(const rr_params_map_t &rr_params_map);

  // ip_to_capable_modules_map_t buildIpToModuleMaps(
  //     const sr_params_map_t& sr_params_map,
  //     region_to_modules_map_t& available_sr_modules,
  //     const rr_params_map_t& rr_params_map,
  //     region_to_modules_map_t& available_rr_modules
  // );

  static void buildIpToSrModuleMap(
    const sr_params_map_t &sr_params_map,
    region_to_modules_map_t &available_sr_modules,
    ip_to_capable_modules_map_t &containing_map
  );

  static void buildIpToRrModuleMap(
    const rr_params_map_t &rr_params_map,
    region_to_modules_map_t &available_rr_modules,
    ip_to_capable_modules_map_t &containing_map
  );
};

#endif
