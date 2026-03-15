#pragma once
#include <map>
#include <set>
#include <memory>
#include <string>
#include "Badge.h"
#include "LecteurBadge.h"
#include "Logger.h"

class Server {
public:
    Server();
    ~Server();
    // charge un fichier de droits simple
    bool loadAccessRights(const std::string& filename);
    // enregistre un lecteur disponible
    void registerReader(std::shared_ptr<LecteurBadge> reader);
    // process request
    bool demandeAcces(const Badge& badge, const LecteurBadge& reader);
    // pour debug / afficher configuration
    void printConfig() const;
private:
    // mapping lecteur_id -> set<Role>
    std::map<int, std::set<Role>> rights_;
    std::map<int, std::shared_ptr<LecteurBadge>> readers_;
    Logger logger_;
};
