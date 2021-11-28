#include "oscillator.h"
#include "rnd.h"
#include "sgi.h"
#include "v2d.h"
#include <stdlib.h>
#include <time.h>

Oscillator *oc[20];

int main(int argc, char *argv[]) {
  int i;
  rnd_Seed(time(NULL), 33);
  for (i = 0; i < 20; i++) {
    oc[i] = NewOscillator();
  }
  sgi_Init(800, 600, "Oscillator");
  sgi_Image *mvr = NewSgiImage("beams.bmp");
  while (!sgi_Done()) {
    sgi_Clear(RGB_Black);
    for (i = 0; i < 20; i++) {
      oc[i]->Update(oc[i]);
      mvr->Draw(mvr, (int)(oc[i]->Posi.x + 400), (int)(oc[i]->Posi.y + 300),
                oc[i]->dir);
    }
    sgi_Update();
    sgi_Delay(16);
  }
  for (i = 0; i < 20; i++) {
    oc[i]->Destroy(oc[i]);
  }
  mvr->Destroy(mvr);
  sgi_Fini();
  return 0;
}
