#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Player.h"
#include "Game.h"

TEST_CASE ( "Player object is initalized", "[parameterized constructor]") {
  Player p1 = Player("testing name", true);
  
  REQUIRE( p1.get_name() == "testing name" );
  REQUIRE( p1.get_position().row == 0 );
  REQUIRE( p1.get_position().col == 0 );
  REQUIRE( p1.is_human() == true );
  REQUIRE( p1.hasTreasure() == false );
  REQUIRE( p1.isDead() == false );
  REQUIRE( p1.getLives() == 3 );
  REQUIRE( p1.getMoves() == 0 );
}

TEST_CASE ( "translate position", "[ToRelativePosition]") {
  Player p1 = Player("testing name", true);
  
  Position pos;
  pos.row = 1;
  pos.col = 0;
  
  REQUIRE( p1.ToRelativePosition(pos) == "DOWN" );
  REQUIRE( p1.get_position().row == 0 );
  REQUIRE( p1.get_position().col == 0 );
}

TEST_CASE ( "Board object is initalized", "[default constructor]") {
  Board b1 = Board();

  REQUIRE( b1.get_rows() == 10 );
  REQUIRE( b1.get_cols() == 10 );
}

TEST_CASE ( "get positions a player could move to", "[GetMoves]") {
  Board b1 = Board();
  Player p1 = Player("testing name", true);
  Player *p = &p1;
  
  REQUIRE( b1.GetMoves(p).size() == 2 );
}

TEST_CASE ( "move enemy to new position", "[MoveEnemy]") {
  Board b1 = Board();
  Player p1 = Player("testing name", true);
  Player *p = &p1;
  Position pos;
  pos.row = 1;
  pos.col = 0;
  
  REQUIRE( b1.MoveEnemy( p, pos) == true );
}
