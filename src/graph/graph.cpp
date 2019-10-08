#include "graph.h"

graph::graph() {}
graph::~graph() {
  // for (unsigned i = 0; i < all_nodes_.size(); i++) {
  // 	delete all_nodes_.at(i);
  // }
}

void graph::addGraphNode(std::string graph_id, unsigned task_type_id) {
  auto new_node = std::shared_ptr<graphNode>(new graphNode(graph_id, task_type_id));

  // Add node to list of all nodes in graph.
  all_nodes_.push_back(new_node);

  // Add corresponding entry to the node dictionary.
  //std::pair<std::string, graphNode*> entry(graph_id, new_node);
  //node_dictionary_.insert(entry);
  node_dictionary_.insert(std::make_pair(graph_id, new_node));
}

void graph::addSuccessorToNode(std::string predecessor_id, std::string successor_id) {
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

void graph::determineTopNodes() {

  // Loop through all nodes in the graph.
  for (auto it : all_nodes_) {
    // If there are no predecessors to a node then it is at the top level.
    if (!it->hasPredecessors()) {
      top_level_nodes_.push_back(it);
    }
  }
}

const std::vector<std::shared_ptr<graphNode>> graph::getAllNodes() const {
  return all_nodes_;
}

const std::deque<std::shared_ptr<graphNode>> graph::getAllTopLevelNodes() const {
  return top_level_nodes_;
}
