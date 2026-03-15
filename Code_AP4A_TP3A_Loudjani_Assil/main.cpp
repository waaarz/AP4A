#include <iostream>
#include <filesystem>  // <--- ajouté
#include "Badge.h"
#include "LecteurBadge.h"
#include "Server.h"
#include "Scheduler.h"
#include <memory>

int main(int argc, char* argv[]) {
    Server server;

    // Récupère le chemin de l’exécutable et construit le chemin du fichier access_rights.txt
    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path exeDir  = exePath.parent_path();
    std::filesystem::path rightsFile = exeDir / "access_rights.txt";

    std::cout << "Looking for access rights file at: " << rightsFile << std::endl;

    if (!server.loadAccessRights(rightsFile.string())) {
        std::cerr << "Failed to load access_rights.txt" << std::endl;
    }

    // crée des lecteurs
    auto b1 = std::make_shared<BuildingReader>(1, "Main Building Entrance");
    auto b2 = std::make_shared<RoomReader>(2, "Lab A - Room 101");
    auto b3 = std::make_shared<RoomReader>(3, "Admin Office - Room 201");
    server.registerReader(b1);
    server.registerReader(b2);
    server.registerReader(b3);

    // crée des badges (personnes)
    auto bdg1 = std::make_shared<Badge>(100, "Alice Dupont", Role::STUDENT);
    auto bdg2 = std::make_shared<Badge>(101, "Dr. Martin", Role::TEACHER);
    auto bdg3 = std::make_shared<Badge>(102, "Paul Admin", Role::STAFF);
    auto bdg4 = std::make_shared<Badge>(103, "Securite 1", Role::SECURITY);

    // scheduler
    Scheduler sched(server);
    sched.addBadge(bdg1);
    sched.addBadge(bdg2);
    sched.addBadge(bdg3);
    sched.addBadge(bdg4);

    sched.addReader(b1);
    sched.addReader(b2);
    sched.addReader(b3);

    server.printConfig();

    // simule 30 événements
    sched.simulateDay(30);

    std::cout << "Logs: access_granted.log and access_denied.log generated." << std::endl;
    return 0;
}
