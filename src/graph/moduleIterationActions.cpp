
#include "moduleIterationActions.h"


/* PUBLIC */

void moduleIterationActions::setNotActiveSr(availableModule* module, unsigned long long &ignore0, int long &ignore1, graphNode** ignore2) {

    setNotActiveRr(0, module, ignore0, ignore1, ignore2);
}

void moduleIterationActions::setNotActiveRr(unsigned ignore0, availableModule* module, unsigned long long &ignore1, int long &ignore2, graphNode** ignore3) {

    module->setIsActive(false);
}

void moduleIterationActions::updateExecutionContextSr(availableModule* module, unsigned long long &execution_counter, int long &ignore1, graphNode** ignore2) {

    updateExecutionContextRr(0, module, execution_counter, ignore1, ignore2);
}

void moduleIterationActions::updateExecutionContextRr(unsigned ignore0, availableModule* module, unsigned long long &execution_counter,
        int long &ignore1, graphNode** ignore2) {

    if (module->getIsActive()) {

        auto task_node = module->getCurrentTask();
        int long cycles_remaining = task_node->adjustExecutionLatencyByContextUpdate(execution_counter);

        if (task_node->getNodeIsComplete()) {
            module->setIsActive(false);
            std::cout << "\n'" << module->getHumanReadableId() << "' has just completed!\n";
        } else
            std::cout << "\n'" << module->getHumanReadableId() << "' is still busy [" << cycles_remaining << " remaining]\n";

    }

}

//	void moduleIterationActions::updateScoreboardSr(availableModule* sr_module, unsigned long long &execution_counter, int long &least_than_scoreboard, graphNode* least_than_reference) {
//
//		if (sr_module->getIsActive()) {
//
//			auto task_node = sr_module->getCurrentTask();
//			auto cycles_remaining = task_node->getCyclesRemaining();
//
//			std::cout << "\n\t" << task_node->getNodeId() << " [" << cycles_remaining << " remaining]";
//
//			if (cycles_remaining < least_than_scoreboard) {
//
//				std::cout << "\t\t\tPICKED\n";
//				least_than_scoreboard = cycles_remaining;
//				least_than_reference = task_node;
//			}
//
//		}
//	}

void moduleIterationActions::updateScoreboardSr(availableModule* sr_module, unsigned long long &execution_counter, int long &least_than_scoreboard, graphNode** least_than_reference) {

    if (sr_module->getIsActive()) {

        auto task_node = sr_module->getCurrentTask();
        auto cycles_remaining = task_node->getCyclesRemaining();

        std::cout << "\n\t" << task_node->getNodeId() << " [" << cycles_remaining << " remaining]";

        if (cycles_remaining < least_than_scoreboard) {

            std::cout << "\t\t\tPICKED\n";
            least_than_scoreboard = cycles_remaining;
            *least_than_reference = task_node;
        }

    }
}

//	void moduleIterationActions::updateScoreboardRr(unsigned region_id, availableModule* rr_module, unsigned long long &execution_counter,
//		int long &least_than_scoreboard, graphNode* least_than_reference) {
//
//		if (rr_module->getIsActive()) {
//
//			auto task_node = rr_module->getCurrentTask();
//			auto cycles_remaining = task_node->getCyclesRemaining();
//
//			std::cout << "\n\t" << task_node->getNodeId() << " [" << cycles_remaining << " remaining]";
//
//			if (cycles_remaining < least_than_scoreboard) {
//
//				std::cout << "\t\t\tPICKED\n";
//				least_than_scoreboard = cycles_remaining;
//				least_than_reference = task_node;
//
//				std::cout << "hold on guy, TELL ME ABOUT YOURSELF least_than_reference: ";
//										std::cout << least_than_reference->getNodeId() << " (ip" << least_than_reference->getIpId() << ")\n";
//			}
//
//		}
//	}

void moduleIterationActions::updateScoreboardRr(unsigned region_id, availableModule* rr_module, unsigned long long &execution_counter,
    int long &least_than_scoreboard, graphNode** least_than_reference) {

    if (rr_module->getIsActive()) {

        auto task_node = rr_module->getCurrentTask();
        auto cycles_remaining = task_node->getCyclesRemaining();

        std::cout << "\n\t" << task_node->getNodeId() << " [" << cycles_remaining << " remaining]";

        if (cycles_remaining < least_than_scoreboard) {

            std::cout << "\t\t\tPICKED\n";
            least_than_scoreboard = cycles_remaining;
            *least_than_reference = task_node;

            //std::cout << "hold on guy, TELL ME ABOUT YOURSELF least_than_reference: ";
            //std::cout << (*least_than_reference)->getNodeId() << " (ip" << (*least_than_reference)->getIpId() << ")\n";
        }

    }
}
