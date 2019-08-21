#include <stdio.h>
#include <cmath>

// ***** localincludes *****
#include "glbfunc.h"
#include "material.h"

using namespace std;

void Material::Set_nu()
{
    //kinetic viscosity
    nu = AMAX1(eta, zeta)/rho0;
}
//----------------------------------------------------------------------------------------
//			obtain parameter b0
//			after nondimensionlization finished
//----------------------------------------------------------------------------------------
void Material::Get_b0(double sound)
{
    //compressiblity
    b0 = a0*sound/gamma;
}
//----------------------------------------------------------------------------------------
//					get pressure
//----------------------------------------------------------------------------------------
double Material::get_p(double rho)
{
    return b0*pow(rho/rho0,gamma);
}
//----------------------------------------------------------------------------------------
//					get rho from pressure
//----------------------------------------------------------------------------------------
double Material::get_rho(double p)
{
    return rho0*pow(p/b0, 1.0/gamma);
}
//----------------------------------------------------------------------------------------
//					get sound speed
//----------------------------------------------------------------------------------------
double Material::get_Cs(double p, double rho)
{
    return sqrt(gamma*p/rho);
}
