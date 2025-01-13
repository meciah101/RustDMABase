#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <string>
#include <iostream>

struct entityInfo {
    std::string className;
    std::string prefabName;
    WORD tag;

    friend std::ostream& operator<<(std::ostream& os, const entityInfo& entity);
};

#endif
