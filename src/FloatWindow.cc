#include "FloatWindow.h"

FloatWindow::FloatWindow(int id, const char *name) : Window(id, name) {
  m_margin = 0;
  m_digit = 0;
  m_movetype = 1;
  m_floatwindow = nullptr;
}

FloatWindow::~FloatWindow() {}

void FloatWindow::Print() {
  PrintBnd();
  PrintBuf();
}

bool FloatWindow::CommandChar(char cmd) {
  if (Window::CommandChar(cmd)) {
    return true;
  }
  switch (cmd) {
    case 27 :
      SetActive(false);
      return true;
    default :
      return false;
  }
}
