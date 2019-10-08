#ifndef LEPTON_MODULE_ITERATION_ACTIONS_H
#define LEPTON_MODULE_ITERATION_ACTIONS_H

#include <memory> // shared_ptr

#include "../core/availableModule.h"
#include "../graph/graphNode.h"

typedef void (*sr_action_t)(
  std::shared_ptr<availableModule> &sr_module,
  unsigned long long &execution_counter,
  int long &least_than_scoreboard,
  std::shared_ptr<graphNode> &least_than_reference
);

typedef void (*rr_action_t)(
  unsigned rr_id,
  std::shared_ptr<availableModule> &rr_module,
  unsigned long long &execution_counter,
  int long &least_than_scoreboard,
  std::shared_ptr<graphNode> &least_than_reference
);

// Static methods used by the mapper::performActionsOverAllModules method.
struct moduleIterationActions {

	static void setNotActiveSr(
		std::shared_ptr<availableModule>& module,
		unsigned long long &ignore0,
		int long &ignore1,
		std::shared_ptr<graphNode>& ignore2
	);

	static void setNotActiveRr(
		unsigned ignore0,
		std::shared_ptr<availableModule>& module,
		unsigned long long &ignore1,
		int long &ignore2,
		std::shared_ptr<graphNode>& ignore3
	);

	static void updateExecutionContextSr(
		std::shared_ptr<availableModule>& module,
		unsigned long long &execution_counter,
		int long &ignore1,
		std::shared_ptr<graphNode>& ignore2
	);

	static void updateExecutionContextRr(
		unsigned ignore0,
		std::shared_ptr<availableModule>& module,
		unsigned long long &execution_counter,
		int long &ignore1,
		std::shared_ptr<graphNode>& ignore2
	);

	static void updateScoreboardSr(
		std::shared_ptr<availableModule>& sr_module,
		unsigned long long &execution_counter,
		int long &least_than_scoreboard,
		std::shared_ptr<graphNode>& least_than_reference
	);

	static void updateScoreboardRr(
		unsigned region_id,
		std::shared_ptr<availableModule>& rr_module,
		unsigned long long &execution_counter,
		int long &least_than_scoreboard,
		std::shared_ptr<graphNode>& least_than_reference
	);
};

#endif
