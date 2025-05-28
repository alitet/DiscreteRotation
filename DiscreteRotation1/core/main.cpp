#include "..\raylib\raylib.h"
#include "..\image\image.h"


int main()
{
  // Init
  const int scW = 800;
  const int scH = 600;

  InitWindow(scW, scH, "raylib [core] example - basic window");

  SetTargetFPS(60);

  auto pxarr = LoadImageCenterGap("resources/cone10p10.png");
  auto rtarr = pxarr;

  float rang = 0.f;

  while (!WindowShouldClose())    //close button or ESC key
  {
    // Update
    //if (IsKeyDown(KEY_DOWN)) {
    //  rang += 6.f;
    //  if (rang > 360.f) { rang -= 360.f; }
    //  rtarr = rotateForward(pxarr, rang);
    //}

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