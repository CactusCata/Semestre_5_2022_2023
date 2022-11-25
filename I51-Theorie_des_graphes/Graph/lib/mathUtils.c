#include "mathUtils.h"

float distance(point p1, point p2) {
  return sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));
}
