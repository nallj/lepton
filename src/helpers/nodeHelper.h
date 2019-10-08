#ifndef LEPTON_NODE_HELPER_H
#define LEPTON_NODE_HELPER_H

#include "../core/reconfigurableRegions.h" // rr_content_t
#include "../graph/graphNode.h"

struct nodeHelper {
	// static void attemptNodeScheduling();
	static void makeReadyNodeSuccessorsAvailable(
		std::shared_ptr<graphNode> &node,
		nodes_list_t &available_nodes,
		nodes_map_t &nodes_with_pending_dependencies
	);
	static void removeCompletedNodes(nodes_map_t &executing_nodes);
};

#endif
