#pragma once
#include <vector>
#include <memory>
#include "Badge.h"
#include "LecteurBadge.h"
#include "Server.h"

class Scheduler {
public:
    Scheduler(Server& server);
    // ajoute un badge (acteur)
    void addBadge(std::shared_ptr<Badge> b);
    void addReader(std::shared_ptr<LecteurBadge> r);
    // simule N événements (génère des demandes aléatoires)
    void simulateDay(int eventsCount = 50);
private:
    Server& server_;
    std::vector<std::shared_ptr<Badge>> badges_;
    std::vector<std::shared_ptr<LecteurBadge>> readers_;
    unsigned int seed_;
};
