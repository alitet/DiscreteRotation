#include "..\raylib\raylib.h"
#include "..\image\image.h"


int main()
{
  // Initialization
//--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  auto pxarr = LoadImageCenterGap("resources/cone10p10.png");

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    DrawCenterRefGrid(screenWidth, screenHeight, 10);
    DrawText("Discrete Grid Rotation", 10, 10, 10, DARKGRAY);

    DrawImageCenter(screenWidth, screenHeight, 10, pxarr);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}