#include "applicationTrace.h"

applicationTrace::applicationTrace(
	unsigned long trace_id,
	unsigned ip_id,
	std::shared_ptr<availableModule> chosen_module,
	unsigned long long request_time,
	unsigned execution_latency,
	traces_t dependent_traces) :
		trace_id_(trace_id),
		ip_id_(ip_id),
		region_id_(chosen_module->getRegionId()),
		is_static_(chosen_module->getIsStatic()),
		module_id_(chosen_module->getModuleId()),
		request_time_(request_time),
		execution_latency_(execution_latency),
		task_node_name_(chosen_module->getCurrentTask()->getNodeId()),
		dependent_traces_(dependent_traces) { }

void applicationTrace::printHumanFriendlyDisplay() const {

	std::cout << "\t" << task_node_name_ << ", trace #" << trace_id_ << ": <" << ip_id_ << ", ";
	if (is_static_)
		std::cout << "s";

	std::cout << region_id_ << ", " << module_id_ << ", " << request_time_ << ", " << execution_latency_;

	// Print dependent traces if any exist.
	if (!dependent_traces_.empty()) {
		std::cout << ", [";

		for (unsigned i = 0; i < dependent_traces_.size(); i++) {

			std::cout << dependent_traces_[i]->getTraceId();

			if (i + 1 != dependent_traces_.size())
				std::cout << ",";
		}

		std::cout << "]";
	}

	std::cout << ">\n";
}

unsigned long applicationTrace::getTraceId() const {
	return trace_id_;
}

unsigned long long applicationTrace::getCalculatedEndTime() const {
	return request_time_ + execution_latency_;
}

std::string applicationTrace::getHumanFriendlyDisplayString() const {
	
	std::string result = std::to_string(ip_id_) + ", ";
	if (is_static_)
		result.append("s");

	result.append(std::to_string(region_id_) + ", "
		+ std::to_string(module_id_) + ", "
		+ std::to_string(request_time_) + ", "
		+ std::to_string(execution_latency_));

	// Dependent traces, if any exist.
	if (!dependent_traces_.empty()) {
		result.append(", [");

		for (unsigned i = 0; i < dependent_traces_.size(); i++) {

			auto trace_id = std::to_string(dependent_traces_[i]->getTraceId());
			result.append(trace_id);

			if (i + 1 != dependent_traces_.size())
				result.append(",");
		}

		result.append("]");
	}

	return result;
}
