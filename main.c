#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
  float x;
  float y;
  float z;
} Position ;

void init_position(Position **obj, float x, float y, float z) {
  *obj = malloc(sizeof(Position));

  (*obj)->x = x;
  (*obj)->y= y;
  (*obj)->z = z;
}

void go_forward(Position *obj) {
  obj->x += 1;
}

void go_backward(Position *obj) {
  obj->x -= 1;
}

void go_left(Position *obj) {
  obj->z -= 1;
}

void go_right(Position *obj) {
  obj->z += 1;
}

void enable_raw_mode(struct termios *original) {
    struct termios raw;

    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}


int main() {
  struct termios original_termios;
  enable_raw_mode(&original_termios);

  Position *obj = NULL;
  init_position(&obj, 0, 0, 0);

  printf("[%f, %f, %f]\n", obj->x, obj->y, obj->z);

  while (1) {

    char ch = getchar();

    if (ch == 'q') {
      printf("Quitting");
      disable_raw_mode(&original_termios);
      free(obj);
      obj = NULL;
      return 0;
    }

    if (ch == 'w') {
      go_forward(obj);
      printf("[%f, %f, %f]\n", obj->x, obj->y, obj->z);
    }

    if (ch == 's') {
      go_backward(obj);
      printf("[%f, %f, %f]\n", obj->x, obj->y, obj->z);
    }

    if (ch == 'a') {
      go_left(obj);
      printf("[%f, %f, %f]\n", obj->x, obj->y, obj->z);
    }

    if (ch == 'd') {
      go_right(obj);
      printf("[%f, %f, %f]\n", obj->x, obj->y, obj->z);
    }

  }


}
