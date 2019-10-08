#ifndef LEPTON_GRAPH_NODE_H
#define LEPTON_GRAPH_NODE_H

#include <deque>
#include <iostream>
#include <memory> // shared_ptr
#include <unordered_map>
#include <vector>

// TODO: Is it possible to avoid the circular dependency while still including the file?
//#include "applicationTrace.h"

// Need to forward declare applicationTrace to avoid circular dependency.
class applicationTrace;
using traces_t = std::vector<std::shared_ptr<applicationTrace>>;

class graphNode;
using nodes_list_t = std::deque<std::shared_ptr<graphNode>>;
using nodes_map_t = std::unordered_map<std::string, std::shared_ptr<graphNode>>;

class graphNode {
	std::string node_id_;
	unsigned task_type_id_;

	std::vector<std::shared_ptr<graphNode>> predecessor_nodes_;
	std::vector<std::shared_ptr<graphNode>> successor_nodes_;

	unsigned ip_id_;
	bool mapped_to_rr_else_sr_;
	unsigned region_id_;
	bool node_is_mapped_to_region_;

	std::shared_ptr<applicationTrace> corresponding_trace_;

	unsigned long long beginning_clock_cycle_;
	int long cycles_remaining_;
	unsigned execution_latency_;

	bool node_is_executing_;
	bool node_is_complete_;
	
public:
	graphNode();
	graphNode(std::string node_id, unsigned task_type_id);

	std::string getNodeId() const;
	unsigned getTaskTypeId() const;
	unsigned getIpId() const;
	bool getIsNodeMappedToRegion() const;
	bool getIsMappedToRr() const;
	unsigned getRegionId() const;
	bool getNodeIsExecuting() const;
	unsigned getExecutionLatency() const;
	bool getNodeIsComplete() const;
	int long getCyclesRemaining() const;

	void setIpId(unsigned ip_id);
	void setNodeIsComplete();

	bool hasPredecessors() const;
	std::vector<std::shared_ptr<graphNode>> getPredecessorNodes() const;
	void addPredecessorNode(std::shared_ptr<graphNode> predecessor);
	std::vector<std::shared_ptr<graphNode>> getSuccessorNodes() const;
	void addSuccessorNode(std::shared_ptr<graphNode> successor);
	std::shared_ptr<applicationTrace> getApplicationTrace() const;
	void setApplicationTrace(std::shared_ptr<applicationTrace> corresponding_trace);

	void setMappedRegion(bool is_rr_else_sr, unsigned region_id);
	traces_t getDependentApplicationTraces();
	void beginExecution(unsigned execution_latency, unsigned long long beginning_clock_cycle);
	bool allDependenciesSatisfied();
	int long adjustExecutionLatencyByContextUpdate(unsigned long long current_clock_cycle);
};

#endif
