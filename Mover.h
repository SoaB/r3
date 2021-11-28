#ifndef __MOVER_H__
#define __MOVER_H__

#include "rnd.h"
#include "v2d.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Mover {
  Vec2D location;
  Vec2D velocity;
  Vec2D acceleration;
  float mass;
  float angle;
  void (*Update)(struct Mover *self);
  void (*Destroy)(struct Mover *self);
  void (*ChkEdge)(struct Mover *mv, int w, int h);
  void (*ApplyForce)(struct Mover *mv, Vec2D force);
} Mover;

static void _update(Mover *mv) {
  Vec2D lastPosi = V2D_Clone(mv->location);
  mv->velocity = V2D_Add(mv->velocity, mv->acceleration);
  mv->location = V2D_Add(mv->location, mv->velocity);
  mv->acceleration = V2D_Zero();
  mv->angle = V2D_Angle(lastPosi, mv->location);
}
static void _destroy(Mover *self) {
  if (self != NULL) {
    free(self);
    self = NULL;
  }
}
static void _applyForce(Mover *mv, Vec2D force) {
  Vec2D f = V2D_DivideVal(force, mv->mass);
  mv->acceleration = V2D_Add(mv->acceleration, f);
}
static void _chkEdge(Mover *mv, int w, int h) {
  if ((int)mv->location.x > w) {
    mv->velocity.x *= -1;
    mv->location.x = w;
  } else if ((int)mv->location.x < 0) {
    mv->velocity.x *= -1;
    mv->location.x = w;
  }
  if ((int)mv->location.y > h) {
    mv->velocity.y *= -1;
    mv->location.y = h;
  }
}
Mover *NewMover(float m, float x, float y) {
  Mover *mv = (Mover *)malloc(sizeof(Mover));
  if (mv != NULL) {
    mv->location = V2D_Set(x, y);
    mv->velocity = V2D_Zero();
    mv->acceleration = V2D_Zero();
    mv->mass = m;
    mv->angle = 0;
    mv->Update = &_update;
    mv->Destroy = &_destroy;
    mv->ChkEdge = &_chkEdge;
    mv->ApplyForce = &_applyForce;
  }
  return mv;
}

#endif // header guard
