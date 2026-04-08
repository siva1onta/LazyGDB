#ifndef TUICONTROLLER_H_
#define TUICONTROLLER_H_

#include "Window.h"

#include <termios.h>

class TuiController final {

public:
  TuiController(const TuiController &) = delete;
  TuiController &operator=(const TuiController &) = delete;

  static TuiController *GetInstance();
  static void DestoryInstance();
  void Clear();
  void Fresh();
  bool CommandChar(char cmd);

private:
  TuiController();
  ~TuiController();

  void SetupTerm();
  void RestoreTerm();
  void InitWin();
  void ConfigWinSz();

  static TuiController *m_instance;
  termios m_preterm;
  termios m_currterm;

  std::vector<Window *> m_windows;
};

#endif
