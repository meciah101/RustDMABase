#include "pch.h"
#include "EntityInfo.h"

std::ostream& operator<<(std::ostream& os, const entityInfo& entity) {
    os << entity.className << " " << entity.prefabName << " " << entity.tag;
    return os;
}