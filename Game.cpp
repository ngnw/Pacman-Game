#include "Game.h"

#include <vector>
#include <algorithm>

//Convert this square type to a string representation of the square type
std::string SquareTypeStringify(SquareType sq){
  std::string sq_translation;
  switch(sq){
    case SquareType::Wall:
    sq_translation = "❎";
    break;
  case SquareType::Dots:
    sq_translation = "🟨";
    break;
  case SquareType::Pacman:
    sq_translation = "😁";
    break;
  case SquareType::Treasure:
    sq_translation = "🎁";
    break;
  case SquareType::Enemies:
    sq_translation = "👻";
    break;
  case SquareType::Empty:
    sq_translation = "⬜";
    break;
  case SquareType::PowerfulPacman:
    sq_translation = "😇";
    break;
  case SquareType::Trap:
    sq_translation = "🔥";
    break;
  case SquareType::EnemySpecialTreasure:
    sq_translation = "🍒";
    break;
  case SquareType::PowerfulEnemy:
    sq_translation = "💀";
    break;
  default:
    sq_translation = "NOT SET";
    break;
  }
  return sq_translation;
}

//initialize a Board with default values
Board::Board(){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      arr_[i][j] = SquareType::Dots;
    }
  }
  
  arr_[0][0] = SquareType::Pacman;
  arr_[0][4] = SquareType::Wall;
  arr_[0][5] = SquareType::Wall;
  arr_[0][6] = SquareType::Wall;
  arr_[0][7] = SquareType::Wall;
  arr_[0][8] = SquareType::Trap;
  
  arr_[1][2] = SquareType::Wall;
  arr_[1][3] = SquareType::Wall;
  arr_[1][5] = SquareType::Wall;
  arr_[1][8] = SquareType::Wall;
  
  arr_[2][2] = SquareType::Wall;
  arr_[2][3] = SquareType::Wall;
  arr_[2][5] = SquareType::Wall;
  arr_[2][8] = SquareType::Wall;
  
  arr_[3][3] = SquareType::Treasure;
  arr_[3][5] = SquareType::Wall;
  arr_[3][6] = SquareType::Wall;
  arr_[3][8] = SquareType::Wall;
  arr_[3][9] = SquareType::EnemySpecialTreasure;
  
  
  arr_[4][1] = SquareType::Wall;
  arr_[4][2] = SquareType::Wall;
  arr_[4][8] = SquareType::Treasure;
  
  arr_[5][1] = SquareType::Wall;
  arr_[5][3] = SquareType::Wall;
  arr_[5][4] = SquareType::Wall;
  
  arr_[6][8] = SquareType::EnemySpecialTreasure;
  
  arr_[7][5] = SquareType::Wall;
  arr_[7][6] = SquareType::Wall;
  
  arr_[8][1] = SquareType::Trap;
  arr_[8][5] = SquareType::Wall;
  arr_[8][6] = SquareType::Wall;
  arr_[8][7] = SquareType::Wall;
  arr_[8][8] = SquareType::Wall;
  arr_[8][9] = SquareType::Wall;
  
  arr_[9][5] = SquareType::Wall;
  arr_[9][6] = SquareType::Wall;
  arr_[9][7] = SquareType::Wall;
  arr_[9][8] = SquareType::Wall;
  arr_[9][9] = SquareType::Wall;
  
  rows_ = 10; 
  cols_ = 10;
}

//get SquareType at the position given
SquareType Board::get_square_value(Position pos) const{
  return arr_[pos.row][pos.col];
}

//set the value of a square to the given SquareType
void Board::SetSquareValue(Position pos, SquareType value){
  arr_[pos.row][pos.col] = value;
}

