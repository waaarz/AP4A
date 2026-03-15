#pragma once
#include <string>
#include <vector>

enum class Role {
    STUDENT,
    TEACHER,
    STAFF,
    SECURITY,
    UNKNOWN
};

inline std::string roleToString(Role r) {
    switch(r) {
    case Role::STUDENT: return "STUDENT";
    case Role::TEACHER: return "TEACHER";
    case Role::STAFF: return "STAFF";
    case Role::SECURITY: return "SECURITY";
    default: return "UNKNOWN";
    }
}

class Badge {
public:
    Badge(int id, std::string name, Role role);
    virtual ~Badge();
    int getId() const;
    const std::string& getName() const;
    Role getRole() const;
    // Generate a request timestamped (string) - scheduler will call
    virtual std::string toString() const;
private:
    int id_;
    std::string name_;
    Role role_;
};
