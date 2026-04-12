#ifndef COMMANDWINDOW_H_
#define COMMANDWINDOW_H_

#include "Window.h"

class CommandWindow final : public Window {

public:
  CommandWindow(int id, const char *name);
  ~CommandWindow() override;

  void Print() override;
  bool CommandChar(char cmd) override;
};

#endif
