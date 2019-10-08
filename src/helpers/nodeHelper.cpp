#include "nodeHelper.h"

// void attemptNodeScheduling(
//   nodes_list_t available_nodes,
//   ip_to_capable_modules_map_t ip_to_capable_modules_map,
//   rr_contents,
//   executing_nodes,
//   _execution_counter,
//   ip_params_map,
//   trace_id,
//   resultant_traces,
//   nodes_with_pending_dependencies,
//   fn: advanceExecutionContextByEarliestFinishingTask
// )

// Remove all completed nodes from the executing list.
void nodeHelper::removeCompletedNodes(nodes_map_t &executing_nodes) {
  std::vector<std::string> node_keys_to_remove_from_exe_nodes;

  for (auto &node_it : executing_nodes) {
    if (node_it.second->getNodeIsComplete()) {
      node_keys_to_remove_from_exe_nodes.push_back(node_it.first);
    }
  }

  for (auto &node_it : node_keys_to_remove_from_exe_nodes) {
    executing_nodes.erase(node_it);
  }
}

// void lol(
//   std::vector<rr_content_t> &capable_modules,
//   reconfigurableRegions &rr_contents,
//   nodes_map_t &executing_nodes,
//   std::shared_ptr<graphNode> node
// ) {

//   auto modules_under_consideration = std::vector<std::shared_ptr<availableModule>>(capable_modules);

//   unsigned total_modules = capable_modules.size();
//     bool module_found = false;

//   std::cout << "\tthere are " << total_modules << " total capable modules for the job. { ";
//   for (auto &it : modules_under_consideration) {
//     std::cout << it->getHumanReadableId() << ", ";
//   }
//   std::cout << "}\n";

//   // Keep searching until a module is chosen or all options are exhausted.
//   while (total_modules != 0 && !module_found) {

//     // Pick a random capable module to run the task.
//     unsigned random_module_index = rand() % static_cast<unsigned>(total_modules);
//     auto &random_module = modules_under_consideration[random_module_index];

//     bool is_not_static = !random_module->getIsStatic();
//     unsigned region_id = random_module->getRegionId();

//     // If the module is already busy remove it from consideration.
//     if (random_module->getIsActive()) {

//       std::cout << "\t'"
//                 << random_module->getHumanReadableId()
//                 << "' was removed from mapping consideration because it was busy.\n";
//       std::cout << "\tthere were "
//                 << modules_under_consideration.size()
//                 << " capable modules and the one to be removed is at index "
//                 << random_module_index << "\n";

//       // Remove the unfit random module from consideration.
//       modules_under_consideration.erase(modules_under_consideration.begin() + random_module_index);
//       total_modules--;

//     // If the random module is a module that only works in a busy reconfigurable region remove it from consideration.
//     } else if (is_not_static && rr_contents.isResidentModuleActive(region_id)) {

//       std::cout << "\t'"
//                 << random_module->getHumanReadableId()
//                 << "' was removed from mapping consideration because the region is must occupy is busy.\n";
//       std::cout << "\tthere were "
//                 << modules_under_consideration.size()
//                 << " capable modules and the one to be removed is at index "
//                 << random_module_index
//                 << "\n";

//       // remove the unfit random module from consideration
//       modules_under_consideration.erase(modules_under_consideration.begin() + random_module_index);
//       total_modules--;

//     // If the module is ready to accept a task then mark the module as busy and add a trace.
//     } else {

//       std::cout << "\t'"
//                 << random_module->getHumanReadableId()
//                 << "' is free and able to accept the task of IP "
//                 << node->getNodeId()
//                 << ".\n";

//       // Mark as active.
//       random_module->setIsActive(true);

//       // Insert into the list of executing nodes
//       executing_nodes.insert(
//         std::pair<std::string, std::shared_ptr<graphNode>>(node->getNodeId(), node)
//       );

//       // If the module belongs to a reconfigurable region then in needs to now occupy its' container.
//       if (is_not_static) {
//         //matching_rr->second = random_module;
//         rr_contents.assignModuleToRegion(region_id, random_module);
//       }
      
//       // Assign the node to the module.
//       random_module->setCurrentTask(node);

//       // Increment the execution counter by one to simulate a restriction wherein a task can only be requested per cycle.
//       _execution_counter++;
//       std::cout << "\tCC Count incremented to " << _execution_counter << "\n";

//       // Choose an execution latency dependent on the IP being mapped to the module.
//       auto ip_param = ip_params_map[node_ip_id];
//       unsigned random_latency_noise = rand() % ip_param.upper_tolerance_ + ip_param.lower_tolerance_;
//       unsigned execution_latency = ip_param.latency_ + random_latency_noise;

//       // Set the execution latency for the node.
//       node->beginExecution(execution_latency, _execution_counter); //, random_module);

