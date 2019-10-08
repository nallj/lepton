#include "availableModule.h"

// For reconfigurable region modules.
availableModule::availableModule(unsigned region_id, unsigned module_id) :
	is_active_(false), region_id_(region_id), module_id_(module_id), is_static_(false) { }

// For static/reconfigurable modules.
availableModule::availableModule(unsigned region_id, unsigned module_id, bool is_static) :
	is_active_(false), region_id_(region_id), module_id_(module_id), is_static_(is_static) { }


// Accessors.

bool availableModule::getIsActive() const {
	return is_active_;
}

unsigned availableModule::getRemainingLatency() const {
	return remaining_latency_;
}

std::shared_ptr<graphNode> availableModule::getCurrentTask() const {
	return current_task_;
}

bool availableModule::getIsStatic() const {
	return is_static_; 
}

unsigned availableModule::getRegionId() const {
	return region_id_;
}

unsigned availableModule::getModuleId() const {
	return module_id_;
}


// Mutators.

void availableModule::setIsActive(bool is_active) {
	is_active_ = is_active;
}

void availableModule::setRemainingLatency(unsigned remaining_latency) {
	remaining_latency_ = remaining_latency;
}

void availableModule::setCurrentTask(std::shared_ptr<graphNode> current_task) {
	current_task_ = current_task;
}


std::string availableModule::getHumanReadableId() const {

	std::ostringstream o;
	o << (is_static_ ? "s" : "r") << region_id_ << "m" << module_id_;

	return o.str();
}
