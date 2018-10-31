#ifndef LEPTON_AVAILABLE_MODULE_H
#define LEPTON_AVAILABLE_MODULE_H

#include <memory> // unique_ptr
#include <sstream>
#include <unordered_map> // unordered_map
#include <vector> // vector

#include "graph/graphNode.h"

class availableModule;

//using ip_to_capable_modules_map_t = std::unordered_multimap<unsigned, std::vector<availableModule*>*>;
using ip_to_capable_modules_map_t = std::unordered_map<unsigned, std::vector<availableModule*>*>;
//using region_to_avail_modules_t = std::vector<std::vector<availableModule*>>;

// Consider changing to region_to_modules_t.
using region_to_avail_modules_t = std::unordered_map<unsigned, std::vector<std::unique_ptr<availableModule>>>;

class availableModule {

	public:
		// For reconfigurable region modules.
		availableModule(unsigned region_id, unsigned module_id) :
			is_active_(false), region_id_(region_id), module_id_(module_id), is_static_(false) { }

		// For static/reconfigurable modules.
		availableModule(unsigned region_id, unsigned module_id, bool is_static) :
			is_active_(false), region_id_(region_id), module_id_(module_id), is_static_(is_static) { }


		// Accessors.
		
		bool getIsActive() {
			return is_active_;
		}
		
		unsigned getRemainingLatency() {
			return remaining_latency_;
		}

		graphNode* getCurrentTask() {
			return current_task_;
		}

		bool getIsStatic() {
			return is_static_; 
		}

		unsigned getRegionId() {
			return region_id_;
		}

		unsigned getModuleId() {
			return module_id_;
		}


		// Mutators.

		void setIsActive(bool is_active) {
			is_active_ = is_active;
		}

		void setRemainingLatency(unsigned remaining_latency) {
			remaining_latency_ = remaining_latency;
		}

		void setCurrentTask(graphNode* current_task) {
			current_task_ = current_task;
		}

		std::string getHumanReadableId() {

			std::ostringstream o;
			o << (is_static_ ? "s" : "r") << region_id_ << "m" << module_id_;

			return o.str();
		}

	private:

		// Relevant to the operation of the application.
		bool is_active_;
		unsigned remaining_latency_;
		graphNode* current_task_;

		// Used solely for debugging purposes.
		bool is_static_;
		unsigned region_id_;
		unsigned module_id_;
};

#endif
