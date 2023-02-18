#include "Player.h"

#include <iostream>
#include <string>

//initialize a Player with the given name and whether or not it is player
Player::Player(const std::string name, const bool is_human){
  name_ = name;
  points_ = 0;
  pos_.row = 0;
  pos_.col = 0;
  is_human_ = is_human;
  has_Treasure_ = false;
  isDead_ = false;
  lives_ = 3;
  moves_ = 0;
}

//update the points_ value according to the int passed in
void Player::ChangePoints(const int x){
  points_ = points_ + x;
}

//update the Player's pos_ to the new position
void Player::SetPosition(Position pos){
  pos_.row = pos.row;
  pos_.col = pos.col;
}

//checks if the player owns a treasure
void Player::setHasTreasure(){
  has_Treasure_ = !has_Treasure_;
}

//checks if the player is dead
void Player::setIsDead(bool isdead){
  isDead_ = isdead;
}

//updates the lives for a player
void Player::setLives(){
  lives_--;
}

//translate the other position into a direction relative to the Player by comparing other with pos_
std::string Player::ToRelativePosition(Position other){
  Position left; 
  Position right;
  Position down;
  Position up;
  std::string translation = "NOT SET";
  
  left.row = this->pos_.row;
  left.col = this->pos_.col-1;
  
  right.row = this->pos_.row;
  right.col = this->pos_.col+1;
  
  down.row = this->pos_.row+1;
  down.col = this->pos_.col;
  
  up.row = this->pos_.row-1;
  up.col = this->pos_.col;
  
  if ( left == other ){
    translation = "LEFT";
  }
  if ( right == other ){
    translation = "RIGHT";
  }
  if ( down == other ){
    translation = "DOWN";
  }
  if ( up == other ){
    translation = "UP";
  }
  
  return translation;
}

//Convert this player to a string representation of their name and points
std::string Player::Stringify(){
  std::string player_rep = "Lives remaining: " + std::to_string(lives_) + '\n' + "Number of moves by Ngozi: " + std::to_string(moves_) + '\n';
  return player_rep;
}

//this method should return the number of moves made by the player in this game 
int Player::getMoves(){
  return moves_;
}

//update the number of moves in each human player's turn
void Player::incrementMoves(){
  moves_++;
}