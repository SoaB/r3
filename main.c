#include "Mover.h"
#include "rnd.h"
#include "sgi.h"
#include "v2d.h"
#include <stdlib.h>
#include <time.h>

Mover *mvs[20];

int main(int argc, char *argv[]) {
  int i;
  rnd_Seed(time(NULL), 33);
  for (i = 0; i < 20; i++) {
    mvs[i] = NewMover(rnd_Fn(5.0) + 0.1, 10, 10);
  }
  sgi_Init(800, 600, "Mover Test");
  sgi_Image *mvr = NewSgiImage("beams.bmp");
  Vec2D wind = V2D_Set(0.01, 0);
  Vec2D gravity = V2D_Set(0, 0.1);
  while (!sgi_Done()) {
    sgi_Clear(RGB_Black);
    for (i = 0; i < 20; i++) {
      mvs[i]->ApplyForce(mvs[i], wind);
      mvs[i]->ApplyForce(mvs[i], gravity);
      mvs[i]->Update(mvs[i]);
      mvs[i]->ChkEdge(mvs[i], 800, 600);
      mvr->Draw(mvr, (int)mvs[i]->location.x, (int)mvs[i]->location.y,
                mvs[i]->angle);
    }
    sgi_Update();
    sgi_Delay(16);
  }
  for (i = 0; i < 20; i++) {
    mvs[i]->Destroy(mvs[i]);
  }
  mvr->Destroy(mvr);
  sgi_Fini();
  return 0;
}
