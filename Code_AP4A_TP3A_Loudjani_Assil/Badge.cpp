#include "Badge.h"
#include <sstream>

Badge::Badge(int id, std::string name, Role role)
    : id_(id), name_(std::move(name)), role_(role) {}

Badge::~Badge() = default;

int Badge::getId() const { return id_; }
const std::string& Badge::getName() const { return name_; }
Role Badge::getRole() const { return role_; }

std::string Badge::toString() const {
    std::ostringstream ss;
    ss << "[" << id_ << "] " << name_ << " (" << roleToString(role_) << ")";
    return ss.str();
}
