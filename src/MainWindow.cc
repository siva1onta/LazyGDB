#include "MainWindow.h"

MainWindow::MainWindow(int id, const char *name) : Window(id, name) {
  m_margin = 8;
  m_digit = 4;
}

MainWindow::~MainWindow() {}

bool MainWindow::CommandChar(char cmd) {
  bool result = Window::CommandChar(cmd);

  if (result == true) {
    return true;
  }

  return true;
}
