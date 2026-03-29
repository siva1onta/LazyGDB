#include "TuiController.hh"
#include "Utils.hh"

#include <unistd.h>
#include <sys/ioctl.h>

#include <cstdio>

// Init
TuiController TuiController::m_instance = TuiController();

// Constructor
TuiController::TuiController() {
  SetupTerm();
  InitWin();

  // Clear();
  m_cmdwin.SetBufStr("Command:");
  m_statuswin.SetBufStr("Status:");
  m_valuewin.SetBufStr("Value:");
  m_mainwin.SetBufStr("Main:");
  Fresh();
}

//
TuiController::~TuiController() {
  MoveCursor(1, 1);
  Clear();
  RestoreTerm();
}

// Get the TuiController single instance
TuiController &TuiController::GetInstance() { return m_instance; }

// Initialize the windows
void TuiController::InitWin() {
  winsize winsz;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz);
  int width = winsz.ws_col;
  int height = winsz.ws_row;

  m_cmdwin.Init(0, "Command", width - 2, 1, height - 1, 2);
  m_statuswin.Init(1, "Status", 50, 10, 2, 2);
  m_valuewin.Init(2, "Value", 50, height - 17, 14, 2);
  m_mainwin.Init(3, "Main", width - 54, height - 5, 2, 54);
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
  printf("\033[2J\033[1;1H");
}

// Flesh the terminal
void TuiController::Fresh() {
  Window wins[4] = {m_cmdwin, m_statuswin, m_valuewin, m_mainwin};
  for (Window &iter : wins) {
    iter.PrintBuf();
  }
  MoveCursor(1, 1);
}

// Get the keyboard input
char TuiController::GetKey() { return getchar(); }

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

