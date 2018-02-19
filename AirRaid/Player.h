class PlayerClass {
  public:
  uint16_t x;
  uint16_t y;
  uint8_t Frame;
  void PlayerMovement();
};

PlayerClass PlayerObj;

class BulletClass{
  public:
  BulletClass(){}  
  void Update();
  void Display();
  bool Active;
  uint8_t x;
  uint8_t y;
};


void BulletClass::Update(){
  if (!Active){return;}
  y+=1;
}

void BulletClass::Display(){
  int _x = x*8;
  int _y = y*8;
  sprites.drawSelfMasked(_x,_y,Tiles,4);
}

BulletClass Bullet;

void PlayerClass::PlayerMovement() {
  if(ard.everyXFrames(5)) Frame = !Frame;
  if(ard.everyXFrames(15))
    if (x < 16) { x++; }
    else {y++; x = 0;}
    
  if (ard.justPressed(B_BUTTON)||ard.justPressed(DOWN_BUTTON)){
      if (Bullet.Active == false) {
        Bullet.x = x;
        Bullet.y = y;
        Bullet.Active = true;
      }
    }
}
