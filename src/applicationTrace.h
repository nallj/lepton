#ifndef LEPTON_APPLICATION_TRACE_H
#define LEPTON_APPLICATION_TRACE_H

#include <iostream>
#include <vector>

#include "availableModule.h"

/*
	All traces are of the following format:
		<containing region ID>,
		<module ID>,
		<request time>,
		<execution time>,
		[<dependency on trace ID>, ...]
*/

class applicationTrace {

	public:

		/*
			NOTE: Normally, a trace would have no need to keep track of which prior traces the
				  subject trace is dependent on.  However, since these traces are fed into Drachma
				  for the purpose of attempting to optimize application performance it is of
				  paramount importance to keep track of this information as well.
		*/

		applicationTrace(
			unsigned long trace_id,
			availableModule* chosen_module,
			unsigned long long request_time,
			unsigned execution_latency,
			std::vector<applicationTrace*> dependent_traces) :
				trace_id_(trace_id),
				region_id_(chosen_module->getRegionId()),
				is_static_(chosen_module->getIsStatic()),
				module_id_(chosen_module->getModuleId()),
				request_time_(request_time),
				execution_latency_(execution_latency),
				task_node_name_(chosen_module->getCurrentTask()->getNodeId()),
				dependent_traces_(dependent_traces) {}

		void printHumanFriendlyDisplay() {

			std::cout << "\t" << task_node_name_ << ", trace #" << trace_id_ << ": <";
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

		unsigned long getTraceId() {
			return trace_id_;
		}

		unsigned long long getCalculatedEndTime() {
			return request_time_ + execution_latency_;
		}

		std::string getHumanFriendlyDisplayString() {
			
			std::string result;
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

	private:
		std::string task_node_name_;
		unsigned long trace_id_;
		unsigned region_id_;
		bool is_static_;
		unsigned module_id_;
		unsigned long long request_time_;
		unsigned execution_latency_;
		std::vector<applicationTrace*> dependent_traces_;
};

#endif
