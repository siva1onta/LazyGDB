#include "VariousWindow.h"

VariousWindow::VariousWindow(int id, const char *name) : Window(id, name) {
  m_margin = 5;
  m_digit = 2;
}

VariousWindow::~VariousWindow() {}

bool VariousWindow::CommandChar(char cmd) {
  bool result = Window::CommandChar(cmd);

  if (result == true) {
    return true;
  }

  return true;
}
