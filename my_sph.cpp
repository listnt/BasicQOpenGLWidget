#include "my_sph.h"

my_SPH::my_SPH()
{

}
void my_SPH::Update()
{
    frame++;
    if(frame>5)
    {
        AddParticle();
        frame=0;
    }
    ComputeDensityPressure();
    ComputeForces();
    Integrate();

}
void my_SPH::InitSPH(void)
{
    std::cout << "initializing dam break with " << DAM_PARTICLES << " particles" << std::endl;
    for(float y = EPS; y < VIEW_HEIGHT-EPS*2.f; y += H)
        for(float x = VIEW_WIDTH/4; x <= VIEW_WIDTH/2; x += H)
            if(particles.size() < DAM_PARTICLES)
            {
                float jitter = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                particles.push_back(Particle(x+jitter,y));
            }
}

void my_SPH::AddParticle()
{
    particles.push_back(Particle(VIEW_WIDTH/4, VIEW_HEIGHT/4));
}

void my_SPH::Integrate(void)
{
    for (auto &p : particles)
    {
        // forward Euler integration
        p.v += DT * p.f / p.rho;
        p.x += DT * p.v;

        // enforce boundary conditions
        if (p.x.x() - EPS < 0.0f)
        {
            p.v.setX(p.v.x() * BOUND_DAMPING);
            p.x.setX( EPS);
        }
        if (p.x.x() + EPS > VIEW_WIDTH)
        {
            p.v.setX( p.v.x()* BOUND_DAMPING);
            p.x.setX( VIEW_WIDTH - EPS);
        }
        if (p.x.y() - EPS < 0.0f)
        {
            p.v.setY (p.v.y() * BOUND_DAMPING);
            p.x.setY(  EPS);
        }
        if (p.x.y() + EPS > VIEW_HEIGHT)
        {
            p.v.setY( p.v.y()* BOUND_DAMPING);
            p.x.setY(VIEW_HEIGHT - EPS);
        }
    }
}

void my_SPH::ComputeDensityPressure(void)
{
    for (auto &pi : particles)
    {
        pi.rho = 0.f;
        for (auto &pj : particles)
        {
            QVector2D rij = pj.x - pi.x;
            float r2 = rij.normalized().length();

            if (r2 < HSQ)
            {
                // this computation is symmetric
                pi.rho += MASS * POLY6 * pow(HSQ - r2, 3.f);
            }
        }
        pi.p = GAS_CONST * (pi.rho - REST_DENS);
    }
}

void my_SPH::ComputeForces(void)
{
    for (auto &pi : particles)
    {
        QVector2D fpress(0.f, 0.f);
        QVector2D fvisc(0.f, 0.f);
        for (auto &pj : particles)
        {
            if (&pi == &pj)
                continue;

            QVector2D rij = pj.x - pi.x;
            float r = rij.normalized().length();

            if (r < H)
            {
                // compute pressure force contribution
                fpress += -rij.normalized() * MASS * (pi.p + pj.p) / (2.f * pj.rho) * SPIKY_GRAD * pow(H - r, 2.f);
                // compute viscosity force contribution
                fvisc += VISC * MASS * (pj.v - pi.v) / pj.rho * VISC_LAP * (H - r);
            }
        }
        QVector2D fgrav = (*G) * pi.rho;
        pi.f = fpress + fvisc + fgrav;
    }
}
