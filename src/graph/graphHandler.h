#ifndef LEPTON_GRAPH_HANDLER_H
#define LEPTON_GRAPH_HANDLER_H

#include <boost/algorithm/string/trim.hpp> // trim
#include <fstream> // ifstream
#include <memory> // shared_ptr
#include <string> // find, getline, string
#include <vector> // vector

#include "graph.h"
#include "graphNode.h"
#include "../helpers/debugHelper.h"

// Debug message controls.
#define DEBUG_FORM_GRAPHS false
#define DEBUG_MARK_GRAPHS false

class graphHandler {
  void markGraphTasksWithIpsRecursive(std::shared_ptr<graphNode> node, unsigned ip_count);

public:
  graphs_t formGraphsFromTgffFile(const std::string& input_file);
  void markGraphTasksWithIps(const graphs_t &graphs, unsigned ip_count);
};

#endif