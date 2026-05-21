/*Desing an structure for circle.
Draw a circle on of * on the screen.
Hint use a 2d buffer.
Modularise into at least 4 functions.
*/
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 24

typedef struct {
  int x, y, r;
} Circle;

void initBuffer(char buffer[HEIGHT][WIDTH]);
void drawCircle(Circle c, char buffer[HEIGHT][WIDTH]);
void printBuffer(char buffer[HEIGHT][WIDTH]);

int main() {
  Circle c;
  printf("Enter the radius of the circle");
  if (scanf("%d", &c.r) != 1) {
    return 1;
  }
  
  c.x = WIDTH / 2;
  c.y = HEIGHT / 2;

  char buffer[HEIGHT][WIDTH];
  initBuffer(buffer);
  drawCircle(c, buffer);
  printBuffer(buffer);

  return 0;
}

void initBuffer(char buffer[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      buffer[i][j] = ' ';
    }
  }
}

void drawCircle(Circle c, char buffer[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int dy = i - c.y;
      int dx = j - c.x;
      // Using aspect ratio correction: (x - cx)^2 + 4 * (y - cy)^2 <= 4 * r^2
      if (dx * dx + 4 * dy * dy <= 4 * c.r * c.r) {
        buffer[i][j] = '*';
      }
    }
  }
}

void printBuffer(char buffer[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf("%c", buffer[i][j]);
    }
    printf("\n");
  }
}