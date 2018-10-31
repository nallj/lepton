#ifndef LEPTON_GRAPH_NODE_H
#define LEPTON_GRAPH_NODE_H

#include <iostream>
#include <vector>

//#include "applicationTrace.h"

// Need to forward declare to avoid circular dependency.
class applicationTrace;

class graphNode {
	std::string node_id_;
	unsigned task_type_id_;

	std::vector<graphNode*> predecessor_nodes_;
	std::vector<graphNode*> successor_nodes_;

	unsigned ip_id_;
	bool mapped_to_rr_else_sr_;
	unsigned region_id_;
	bool node_is_mapped_to_region_;

	applicationTrace* corresponding_trace_;

	unsigned long long beginning_clock_cycle_;
	int long cycles_remaining_;
	unsigned execution_latency_;

	bool node_is_executing_;
	bool node_is_complete_;
	
public:
	graphNode() :
		beginning_clock_cycle_(0), node_is_executing_(false), node_is_complete_(false) { }

	graphNode(std::string node_id, unsigned task_type_id) :
		beginning_clock_cycle_(0), node_is_executing_(false), node_is_complete_(false) {

		node_id_ = node_id;
		task_type_id_ = task_type_id;
	}

	~graphNode() {

		for (unsigned i = 0; i < successor_nodes_.size(); i++) {
			delete successor_nodes_.at(i);
		}
	}


	std::string getNodeId() const { return node_id_; }
	unsigned getTaskTypeId() const { return task_type_id_; }
	unsigned getIpId() const { return ip_id_; }
	bool getIsNodeMappedToRegion() const { return node_is_mapped_to_region_; }
	bool getIsMappedToRr() const { return mapped_to_rr_else_sr_; }
	unsigned getRegionId() const { return region_id_; }
	bool getNodeIsExecuting() const { return node_is_executing_; }
	unsigned getExecutionLatency() const { return execution_latency_; }
	bool getNodeIsComplete() const { return node_is_complete_; }
	int long getCyclesRemaining() const { return cycles_remaining_; }

	void setIpId(unsigned ip_id) { ip_id_ = ip_id; }
	void setNodeIsComplete() { node_is_complete_ = true; }

	bool hasPredecessors() const { return !predecessor_nodes_.empty(); }
	std::vector<graphNode*> getPredecessorNodes() const { return predecessor_nodes_; }
	void addPredecessorNode(graphNode* predecessor) { predecessor_nodes_.push_back(predecessor); }

	std::vector<graphNode*> getSuccessorNodes() const { return successor_nodes_; }
	void addSuccessorNode(graphNode* successor) { successor_nodes_.push_back(successor); }

	applicationTrace* getApplicationTrace() const { return corresponding_trace_; }
	void setApplicationTrace(applicationTrace* corresponding_trace) { corresponding_trace_ = corresponding_trace; }

	void setMappedRegion(bool is_rr_else_sr, unsigned region_id);
	std::vector<applicationTrace*> getDependentApplicationTraces();
	void beginExecution(unsigned execution_latency, unsigned long long beginning_clock_cycle);
	bool allDependenciesSatisfied();
	int long adjustExecutionLatencyByContextUpdate(unsigned long long current_clock_cycle);
};

#endif
