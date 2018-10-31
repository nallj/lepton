#ifndef GRAPH_HANDLER_H
#define GRAPH_HANDLER_H

#include <boost/algorithm/string/trim.hpp> // trim
#include <fstream> // ifstream
#include <string> // find, getline, string
#include <vector> // vector

#include "../debugHelper.h"
#include "graph.h"
#include "graphNode.h"

// Debug message controls.
#define DEBUG_FORM_GRAPHS false
#define DEBUG_MARK_GRAPHS false

class graphHandler {

public:
    std::vector<graph> formGraphsFromTgffFile(const std::string& input_file);

    void markGraphTasksWithIps(const std::vector<graph>& graphs, unsigned ip_count);

private:
    void markGraphTasksWithIpsRecursive(graphNode* node, unsigned ip_count);
};

#endif