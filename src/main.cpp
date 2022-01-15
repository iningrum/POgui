#include <stdlib.h>
#include <unistd.h>

#include "winsys.h"
#include "clock.h"


int main(int argc, char *argv[]) {
  if (gfx_init())
    exit(3);

  CWindow* pW1 = new CWindow(CRect(CPoint(100, 100), CPoint(200, 300)));
  CFramedWindow* pW2 = new CFramedWindow(CRect(CPoint(150, 150), CPoint(250, 250)));

  CFramedWindow* pW3 = new CFramedWindow(CRect(CPoint(140, 200), CPoint(300, 300)), YELLOW, BLACK);
  CInputLine* pW4 = new CInputLine(CRect(CPoint(200, 170), CPoint(350, 350)), WHITE, RED);

  CGroup* pG = new CGroup;
  pG->insert(pW3);
  pG->insert(pW4);

  CClock* pClock = new CClock(CRect(CPoint(350, 50), CPoint(300, 300)), GREEN, BLACK);

  CDesktop d;

  d.insert(pW1);
  d.insert(pW2);
  d.insert(pG);

  d.insert(pClock);

  d.run ();

  return 0;
}
