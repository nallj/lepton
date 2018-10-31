#ifndef MODULE_HELPER_H
#define MODULE_HELPER_H

#include <memory> // unique_ptr
#include <unordered_map> // unordered_map
#include <utility> // make_pair, move
#include <vector> // vector

#include "../availableModule.h"
#include "../debugHelper.h"
#include "../parameters/parameters.h"

// Debug message controls.
#define DEBUG_IP_TO_REGIONS false

struct moduleHelper {

    // void buildRegionToAvailableModuleVectors(
    //     region_to_avail_modules_t& available_sr_modules,
    //     const sr_params_map_t& sr_params_map,
    //     region_to_avail_modules_t& available_rr_modules,
    //     const rr_params_map_t& rr_params_map
    // );

    region_to_avail_modules_t buildSrToAvailableModuleMap(const sr_params_map_t& sr_params_map) const;
    region_to_avail_modules_t buildRrToAvailableModuleMap(const rr_params_map_t& rr_params_map) const;

    // void buildIpToModuleDictionaries(
    //     ip_to_capable_modules_map_t& ip_to_capable_modules_dictionary,
    //     const sr_params_map_t& sr_params_map,
    //     region_to_avail_modules_t& available_sr_modules,
    //     const rr_params_map_t& rr_params_map,
    //     region_to_avail_modules_t& available_rr_modules
    // );

    // // // ip_to_capable_modules_map_t buildIpToSrModuleMap(
    // // //     const sr_params_map_t& sr_params_map,
    // // //     region_to_avail_modules_t& available_sr_modules
    // // // ) const;

    // // // ip_to_capable_modules_map_t buildIpToRrModuleMap(
    // // //     const rr_params_map_t& rr_params_map,
    // // //     region_to_avail_modules_t& available_rr_modules
    // // // ) const;
};

#endif