#ifndef LEPTON_IP_PARAMS_H
#define LEPTON_IP_PARAMS_H

#include <unordered_map>

struct ipParam;

using ip_params_map_t = std::unordered_map<unsigned, ipParam>;

// Container of parameters relating to a single type of IP (intellectual property).
struct ipParam {
	unsigned latency_;
	unsigned upper_tolerance_;
	unsigned lower_tolerance_;
};

#endif
