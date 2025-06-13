#ifndef PROFILE_H
#define PROFILE_H

#include <string>

class Profile
{
    std::string m_username;
    uint32_t m_recipeCount;

public:
    Profile();
    Profile(const std::string &username, uint32_t recipeCount);

    std::string getUsername() const;

    void setUsername(const std::string &username);
};

#endif // PROFILE_H
