#ifndef LEPTON_APPLICATION_TRACE_H
#define LEPTON_APPLICATION_TRACE_H

#include <iostream> // cout
#include <memory> // shared_ptr
#include <vector> // vector

#include "availableModule.h"

/*
	All traces are of the following format:
		<containing region ID>,
		<module ID>,
		<request time>,
		<execution time>,
		[<dependency on trace ID>, ...]
*/

using traces_t = std::vector<std::shared_ptr<applicationTrace>>;

/*
	NOTE: Normally, a trace would have no need to keep track of which prior traces the
        subject trace is dependent on.  However, since these traces are fed into Drachma
        for the purpose of attempting to optimize application performance it is of
        paramount importance to keep track of this information as well.
*/

class applicationTrace {
	std::string task_node_name_;
	unsigned long trace_id_;
	unsigned ip_id_;
	unsigned region_id_;
	bool is_static_;
	unsigned module_id_;
	unsigned long long request_time_;
	unsigned execution_latency_;
	traces_t dependent_traces_;

public:
	applicationTrace(
		unsigned long trace_id,
		unsigned ip_id,
		std::shared_ptr<availableModule> chosen_module,
		unsigned long long request_time,
		unsigned execution_latency,
		traces_t dependent_traces
	);

	void printHumanFriendlyDisplay() const;
	unsigned long getTraceId() const;
	unsigned long long getCalculatedEndTime() const;
	std::string getHumanFriendlyDisplayString() const;
};

#endif
