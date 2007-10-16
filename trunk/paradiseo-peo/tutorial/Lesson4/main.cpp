//For define a parallel PSO or a sequential PSO
#define PARA

#include <peo>

typedef eoRealParticle < double >Indi;
//Evaluation function

double f (const Indi & _indi)
{  
    //Levy function f* = -21.502356 x=(1,1,1,-9.752356 ) for size = 4
    
    const double PI = 4.0 * atan(1.0);
    double sum=0.;
    for (unsigned i = 0; i < _indi.size()-1; i++)
    	sum+=pow((_indi[i]-1),2)*(1+pow(sin(3*PI*_indi[i+1]),2));
    sum+=pow(sin(3*PI*_indi[0]),2);
    sum+=(_indi[_indi.size()-1]-1)*(1+pow(sin(2*PI*_indi[_indi.size()-1]),2));
    return (-sum);
}

int main (int __argc, char *__argv[])
{

#ifdef PARA 
//Initialization
  peo :: init( __argc, __argv );
#endif
//Parameters
    const unsigned int VEC_SIZE = 4;        
    const unsigned int POP_SIZE = 20;        
    const unsigned int NEIGHBORHOOD_SIZE= 5; 
    const unsigned int MAX_GEN = 500;
    const double INIT_POSITION_MIN = -10.0;
    const double INIT_POSITION_MAX = 1.0;
    const double INIT_VELOCITY_MIN = -1;
    const double INIT_VELOCITY_MAX = 1;
    const double C1 = 0.5; 
    const double C2 = 2;
    rng.reseed (time(0));
#ifndef PARA 
	eoEvalFuncPtr<Indi, double, const Indi& > plainEval(f);
    eoEvalFuncCounter < Indi > eval (plainEval);
#else
	peoEvalFuncPSO<Indi, double, const Indi& > plainEval(f);
    eoEvalFuncCounter < Indi > evalSeq (plainEval);
    peoParaPopEval< Indi > eval(plainEval);                
#endif
    eoUniformGenerator < double >uGen (INIT_POSITION_MIN, INIT_POSITION_MAX);
    eoInitFixedLength < Indi > random (VEC_SIZE, uGen);
//Velocity
    eoUniformGenerator < double >sGen (INIT_VELOCITY_MIN, INIT_VELOCITY_MAX);
    eoVelocityInitFixedLength < Indi > veloRandom (VEC_SIZE, sGen);
//Initializing the best
    eoFirstIsBestInit < Indi > localInit;
//Flight
    eoRealVectorBounds bndsFlight(VEC_SIZE,INIT_POSITION_MIN,INIT_POSITION_MAX);
    eoStandardFlight < Indi > flight(bndsFlight);        
    eoPop < Indi > pop;
    pop.append (POP_SIZE, random);    
#ifndef PARA 
    apply(eval, pop);
#else
//The first evaluation must be sequential
    apply(evalSeq, pop);
#endif
    apply < Indi > (veloRandom, pop);
    apply < Indi > (localInit, pop);
//Topology
    eoLinearTopology<Indi> topology(NEIGHBORHOOD_SIZE);
    topology.setup(pop);
    eoRealVectorBounds bnds(VEC_SIZE,INIT_VELOCITY_MIN,INIT_VELOCITY_MAX);
    eoStandardVelocity < Indi > velocity (topology,C1,C2,bnds);
    eoGenContinue < Indi > genContPara (MAX_GEN);
    eoCombinedContinue <Indi> continuatorPara (genContPara);
    eoCheckPoint<Indi> checkpoint(continuatorPara);
#ifndef PARA
//Sequential algorithm
    eoSyncEasyPSO < Indi > psa(checkpoint, eval, velocity, flight);
    psa (pop); 
    pop.sort (); 
#else
//Parallel algorithm
    peoPSO < Indi > psa(checkpoint, eval, velocity, flight);
    psa(pop);    
    peo :: run(); 
    peo :: finalize();
#endif
    std::cout << "Population finale :\n" << pop << std::endl;
}