#ifndef FLOATWINDOW_H_
#define FLOATWINDOW_H_

#include "Window.h"

class FloatWindow final : public Window {

public:
  FloatWindow(int id, const char *name);
  ~FloatWindow();

  void Print() override;
  bool CommandChar(char cmd) override;
};

#endif // FLOATWINDOW_H_
