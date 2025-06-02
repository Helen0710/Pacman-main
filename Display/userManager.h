#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include <utility>

class UserManager {
public:
    UserManager();

    void inputName();                // Benutzer gibt Namen ein
    std::string getCurrentUser() const;

    void saveScore(int score, const std::string& filename);
    std::vector<std::pair<std::string, int>> loadScores(const std::string& filename);

    void drawNameInput();           // Name-Eingabe anzeigen
    bool isNameEntered() const;

private:
    std::string currentUser;
    char nameBuffer[32];
    bool nameEntered;
};

#endif // USER_MANAGER_H
