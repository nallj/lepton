
#include "graphNode.h"

void graphNode::setMappedRegion(bool is_rr_else_sr, unsigned region_id) {

		mapped_to_rr_else_sr_ = is_rr_else_sr;
		region_id_ = region_id;
		node_is_mapped_to_region_ = true;
	}


std::vector<applicationTrace*> graphNode::getDependentApplicationTraces() {

    std::vector<applicationTrace*> dependent_application_traces;

    // Assemble the traces of all completed nodes.
    for (unsigned i = 0; i < predecessor_nodes_.size(); i++)
        dependent_application_traces.push_back(predecessor_nodes_[i]->getApplicationTrace());

    return dependent_application_traces;
}

void graphNode::beginExecution(unsigned execution_latency, unsigned long long beginning_clock_cycle) {

    execution_latency_ = execution_latency;
    cycles_remaining_ = execution_latency;

    beginning_clock_cycle_ = beginning_clock_cycle;

    node_is_executing_ = true;
}

bool graphNode::allDependenciesSatisfied() {

    // If one of the nodes predecessors have not completed execution then there are outstanding dependencies.
    for (unsigned i = 0; i < predecessor_nodes_.size(); i++)
        if (!predecessor_nodes_[i]->getNodeIsComplete())
            return false;


    // No dependencies remain.
    return true;
}

int long graphNode::adjustExecutionLatencyByContextUpdate(unsigned long long current_clock_cycle) {

    int long cycles_passed = current_clock_cycle - beginning_clock_cycle_;
    //std::cout << "\n\t\t'adjustExecutionLatencyByContextUpdate' says:\n\t\t\ttcurr - tstart = " << current_clock_cycle << " - "
    //		  << beginning_clock_cycle_ << " = " << cycles_passed << " cycles have passed since starting";

    cycles_remaining_ = execution_latency_ - cycles_passed;
    //std::cout << "\n\t\t\ttexe - tpassed = " << execution_latency_ << " - "
    //		  << cycles_passed << " = " << cycles_remaining_ << " remaining in exe";

    // DEBUG
    //if (node_is_complete_) std::cout << "\t\tnode_is_complete_ set to 'true'";
    //else std::cout << "\t\tnode_is_complete_ set to 'false'";

    // Completed execution.
    if (cycles_remaining_ <= 0) {

        // It's not possible to have less than 0 cycles remaining.
        cycles_remaining_ = 0;

        node_is_complete_ = true;
        node_is_executing_ = false;
    }

    // DEBUG
    //if (node_is_complete_) std::cout << "\t\tnow 'true'";
    //else std::cout << "\t\tnow 'false'";

    // If enough cycles have passed to satisfy the execution cost then put the node to rest.
//			if (cycles_passed > execution_latency_) {
//
//				node_is_complete_ = true;
//				node_is_executing_ = false;
//			}

    return cycles_remaining_;
}
