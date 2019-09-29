
#include "parameterBuilder.h"

/* DECLARATIONS */

std::pair<unsigned, unsigned> getRegionAndModuleId(
  const std::string &param,
  std::size_t param_start_position
);

template <typename TKey, typename TVal>
bool keyInMap(const std::unordered_map<TKey, TVal> &map, const TKey &key);

/* PUBLIC */

allParamMaps parameterBuilder::collectAllParamMapsFromConfigFile(
    const std::vector<std::string> &param_data
) {

  allParamMaps all_params;

  auto &ip_params = all_params.ip_params_map;
  auto &sr_params = all_params.sr_params_map;
  auto &rr_params = all_params.rr_params_map;

  //for (unsigned i = 0; i < param_data.size(); i++) {
  for (const auto &param_string : param_data) {
    std::size_t colon_position = param_string.find(":");

    // Grab parameter and corresponding argument from the data string.
    std::string param = param_string.substr(0, colon_position);
    std::string arg = param_string.substr(colon_position + 1);

    // Trim the argument of any whitespace.
    boost::trim(arg);

    std::size_t space_position;

    std::size_t ip_param_position = param.find("ip");
    if (ip_param_position != std::string::npos) {

      // Parse as an IP parameter and skip remaining checks.
      parseIpParam(ip_param_position, param, arg, ip_params);
      continue;
    }

    std::size_t sr_param_position = param.find("sr");
    if (sr_param_position != std::string::npos) {

      // Parse as a SR parameter and skip final check.
      parseSrParam(sr_param_position, param, arg, sr_params);
      continue;
    }

    std::size_t rr_param_position = param.find("rr");
    if (rr_param_position != std::string::npos) {

      // Parse as a RR parameter.
      parseRrParam(rr_param_position, param, arg, rr_params);
    }
  }

  // DEBUG MESSAGES
  if (DEBUG_COLLECT_CONFIG_PARAMS) {
    auto debug_helper = debugHelper();
    debug_helper.debugCollectConfigParams(all_params);
  }

  return all_params;
}


/* PRIVATE */

void parameterBuilder::parseIpParam(
    std::size_t ip_param_position,
    const std::string &param,
    const std::string &arg,
    ip_params_map_t &ip_params_map
) {
  std::size_t space_position = param.find(" ");
  std::string ip_id_string = param.substr(ip_param_position + 2, space_position - ip_param_position - 2);

  unsigned ip_id = std::stoul(ip_id_string);

  // Create the entry for this IP if it doesn't yet exist in the map.
  if (!keyInMap(ip_params_map, ip_id)) {

    auto ip_params = ipParams();
    ip_params_map.insert(std::pair<unsigned, ipParams>(ip_id, ip_params));
  }

  auto &ip_params = ip_params_map[ip_id];
  std::string param_type = param.substr(space_position + 1);

  // Assign argument to IP parameter.
  if (param_type == "latency") {
    ip_params.latency_ = std::stoul(arg);
  }
  else if (param_type == "upper tolerance") {
    ip_params.upper_tolerance_ = std::stoul(arg);
  }
  else if (param_type == "lower tolerance") {
    ip_params.lower_tolerance_ = std::stoul(arg);
  } else {
    throw std::invalid_argument("Unrecognized IP parameter type.");
  }
}

void parameterBuilder::parseSrParam(
  std::size_t sr_param_position,
  const std::string &param,
  const std::string &arg,
  sr_params_map_t &sr_params_map
) {
  auto region_and_module_ids = getRegionAndModuleId(param, sr_param_position);

  auto sr_id = region_and_module_ids.first;
  auto sr_module_id = region_and_module_ids.second;

  auto ip_id_string = arg.substr(2);
  auto ip_id = std::stoul(ip_id_string);

  // Entry for this SR exists.
  if (keyInMap(sr_params_map, sr_id)) {

    sr_params_map[sr_id].assignIpIdToModule(sr_module_id, ip_id);

  // First occurrence of this SR.
  } else {
    auto sr_params = srParams(sr_module_id, ip_id);
    sr_params_map.insert(std::pair<unsigned, srParams>(sr_id, sr_params));
  }
}

