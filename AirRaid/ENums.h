#pragma once

#define CENTERX 63
#define CENTERY 31
#define MAXBUILDINGS 16

uint16_t Points = 0;
bool Audio = true;

struct Building {
  bool Hit = false;
  uint8_t Height = 0;
  uint8_t Type = 0;
} Buildings[MAXBUILDINGS];


enum class GameState { 
      MainMenu, 
      GameStart,
      NewLevel, 
      Game ,
      Dead ,
};

GameState gameState = GameState::MainMenu;
