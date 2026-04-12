#include "CommandWindow.h"
#include "FloatWindow.h"

#include <unistd.h>
#include <fcntl.h>

#include "Ulogger.h"

CommandWindow::CommandWindow(int id, const char *name) : Window(id, name) {
  m_margin = 0;
  m_digit = 0;
  m_movetype = 0;
  m_floatwindow = new FloatWindow(id, name);
  m_floatwindow->SetSizePos(10, 40, 15, 35);
}

CommandWindow::~CommandWindow() {}

void CommandWindow::Print() {
  PrintBnd();
  PrintBuf();
  Debug("Command Window Print, ");
  if (m_floatwindow->GetActive()) {
    Debug("Command Float Window Print, ");
    m_floatwindow->Print();
  }
}

bool CommandWindow::CommandChar(char cmd) {
  if (m_floatwindow->CommandChar(cmd)) {
    return true;
  }
  if (Window::CommandChar(cmd) == true) {
    return true;
  }

  int fd = 0;
  switch (cmd) {
    case 'h' :
      fd = open("./share/Float_Command.txt", O_RDONLY);
      m_floatwindow->SetBufFd(fd);
      close(fd);
      m_floatwindow->SetActive(true);
      return true;
    default :
      return false;
  }
}
