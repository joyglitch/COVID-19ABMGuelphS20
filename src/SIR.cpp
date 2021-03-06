/****************
 * COVID-19ABMGuelphS20
 * 13/08/20
 * ver 1.01
 * 
 * This is the class file for the SIR class
 ***************/


#include "SIR.hh"
#include <iostream>

// Constructor
SIR::SIR() {
    currentSeverity = SUSCEPTIBLE;
    quarantineCases = 0.0;
}

// leave these to check all references
// can all be changed to user inputs
// 45% asymptomatic if not srs (check)
// 25% icu death rate once in ICU
// approx 20% need hospital, 80% recover at home
// 6% need ICU of total cases
// around 26 days to srs recovery once in icu
// icu 1 to 3 days after hospitilization
// non-icu recovery 14 days
// icu death after 5 days
//possible timestep 0.125 3 hrs

/*************************
 * SIRTimeStep
 * 
 * This progresses agents through their various SIR model paths.
 ************************/
string SIR::SIRTimeStep(double timeStep) {
    if (currentSeverity == SUSCEPTIBLE || currentSeverity == RECOVERED || currentSeverity == DECEASED) {
        return "NA";
    }
    
    // incubating stage (infect other ppl?)
    if (isIncubating) {
        incubationPeriod -= timeStep;

        if (incubationPeriod <= 0 ) {
            isIncubating = false;
            double quarantineChance = (double) rand()/RAND_MAX;
            if (showsSymptoms && quarantineCases > quarantineChance) {
                QuarantineAgent();
                return "ISOAGENT";
            }
        }
        return "NA";
    }
    
    // move agents between stages, check stages in order
    if (needHospital && timeTilHospital > 0) {
        timeTilHospital -= timeStep;
        if (timeTilHospital <= 0) {
            HospitalAgent();
            return "HOSPITALAGENT";
        }
    } else if (needIcu && timeTilICU > 0) {
        timeTilICU -= timeStep;
        if (timeTilICU <= 0) {
            PlaceAgentInICU();
            return "ICUAGENT";
        }
    } else if (fatalCase && timeTilDeath > 0) {
        timeTilDeath -= timeStep;
        if (timeTilDeath <= 0) {
            AgentDeceased();
            return "DECEASEAGENT";
        }
    } else {
        timeTilRecovery -= timeStep;
        if (timeTilRecovery <= 0) {
            RecoverAgent();
            return "RECOVERAGENT";
        }
    }

    return "NA";
}

/*************************
 * DecideSIRCase
 * 
 * Determines the path the agents COVID19 case will follow.
 ************************/
void SIR::DecideSIRCase(double infectedNumb, double infectedChance) {
    // decide if the case is fatal
    if (infectedNumb <  infectedChance) {
        showsSymptoms = true;
        needIcu = true;
        needHospital = true;
        fatalCase = true;
        timeTilHospital = 5;
        timeTilICU = 3;
        timeTilDeath = 5;
      // if the case is not fatal decide path to recovery
    } else {
        fatalCase = false;

        double randomNumber = (double) rand()/RAND_MAX;

        // case is asymptomatic
        if (randomNumber < 0.45) {
            showsSymptoms = false;
            needHospital = false;
            needIcu = false;
            timeTilRecovery = 7;
          // case requires hospitilzation
        } else if (randomNumber >= 0.45 && randomNumber <= 0.65) {
            showsSymptoms = true;
            needHospital = true;
            timeTilHospital = 7;

            double icuNeeded = (double) rand()/RAND_MAX;

            // case requires icu
            if (icuNeeded < 0.2) {
                needIcu = true;
                timeTilICU = 3;
                timeTilRecovery = 20;
              // case requires general ward hospital
            } else {
                needIcu = false;
                timeTilRecovery = 10;
            }
          // case requires no hospital but shows symptoms
        } else {
            showsSymptoms = true;
            needHospital = false;
            needIcu = false;
            timeTilRecovery = 7;
        }
    }
}

/*************************
 * AgentInfected
 * 
 * Infect the agent and decide their path through the SIR model.
 ************************/
void SIR::AgentInfected() {
    currentSeverity = INFECTED;
    isIncubating = true;
    incubationPeriod = rand()%4 + rand()%4 + 1;

    double randomDeathSentence = (double) rand()/RAND_MAX;

    // based on worldometer death rates for each age group
    if(MALE0TO4 == info || MALE5TO9 == info || FEMALE0TO4 == info || FEMALE5TO9 == info) {
        DecideSIRCase(randomDeathSentence, 0.0);
    } else if (MALE10TO14 == info || MALE15TO19 == info || FEMALE10TO14 == info || FEMALE15TO19 == info) {
        DecideSIRCase(randomDeathSentence, 0.002);
    } else if (MALE20TO24 == info || MALE25TO29 == info || FEMALE20TO24 == info || FEMALE25TO29 == info) {
        DecideSIRCase(randomDeathSentence, 0.002);
    } else if (MALE30TO34 == info || MALE35TO39 == info || FEMALE30TO34 == info || FEMALE35TO39 == info) {
        DecideSIRCase(randomDeathSentence, 0.002);
    } else if (MALE40TO44 == info || MALE45TO49 == info || FEMALE40TO44 == info || FEMALE45TO49 == info) {
        DecideSIRCase(randomDeathSentence, 0.004);
    } else if (MALE50TO54 == info || MALE55TO59 == info || FEMALE50TO54 == info || FEMALE55TO59 == info) {
        DecideSIRCase(randomDeathSentence, 0.013);
    } else if (MALE60TO64 == info || MALE65TO69 == info || FEMALE60TO64 == info || FEMALE65TO69 == info) {
        DecideSIRCase(randomDeathSentence, 0.036);
    } else if (MALE70TO74 == info || MALE75TO79 == info || FEMALE70TO74 == info || FEMALE75TO79 == info) {
        DecideSIRCase(randomDeathSentence, 0.08);
    } else {
        DecideSIRCase(randomDeathSentence, 0.148);
    }
}

/*************************
 * The functions below move the agent through the SIR model.
 ************************/

void SIR::HospitalAgent() {
    currentSeverity = HOSPITALIZED;
    needHospital = false;
}

void SIR::QuarantineAgent() {
    currentSeverity = ISOLATED;
}

void SIR::PlaceAgentInICU() {
    currentSeverity = ICU;
    needIcu = false;
}

void SIR::RecoverAgent() {
    currentSeverity = RECOVERED;
    showsSymptoms = false;
} 

void SIR::AgentDeceased() {
    needIcu = false;
    currentSeverity = DECEASED;
} 

/*************************
 * DetermineSeverity
 * 
 * Get the current severity of the agents case.
 ************************/
SIRSeverity SIR::DetermineSeverity() {
    return currentSeverity;
}

bool SIR::getSymptoms() {
    return showsSymptoms;
}

void SIR::setQuarantineCases(double val) {
    quarantineCases = val;
}
