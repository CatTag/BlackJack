#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card {
  int value;
  int color;
  int type;
  int special;
  bool exists;
};

int max(int a, int max) {
  if (a > max) {
    return max;
  } else {
    return a;
  }
}

void shuffle(struct card *buf) {
  int picked[52];
  for (int i = 0; i < 52; i++) {
    picked[i] = i;
  }
  int pickediter = 51;
  struct card tempdeck[52];
  int temprand;
  while (pickediter >= 0) {
    if (pickediter > 0) {
      temprand = rand() % pickediter;
      tempdeck[51 - pickediter] = buf[picked[temprand]];
      for (int i = temprand; i < 51; i++) {
        picked[i] = picked[i + 1];
      }
      pickediter--;
    } else {
      tempdeck[51] = buf[0];
      break;
    }
  }
  for (int i = 0; i < 52; i++) {
    buf[i] = tempdeck[i];
  }
}

void drawheart(Vector2 pos, float height, float radius, Color color) {

  DrawCircle(pos.x, pos.y, radius, color);
  DrawCircle(pos.x + 2 * radius, pos.y, radius, color);
  Vector2 pos1 = {pos.x - (height * sin(2 * atan(radius / height)) - radius),
                  pos.y + (height - (height * cos(2 * atan(radius / height))))};
  Vector2 pos2 = {pos.x + radius, pos.y + height};

  Vector2 pos3 = {pos.x + 2 * radius +
                      (height * sin(2 * atan(radius / height)) - radius),
                  pos.y + (height - (height * cos(2 * atan(radius / height))))};

  DrawTriangle(pos1, pos2, pos3, color);
  DrawRectangle(pos.x, pos.y, radius * 2, radius, color);
}
void drawspade(Vector2 pos, float height, float radius, Color color) {

  DrawCircle(pos.x, pos.y, radius, color);
  DrawCircle(pos.x + 2 * radius, pos.y, radius, color);
  Vector2 pos1 = {pos.x - (height * sin(2 * atan(radius / height)) - radius),
                  pos.y - (height - (height * cos(2 * atan(radius / height))))};
  Vector2 pos2 = {pos.x + radius, pos.y - height};

  Vector2 pos3 = {pos.x + 2 * radius +
                      (height * sin(2 * atan(radius / height)) - radius),
                  pos.y - (height - (height * cos(2 * atan(radius / height))))};

  DrawTriangle(pos1, pos3, pos2, color);
  DrawRectangle(pos.x, pos.y - radius, radius * 2, radius, color);
  DrawRectangle(pos.x + radius / 2., pos.y, radius, radius + height / 4.,
                color);
}
void drawdiamond(Vector2 pos, float width, float height, Color color) {
  Vector2 pos2 = {pos.x - width / 2., pos.y + height / 2.};
  Vector2 pos3 = {pos.x + width / 2., pos.y + height / 2.};
  Vector2 pos4 = {pos.x, pos.y + height};
  DrawTriangle(pos, pos2, pos3, color);
  DrawTriangle(pos2, pos4, pos3, color);
}
void drawclub(Vector2 pos, float radius, Color color) {
  DrawCircle(pos.x, pos.y, radius, color);
  DrawCircle(pos.x + 3 * radius, pos.y, radius, color);
  DrawCircle(pos.x + 1.5 * radius, pos.y - 1.5 * radius, radius, color);
  DrawRectangle(pos.x, pos.y - radius / 4., 3 * radius, radius / 2., color);
  DrawRectangle(pos.x + 1.5 * radius - radius / 4., pos.y - 1.5 * radius,
                radius / 2., 3.5 * radius, color);
}

void drawblankcard(Vector2 pos, float width, float height) {

  DrawRectangle(pos.x + 10, pos.y, width - 20, height, WHITE);
  DrawRectangle(pos.x, pos.y + 10, width, height - 20, WHITE);
  DrawCircle(pos.x + 10, pos.y + 10, 10, WHITE);
  DrawCircle(pos.x + 10, pos.y + height - 10, 10, WHITE);
  DrawCircle(pos.x + width - 10, pos.y + 10, 10, WHITE);
  DrawCircle(pos.x + width - 10, pos.y + height - 10, 10, WHITE);
}

