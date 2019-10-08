
#include "graphHandler.h"

graphs_t graphHandler::formGraphsFromTgffFile(
	const std::string& input_file
) {
	graphs_t graphs;

	std::ifstream in_file(input_file.c_str());
	std::string line;

	bool building_graph = false;
	//graph* current_graph;

	// Loop through the .tgff file and build all graph structures.
	while (std::getline(in_file, line)) {

		// Search for the beginning of a graph specification.
		if (!building_graph) {

			// If found begin building a new graph.
			if (line.find("@TASK_GRAPH") != std::string::npos) {

				building_graph = true;
				//current_graph = new graph();

				auto new_graph = std::shared_ptr<graph>(new graph());
				graphs.push_back(new_graph);
			}

			continue;
		}
		
		// Get the current graph being assembled.
		auto& current_graph = graphs.back();

		// If the end of a graph specification has been reached save the graph and continue searching the file.
		if (line.length() > 0 && line.at(0) == '}') {

			// Before saving the graph determine the top level nodes for the graph.
			current_graph->determineTopNodes();

			building_graph = false;
			//graphs.push_back(current_graph);

			continue;
		}

		std::size_t position, space_position;

		// Check for task node specification.
		position = line.find("TASK");

		if (position != std::string::npos) {

			space_position = line.find("\t", position + 5);
			std::string node_id = line.substr(position + 5, space_position - position - 5);

			position = line.find("TYPE");

			std::string task_type_id_string = line.substr(position + 5);
			boost::trim(task_type_id_string);

			unsigned task_type_id = std::stoul(task_type_id_string);

			// Add node to the graph and continue to the next line in the graph specification.
			current_graph->addGraphNode(node_id, task_type_id);
			continue;
		}

		// Check for node edge specification.
		position = line.find("ARC");

		if (position != std::string::npos) {
			
			space_position = line.find(" ", position + 4);
			std::string edge_id = line.substr(position + 4, space_position - position - 4);

			position = line.find("FROM");
			space_position = line.find(" ", position + 5);

			std::string from_id_string = line.substr(position + 5, space_position - position - 5);

			position = line.find("TO");
			space_position = line.find(" ", position + 4);

			std::string to_id_string = line.substr(position + 4, space_position - position - 4);

			// Add the successor node under the target predecessor node.
			current_graph->addSuccessorToNode(from_id_string, to_id_string);
			continue;
		}

	}

	in_file.close();

	// DEBUG MESSAGES
	if (DEBUG_FORM_GRAPHS) {
		debugHelper::debugFormGraphs(graphs);
	}

	return graphs;
}

// TODO: Support user specified restrictions on which IPs may match with which task types.
void graphHandler::markGraphTasksWithIps(
	const graphs_t &graphs,
	unsigned ip_count
) {
	// TODO: This should be derived from configuration parameters, otherwise set to 0.
	bool use_time_as_random_seed = false;
	unsigned random_seed;

	if (use_time_as_random_seed) {
		random_seed = (unsigned) time(0);
	} else {
		random_seed = 5762;
	}

	// Feed the seed to the pseudo-random number generator.
	srand(random_seed);

	// Perform marking activities for each graph.
	//for (std::vector<graph*>::iterator it = graphs.begin(); it != graphs.end(); ++it) {
	for (auto& graph : graphs) {

		//std::deque<graphNode*> all_top_level_nodes = (*it)->getAllTopLevelNodes();
		auto all_top_level_nodes = graph->getAllTopLevelNodes();
		//for (unsigned i = 0; i < all_top_level_nodes.size(); i++) {
			for (auto top_level_node : all_top_level_nodes) {

			// Recursively travel from every top level node to mark every node with a pseudo-randomly chosen IP.
			markGraphTasksWithIpsRecursive(top_level_node, ip_count);
		}
	}

	// DEBUG MESSAGES
	if (DEBUG_MARK_GRAPHS) {
		debugHelper::debugMarkGraphs(graphs);
	}
}

void graphHandler::markGraphTasksWithIpsRecursive(std::shared_ptr<graphNode> node, unsigned ip_count) {

	// Mark the node with the chosen ID.
	unsigned random_ip_id = rand() % static_cast<unsigned>(ip_count);
	node->setIpId(random_ip_id);

	std::vector<std::shared_ptr<graphNode>> successors = node->getSuccessorNodes();

	// Continue recursive marking if there are any successor nodes.
	if (successors.size() > 0) {
		for (auto successor_node : successors) {
			markGraphTasksWithIpsRecursive(successor_node, ip_count);
		}
	}

	//for (std::vector<graphNode*>::iterator it = successors.begin(); it != successors.end(); ++it)
	//	markGraphTasksWithIpsRecursive(*it, ip_count);
}
