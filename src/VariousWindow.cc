#include "VariousWindow.h"
#include "FloatWindow.h"

VariousWindow::VariousWindow(int id, const char *name) : Window(id, name) {
  m_margin = 5;
  m_digit = 2;
  m_movetype = 2;
  m_floatwindow = new FloatWindow(id, name);
}

VariousWindow::~VariousWindow() {}

bool VariousWindow::CommandChar(char cmd) {
  if (Window::CommandChar(cmd)) {
    return true;
  }
  switch (cmd) {
    default :
      return false;
  }
}
