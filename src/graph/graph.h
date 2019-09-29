#ifndef LEPTON_GRAPH_H
#define LEPTON_GRAPH_H

#include <deque> // deque
#include <map> // multimap
#include <memory> // shared_ptr
#include <vector> // vector

#include "graphNode.h"

class graph {
	std::vector<std::shared_ptr<graphNode>> all_nodes_;
	std::multimap<std::string, std::shared_ptr<graphNode>> node_dictionary_;
	std::deque<std::shared_ptr<graphNode>> top_level_nodes_;

public:
	graph() {}
	~graph() {

		// for (unsigned i = 0; i < all_nodes_.size(); i++) {
		// 	delete all_nodes_.at(i);
		// }
	}


	void addGraphNode(std::string graph_id, unsigned task_type_id) {

		auto new_node = std::shared_ptr<graphNode>(new graphNode(graph_id, task_type_id));

		// Add node to list of all nodes in graph.
		all_nodes_.push_back(new_node);

		// Add corresponding entry to the node dictionary.
		//std::pair<std::string, graphNode*> entry(graph_id, new_node);
		//node_dictionary_.insert(entry);
		node_dictionary_.insert(std::make_pair(graph_id, new_node));
	}

	void addSuccessorToNode(std::string predecessor_id, std::string successor_id) {

		std::multimap<std::string, std::shared_ptr<graphNode>>::iterator it;

		// Get predecessor node.
		it = node_dictionary_.find(predecessor_id);
		auto predecessor = it->second;

		// Get successor node.
		it = node_dictionary_.find(successor_id);
		auto successor = it->second;

		// Add successor under the predecessor.
		predecessor->addSuccessorNode(successor);

		// Indicate the successor node has at least one predecessor.
		//successor->setHasPredecessorsTrue();

		// Add predecessor above the successor.
		successor->addPredecessorNode(predecessor);
	}

	void determineTopNodes() {

		// Loop through all nodes in the graph.
		// for (std::vector<graphNode*>::iterator it = all_nodes_.begin(); it != all_nodes_.end(); ++it) {

		// 	// If there are no predecessors to a node then it is at the top level.
		// 	if (!(*it)->hasPredecessors()) {
		// 		top_level_nodes_.push_back(*it);
		// 	}			// If there are no predecessors to a node then it is at the top level.
		// 	if (!(*it)->hasPredecessors()) {
		// 		top_level_nodes_.push_back(*it);
		// 	}
		// }

		for (auto it : all_nodes_) {

			// If there are no predecessors to a node then it is at the top level.
			if (!it->hasPredecessors()) {
				top_level_nodes_.push_back(it);
			}
		}
	}

	const std::vector<std::shared_ptr<graphNode>> getAllNodes() const { return all_nodes_; }
	//std::vector<graphNode*> getAllNodes() { return all_nodes_; }

	const std::deque<std::shared_ptr<graphNode>> getAllTopLevelNodes() const { return top_level_nodes_; }
	//std::deque<graphNode*> getAllTopLevelNodes() { return top_level_nodes_; }

};

#endif