//get the possible Positions that a Player/Enemy could move to (not off the board or into a wall)
std::vector<Position> Board::GetMoves(Player *p){
  int current_row = p->get_position().row;
  int current_col = p->get_position().col;
  
  Position left; 
  Position right;
  Position down;
  Position up;
  
  left.row = current_row;
  left.col = current_col-1;
  
  right.row = current_row;
  right.col = current_col+1;
  
  down.row = current_row+1;
  down.col = current_col;
  
  up.row = current_row-1;
  up.col = current_col;

  std::vector<Position> accepted_moves;
  //for human player
  if (p->is_human() == true){
    //check left position is on the board + not into a wall + not enemy powerup
    if ( 0 <= left.col ){
      SquareType leftsq = arr_[left.row][left.col];
      if (leftsq != SquareType::Wall && leftsq != SquareType::EnemySpecialTreasure){
        accepted_moves.push_back(left);
      }
    }
    //check right position is on the board + not into a wall + not enemy powerup
    if ( right.col < this->get_cols() ){
      SquareType rightsq = arr_[right.row][right.col];
      if (rightsq != SquareType::Wall && rightsq != SquareType::EnemySpecialTreasure){
        accepted_moves.push_back(right);
      }
    }
    //check down position is on the board + not into a wall + not enemy powerup
    if ( down.row < this->get_rows() ){
      SquareType downsq = arr_[down.row][down.col];
      if (downsq != SquareType::Wall && downsq != SquareType::EnemySpecialTreasure){
        accepted_moves.push_back(down);
      }
    }
    //check up position is on the board + not into a wall + not enemy powerup
    if ( 0 <= up.row ){
      SquareType upsq = arr_[up.row][up.col];
      if (upsq != SquareType::Wall && upsq != SquareType::EnemySpecialTreasure){
        accepted_moves.push_back(up);
      }
    }
    return accepted_moves;
  }
  //for enemy player
  else {
    //check left position is on the board + not into a wall + not a treasure + not a trap
    if ( 0 <= left.col ){
      SquareType leftsq = arr_[left.row][left.col];
      if (leftsq != SquareType::Wall && leftsq != SquareType::Treasure && leftsq != SquareType::Trap){
        accepted_moves.push_back(left);
      }
    }
    //check right position is on the board + not into a wall + not a treasure + not a trap
    if ( right.col < this->get_cols() ){
      SquareType rightsq = arr_[right.row][right.col];
      if (rightsq != SquareType::Wall && rightsq != SquareType::Treasure && rightsq != SquareType::Trap){
        accepted_moves.push_back(right);
      }
    }
    //check down position is on the board + not into a wall + not a treasure + not a trap
    if ( down.row < this->get_rows() ){
      SquareType downsq = arr_[down.row][down.col];
      if (downsq != SquareType::Wall && downsq != SquareType::Treasure && downsq != SquareType::Trap){
        accepted_moves.push_back(down);
      }
    }
    //check up position is on the board + not into a wall + not a treasure + not a trap
    if ( 0 <= up.row ){
      SquareType upsq = arr_[up.row][up.col];
      if (upsq != SquareType::Wall && upsq != SquareType::Treasure && upsq != SquareType::Trap){
        accepted_moves.push_back(up);
      }
    }
    return accepted_moves;
  }
}

