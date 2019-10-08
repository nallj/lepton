#ifndef LEPTON_RECONFIGURABLE_REGIONS_H
#define LEPTON_RECONFIGURABLE_REGIONS_H

#include <memory> // shared_ptr
#include <unordered_map> // unordered_map

#include "availableModule.h"
#include "../helpers/moduleIterationActions.h"

using rr_content_t = std::shared_ptr<availableModule>;
using reconfig_regions_t = std::unordered_map<unsigned, rr_content_t>;

struct reconfigurableRegions {
  reconfig_regions_t rr_contents;

  void assignModuleToRegion(unsigned region_id, rr_content_t module);
  rr_content_t getCurrentModule(unsigned region_id);
  void performActionOverAllRegions(
    rr_action_t rr_action,
    unsigned long long &execution_counter,
    int long &least_than_scoreboard,
    std::shared_ptr<graphNode> &least_than_reference
  );

public:
  reconfigurableRegions(region_to_modules_map_t &rr_modules);
  bool isResidentModuleActive(unsigned region_id);
};

#endif
