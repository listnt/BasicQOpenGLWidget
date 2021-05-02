#ifndef MY_SPH_H
#define MY_SPH_H
#include <QtOpenGL>
#include <iostream>

struct Particle
{
    Particle(float _x, float _y) : x(_x, _y), v(0.f, 0.f), f(0.f, 0.f), rho(0), p(0.f) {}
    QVector2D x, v, f;
    float rho, p;
};

class my_SPH
{
public:
    my_SPH();
     QVector2D *G=new QVector2D(0.f, 12000 * -9.8f); // external (gravitational) forces
     float REST_DENS = 1000.f;		 // rest density
     float GAS_CONST = 2000.f;		 // const for equation of state
     float H = 16.f;				 // kernel radius
     float HSQ = H * H;				 // radius^2 for optimization
     float MASS = 65.f;				 // assume all particles have the same mass
     float VISC = 250.f;			 // viscosity constant
     float DT = 0.0008f;			 // integration timestep

    // smoothing kernels defined in Müller and their gradients
     float POLY6 = 315.f / (65.f * M_PI * pow(H, 9.f));
     float SPIKY_GRAD = -45.f / (M_PI * pow(H, 6.f));
     float VISC_LAP = 45.f / (M_PI * pow(H, 6.f));

    // simulation parameters
     float EPS = H; // boundary epsilon
     float BOUND_DAMPING = -0.5f;

    // particle data structure
    // stores position, velocity, and force for integration
    // stores density (rho) and pressure values for SPH


    // solver data
    QVector<Particle> particles;

    // interaction
     int MAX_PARTICLES = 2500;
     int DAM_PARTICLES = 500;
     int BLOCK_PARTICLES = 250;

     // rendering projection parameters
      int WINDOW_WIDTH = 800;
      int WINDOW_HEIGHT = 600;
      double VIEW_WIDTH = 1.5 * 800.f;
      double VIEW_HEIGHT = 1.5 * 600.f;

      int frame=0;

     void AddParticle(void);
     void InitSPH(void);
     void Integrate(void);
     void ComputeDensityPressure(void);
     void ComputeForces(void);
     void Update(void);
};

#endif // MY_SPH_H
