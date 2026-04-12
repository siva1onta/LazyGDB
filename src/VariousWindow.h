#ifndef VARIOUSWINDOW_H_
#define VARIOUSWINDOW_H_

#include "Window.h"

class VariousWindow final : public Window {

public:
  VariousWindow(int id, const char *name);
  ~VariousWindow() override;

  bool CommandChar(char cmd) override;
};

#endif // VARIOUSWINDOW_H_
