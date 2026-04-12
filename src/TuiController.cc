#include "TuiController.h"
#include "MainWindow.h"
#include "VariousWindow.h"
#include "StatusWindow.h"
#include "CommandWindow.h"
#include "FloatWindow.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <cstdio>
#include <cstring>

#include "Ulogger.h"

// Init
TuiController *TuiController::m_instance = nullptr;

// Constructor
TuiController::TuiController() {
  SetupTerm();
  InitWin();

  // Clear();
  int fd = 0;
  m_windows[0]->SetBufStr("Command: h for help");
  fd = open("/home/siva1onta/WORK/LazyGDB/data/test1.txt", O_RDONLY);
  m_windows[1]->SetBufFd(fd);
  close(fd);
  fd = open("/home/siva1onta/WORK/LazyGDB/data/test2.txt", O_RDONLY);
  m_windows[2]->SetBufFd(fd);
  close(fd);
  fd = open("/home/siva1onta/WORK/LazyGDB/data/test3.txt", O_RDONLY);
  m_windows[3]->SetBufFd(fd);
  close(fd);
  m_windows[3]->SetActive(true);
  Fresh();
}

//
TuiController::~TuiController() {
  Clear();
  RestoreTerm();
}

// Get the TuiController single instance
TuiController *TuiController::GetInstance() {
  if (m_instance == nullptr) {
    m_instance = new TuiController();
  }
  return m_instance;
}

void TuiController::DestoryInstance() {
  if (m_instance != nullptr) {
    delete m_instance;
    m_instance = nullptr;
  }
}

// Initialize the windows
void TuiController::InitWin() {
  winsize winsz;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz);
  int width = winsz.ws_col;
  int height = winsz.ws_row;

  m_windows.push_back(new CommandWindow(0, "Command"));
  m_windows.push_back(new StatusWindow(1, "Status"));
  m_windows.push_back(new VariousWindow(2, "Various"));
  m_windows.push_back(new MainWindow(3, "Main"));

  m_windows[0]->SetSizePos(3 - 2, width - 2, height - 1, 2);
  m_windows[1]->SetSizePos(12 - 2, 50 - 2, 2, 2);
  m_windows[2]->SetSizePos(height - 15 - 2, 50 - 2, 12 + 2, 2);
  m_windows[3]->SetSizePos(height - 4 - 1, width - 50 - 2, 2, 50 + 2);
}

// Config the windows' sizes
void TuiController::ConfigWinSz() {
  winsize winsz;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz);
  int width = winsz.ws_col;
  int height = winsz.ws_row;
}

// Clear the screen
void TuiController::Clear() {
  char buf[11] {0};
  strcpy(buf, "\033[2J\033[1;1H");
  write(STDOUT_FILENO, buf, 10);
}

// Flesh the terminal
void TuiController::Fresh() {
  Clear();
  Window *activewindow = nullptr;
  for (Window *iter : m_windows) {
    if (iter->GetActive()) {
      activewindow = iter;
    } else {
      iter->Print();
    }
  }
  activewindow->Print();
}

bool TuiController::CommandChar(char cmd) {
  for (Window *iter : m_windows) {
    if (iter->GetActive()) {
      if (iter->CommandChar(cmd)) {
        Fresh();
        return true;
      }
    }
  }
  switch (cmd) {
    case '0' :
    case '1' :
    case '2' :
    case '3' :
      for (Window *iter : m_windows) {
        iter->SetActive(cmd - '0' == iter->GetId());
      }
      Fresh();
      return true;
    default :
      return false;
  }
}

void TuiController::SetupTerm() {
  tcgetattr(STDIN_FILENO, &m_preterm);

  m_currterm = termios(m_preterm);
  m_currterm.c_lflag &= ~ECHO;
  m_currterm.c_lflag &= ~ICANON;

  tcsetattr(STDIN_FILENO, TCSANOW, &m_currterm);
}

void TuiController::RestoreTerm() {
  tcsetattr(STDIN_FILENO, TCSANOW, &m_preterm);
}

