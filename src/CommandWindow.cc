#include "unistd.h"

#include "CommandWindow.h"
#include "cstring"
#include "Utils.h"

CommandWindow::CommandWindow(int id, const char *name) : Window(id, name) {
  m_margin = 0;
  m_digit = 0;
}

CommandWindow::~CommandWindow() {}

void CommandWindow::Print() {
  PrintBnd();
  PrintBuf();
}

bool CommandWindow::CommandChar(char cmd) {
  bool result = Window::CommandChar(cmd);

  if (result == true) {
    return true;
  }

  return true;
}

void CommandWindow::PrintBuf() {
  int begin = m_firstline;
  int end = m_firstline + m_height;

  char buf[MAXCOLUME];

  for (int id = begin; id < end && id < m_line; ++id) {
    memset(buf, ' ', m_width);
    memcpy(buf, m_buf + m_offset[id], m_length[id]);

    MoveCursor(m_x + (id - begin), m_y + m_margin);
    write(STDOUT_FILENO, buf, m_width - m_margin);
  }
}
