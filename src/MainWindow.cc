#include "MainWindow.h"
#include "FloatWindow.h"

MainWindow::MainWindow(int id, const char *name) : Window(id, name) {
  m_margin = 8;
  m_digit = 4;
  m_movetype = 2;
  m_floatwindow = new FloatWindow(id, name);
}

MainWindow::~MainWindow() {}

bool MainWindow::CommandChar(char cmd) {
  if (Window::CommandChar(cmd)) {
    return true;
  }
  switch (cmd) {
    default :
      return false;
  }
}
