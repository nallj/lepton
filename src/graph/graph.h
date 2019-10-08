#ifndef LEPTON_GRAPH_H
#define LEPTON_GRAPH_H

#include <deque>
#include <map> // multimap
#include <memory> // shared_ptr
#include <vector> // vector

#include "graphNode.h"

class graph;
using graphs_t = std::vector<std::shared_ptr<graph>>;

class graph {
	std::vector<std::shared_ptr<graphNode>> all_nodes_;
	std::multimap<std::string, std::shared_ptr<graphNode>> node_dictionary_;
	nodes_list_t top_level_nodes_;

public:
	graph();
	~graph();

	void addGraphNode(std::string graph_id, unsigned task_type_id);
	void addSuccessorToNode(std::string predecessor_id, std::string successor_id);
	void determineTopNodes();
	const std::vector<std::shared_ptr<graphNode>> getAllNodes() const;
	const std::deque<std::shared_ptr<graphNode>> getAllTopLevelNodes() const;
};

#endif
