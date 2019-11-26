#ifndef LEPTON_GRAPH_MAPPER_2_H
#define LEPTON_GRAPH_MAPPER_2_H

#include <limits> // numeric_limits
#include <memory> // shared_ptr
#include <unordered_map>
#include <utility> // make_pair
#include <vector>

#include "graph.h"
#include "graphNode.h"
#include "../core/applicationTrace.h"
#include "../core/availableModule.h"
#include "../core/reconfigurableRegions.h"
#include "../files/fileWriter.h"
#include "../helpers/debugHelper.h"
#include "../helpers/moduleIterationActions.h"
#include "../helpers/nodeHelper.h"
#include "../parameters/ipParam.h"

// Debug message controls.
#define DEBUG_MAP_REGIONS false

enum class moduleSelectionType {
	random,
  least_cost
};

class graphMapper {
  unsigned long long _execution_counter;
  std::string input_file_;

  void advanceExecutionContextByEarliestFinishingTask(
    region_to_modules_map_t& available_sr_modules,
    reconfigurableRegions& rr_contents
  );

  void attemptNodeScheduling(
    nodes_list_t &available_nodes,
    ip_to_capable_modules_map_t &ip_to_capable_modules_map,
    reconfigurableRegions &rr_contents,
    nodes_map_t &executing_nodes,
    ip_params_map_t &ip_params_map,
    unsigned long &trace_id,
    traces_t &resultant_traces,
    nodes_map_t &nodes_with_pending_dependencies,
    region_to_modules_map_t &available_sr_modules
  );

  void handleNodesWithPendingDependencies(
    nodes_map_t &nodes_with_pending_dependencies,
    nodes_list_t &available_nodes,
    region_to_modules_map_t &available_sr_modules,
    reconfigurableRegions &rr_contents
  );

  traces_t mapRegionsToGraphNodesAndProduceTracesIterativeBreadthFirst(
    nodes_list_t available_nodes,
    ip_params_map_t& ip_params_map,
    region_to_modules_map_t& available_sr_modules,
    region_to_modules_map_t& available_rr_modules,
    ip_to_capable_modules_map_t ip_to_capable_modules_map
  );

  // F.60: Prefer T* over T& when "no argument" is a valid option
  void performActionsOverAllModules(
    region_to_modules_map_t& available_sr_modules,
    //std::unordered_map<unsigned, std::shared_ptr<availableModule>>& rr_contents,
    reconfigurableRegions& rr_contents,
    int long& least_than_scoreboard,
    std::shared_ptr<graphNode>& least_than_reference,
    sr_action_t sr_action,
    rr_action_t rr_action
  );

public:
  graphMapper(std::string input_file);

  void mapRegionsToGraphNodesAndProduceTraces(
    const graphs_t &graphs,
    ip_params_map_t& ip_params_map,
    region_to_modules_map_t& available_sr_modules,
    region_to_modules_map_t& available_rr_modules,
    ip_to_capable_modules_map_t& ip_to_capable_modules_map,
    moduleSelectionType module_selection_method,
    unsigned random_seed
  );
};

#endif
