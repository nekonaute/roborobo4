/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef TEMPLATEEESHAREDDATA_H
#define TEMPLATEEESHAREDDATA_H

#include "Utilities/LogManager.h"

extern std::ofstream gLitelogFile;
extern LogManager *gLitelogManager;

class TemplateEESharedData {
    
public:
    
    // -----
    
    static double gSigmaMin; //! used with gDynamicSigma defined to true
    static double gUpdateSigmaStep; //!step used in the drecrease or increas of the value of sigma
    static double gSigmaRef; //! reference value of sigma
    static double gSigmaMax; //! maximal value of sigma
    static double gProbaMutation; //! probability of transmitting the current genome mutated with sigma ref
    static int gEvaluationTime; //! theoretical duration of a generation (ie. maximum time a controller will be evaluated on a robot)
    static int gIteration; //! used by every class to know what is the current iteration step of roborobo

    static bool gEnergyRequestOutput; // does the robot can modulate its energy request (when being given some) ?
    
    static double gMonitorPositions; //! used in WorldObserver. Compute and log all necessary information for monitoring position and orientation wrt. center.
    
    static bool gPropertiesLoaded;
    
    static int gNbHiddenLayers; // default: 1
    static int gNbNeuronsPerHiddenLayer; // default: 5
    static int gNeuronWeightRange; // default: 800.0 (ie. weights are in [-400,+400[

    static int gESNStepsBySimulationStep; // default: 10
    static int gESNReservoirSize; // default: 100
    static double gESNDensityOfConnections; // default: 0.10
    static double gESNAlpha; // default: 0.88
    static bool gESNAllowInputToOutputDirectConnections; // default: false
    static bool gESNAllowOutputSelfRecurrentConnections; // default: true
    static bool gESNAllowInputToReservoirConnections; // default: true
    static bool gESNFixedInputToReservoirConnections; // default: true
    static bool gESNAllowOutputToReservoirConnections; // default: true
    static bool gESNAddConstantInputBias; // default: true
    static bool gESNAddSinInputBias; // default: false
    static double gESNSinBiasPeriod; // default: 0.01
    static bool gESNUseSparseComputation; // default: false
    
    static bool gSnapshots; // take snapshots
    static int gSnapshotsFrequency; // every N generations
    
    static int gControllerType; // controller type (0: MLP, 1: Perceptron, 2: Elman)
    
    static int gMaxNbGenomeTransmission; // max. nb of genome transmission per individual per lifetime.
    static bool gLimitGenomeTransmission; // enable/disable limiting transmission
    
    static int gSelectionMethod; // check PrjMateSelectionController::loadNewGenome() for authorized values.
    
    static int gNotListeningStateDelay; // -1: infinite ; 0: no delay ; >0: delay
    static int gListeningStateDelay;    // -1: infinite ; 0: no delay ; >0: delay (ignored if gNotListeningStateDelay=-1)
    
    static bool gLogGenome;
    static bool gLogGenomeSnapshot;   // log only if it%gEvaluationTime*gSnapshotsFrequency=0
    
    static double gIndividualMutationRate;
    
    static int gMutationOperator;
    
    static double gSigma;
    
    // -----
    
    
    
};


#endif
