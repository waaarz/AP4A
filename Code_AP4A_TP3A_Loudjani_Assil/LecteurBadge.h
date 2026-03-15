#pragma once
#include <string>
#include <ostream>

class LecteurBadge {
public:
    LecteurBadge(int id, std::string location);
    virtual ~LecteurBadge();
    int getId() const;
    const std::string& getLocation() const;
    virtual std::string toString() const;
protected:
    int id_;
    std::string location_;
};

class BuildingReader : public LecteurBadge {
public:
    BuildingReader(int id, std::string location);
    std::string toString() const override;
};

class RoomReader : public LecteurBadge {
public:
    RoomReader(int id, std::string location);
    std::string toString() const override;
};
