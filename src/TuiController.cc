#include "TuiController.hh"

#include <unistd.h>
#include <sys/ioctl.h>

#include <cstdlib>
#include <cstdio>

// Init
TuiController TuiController::m_instance = TuiController();

// Constructor
TuiController::TuiController() {
  SetupTerm();
  InitWin();
}

//
TuiController::~TuiController() {
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

  m_cmdwin = Window(1, "Command", width - 2, 1, height - 1, 1);
  m_statuswin = Window(1, "Status", width - 2, 1, height - 1, 1);
  m_mainwin = Window(1, "Main", width - 2, 1, height - 1, 1);
}

// Config the windows' sizes
void TuiController::ConfigWinSz() {
  winsize winsz;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz);
  int width = winsz.ws_col;
  int height = winsz.ws_row;
}

// Flesh the terminal
void TuiController::Fresh() {}

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

