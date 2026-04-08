#include "StatusWindow.h"

StatusWindow::StatusWindow(int id, const char *name) : Window(id, name) {
  m_margin = 5;
  m_digit = 2;
}

StatusWindow::~StatusWindow() {}

bool StatusWindow::CommandChar(char cmd) {
  bool result = Window::CommandChar(cmd);

  if (result == true) {
    return true;
  }

  return true;
}
