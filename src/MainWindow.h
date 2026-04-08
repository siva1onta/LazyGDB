#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "Window.h"

class MainWindow : public Window {

public:
  MainWindow(int id, const char *name);
  ~MainWindow() override;

  bool CommandChar(char cmd) override;
};

#endif
