#ifndef LEPTON_PARAMETER_BUILDER_H
#define LEPTON_PARAMETER_BUILDER_H

#include <boost/algorithm/string/trim.hpp>
#include <string> // string
#include <unordered_map> // unordered_map
#include <utility> // pair
#include <vector> // vector

#include "../debugHelper.h"
#include "parameters.h"

// Debug message controls.
#define DEBUG_COLLECT_CONFIG_PARAMS false

struct allParamMaps {
    //std::vector<ipParams> ip_params;
    ip_params_map_t ip_params_map;
    sr_params_map_t sr_params_map;
    rr_params_map_t rr_params_map;
};

// Collection of functions that receives a given parameter and argument, assembles a corresponding
// parameter object, and adds it to an existing vector of the aforementioned object type.
class parameterBuilder {
    std::vector<unsigned> getIpIdsFromString(std::string ip_ids_string);

    void parseIpParam(
        std::size_t ip_param_position,
        const std::string& param,
        const std::string& arg,
        ip_params_map_t& ip_params_map
    );

    void parseSrParam(
        std::size_t sr_param_position,
        const std::string& param,
        const std::string& arg,
        sr_params_map_t& sr_params_map
    );

    void parseRrParam(
        std::size_t rr_param_position,
        const std::string& param,
        const std::string& arg,
        rr_params_map_t& rr_params_map
    );

    // void parseSrParam(
    //     std::size_t sr_param_position,
    //     const std::string& param,
    //     const std::string& arg,
    //     std::vector<srParams>& sr_params
    // );

    // void parseRrParam(
    //     std::size_t rr_param_position,
    //     const std::string& param,
    //     const std::string& arg,
    //     std::vector<rrParams>& rr_params
    // );

public:
    allParamMaps collectAllParamMapsFromConfigFile(const std::vector<std::string>& param_data);
    // void collectAllParamMapsFromConfigFile(
    //     std::vector<std::string> &param_data,
    //     std::vector<ipParams> &ip_params,
    //     std::vector<srParams> &sr_params,
    //     std::vector<rrParams> &rr_params
    // );
};

#endif