#include "..\raylib\raylib.h"
#include "..\image\image.h"
#include <iostream>

int main()
{
  // Init
  const int scW = 800;
  const int scH = 600;

  InitWindow(scW, scH, "raylib [core] example - basic window");

  SetTargetFPS(60);

  auto pxarr = LoadImageCenterGap("resources/cone10p10.png");
  sImgData rtarr{ pxarr.ws, pxarr.hs, {pxarr.pixels.begin(), pxarr.pixels.end()} };

  float rang = 0.f;

  while (!WindowShouldClose())    //close button or ESC key
  {
    // Update
    //float dtime = GetFrameTime();

    if (IsKeyDown(KEY_UP)) {
      rang += 6.f;
      if (rang >= 360.f) { rang -= 360.f; }
      //std::cout << "rot: " << rang << std::endl;
      rotateForward(pxarr, rtarr, rang);
    }

    // Draw
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    DrawCenterRefGrid(scW, scH, 10);
    DrawText("Discrete Grid Rotation", 10, 10, 10, DARKGRAY);

    DrawImageCenter(scW, scH, 10, rtarr);


    DrawCenterRefCross(scW, scH, 10);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}