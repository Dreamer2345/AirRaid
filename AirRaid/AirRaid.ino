#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Tinyfont.h"
Arduboy2 ard;
Tinyfont tinyfont = Tinyfont(ard.sBuffer, Arduboy2::width(), Arduboy2::height());
Sprites sprites;
ArduboyTones sound(ard.audio.enabled);

#include "Music.h"
#include "Bitmaps.h"
#include "ENums.h"
#include "Player.h"
#include "Game.h"

void setup() {
  ard.boot();
  ard.flashlight();
  ard.audio.begin();
  ard.setFrameRate(30);
  ard.initRandomSeed();
  
  ard.clear();
  sprites.drawSelfMasked(CENTERX-26,CENTERY-17,MainLogo,0);
  ard.display();
  delay(1000);
}


void loop() {
  if(!ard.nextFrame())
    return;

  ard.pollButtons();
  ard.clear();

  switch(gameState)
  {
    case GameState::MainMenu: UpdateMainMenu(); break;
    case GameState::GameStart: GameInit(); break;
    case GameState::Game: UpdateGame(); break;
    case GameState::Dead: Death(); break;
    case GameState::NewLevel: NewLevel(); break;
  }
  ard.display();
  
}
