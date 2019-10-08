#ifndef LEPTON_AVAILABLE_MODULE_H
#define LEPTON_AVAILABLE_MODULE_H

#include <memory> // shared_ptr
#include <sstream>
#include <string> // string
#include <unordered_map> // unordered_map
#include <vector> // vector

#include "../graph/graphNode.h"

class availableModule;

using ip_to_capable_modules_map_t = std::unordered_map<unsigned, std::vector<std::shared_ptr<availableModule>>>;
using region_to_modules_map_t = std::unordered_map<unsigned, std::vector<std::shared_ptr<availableModule>>>;

class availableModule {

		// Relevant to the operation of the application.
		bool is_active_;
		unsigned remaining_latency_;
		std::shared_ptr<graphNode> current_task_;

		// Used solely for debugging purposes.
		bool is_static_;
		unsigned region_id_;
		unsigned module_id_;

	public:
		availableModule(unsigned region_id, unsigned module_id);
		availableModule(unsigned region_id, unsigned module_id, bool is_static);


		// Accessors.
		bool getIsActive() const;
		unsigned getRemainingLatency() const;
		std::shared_ptr<graphNode> getCurrentTask() const;
		bool getIsStatic() const;
		unsigned getRegionId() const;
		unsigned getModuleId() const;


		// Mutators.
		void setIsActive(bool is_active);
		void setRemainingLatency(unsigned remaining_latency);
		void setCurrentTask(std::shared_ptr<graphNode> current_task);

		std::string getHumanReadableId() const;
};

#endif
