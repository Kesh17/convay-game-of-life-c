#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

#define SCALE 40
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define COL (WINDOW_HEIGHT / SCALE)
#define ROW (WINDOW_WIDTH / SCALE)

typedef struct Cell {
  bool alive;
} Cell;

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game-of-life");
  SetTargetFPS(15);

  Cell grid[COL][ROW];
  for (int i = 0; i < COL; i++) {
    for (int j = 0; j < ROW; j++) {
      grid[i][j].alive = false;
    }
  }

  bool isPaused = true;

  while (!WindowShouldClose()) {
    Cell new_grid[COL][ROW];

    BeginDrawing();

    if (IsKeyPressed(KEY_SPACE)) {
      isPaused = !isPaused;
    }

    if (isPaused) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        grid[GetMouseX() / SCALE][GetMouseY() / SCALE].alive = true;
      }
      for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
          int x = i * SCALE;
          int y = j * SCALE;

          if (grid[i][j].alive) {
            DrawRectangle(x, y, SCALE - 1, SCALE - 1, WHITE);
          }
        }
      }
    } else {
      for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {

          int state = grid[i][j].alive;
          int neighbour = 0;
          neighbour += grid[(i - 1 + COL) % COL][(j - 1 + ROW) % ROW].alive;
          neighbour += grid[(i + COL) % COL][(j - 1 + ROW) % ROW].alive;
          neighbour += grid[(i + 1 + COL) % COL][(j - 1 + ROW) % ROW].alive;
          neighbour += grid[(i + 1 + COL) % COL][(j + ROW) % ROW].alive;
          neighbour += grid[(i + 1 + COL) % COL][(j + 1 + ROW) % ROW].alive;
          neighbour += grid[(i + COL) % COL][(j + 1 + ROW) % ROW].alive;
          neighbour += grid[(i - 1 + COL) % COL][(j + 1 + ROW) % ROW].alive;
          neighbour += grid[(i - 1 + COL) % COL][(j + ROW) % ROW].alive;

          if (state == 0 && neighbour == 3) {
            new_grid[i][j].alive = true;
          } else if (state == 1 && (neighbour < 2 || neighbour > 3)) {
            new_grid[i][j].alive = false;
          } else {
            new_grid[i][j].alive = state;
          }
        }
      }

      for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
          grid[i][j].alive = new_grid[i][j].alive;
        }
      }

      for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
          int x = i * SCALE;
          int y = j * SCALE;

          if (grid[i][j].alive) {
            DrawRectangle(x, y, SCALE - 1, SCALE - 1, WHITE);
          }
        }
      }
    }
    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return EXIT_SUCCESS;
}
