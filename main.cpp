#include "Player.h"
#include "Game.h"

#include <iostream>

//Step 2: I implemented all 3 of the options

int main() {

  Game *g1 = new Game();
  
  Player *p = new Player("Ngozi", true);

  Player *p_2 = new Player("enemy", false);
  Position pos2;
  pos2.row = 0;
  pos2.col = 9;
  p_2->SetPosition(pos2);
  
  Player *p_3 = new Player("enemy", false);
  Position pos3;
  pos3.row = 5;
  pos3.col = 2;
  p_3->SetPosition(pos3);
  
  std::vector<Player*> Enemy;
  Enemy.push_back(p_2);
  Enemy.push_back(p_3);
  
  g1->NewGame(p, Enemy, 2);
  
  while (!g1->IsGameOver(p)){
    g1->TakeTurn(p,Enemy);
    g1->TakeTurnEnemy(p_2);
    g1->TakeTurnEnemy(p_3);
    if (p->getLives() <= 0){
      p->setIsDead(true);
    }
  }
  std::cout << g1->GenerateReport(p) << std::endl;
}