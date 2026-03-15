#include "Scheduler.h"
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

Scheduler::Scheduler(Server& server)
    : server_(server)
{
    seed_ = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
}

void Scheduler::addBadge(std::shared_ptr<Badge> b) {
    badges_.push_back(b);
}

void Scheduler::addReader(std::shared_ptr<LecteurBadge> r) {
    readers_.push_back(r);
}

void Scheduler::simulateDay(int eventsCount) {
    if (badges_.empty() || readers_.empty()) {
        std::cout << "No badges or readers registered. Nothing to simulate.\n";
        return;
    }
    std::mt19937 rng(seed_);
    std::uniform_int_distribution<size_t> db(0, badges_.size()-1);
    std::uniform_int_distribution<size_t> dr(0, readers_.size()-1);

    std::cout << "Simulation start (" << eventsCount << " events)...\n";
    for (int i = 0; i < eventsCount; ++i) {
        auto b = badges_[db(rng)];
        auto r = readers_[dr(rng)];
        bool granted = server_.demandeAcces(*b, *r);
        std::cout << (granted ? "[GRANTED] " : "[DENIED ] ") << b->toString() << " -> " << r->toString() << "\n";
        // petite pause pour lisibilité (optionnel)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "Simulation finished.\n";
}
