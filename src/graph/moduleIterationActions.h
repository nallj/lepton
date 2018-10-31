#ifndef LEPTON_MODULE_ITERATION_ACTIONS_H
#define LEPTON_MODULE_ITERATION_ACTIONS_H

#include "../availableModule.h"
#include "graphNode.h"

// Static methods used by the mapper::performActionsOverAllModules method.
class moduleIterationActions {

    public:

		static void setNotActiveSr(availableModule* module, unsigned long long &ignore0, int long &ignore1, graphNode** ignore2);

		static void setNotActiveRr(unsigned ignore0, availableModule* module, unsigned long long &ignore1, int long &ignore2, graphNode** ignore3);

		static void updateExecutionContextSr(availableModule* module, unsigned long long &execution_counter, int long &ignore1, graphNode** ignore2);

		static void updateExecutionContextRr(unsigned ignore0, availableModule* module, unsigned long long &execution_counter,
				int long &ignore1, graphNode** ignore2);

		static void updateScoreboardSr(availableModule* sr_module, unsigned long long &execution_counter, int long &least_than_scoreboard, graphNode** least_than_reference);

		static void updateScoreboardRr(unsigned region_id, availableModule* rr_module, unsigned long long &execution_counter,
			int long &least_than_scoreboard, graphNode** least_than_reference);

};

#endif