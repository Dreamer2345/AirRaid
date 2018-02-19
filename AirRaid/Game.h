#pragma once


void GameInit(){
  for(int i=0; i<MAXBUILDINGS; ++i){
    Buildings[i].Height = random(0,4);
    Buildings[i].Type = random(0,3);
    Buildings[i].Hit = false;
  }
  Points = 0;
  PlayerObj.x = 0;
  PlayerObj.y = 0;
  gameState = GameState::Game;
}

void DrawBuildings(){
  for(int i=0; i<16; ++i){
    sprites.drawSelfMasked(i*8,55,Tiles,5);
  }
  uint8_t Tile = 0;
  for(int i=0; i<MAXBUILDINGS; ++i){
    for(int j=0; j<Buildings[i].Height; ++j){
      if (j != Buildings[i].Height-1){
        if (Buildings[i].Type <= 1)
          Tile = 1;
        else
          Tile = 2;
      } else {
        if (Buildings[i].Type % 2 == 0)
          if (Buildings[i].Hit)
            Tile = 8;
          else
            Tile = 0;
        else
          if (Buildings[i].Hit)
            Tile = 7;
          else
            Tile = 3;
      }
      sprites.drawOverwrite(i*8,55-((j+1)*8),Tiles,Tile); 
    }
  }
}

void DrawPoints(){
  tinyfont.setCursor(0, 0);
  tinyfont.print(F("Points:"));
  tinyfont.print(Points);
}

void DrawPlayer(){
  sprites.drawSelfMasked((PlayerObj.x-1) * 8,PlayerObj.y * 8,PlaneTiles,0); 
  sprites.drawSelfMasked(PlayerObj.x * 8,PlayerObj.y * 8,PlaneTiles,PlayerObj.Frame+1);
}

void BulletUpdate(){
  if (Bullet.Active){
    if(ard.everyXFrames(10))
      Bullet.Update();
    uint8_t Local = (Buildings[Bullet.x].Height);
    uint8_t bombheight = (7 - Bullet.y);
    if (Local >= bombheight){
      if (Local>0){
        if (Buildings[Bullet.x].Hit == false) Buildings[Bullet.x].Hit = true;
        Buildings[Bullet.x].Height--;
        Points++;
        sound.noTone();
        sound.tone(NOTE_E3,50,NOTE_C4,50,NOTE_G5,50);
        sprites.drawSelfMasked(Bullet.x * 8,Bullet.y * 8,Tiles,6);
        }
      Bullet.Active = false; 
    } else 
      Bullet.Display();
  }
}

void PlayerCheck(){
  uint8_t Local = (Buildings[PlayerObj.x % 16].Height);
  uint8_t Playerheight = (7 - PlayerObj.y);
    if (Local >= Playerheight){
      gameState = GameState::Dead;  
    }
  bool BuildingsActive = false;
  for(int i=0; i<MAXBUILDINGS; ++i){
    if (Buildings[i].Height > 0){BuildingsActive = true; break;}
  }
  
  if (BuildingsActive == false){
    gameState = GameState::NewLevel; 
    PlayerObj.y = 6;
    PlayerObj.x = 0;
  }
}

void NewLevel(){
  DrawBuildings();
  DrawPlayer();
  if (!sound.playing()) 
    sound.tones(Win);
  ard.setCursor(CENTERX-27,CENTERY-3);
  ard.print(F("WELL DONE"));
  if(ard.everyXFrames(5)) PlayerObj.Frame = !PlayerObj.Frame;
  if (PlayerObj.x == 7) {  
    for(int i=0; i<MAXBUILDINGS; ++i){
      Buildings[i].Height = random(0,4);
      Buildings[i].Type = random(0,3);
      Buildings[i].Hit = false;
    }
    PlayerObj.x = 0;
    PlayerObj.y = 0;
    Bullet.Active = false;
    gameState = GameState::Game;
    }
  if ((ard.everyXFrames(15)) && PlayerObj.x != 7) PlayerObj.x++;
}

void Death(){
  ard.setCursor(CENTERX-27,CENTERY-3);
  ard.print(F("GAME OVER"));
  ard.setCursor(CENTERX-42,CENTERY+5);
  ard.print(F("POINTS:"));
  ard.print(Points);
  if (ard.justPressed(B_BUTTON)||ard.justPressed(DOWN_BUTTON)||ard.everyXFrames(250)){
    gameState = GameState::MainMenu;
  }
}

void UpdateMainMenu(){
  if (!sound.playing())
    sound.tones(Title);
  sprites.drawSelfMasked(0,0,Logo,0);
  if (ard.justPressed(A_BUTTON)){
    Audio = !Audio;
    sound.noTone();
    sound.tone(NOTE_C4,100);
    if (Audio){ard.audio.on();}else{ard.audio.off();}
  }
  if (ard.justPressed(B_BUTTON)||ard.justPressed(DOWN_BUTTON)){
    sound.noTone();
    gameState = GameState::GameStart;
  }  
}

void UpdateGame(){
  if (!sound.playing()) {
  sound.tone(NOTE_C2,10,NOTE_REST,10);
  }
  PlayerObj.PlayerMovement();
  PlayerCheck();
  BulletUpdate();
  DrawPlayer();
  DrawBuildings();
  DrawPoints();
}

