#pragma once

#include "Window.h"

#include <termios.h>

class TuiController final {

public:
  TuiController(const TuiController &) = delete;
  TuiController &operator=(const TuiController &) = delete;

  static TuiController &GetInstance();
  void Clear();
  void Fresh();
  char GetKey();

private:
  TuiController();
  ~TuiController();

  void SetupTerm();
  void RestoreTerm();
  void InitWin();
  void ConfigWinSz();

  static TuiController m_instance;
  termios m_preterm;
  termios m_currterm;
  Window m_cmdwin;
  Window m_statuswin;
  Window m_valuewin;
  Window m_mainwin;

};
