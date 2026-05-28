#include "interface/solver_interface.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  SolverInterface::run();

  return 0;
}