//       // TODO: Figure out how to derive the trace's dependent traces and supply them to the object.
//       traces_t dependent_traces = node->getDependentApplicationTraces();

//       // Create the corresponding trace and add it to the result.
//       auto confirmed_trace = std::shared_ptr<applicationTrace>(
//         new applicationTrace(
//           trace_id++,
//           node_ip_id,
//           random_module,
//           _execution_counter,
//           execution_latency,
//           dependent_traces
//         )
//       );
//       resultant_traces.push_back(confirmed_trace);

//       // Assign newly created application trace to the task node for dependency tracking.
//       node->setApplicationTrace(confirmed_trace);

//       // Indicate a viable module was found and that a mapping has occurred this loop iteration.
//       module_found = true;

//       // Add successor nodes to available nodes if it is not mapped to a region and all dependencies are satisfied.
//       auto successor_nodes = node->getSuccessorNodes();

//       std::cout << "\thas " << successor_nodes.size() << " successors: ";

//       for (auto it = successor_nodes.begin(); it != successor_nodes.end(); ++it) {

//         std::string node_id = (*it)->getNodeId();
//         std::cout << "'" << node_id << "' (ip" << (*it)->getIpId() << ") [";

//         // If all dependencies are now satisfied then add this successor node to the list of available nodes.
//         if ((*it)->allDependenciesSatisfied()) {

//           std::cout << "ready to execute";
//           available_nodes.push_back(*it);

//         // If the successor node still has pending dependencies then...
//         }  else {
//           std::cout << "outstanding dependencies";

//           auto vector_presence = nodes_with_pending_dependencies.find(node_id);

//           if (vector_presence == nodes_with_pending_dependencies.end()) {
//             nodes_with_pending_dependencies.insert(std::pair<std::string, std::shared_ptr<graphNode>>(node_id, *it));
//           }
//         }

//         std::cout << "], ";
//       }
//       std::cout << "\n";
//     }

//   } // /Find available module loop.
// }


// Add nodes to available_nodes if all dependencies are satisfied.  Otherwise, add to
// nodes_with_pending_dependencies.
void nodeHelper::makeReadyNodeSuccessorsAvailable(
  std::shared_ptr<graphNode> &node,
  nodes_list_t &available_nodes,
  nodes_map_t &nodes_with_pending_dependencies
) {
  auto successor_nodes = node->getSuccessorNodes();

  std::cout << "\thas " << successor_nodes.size() << " successors: ";

  for (auto it = successor_nodes.begin(); it != successor_nodes.end(); ++it) {

    std::string node_id = (*it)->getNodeId();
    std::cout << "'" << node_id << "' (ip" << (*it)->getIpId() << ") [";

    // If all dependencies are now satisfied then add this successor node to the list of available nodes.
    if ((*it)->allDependenciesSatisfied()) {

      std::cout << "ready to execute";
      available_nodes.push_back(*it);

    // If the successor node still has pending dependencies then...
    }  else {
      std::cout << "outstanding dependencies";

      auto vector_presence = nodes_with_pending_dependencies.find(node_id);

      if (vector_presence == nodes_with_pending_dependencies.end()) {
        nodes_with_pending_dependencies.insert(std::pair<std::string, std::shared_ptr<graphNode>>(node_id, *it));
      }
    }

    std::cout << "], ";
  }
  std::cout << "\n";
}

// bool isModuleAbleToAcceptTask() {
//   std::vector<rr_content_t> &capable_modules,
//   reconfigurableRegions &rr_contents,
//   nodes_map_t &executing_nodes,
//   std::shared_ptr<graphNode> node
// ) {

//     // If the module is already busy remove it from consideration.
//     if (random_module->getIsActive()) {

//       std::cout << "\t'"
//                 << random_module->getHumanReadableId()
//                 << "' was removed from mapping consideration because it was busy.\n";
//       std::cout << "\tthere were "
//                 << modules_under_consideration.size()
//                 << " capable modules and the one to be removed is at index "
//                 << random_module_index << "\n";

//       // Remove the unfit random module from consideration.
//       modules_under_consideration.erase(modules_under_consideration.begin() + random_module_index);
//       total_modules--;

//     // If the random module is a module that only works in a busy reconfigurable region remove it from consideration.
//     } else if (is_not_static && rr_contents.isResidentModuleActive(region_id)) {

//       std::cout << "\t'"
//                 << random_module->getHumanReadableId()
//                 << "' was removed from mapping consideration because the region is must occupy is busy.\n";
//       std::cout << "\tthere were "
//                 << modules_under_consideration.size()
//                 << " capable modules and the one to be removed is at index "
//                 << random_module_index
//                 << "\n";

//       // remove the unfit random module from consideration
//       modules_under_consideration.erase(modules_under_consideration.begin() + random_module_index);
//       total_modules--;

//     }
//     // If the module is ready to accept a task then mark the module as busy and add a trace.
//     return true;
// }
