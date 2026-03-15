#include "LecteurBadge.h"
#include <sstream>

LecteurBadge::LecteurBadge(int id, std::string location)
    : id_(id), location_(std::move(location)) {}

LecteurBadge::~LecteurBadge() = default;

int LecteurBadge::getId() const { return id_; }
const std::string& LecteurBadge::getLocation() const { return location_; }

std::string LecteurBadge::toString() const {
    std::ostringstream ss;
    ss << "Reader[" << id_ << "] at " << location_;
    return ss.str();
}

BuildingReader::BuildingReader(int id, std::string location)
    : LecteurBadge(id, std::move(location)) {}

std::string BuildingReader::toString() const {
    std::ostringstream ss;
    ss << "BuildingReader[" << id_ << "] at " << location_;
    return ss.str();
}

RoomReader::RoomReader(int id, std::string location)
    : LecteurBadge(id, std::move(location)) {}

std::string RoomReader::toString() const {
    std::ostringstream ss;
    ss << "RoomReader[" << id_ << "] at " << location_;
    return ss.str();
}
