#ifndef LEPTON_GRAPH_MAPPER_2_H
#define LEPTON_GRAPH_MAPPER_2_H

#include <deque> // deque
#include <limits> // numeric_limits
#include <memory> // shared_ptr
#include <unordered_map> // unordered_map
#include <utility> // make_pair
#include <vector> // vector

#include "graph.h"
#include "moduleHelper.h"
#include "moduleIterationActions.h"
#include "../applicationTrace.h"
#include "../availableModule.h"
#include "../files/fileWriter.h"
#include "../parameters/parameters.h"

// Debug message controls.
#define DEBUG_MAP_REGIONS false

enum class moduleSelectionType {
	random,
  least_cost
};

class graphMapper {

  std::string input_file_;

  std::vector<std::shared_ptr<applicationTrace>> mapRegionsToGraphNodesAndProduceTracesIterativeBreadthFirst(
    std::deque<std::shared_ptr<graphNode>> available_nodes,
    ip_params_map_t& ip_params_map,
    region_to_avail_modules_t& available_sr_modules,
    region_to_avail_modules_t& available_rr_modules,
    ip_to_capable_modules_map_t ip_to_capable_modules_map
  );

  void advanceExecutionContextByEarliestFinishingTask(
    region_to_avail_modules_t& available_sr_modules,
    std::unordered_map<unsigned, std::shared_ptr<availableModule>>& rr_contents,
    unsigned long long& execution_counter
  );

  // F.60: Prefer T* over T& when "no argument" is a valid option
  void performActionsOverAllModules(
    region_to_avail_modules_t& available_sr_modules,
    std::unordered_map<unsigned, std::shared_ptr<availableModule>>& rr_contents,
    unsigned long long& execution_counter,
    int long& least_than_scoreboard,
    std::shared_ptr<graphNode>& least_than_reference,
    
    void (*sr_action)(
      std::shared_ptr<availableModule>& sr_module,
      unsigned long long& execution_counter,
      int long& least_than_scoreboard,
      std::shared_ptr<graphNode>& least_than_reference
    ),
    void (*rr_action)(
      unsigned rr_id,
      std::shared_ptr<availableModule>& rr_module,
      unsigned long long& execution_counter,
      int long& least_than_scoreboard,
      std::shared_ptr<graphNode>& least_than_reference
    )
  );

public:
  graphMapper(std::string input_file) :
    input_file_(input_file) {}

  void mapRegionsToGraphNodesAndProduceTraces(
    const std::vector<std::shared_ptr<graph>>& graphs,
    ip_params_map_t& ip_params_map,
    region_to_avail_modules_t& available_sr_modules,
    region_to_avail_modules_t& available_rr_modules,
    ip_to_capable_modules_map_t& ip_to_capable_modules_map,
    moduleSelectionType module_selection_method
  );
};

#endif
