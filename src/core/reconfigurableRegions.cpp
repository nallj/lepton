#include "reconfigurableRegions.h"

/* PUBLIC */

reconfigurableRegions::reconfigurableRegions(region_to_modules_map_t &rr_modules) {
  for (auto i = 0; i < rr_modules.size(); i++) {
    rr_contents.insert(
      std::make_pair(i, std::shared_ptr<availableModule>(new availableModule(0, 0)))
    );
  }
}


void reconfigurableRegions::assignModuleToRegion(unsigned region_id, rr_content_t module) {
  rr_contents[region_id] = module;
}

bool reconfigurableRegions::isResidentModuleActive(unsigned region_id) {
  return getCurrentModule(region_id)->getIsActive();
}

// TODO: Consider breaking out execution_counter, least_than_scoreboard, and least_than_reference
//       into a struct called "scoringContext" (or something like that).
void reconfigurableRegions::performActionOverAllRegions(
  rr_action_t rr_action,
  unsigned long long &execution_counter,
  int long &least_than_scoreboard,
  std::shared_ptr<graphNode> &least_than_reference
) {
  for (auto &rr_it : rr_contents) {

    auto rr_id = rr_it.first;
    auto &rr_module = rr_it.second;

    // Perform RR-specific module action.
    rr_action(rr_id, rr_module, execution_counter, least_than_scoreboard, least_than_reference);
  }
}


/* PRIVATE */

rr_content_t reconfigurableRegions::getCurrentModule(unsigned region_id) {
  return rr_contents.find(region_id)->second;
}
