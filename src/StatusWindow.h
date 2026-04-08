#ifndef STATUSWINDOW_H_
#define STATUSWINDOW_H_

#include "Window.h"

class StatusWindow : public Window {

public:
  StatusWindow(int id, const char *name);
  ~StatusWindow() override;

  bool CommandChar(char cmd) override;
};

#endif