void drawcard(Vector2 pos, float width, float height, int num, int type,
              int special, int color) {
  float offset = 0;
  Color cardcolor;
  Vector2 typepos;
  if (color == 0) {
    cardcolor = BLACK;
  } else {
    cardcolor = RED;
  }
  DrawRectangle(pos.x + 10, pos.y, width - 20, height, WHITE);
  DrawRectangle(pos.x, pos.y + 10, width, height - 20, WHITE);
  DrawCircle(pos.x + 10, pos.y + 10, 10, WHITE);
  DrawCircle(pos.x + 10, pos.y + height - 10, 10, WHITE);
  DrawCircle(pos.x + width - 10, pos.y + 10, 10, WHITE);
  DrawCircle(pos.x + width - 10, pos.y + height - 10, 10, WHITE);
  switch (special) {
  case 0:
    if (num >= 10) {
      offset = 6;
    }
    DrawText(TextFormat("%i", num), pos.x + (width / 2. - 10) - offset,
             pos.y + 20, 40, cardcolor);
    break;
  case 1:
    DrawText("J", pos.x + (width / 2. - 10), pos.y + 20, 40, cardcolor);
    break;

  case 2:
    DrawText("Q", pos.x + (width / 2. - 10) - 2, pos.y + 20, 40, cardcolor);
    break;

  case 3:
    DrawText("K", pos.x + (width / 2. - 10) - 2, pos.y + 20, 40, cardcolor);
    break;
  case 4:
    DrawText("A", pos.x + (width / 2. - 10) - 4, pos.y + 20, 40, cardcolor);
    break;
  default:
    break;
  }
  if (type == 0) {
    typepos = pos;
    typepos.x += 38;
    typepos.y += 100;
    drawspade(typepos, 38.4, 12, cardcolor);
  }
  if (type == 1) {
    typepos = pos;
    typepos.x += 32;
    typepos.y += 100;
    drawclub(typepos, 12, cardcolor);
  }
  if (type == 2) {
    typepos = pos;
    typepos.x += 38;
    typepos.y += 80;
    drawheart(typepos, 38.4, 12, cardcolor);
  }
  if (type == 3) {
    typepos = pos;
    typepos.x += 50;
    typepos.y += 70;
    drawdiamond(typepos, 40, 60, cardcolor);
  }
}

void newgame(struct card *player, struct card *dealer, struct card *maindeck,
             int deckiter) {
  if (deckiter >= 48) {
    deckiter = 0;
  }
  player[0] = maindeck[deckiter];
  player[1] = maindeck[deckiter + 1];
  dealer[0] = maindeck[deckiter + 2];
  dealer[1] = maindeck[deckiter + 3];
  for (int i = 2; i < 11; i++) {
    player[i].exists = false;
    dealer[i].exists = false;
  }
}

