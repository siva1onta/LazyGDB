#include "TuiController.hh"

#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
  TuiController &tui = TuiController::GetInstance();

  bool run = true;
  while (run) {
    switch (tui.GetKey()) {
      case 'q':
        run = false;
        break;
      default:
        break;
    }
  }


  return 0;
}