//Move a player to a new position on the board. Return true if they moved successfully, false otherwise.
bool Board::MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist){
  //not a enemy or trap
  if(arr_[pos.row][pos.col] != SquareType::Enemies && arr_[pos.row][pos.col] != SquareType::PowerfulEnemy && arr_[pos.row][pos.col] != SquareType::Trap) {
    //dot
    if (arr_[pos.row][pos.col] == SquareType::Dots){
      p->ChangePoints(1);
    }
    //treasure
    if (arr_[pos.row][pos.col] == SquareType::Treasure){
      p->setHasTreasure();
      p->ChangePoints(100);
    }
    arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;
    if (p->hasTreasure() == true){
      arr_[pos.row][pos.col] = SquareType::PowerfulPacman;
    }
    else {
      arr_[pos.row][pos.col] = SquareType::Pacman;
    }
    p->SetPosition(pos);
    p->incrementMoves();
    return true;
  }
  //trap
  else if (arr_[pos.row][pos.col] == SquareType::Trap){
    p->setLives();
    p->incrementMoves();
    return false;
  }
  //destroys enemy
  else if (arr_[pos.row][pos.col] == SquareType::Enemies && arr_[p->get_position().row][p->get_position().col] == SquareType::PowerfulPacman){
    p->setHasTreasure();
    for (int i = 0; i<enemylist.size();i++){
      if (pos == enemylist[i]->get_position()){
        Player *e = enemylist[i];
        Position restart;
        restart.row = 9;
        restart.col = 0;
        MoveEnemy(e, restart);
        break;
      }
    }
    arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;
    if (p->hasTreasure() == true){
      arr_[pos.row][pos.col] = SquareType::PowerfulPacman;
    }
    else {
      arr_[pos.row][pos.col] = SquareType::Pacman;
    }
    p->SetPosition(pos);
    p->incrementMoves();
    return true;
  }
  //equal strength
  else if (arr_[pos.row][pos.col] == SquareType::PowerfulEnemy && arr_[p->get_position().row][p->get_position().col] == SquareType::PowerfulPacman){
    for (int i = 0; i<enemylist.size();i++){
      if (pos == enemylist[i]->get_position()){
        enemylist[i]->setHasTreasure();
        break;
      }
    }
    arr_[p->get_position().row][p->get_position().col] = SquareType::Pacman;
    p->setHasTreasure();
    p->incrementMoves();
    return false;
  }
  //enemy destroy player
  else {
    if (arr_[pos.row][pos.col] == SquareType::PowerfulEnemy){
      for (int i = 0; i<enemylist.size();i++){
        if (pos == enemylist[i]->get_position()){
          enemylist[i]->setHasTreasure();
          break;
        }
      }
    }
    p->setLives();
    p->incrementMoves();
    return false;
  }
}

//Move an enemy to a new position on the board. Return true if they moved successfully, false otherwise.
bool Board::MoveEnemy(Player *p, Position pos){
  //not a pacman
  if (arr_[pos.row][pos.col] != SquareType::Pacman && arr_[pos.row][pos.col] != SquareType::PowerfulPacman){
    //dots
    if (arr_[pos.row][pos.col] == SquareType::Dots){
      arr_[p->get_position().row][p->get_position().col] = SquareType::Dots;
    }
    //empty
    if (arr_[pos.row][pos.col] == SquareType::Empty){
      arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;
    }
    //powerup
    if (arr_[pos.row][pos.col] == SquareType::EnemySpecialTreasure){
      arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;
      p->setHasTreasure();
    }
    p->SetPosition(pos);
    if (p->hasTreasure() == true){
      arr_[pos.row][pos.col] = SquareType::PowerfulEnemy;
    }
    else {
      arr_[pos.row][pos.col] = SquareType::Enemies;
    }
    return true;
  }
  else {
    //player destroy enemy
    if (arr_[pos.row][pos.col] == SquareType::PowerfulPacman && p->hasTreasure() == false){
      Position restart;
      restart.row = 9;
      restart.col = 0;
      MoveEnemy(p, restart);
      return false;
    }
    //destroy pacman
    else if (arr_[pos.row][pos.col] == SquareType::Pacman && p->hasTreasure() == true){
      p->setHasTreasure();
      return true;
    }
  }
}

//print board
std::ostream& operator<<(std::ostream& os, const Board &b){
  for (int i = 0; i<b.get_rows(); i++){
    for (int j = 0; j<b.get_cols(); j++){
      os << SquareTypeStringify(b.arr_[i][j]) << "  ";
    }
    os << std::endl;
  }
  return os;
}

//initialize a Game with default values
Game::Game(){
  board_ = new Board();
  turn_count_ = 0;
  dots_count_ = 0;
  GameOver = false;
  
  for (int i = 0; i < board_->get_rows(); i++){
    for (int j = 0; j < board_->get_cols(); j++){
      Position temp;
      temp.row = i;
      temp.col = j; 
      if (board_->get_square_value(temp) == SquareType::Dots){
        dots_count_++;
      }
    }
  }
}

//initialize a new game, given one human player and a number of enemies to generate
void Game::NewGame(Player *human,std::vector<Player*> enemylist, const int enemies){
  players_.push_back(human);
  
  for (int i = 0; i<enemies; i++){
    players_.push_back(enemylist[i]);
    board_->SetSquareValue(enemylist[i]->get_position(), SquareType::Enemies);
    dots_count_--;
  }
}

