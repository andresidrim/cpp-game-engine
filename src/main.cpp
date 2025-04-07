#include <game.hpp>
#include <raylib.h>

int main() {
  InitWindow(800, 600, "Fixed Camera With Movement");
  InitGame();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateGame();
  }

  CloseWindow();
  return 0;
}
