#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"
#define TERM_DEF "\033[0m"

#include "gameState.h"

// Сохранение состояния игры
void gameState::save() {
    File file("save.txt", false);
    std::stringstream st;
    st << *this;
    file.write(st.str());
}

// Загрузка состояния игры
void gameState::load() {
    File file("save.txt", true);
    std::stringstream str = file.read();
    str >> *this;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, shipManager& manager) {
    shipManager man(0, std::vector<std::vector<Ship>>(0));
    std::string str;
    getline(is, str);
    while (!str.empty()) {
        std::string ship_tmp = str.substr(0, str.find(' '));
        Ship tmp = Ship(ship_tmp.size()-1, ship_tmp[0]);
        for (int i = 1; i < ship_tmp.size(); i++)
            tmp.setState(i, (int)ship_tmp[i]-48);
        man.refresh(tmp);
        if (str.find(' ') == std::string::npos)
            break;
        str = str.substr(str.find(' ')+1);
    }
    manager = man;
    return is;
}

std::istream& operator>>(std::istream& is, skillManager& manager) {
    std::string str;
    getline(is, str);
    if (str == "-1")
        return is;
    std::istringstream iss(str);

    std::vector<int> ids;
    int id;
    while (iss >> id) {
        ids.push_back(id);
    }
    manager = skillManager(ids);
    return is;
}

std::istream& operator>>(std::istream& is, Field& field) {
    std::string str;
    std::vector<std::vector<int>> blocks;
    int x = 0;
    while(getline(is, str) && str.size()) {
        std::istringstream iss(str);
        blocks.resize(x+1);
        int block;
        while (iss >> block) {
            if (block < -3)
                throw fileReadException();
            blocks[x].push_back(block);
        }
        if (blocks[x].size() != field.getSize())
            throw std::runtime_error("Incorrect data obtained!");
        x++;
    }
    field = Field(blocks);
    return is;
}

std::istream& operator>>(std::istream& is, gameState& gameState) {
    is >> gameState.score.player >> gameState.score.enemy;
    is.ignore();
    is >> gameState.playersManager;
    is >> gameState.playerSkills;
    is >> gameState.playerField;
    gameState.playerField.isMine = true;
    gameState.playerField.validateField(gameState.playersManager);
    
    is >> gameState.enemyManager;
    is >> gameState.enemyField;
    gameState.enemyField.isMine = false;
    gameState.enemyField.validateField(gameState.enemyManager);
    return is;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const gameState& gameState) {
    os << gameState.score.player << ' ' << gameState.score.enemy << std::endl;
    os << gameState.playersManager.saveShips() << std::endl;
    os << gameState.playerSkills.saveSkills() << std::endl;
    os << gameState.playerField.saveField();
    os << std::endl;
    
    os << gameState.enemyManager.saveShips() << std::endl;
    os << gameState.enemyField.saveField();
    return os;
}