//have the given Player take their turn
void Game::TakeTurn(Player *p,std::vector<Player*> enemylist){
  std::cout << p->Stringify() << std::endl;
  std::cout << *board_ << std::endl;
  std::vector<Position> choices = board_->GetMoves(p);
  std::vector<std::string> match_choice;
  std::string temp = "Pacman can go: ";
  for (int i = 0; i < choices.size(); i++){
    match_choice.push_back(p->ToRelativePosition(choices[i]));
    temp = temp + p->ToRelativePosition(choices[i]) + " ";
  }
  std::cout << temp << std::endl;
  std::string choice_move;
  std::cout << "Please enter your choice: ";
  std::cin >> choice_move;
  bool inthere = false;
  //check if valid value was passed
  while (inthere == false){
    std::string temp = "";
    for (int i = 0; i <choice_move.length();i++){
      temp = temp + tolower(choice_move[i], std::locale());
    }
    for (int i = 0; i<match_choice.size();i++){
      std::string temp2 = match_choice[i];
      std::string comp = "";
      for (int i = 0; i <choice_move.length();i++){
        comp = comp + tolower(temp2[i], std::locale());
      }
      if (temp == comp){
        inthere = true;
      }
    }
    if (inthere == true){
      break;
    }
    std::cout << "---Enter an Allowed Move---" << std::endl;
    std::cout << "Please enter your choice: ";
    std::cin >> choice_move;
  }
  //make the move according to input
  if (choice_move == "RIGHT" || choice_move == "right"){
    Position right;
    right.row = p->get_position().row;
    right.col = p->get_position().col+1;
    if (board_->get_square_value(right) == SquareType::Dots){
      dots_count_--;
    }
    board_->MovePlayer(p, right, enemylist);
  }
  else if (choice_move == "LEFT" || choice_move == "left"){
    Position left;
    left.row = p->get_position().row;
    left.col = p->get_position().col-1;
    if (board_->get_square_value(left) == SquareType::Dots){
      dots_count_--;
    }
    board_->MovePlayer(p, left, enemylist);
  }
  else if (choice_move == "DOWN" || choice_move == "down"){
    Position down;
    down.row = p->get_position().row+1;
    down.col = p->get_position().col;
    if (board_->get_square_value(down) == SquareType::Dots){
      dots_count_--;
    }
    board_->MovePlayer(p, down, enemylist);
  }
  else if (choice_move == "UP" || choice_move == "up"){
    Position up;
    up.row = p->get_position().row-1;
    up.col = p->get_position().col;
    if (board_->get_square_value(up) == SquareType::Dots){
      dots_count_--;
    }
    board_->MovePlayer(p, up, enemylist);
  }
  turn_count_++;
}

//have the enemy take turn
void Game::TakeTurnEnemy(Player *p){
  std::vector<Position> choices = board_->GetMoves(p);
  bool nopac = board_->MoveEnemy(p, choices[0]);
  //check if pacman was there
  if (nopac == false){
    if (players_[0]->hasTreasure() == true){
      players_[0]->setHasTreasure();
    }
    else {
      players_[0]->setLives();
    }
  }
}

//Prints status of game for the Player
bool Game::IsGameOver(Player *p){
  if (p->isDead() == true && p->is_human() == true){
    return true;
  }
  if (this->CheckifdotsOver() == true){
    return true;
  }
  return false;
}

//return true if all pellets have been collected
bool Game::CheckifdotsOver(){
  if (dots_count_ == 0){
    return true;
  }
  return false;
}

//string info about the game's conditions after it is over
std::string Game::GenerateReport(Player *p){
  std::string player_rep = "Pacman Score : " + std::to_string(p->get_points()) + " points.--Game Over-- \n";
  return player_rep;
}

//Print how many games there are going on with the player names and points
std::ostream& operator<<(std::ostream& os, const Game &m){
  os << (*m.board_) << std::endl;
  return os;
}