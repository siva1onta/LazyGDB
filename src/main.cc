#include "TuiController.h"

#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Ulogger.h"

int main(int argc, char **argv) {
  Ulogger *log = Ulogger::GetInstance();
  log->SetLevel(Ulogger::DEBUG);
  log->Open("./data/LazyGDB.log");

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
