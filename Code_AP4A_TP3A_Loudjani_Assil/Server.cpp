#include "Server.h"
#include <fstream>
#include <sstream>
#include <iostream>

Server::Server()
    : logger_("access_granted.log", "access_denied.log")
{}

Server::~Server() = default;

static Role parseRole(const std::string& s) {
    if (s == "STUDENT") return Role::STUDENT;
    if (s == "TEACHER") return Role::TEACHER;
    if (s == "STAFF") return Role::STAFF;
    if (s == "SECURITY") return Role::SECURITY;
    return Role::UNKNOWN;
}

// Format attendu (ligne par ligne) : reader_id;ROLE1,ROLE2,...
// ex: 1;STUDENT,TEACHER
bool Server::loadAccessRights(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string left, right;
        if (!std::getline(ss, left, ';')) continue;
        if (!std::getline(ss, right)) continue;
        int rid = std::stoi(left);
        std::set<Role> setRoles;
        std::istringstream rr(right);
        std::string token;
        while (std::getline(rr, token, ',')) {
            Role r = parseRole(token);
            if (r != Role::UNKNOWN) setRoles.insert(r);
        }
        rights_[rid] = setRoles;
    }
    return true;
}

void Server::registerReader(std::shared_ptr<LecteurBadge> reader) {
    readers_[reader->getId()] = reader;
}

bool Server::demandeAcces(const Badge& badge, const LecteurBadge& reader) {
    int rid = reader.getId();
    auto it = rights_.find(rid);
    std::ostringstream out;
    out << badge.toString() << " -> " << reader.toString();
    if (it == rights_.end()) {
        // pas de configuration pour ce reader -> refuser par defaut
        logger_.logDeny(out.str() + " [NO_RULE]");
        return false;
    }
    const auto& allowed = it->second;
    if (allowed.find(badge.getRole()) != allowed.end()) {
        logger_.logGrant(out.str());
        return true;
    } else {
        logger_.logDeny(out.str());
        return false;
    }
}

void Server::printConfig() const {
    std::cout << "Server Access Configuration:\n";
    for (auto &p : rights_) {
        std::cout << " Reader " << p.first << " : ";
        bool first = true;
        for (auto r : p.second) {
            if (!first) std::cout << ", ";
            std::cout << roleToString(r);
            first = false;
        }
        std::cout << "\n";
    }
}
