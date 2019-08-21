#include <stdio.h>
#include <cmath>
#include "glbfunc.h"
#include "material.h"

using namespace std;

void Material::Set_nu()
{
    //kinetic viscosity
    nu = AMAX1(eta, zeta)/rho0;
}

void Material::Get_b0(double sound)
{
    //compressiblity
    b0 = a0*sound/gamma;
}

double Material::get_p(double rho)
{
    return b0*pow(rho/rho0,gamma);
}

double Material::get_rho(double p)
{
    return rho0*pow(p/b0, 1.0/gamma);
}

double Material::get_Cs(double p, double rho)
{
    return sqrt(gamma*p/rho);
}