// using rr_module_ip_map_t = std::unordered_map<unsigned, std::vector<unsigned>>
void parameterBuilder::parseRrParam(
  std::size_t rr_param_position,
  const std::string &param,
  const std::string &arg,
  std::unordered_map<unsigned, rrParams> &rr_params_map
) {
  auto region_and_module_ids = getRegionAndModuleId(param, rr_param_position);

  unsigned rr_id = region_and_module_ids.first;
  unsigned rr_module_id = region_and_module_ids.second;

  // Get the IP IDs string without the enclosing brackets.
  auto ip_ids_string = arg.substr(1, arg.length() - 2);

  // Get the equivalent vector of IDs.
  auto ip_ids = getIpIdsFromString(ip_ids_string);

  // Entry for this RR exists.
  if (keyInMap(rr_params_map, rr_id)) {
    auto matching_rr_params = rr_params_map[rr_id];
    matching_rr_params.assignIpsToModule(rr_module_id, ip_ids);
    rr_params_map[rr_id] = matching_rr_params;

    // First occurrence of this RR.
  } else {
    auto rr_params = rrParams(rr_module_id, ip_ids);
    rr_params_map.insert(std::pair<unsigned, rrParams>(rr_id, rr_params));
  }
}

std::vector<unsigned> parameterBuilder::getIpIdsFromString(std::string ip_ids_string) {

  std::vector<unsigned> ip_ids;
  std::size_t next_comma_position = ip_ids_string.find(",");

  if (next_comma_position == std::string::npos) {
    boost::trim(ip_ids_string);

    unsigned single_ip = std::stoul(ip_ids_string);
    ip_ids.push_back(single_ip);
  } else {
    std::string next_ip_id_string;
    unsigned next_ip_id;

    // Loop through the IP ID list, parse each individual number, and then move the iterator
    // forward.
    while (next_comma_position != std::string::npos) {

      // Get single IP string and trim off whitespace.
      next_ip_id_string = ip_ids_string.substr(0, next_comma_position);
      boost::trim(next_ip_id_string);

      // Clip off the "ip" at the front.
      next_ip_id_string = next_ip_id_string.substr(2);

      // Parse the ID and push it onto the vector.
      next_ip_id = std::stoul(next_ip_id_string);
      ip_ids.push_back(next_ip_id);

      // Move the iterator forward.
      ip_ids_string = ip_ids_string.substr(next_comma_position + 1);
      next_comma_position = ip_ids_string.find(",");
    }

    // Once the loop is complete, the final IP ID is left in ip_ids_string.
    boost::trim(ip_ids_string);

    // Clip off the "ip" at the front.
    next_ip_id_string = ip_ids_string.substr(2);

    // Parse the ID and push it onto the vector.
    next_ip_id = std::stoul(next_ip_id_string);
    ip_ids.push_back(next_ip_id);
  }

  return ip_ids;
}


/* HELPER */

std::pair<unsigned, unsigned> getRegionAndModuleId(
  const std::string &param,
  std::size_t param_start_position
) {

  // Find first space.
  std::size_t space_position = param.find(" ");

  // Parse region ID.
  std::string region_id_string = param.substr(param_start_position + 2, space_position - param_start_position - 2);
  unsigned region_id = std::stoul(region_id_string);

  // Find second space.
  space_position = param.find(" ", space_position + 1);
  std::size_t colon_position = param.length();

  // Parse module ID.
  std::string module_id_string = param.substr(space_position + 1, colon_position - space_position - 1);
  unsigned module_id = std::stoul(module_id_string);

  // Return pair of IDs.
  return std::make_pair(region_id, module_id);
}

template <typename TKey, typename TVal>
bool keyInMap(const std::unordered_map<TKey, TVal> &map, const TKey &key) {
  return map.find(key) != map.end();
}
