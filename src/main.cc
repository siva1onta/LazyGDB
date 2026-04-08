#include "TuiController.h"

#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
  TuiController *tui = TuiController::GetInstance();

  bool run = true;
  char cmd;
  while (run) {
    cmd = getchar();
    switch (cmd) {
      case 'q' :
        run = false;
        break;
      default :
        tui->CommandChar(cmd);
        break;
    }
  }

  TuiController::DestoryInstance();
  return 0;
}