int main(void) {
  InitWindow(1280, 720, "Blackjack");
  srand(time(0));
  struct card maindeck[52];
  int deckiter = 0;
  int vertpos = 0;
  char drawval[2];
  char drawtype[8];
  char drawcolor[5];
  int typecount = 0;
  int multiiter = 0;
  int count = 0;
  float curtime = 0.;
  int dealercount = 0;
  bool ace = false;
  Vector2 drawpos = {0, 0};
  bool stand = false;
  bool overtwentyone = false;
  bool newgamepressed = true;
  bool loss = false;
  bool win = false;
  bool hashit = false;
  int money = 100;
  int bet = 0;
  bool hitbutton = false;
  bool standbutton = false;
  float totaltime = 0.;
  Vector2 mousepos = {0, 0};
  for (int i = 0; i < 52; i++) {
    maindeck[i].value = max(i % 13 + 1, 10);
    if (i < 26) {
      maindeck[i].color = 0;
    } else {
      maindeck[i].color = 1;
    }
    if (i == 13 || i == 26 || i == 39) {
      typecount++;
    }
    maindeck[i].type = typecount;
    if (i % 13 + 1 == 11) {
      maindeck[i].special = 1;
    } else if (i % 13 + 1 == 12) {
      maindeck[i].special = 2;
    } else if (i % 13 + 1 == 13) {
      maindeck[i].special = 3;
    } else if (i % 13 + 1 == 1) {
      maindeck[i].special = 4;
    } else {
      maindeck[i].special = 0;
    }
    maindeck[i].exists = true;
  }
  shuffle(maindeck);
  struct card player[11];
  struct card dealer[11];
  for (int i = 0; i < 11; i++) {
    if (i < 2) {
      player[i].exists = true;
      dealer[i].exists = true;
    } else {
      player[i].exists = false;
      dealer[i].exists = false;
    }
  }
  dealer[0] = maindeck[deckiter];
  dealer[1] = maindeck[deckiter + 1];
  player[0] = maindeck[deckiter + 2];
  player[1] = maindeck[deckiter + 3];
  deckiter += 4;
  multiiter = 2;

  while (!WindowShouldClose()) {
    if (!overtwentyone && !stand) {
      // printf("test\n");

      mousepos = GetMousePosition();
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (mousepos.x > 800 && mousepos.x < 900 && mousepos.y > 100 &&
            mousepos.y < 200) {
          stand = true;
          multiiter = 2;
          curtime = totaltime + 1.;
          standbutton = true;
        }
        if (mousepos.x > 1000 && mousepos.x < 1100 && mousepos.y > 100 &&
            mousepos.y < 200 && !stand && !hitbutton) {
          hashit = true;
          hitbutton = true;
          player[multiiter] = maindeck[deckiter];
          player[multiiter].exists = true;
          multiiter++;
          if (deckiter >= 51) {
            deckiter = 0;
          } else {
            deckiter++;
          }
        }
      } else {
        hitbutton = false;
        standbutton = false;
      }
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!hashit) {
          if (mousepos.x > 800 && mousepos.x < 850 && mousepos.y > 625 &&
              mousepos.y < 675) {
            if (bet != money*0.2) {
            bet = money * 0.2;
            } else {
              bet = 0;
            }
          }
          if (mousepos.x > 875 && mousepos.x < 925 && mousepos.y > 625 &&
              mousepos.y < 675) {
            if (bet != money*0.5) {
            bet = money * 0.5;
            } else {
              bet = 0;
            }
          }
          if (mousepos.x > 725 && mousepos.x < 775 && mousepos.y > 625 &&
              mousepos.y < 675) {
            if (bet != money*0.1) {
            bet = money * 0.1;
            } else {
              bet = 0;
            }
          }
          if (mousepos.x > 975 && mousepos.x < 1025 && mousepos.y > 625 &&
              mousepos.y < 675) {
            if (bet != money) {
            bet = money;
            } else {
              bet = 0;
            }
          }
        }
      }
      ace = false;
      count = 0;
      for (int i = 0; i < 11; i++) {
        if (!player[i].exists) {
          break;
        }
        count += player[i].value;
        if (player[i].special == 4) {
          ace = true;
        }
      }
      if (ace && count <= 11) {
        count += 10;
      }
      if (count > 21) {
        overtwentyone = true;
        money -= bet;
        bet = 0;
        curtime = totaltime + 1.;
        multiiter = 2;
      }
    } else if (stand) {
      ace = false;
      dealercount = 0;
      for (int i = 0; i < 11; i++) {
        if (!dealer[i].exists) {
          break;
        }
        dealercount += dealer[i].value;
        if (dealer[i].special == 4) {
          ace = true;
        }
      }
      if (ace && dealercount <= 11) {
        dealercount += 10;
      }
      if (dealercount > 21) {
        win = true;
        money += bet;
        bet = 0;
        if (totaltime > curtime) {
          win = false;
          newgame(player, dealer, maindeck, deckiter);
          standbutton = false;
          hashit = false;
          multiiter = 1;
          stand = false;
          if (deckiter >= 48) {
            deckiter = 0;
          } else {
            deckiter += 4;
          }
          overtwentyone = false;
        }
      }
      if (dealercount > count && !win) {
        loss = true;
        money -= bet;
        bet = 0;
        if (totaltime > curtime) {
          newgame(player, dealer, maindeck, deckiter);
          standbutton = false;
          hashit = false;
          loss = false;
          multiiter = 1;
          stand = false;
          if (deckiter >= 48) {
            deckiter = 0;
          } else {
            deckiter += 4;
          }
          overtwentyone = false;
        }
      }
      if (totaltime > curtime) {
        curtime = totaltime + 1.;
        dealer[multiiter] = maindeck[deckiter];
        multiiter++;
        if (deckiter >= 51) {
          deckiter = 0;
        } else {
          deckiter++;
        }
      }
    }
    if (overtwentyone && totaltime > curtime) {
      newgame(player, dealer, maindeck, deckiter);
      hashit = false;
      multiiter = 2;
      stand = false;
      deckiter += 4;
      overtwentyone = false;
    }

    totaltime += GetFrameTime();
    BeginDrawing();
    Color tempred = {155,0,0,255};
    ClearBackground(GRAY);
    DrawText("Stand", 805, 50, 30, WHITE);
    DrawCircle(850, 150, 50, WHITE);
    DrawCircle(850,150,40, tempred);
    if (!standbutton) {
    DrawRectangle(810, 140, 80, 10, tempred);
    DrawCircle(850,140,40, RED);
    }
    DrawText("Hit", 1030, 50, 30, WHITE);
    DrawCircle(1050, 150, 50, WHITE);
    DrawCircle(1050,150,40, tempred);
    if (!hitbutton && !stand) {
    DrawRectangle(1010, 140, 80, 10, tempred);
    DrawCircle(1050,140,40, RED);
    }
    DrawText(TextFormat("Bet: $%i", bet), 50, 650, 30, WHITE);
    DrawText(TextFormat("Bank: $%i", money), 50, 600, 30, WHITE);
    if (!hashit && !stand) {
      DrawText("20%", 810, 600, 20, WHITE);
      DrawCircle(825, 650, 25, WHITE);
      DrawCircle(825, 650, 20, RED);
      if (bet == money*0.2) {
      DrawRectangle(825, 630, 20, 20, RED);
      } else {
      DrawRectangle(805, 630, 20, 20, RED);
      }
      DrawText("50%", 885, 600, 20, WHITE);
      DrawCircle(900, 650, 25, WHITE);
      DrawCircle(900, 650, 20, RED);
      if (bet == money*0.5) {
      DrawRectangle(900, 630, 20, 20, RED);
      } else {
      DrawRectangle(880, 630, 20, 20, RED);
      }
      DrawText("10%", 740, 600, 20, WHITE);
      DrawCircle(750, 650, 25, WHITE);
      DrawCircle(750, 650, 20, RED);
      if (bet == money*0.1) {
      DrawRectangle(750, 630, 20, 20, RED);
      } else {
      DrawRectangle(730, 630, 20, 20, RED);
      }
      DrawText("All in!", 970, 600, 20, WHITE);
      DrawCircle(1000, 650, 25, WHITE);
      DrawCircle(1000, 650, 20, RED);
      if (bet == money) {
      DrawRectangle(1000, 630, 20, 20, RED);
      } else {
      DrawRectangle(980, 630, 20, 20, RED);
      }
    }
    DrawText("Dealers Cards:", 20, 20, 60, WHITE);
    drawpos.x = 40;
    drawpos.y = 100;
    for (int i = 0; i < 11; i++) {
      if (!dealer[i].exists) {
        break;
      }
      if (i >= 1 && !stand) {
        drawblankcard(drawpos, 100, 150);
      } else {
        drawcard(drawpos, 100, 150, dealer[i].value, dealer[i].type,
                 dealer[i].special, dealer[i].color);
        drawpos.x += 120;
      }
    }
    DrawText("Players Cards:", 20, 300, 60, WHITE);
    drawpos.x = 40;
    drawpos.y = 380;
    for (int i = 0; i < 11; i++) {
      if (!player[i].exists) {
        break;
      }
      drawcard(drawpos, 100, 150, player[i].value, player[i].type,
               player[i].special, player[i].color);
      drawpos.x += 120;
    }
    if (overtwentyone) {
      DrawText("Over Twenty One!", 200, 200, 100, GREEN);
    }
    if (loss) {
      DrawText("You Lost!", 500, 400, 100, GREEN);
    }
    if (win) {
      DrawText("You Win!", 500, 400, 100, GREEN);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
