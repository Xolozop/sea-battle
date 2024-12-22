#include "termDrawer.h"

void termDrawer::drawField(Game game, bool showPaddings) {
    
    std::cout << std::setw(game.playerField.getSize()*2+20) << "Score: " << game.state.score.player << ":" << game.state.score.enemy << std::endl;

    std::cout << "Available skills: ";
    if (game.playerSkills.getSkillList() != "None")
        std::cout << TERM_GREEN << game.playerSkills.getSkillList();
    else
        std::cout << TERM_RED << game.playerSkills.getSkillList();
    std::cout << TERM_DEF << std::endl;

    std::cout << "Your ships: " << std::endl;
    std::cout << game.playersManager.printShipList();
    std::cout << "Enemy ships: " << std::endl;
    std::cout << game.enemyManager.printShipList();

    std::cout << TERM_DEF << std::endl;
    std::cout << std::setw(game.playerField.getSize()*2+8) << "Your field: ";
    std::cout << std::setw(game.playerField.getSize()*2+12) << "Enemy field: " << std::endl;
    for (int row = 0; row < game.playerField.getSize()+1; row++) {
        std::cout << game.playerField.printFieldRow(row, showPaddings, game.playersManager);
        std::cout << game.enemyField.printFieldRow(row, false, game.enemyManager);
        std::cout << std::endl;
    }
}