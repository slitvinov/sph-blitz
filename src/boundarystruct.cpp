#include "boundarystruct.h"
#include "glbfunc.h"
#include "initiation.h"
#include <vector>

#include "glbfunc.h"


BoundaryStruct::BoundaryStruct(const Vec2d& newdR):
   dR(newdR)
{
}

PeriodicBoundaryStruct::PeriodicBoundaryStruct(const Vec2d& newdR)
{  
  dR = newdR;
}


BoundaryStruct::BoundaryStruct():
  dR(0.0)
{
}

Vec2d BoundaryStruct::getDistance(const Vec2d& x, const Vec2d& y) const {
  return y - x;
}

BoundaryStruct::~BoundaryStruct() {
}

Vec2d PeriodicBoundaryStruct::getDistance(const Vec2d& x, const Vec2d& y) const {
  vector<Vec2d> R_vec;
  R_vec.push_back(y-x);
  R_vec.push_back(y + dR - x);
  R_vec.push_back(y - dR - x);
  ///Fix::
#ifdef QFIX  
  Vec2d ort(-dR[1], dR[0]);
  R_vec.push_back(y - x + dR - ort);
  R_vec.push_back(y - x - dR + ort);
#endif
  
  double minD(dot(R_vec.at(0), R_vec.at(0)));
  Vec2d minVec(R_vec.at(0)); 
  unsigned int imin(0);
  for (unsigned int q=0; q<R_vec.size(); q++) {    
    double D = dot(R_vec.at(q), R_vec.at(q));
    if (D < minD) {
      minD = D;
      minVec = R_vec.at(q);
      imin = q;
    }
  }
  return minVec;
}

BoundaryStruct* BoundaryStructFactory::Create(BPosition bp,  int bcFlag) {

  //  Vec2d dR(0.0, 0.0);
  switch (bcFlag) {
  case 0:
    return new WallBoundaryStruct();
    break;
  case 1: {
    Vec2d dR(0.0, 0.0);
    Initiation* ini = Initiation::Instance();
    Vec2d box(ini->box_size);
    switch (bp) {
    case N:
      dR[0] += box[0];
      break;
    case S:
      dR[0] -= box[0];
      break;
    case E:
      dR[1] += box[1];
      break;
    case W:
      dR[1] -= box[1];
      break;
    }
    return new PeriodicBoundaryStruct(dR);
    break;
  }
  case 2:
    return new FreeSlipBoundaryStruct();
    break;
  case 3:
    return new SymmBoundaryStruct();
    break;
  }
}
