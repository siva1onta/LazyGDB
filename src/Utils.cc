#include "Utils.hh"

#include <unistd.h>

#include <cstdio>

void MoveCursor(int x, int y) {
  char buf[32] {0};
  int len = snprintf(buf, sizeof(buf), "\033[%d;%dH", x, y);
  write(STDOUT_FILENO, buf, len);
}
