#include "..\raylib\raylib.h"
#include "..\image\image.h"
#include <iostream>

int main()
{
  // Init
  const int scW = 800;
  const int scH = 600;

  const int16_t FWDX = 12;
  const int16_t FWDY = 10;

  //const int16_t FWDX = 0;
  //const int16_t FWDY = 0;

  const int16_t BCKX = -12;
  const int16_t BCKY = 10;

  InitWindow(scW, scH, "raylib [core] example - basic window");

  SetTargetFPS(60);

  auto pxarr = LoadImageCenterGap("resources/cone10p10.png");
  //auto pxarr = LoadImageCenterGap("resources/nave11p11.png");



  //sImgData rtarrFW{ pxarr.ws, pxarr.hs, {pxarr.pixels.begin(), pxarr.pixels.end()} };
  //sImgData mvarrFW; //mvarrFW.pixels.resize(rtarrFW.pixels.size());
  //moveImage(rtarrFW, mvarrFW, FWDX, FWDY);
  ////moveImage(rtarrFW, mvarrFW, 0, 0);

  //sImgData rtarrBK{ pxarr.ws, pxarr.hs, {pxarr.pixels.begin(), pxarr.pixels.end()} };
  //sImgData mvarrBK; //mvarrBK.pixels.resize(rtarrBK.pixels.size());
  //moveImage(rtarrBK, mvarrBK, BCKX, BCKY);

  float rang = 0.f;

  while (!WindowShouldClose())    //close button or ESC key
  {
    // Update
    //float dtime = GetFrameTime();

    //if (IsKeyDown(KEY_UP)) {
    //  rang += 6.f;
    //  if (rang >= 360.f) { rang -= 360.f; }
    //  //std::cout << "rot: " << rang << std::endl;
    //  rotateForward(pxarr, rtarrFW, rang);
    //  moveImage(rtarrFW, mvarrFW, FWDX, FWDY);
    //  //moveImage(rtarrFW, mvarrFW, 0, 0);

    //  rotateBackward(pxarr, rtarrBK, rang);
    //  moveImage(rtarrBK, mvarrBK, BCKX, BCKY);
    //  //moveImage(rtarrBK, mvarrBK, BCKX, BCKY);
    //}

    // Draw
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    DrawCenterRefGrid(scW, scH, 10);
    DrawText("Discrete Grid Rotation", 10, 10, 10, DARKGRAY);

    DrawImageCenter(scW, scH, 10, pxarr);// mvarrFW);

   // DrawImageCenter(scW, scH, 10, mvarrBK);


    DrawCenterRefCross(scW, scH, 10);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}