#ifndef LEPTON_GRAPH_MAPPER_2_H
#define LEPTON_GRAPH_MAPPER_2_H

#include <deque> // deque
#include <limits> // numeric_limits
#include <unordered_map> // unordered_map
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

class graphMapper {

public:
    graphMapper(std::string input_file) :
        input_file_(input_file) {}


    void mapRegionsToGraphNodesAndProduceTraces(
        std::vector<graph*> &graphs,
        std::vector<ipParams> &ip_params,
        region_to_avail_modules_t &available_sr_modules,
        region_to_avail_modules_t &available_rr_modules,
        ip_to_capable_modules_map_t ip_to_capable_modules_dictionary,
        bool use_random_else_least_cost
    );


private:
    std::vector<applicationTrace*>* mapRegionsToGraphNodesAndProduceTracesIterativeBreadthFirst(
        std::deque<graphNode*> available_nodes,
        std::vector<ipParams> &ip_params,
        region_to_avail_modules_t &available_sr_modules,
        region_to_avail_modules_t &available_rr_modules,
        ip_to_capable_modules_map_t ip_to_capable_modules_dictionary);

    void advanceExecutionContextByEarliestFinishingTask(
        region_to_avail_modules_t &available_sr_modules,
        std::map<unsigned, availableModule*> &rr_contents,
        unsigned long long &execution_counter);

    void performActionsOverAllModules(
        region_to_avail_modules_t &available_sr_modules,
        std::map<unsigned, availableModule*> &rr_contents,
        unsigned long long &execution_counter,
        int long &least_than_scoreboard,
        graphNode** least_than_reference,

        void (*sr_action)(
            availableModule* sr_module,
            unsigned long long &execution_counter,
            int long &least_than_scoreboard,
            graphNode** least_than_reference
        ),

        void (*rr_action)(
            unsigned rr_id,
            availableModule* rr_module,
            unsigned long long &execution_counter,
            int long &least_than_scoreboard,
            graphNode** least_than_reference
        )
    );

    std::string input_file_;
};

#endif