#include "moduleIterationActions.h"

/* PUBLIC */

void moduleIterationActions::setNotActiveSr(
  std::shared_ptr<availableModule> &module,
  unsigned long long &ignore0,
  int long &ignore1,
  std::shared_ptr<graphNode> &ignore2
) {
  setNotActiveRr(0, module, ignore0, ignore1, ignore2);
}

void moduleIterationActions::setNotActiveRr(
  unsigned ignore0,
  std::shared_ptr<availableModule> &module,
  unsigned long long &ignore1,
  int long &ignore2,
  std::shared_ptr<graphNode> &ignore3
) {
  module->setIsActive(false);
}

void moduleIterationActions::updateExecutionContextSr(
  std::shared_ptr<availableModule> &module,
  unsigned long long &execution_counter,
  int long &ignore1,
  std::shared_ptr<graphNode> &ignore2
) {
  updateExecutionContextRr(0, module, execution_counter, ignore1, ignore2);
}

void moduleIterationActions::updateExecutionContextRr(
  unsigned ignore0,
  std::shared_ptr<availableModule> &module,
  unsigned long long &execution_counter,
  int long &ignore1,
  std::shared_ptr<graphNode> &ignore2
) {
  if (module->getIsActive()) {

    auto task_node = module->getCurrentTask();
    int long cycles_remaining = task_node->adjustExecutionLatencyByContextUpdate(execution_counter);

    if (task_node->getNodeIsComplete()) {
      module->setIsActive(false);
      std::cout << "\n'" << module->getHumanReadableId() << "' (" << task_node->getNodeId() << ") has just completed!\n";
    } else {
      std::cout << "\n'" << module->getHumanReadableId() << "' (" << task_node->getNodeId() << ") is still busy [" << cycles_remaining << " remaining]\n";
    }
  }
}

void moduleIterationActions::updateScoreboardSr(
  std::shared_ptr<availableModule> &sr_module,
  unsigned long long &execution_counter,
  int long &least_than_scoreboard,
  std::shared_ptr<graphNode> &least_than_reference)
{
  std::cout << sr_module->getHumanReadableId() << " CHECK0\n";
  if (sr_module->getIsActive()) {

    auto task_node = sr_module->getCurrentTask();
    auto cycles_remaining = task_node->getCyclesRemaining();

    std::cout << "\n\ts"
              << sr_module->getHumanReadableId()
              << " ("
              << task_node->getNodeId()
              << ") ["
              << cycles_remaining
              << " remaining]";

    if (cycles_remaining < least_than_scoreboard) {

      std::cout << "\t\t\tPICKED\n";
      least_than_scoreboard = cycles_remaining;
      least_than_reference = task_node;
    }
  }
}

void moduleIterationActions::updateScoreboardRr(
  unsigned region_id,
  std::shared_ptr<availableModule> &rr_module,
  unsigned long long &execution_counter,
  int long &least_than_scoreboard,
  std::shared_ptr<graphNode> &least_than_reference
) {
  std::cout << rr_module->getHumanReadableId() << " CHECK1\n";
  if (rr_module->getIsActive()) {

    auto task_node = rr_module->getCurrentTask();
    auto cycles_remaining = task_node->getCyclesRemaining();

    std::cout << "\n\t" << rr_module->getHumanReadableId() << " (" << task_node->getNodeId() << ") [" << cycles_remaining << " remaining]";

    if (cycles_remaining < least_than_scoreboard) {

      std::cout << "\t\t\tPICKED\n";
      least_than_scoreboard = cycles_remaining;

      least_than_reference = task_node;
      std::cout << "task_node: " << task_node.get() << std::endl
                << std::flush;
      std::cout << "least_than_reference: " << least_than_reference.get() << std::endl
                << std::flush;
    }
  }
}
