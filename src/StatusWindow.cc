#include "StatusWindow.h"
#include "FloatWindow.h"

StatusWindow::StatusWindow(int id, const char *name) : Window(id, name) {
  m_margin = 5;
  m_digit = 2;
  m_movetype = 1;
  m_floatwindow = new FloatWindow(id, name);
}

StatusWindow::~StatusWindow() {}

bool StatusWindow::CommandChar(char cmd) {
  if (Window::CommandChar(cmd)) {
    return true;
  }
  switch (cmd) {
    default :
      return false;
  }
}
