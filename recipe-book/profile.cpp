#include "profile.h"

Profile::Profile() : Profile("", 0) {}

Profile::Profile(const std::string &username, uint32_t recipeCount)
    : m_username(username)
    , m_recipeCount(recipeCount) {}

std::string Profile::getUsername() const {
    return m_username;
}

void Profile::setUsername(const std::string &username) {
    m_username = username;
}
