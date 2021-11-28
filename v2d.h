#ifndef HEADER_DF97652C2C1BE970
#define HEADER_DF97652C2C1BE970

#include <math.h>

#define PI 3.141592658539327

typedef struct Vec2D {
  float x;
  float y;
} Vec2D;
/*
-- Header define.
*/
Vec2D V2D_Zero(void);
Vec2D V2D_One(void);
int V2D_Equal(Vec2D v1, Vec2D v2);
Vec2D V2D_Set(float x, float y);
Vec2D V2D_Clone(Vec2D v);
Vec2D V2D_Add(Vec2D v1, Vec2D v2);
Vec2D V2D_AddValue(Vec2D v, float add);
Vec2D V2D_Subtract(Vec2D v1, Vec2D v2);
Vec2D V2D_SubtractValue(Vec2D v, float sub);
float V2D_Length(Vec2D v);
float V2D_LengthSqr(Vec2D v);
float V2D_DotProduct(Vec2D v1, Vec2D v2);
float V2D_Distance(Vec2D v1, Vec2D v2);
float V2D_Angle(Vec2D v1, Vec2D v2);
Vec2D V2D_Scale(Vec2D v, float scale);
Vec2D V2D_Multiply(Vec2D v1, Vec2D v2);
Vec2D V2D_Negate(Vec2D v);
Vec2D V2D_Divide(Vec2D v1, Vec2D v2);
Vec2D V2D_DivideVal(Vec2D v1, float val);
Vec2D V2D_Normalize(Vec2D v);
Vec2D V2D_Lerp(Vec2D v1, Vec2D v2, float amount);
Vec2D V2D_Reflect(Vec2D v, Vec2D normal);
Vec2D V2D_Rotate(Vec2D v, float angle);
Vec2D V2D_MoveTowards(Vec2D v, Vec2D target, float maxDistance);

/////////////////////////////////////
Vec2D V2D_Zero(void) {
  Vec2D result = {0.0f, 0.0f};

  return result;
}

Vec2D V2D_One(void) {
  Vec2D result = {1.0f, 1.0f};

  return result;
}
int V2D_Equal(Vec2D v1, Vec2D v2) {
  if (v1.x == v2.x && v1.y == v2.y)
    return 1;
  else
    return 0;
}
Vec2D V2D_Set(float x, float y) {
  Vec2D result = {x, y};
  return result;
}

Vec2D V2D_Clone(Vec2D v) {
  Vec2D result = {v.x, v.y};
  return result;
}

Vec2D V2D_Add(Vec2D v1, Vec2D v2) {
  Vec2D result = {v1.x + v2.x, v1.y + v2.y};

  return result;
}

Vec2D V2D_AddValue(Vec2D v, float add) {
  Vec2D result = {v.x + add, v.y + add};

  return result;
}

Vec2D V2D_Subtract(Vec2D v1, Vec2D v2) {
  Vec2D result = {v1.x - v2.x, v1.y - v2.y};

  return result;
}

Vec2D V2D_SubtractValue(Vec2D v, float sub) {
  Vec2D result = {v.x - sub, v.y - sub};

  return result;
}

float V2D_Length(Vec2D v) {
  float result = sqrtf((v.x * v.x) + (v.y * v.y));

  return result;
}

float V2D_LengthSqr(Vec2D v) {
  float result = (v.x * v.x) + (v.y * v.y);

  return result;
}

float V2D_DotProduct(Vec2D v1, Vec2D v2) {
  float result = (v1.x * v2.x + v1.y * v2.y);

  return result;
}

float V2D_Distance(Vec2D v1, Vec2D v2) {
  float result =
      sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));

  return result;
}

float V2D_Angle(Vec2D v1, Vec2D v2) {
  float result = atan2f(v2.y - v1.y, v2.x - v1.x) * (180.0f / PI);

  if (result < 0)
    result += 360.0f;

  return result;
}

Vec2D V2D_Scale(Vec2D v, float scale) {
  Vec2D result = {v.x * scale, v.y * scale};

  return result;
}

Vec2D V2D_Multiply(Vec2D v1, Vec2D v2) {
  Vec2D result = {v1.x * v2.x, v1.y * v2.y};

  return result;
}

Vec2D V2D_Negate(Vec2D v) {
  Vec2D result = {-v.x, -v.y};

  return result;
}

Vec2D V2D_Divide(Vec2D v1, Vec2D v2) {
  Vec2D result = {v1.x / v2.x, v1.y / v2.y};

  return result;
}
Vec2D V2D_DivideVal(Vec2D v1, float val) {
  Vec2D result = {v1.x / val, v1.y / val};

  return result;
}

Vec2D V2D_Normalize(Vec2D v) {
  Vec2D result = {0};
  float length = sqrtf((v.x * v.x) + (v.y * v.y));

  if (length > 0) {
    result.x = v.x * 1.0f / length;
    result.y = v.y * 1.0f / length;
  }

  return result;
}

Vec2D V2D_Lerp(Vec2D v1, Vec2D v2, float amount) {
  Vec2D result = {0};

  result.x = v1.x + amount * (v2.x - v1.x);
  result.y = v1.y + amount * (v2.y - v1.y);

  return result;
}

Vec2D V2D_Reflect(Vec2D v, Vec2D normal) {
  Vec2D result = {0};

  float dotProduct = (v.x * normal.x + v.y * normal.y); // Dot product

  result.x = v.x - (2.0f * normal.x) * dotProduct;
  result.y = v.y - (2.0f * normal.y) * dotProduct;

  return result;
}

Vec2D V2D_Rotate(Vec2D v, float angle) {
  Vec2D result = {0};

  result.x = v.x * cosf(angle) - v.y * sinf(angle);
  result.y = v.x * sinf(angle) + v.y * cosf(angle);

  return result;
}

Vec2D V2D_MoveTowards(Vec2D v, Vec2D target, float maxDistance) {
  Vec2D result = {0};

  float dx = target.x - v.x;
  float dy = target.y - v.y;
  float value = (dx * dx) + (dy * dy);

  if ((value == 0) ||
      ((maxDistance >= 0) && (value <= maxDistance * maxDistance)))
    return target;

  float dist = sqrtf(value);

  result.x = v.x + dx / dist * maxDistance;
  result.y = v.y + dy / dist * maxDistance;

  return result;
}
Vec2D V2D_Limit(Vec2D v, float n) {
  Vec2D rv;
  rv.x = v.x;
  rv.y = v.y;
  float l = (v.x * v.x) + (v.y * v.y);
  if ((n*n) <= l) {
	l = sqrtf(l);  
    float ra = n / l;
    rv.x = rv.x * ra;
    rv.y = rv.y * ra;
  }
  return rv;
}
#endif // header guard
