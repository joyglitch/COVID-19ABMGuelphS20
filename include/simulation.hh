/****************
 * COVID-19ABMGuelphS20
 * 13/08/20
 * ver 1.02
 * 
 * This is the header file for the simulation class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <vector>
#include "SIRtotals.hh"
#include "transportation.hh"
#include "agent.hh"
#include "location.hh"
#include "hospital.hh"
#include "isolationcompartment.hh"

using namespace std;

//Declare simulation class
class Simulation {
    public:
    /**
     * Simulation
     * 
     * This is the constructor for the simulation class it takes
     * in a file name of the csv file of the demographic data and creates
     * all the needed data to start the simulation
     * 
     * @param fileName the file name of the census data
     */
    Simulation(string fileName);

    /**
     * ~Simulation
     * 
     * This is the deconstructor for the simlation class
     */
    ~Simulation();//Destructor

    /**
     * simulateTimeStep
     * 
     * when called this will simulate one time step in the simulation
     * it will do everything for agent movement infection spread and time
     * and date.
     */
    void simulateTimeStep();

    /**
     * getAgentAt
     * 
     * This function gets a specific agent from the internal data for 
     * what ever reason. It returns a copy of the agent instead of the original pointer
     * 
     * @param index the index in the internal array must be in range of 0 <= index < population
     */
    Agent *getAgentAt(int index);

    /**
     * getPopulation
     * 
     * This gets the population of the simulation based on
     * the amount of agents in the simulation
     * 
     * @return the amount of agents in the internal array
     */
    int getPopulation();

    /**
     * runSim
     * 
     * This function is called to indefinitly run the sim
     * currently it is not used all too much as the front end calls
     * simulate time step over and over
     */
    void runSim();

    /**
     * getInfectedCurrent
     * 
     * This get the current number of infected agents
     */
    int getInfectedCurrent();

    /**
     * getInfectedTotal
     * 
     * This get the current number of infected agents
     */
    int getInfectedTotal();

    /**
     * getDeceasedTotal
     * 
     * This get the current number of deceased agents
     * 
     * @return number of total deceased agents
     */
    int getDeceasedTotal();

    /**
     * getRecoveredTotal
     * 
     * This get the current number of recovered agents
     * 
     * @return number of total recovered agents
     */
    int getRecoveredTotal();

    /**
     * getHospitalTotal
     * 
     * This get the current number of total agents ever hospitilized
     * 
     * @return number of total hospitalized agents
     */
    int getHospitalTotal();

    /**
     * getHospitalCurrent
     * 
     * This get the current number of current hospital agents
     * 
     * @return number of current hospitalized agents
     */
    int getHospitalCurrent();

    /**
     * getICUtotal
     * 
     * This get the current number of total ICU agents
     * 
     * @return number of total ICU agents
     */
    int getICUtotal();

    /**
     * getICUCurrent
     * 
     * This get the current number of current ICU agents
     * 
     * @return number of current ICU agents
     */
    int getICUCurrent();

    /**
     * getNewlyInfected
     * 
     * This get the newly infected agents during timestep
     * 
     * @return number of newly infected agents
     */
    int getNewlyInfected();

    /**
     * setInputs
     * 
     * Takes inputs from front end sends them to the associated classes
     */
    // void setInputs();

    //user input setters
    /**
     * setSocialDistancingSeverity
     * 
     * setter for SocialDistancingSeverity
     * @param val the value to set
     */
    void setSocialDistancingSeverity(int val);

    /**
     * setMaskCompliance
     * 
     * setter for MaskCompliance
     * @param val the value to set
     */
    void setMaskCompliance(double val);

    /**
     * setHygieneMaintainence
     * 
     * setter for HygieneMaintainence
     * @param val the value to set
     */
    void setHygieneMaintainence(double val);

    //location risks
    /**
     * setGenStoreRisk
     * 
     * setter for GenStoreRisk
     * @param val the value to set
     */
    void setGenStoreRisk(double val);

    /**
     * setTransportRisk
     * 
     * setter for TransportRisk
     * @param val the value to set
     */
    void setTransportRisk(double val);

    /**
     * setSchoolRisk
     * 
     * setter for SchoolRisk
     * @param val the value to set
     */
    void setSchoolRisk(double val);

    /**
     * setParkRisk
     * 
     * setter for ParkRisk
     * @param val the value to set
     */
    void setParkRisk(double val);

    /**
     * setServiceRisk
     * 
     * setter for ServiceRisk
     * @param val the value to set
     */
    void setServiceRisk(double val);

    /**
     * setEntertainmentRisk
     * 
     * setter for EntertainmentRisk
     * @param val the value to set
     */
    void setEntertainmentRisk(double val);

    /**
     * setHealthPlaceRisk
     * 
     * setter for HealthPlaceRisk
     * @param val the value to set
     */
    void setHealthPlaceRisk(double val);

    /**
     * setPlaceOfWorshipRisk
     * 
     * setter for PlaceOfWorshipRisk
     * @param val the value to set
     */
    void setPlaceOfWorshipRisk(double val);

    /**
     * setResidentialRisk
     * 
     * setter for ResidentialRisk
     * @param val the value to set
     */
    void setResidentialRisk(double val);

    /**
     * setQuarantineSeverity
     * 
     * setter for Quarantine severity (odds of quarantine symptomatic cases)
     * @param val the value to set
     */
    void setQuarantineSeverity(double val);
    
    SIRtotals totalSimSIRStats;
    
    Transportation *locationInfo = NULL;

    std::vector<Agent *> recoveredAgents;
    std::vector<Agent *> deceasedAgents;

    private:
    Agent** simAgents;
    Hospital guelphHospital;
    IsolationCompartment isoCompartment;
    int timeStep;
    int currTime;
    DayOfWeek currDay;
    int timeQuarantined;
    int agentCount;
    int population;
    int newlyInfected;
    double sirTimeStep;
    double locationRisk[9];

    // user inputs
    // geographical risks
    int socialDistancingSeverity;
    double maskCompliance;
    double hygieneMaintainence;

    //outputs for Front End graph
    int infectedCurrent;
    int infectedTotal;
    int deceasedTotal;
    int recoveredTotal;
    int hospitalCurrent;
    int hospitalTotal;
    int icuCurrent;
    int icuTotal;
    int timeElapsed;

    double initiallyInfectedChance;
    int initiallyInfected;


    /**
     * addNewAgent
     * 
     * This function takes in the agents info and the amount of said
     * agent and adds that amount to the array of people
     * 
     * @param personInfo this is a string in the fomat GENDER N-N where N is the age range
     * @param amountToAdd this is a int of how many of that agent there are for the area i.e there are 3875 males 0-4 in guelph
     */
    void addNewAgent(string personInfo, int amountToAdd);

    /**
     * setUpAgents
     * 
     * This function takes in the file name of the demographic file
     * of an area in the format typeOfDataDataInfoAmountOfPeople
     * 
     * @param filename must be in the above format
     */
    void setUpAgents(string filename);

    /**
     * stepTime
     * 
     * This function is a helper function to push the time and day
     * forward on every iteration of the timesetp
     */
    void stepTime();

    /**
     * getNextDay
     * 
     * This is a helper function to increment the currDay counter
     * int the program
     */
    DayOfWeek getNextDay(DayOfWeek currDay);
};


//for python binding
extern "C" {
    Simulation* Simulation_new(){ return new Simulation("demographicGuelph.csv"); }
    void simTimeStep(Simulation* sim){ sim->simulateTimeStep(); }
    int newlyInfected(Simulation* sim) { return sim->getNewlyInfected(); }
    int infectedCurrent(Simulation* sim){ return sim->getInfectedCurrent(); }
    int infectedTotal(Simulation* sim){ return sim->getInfectedTotal(); }
    int deceasedTotal(Simulation* sim){ return sim->getDeceasedTotal(); }
    int recoveredTotal(Simulation* sim){ return sim->getRecoveredTotal(); }
    int hospitalTotal(Simulation* sim){ return sim->getHospitalTotal(); }
    int hospitalCurrent(Simulation* sim){ return sim->getHospitalCurrent(); }
    int ICUtotal(Simulation* sim){ return sim->getICUtotal(); }
    int ICUCurrent(Simulation* sim){ return sim->getICUCurrent(); }
    void socialDistanceServeritySetter(Simulation* sim, int val){sim->setSocialDistancingSeverity(val);}
    void maskComplianceSetter(Simulation* sim, double val){sim->setMaskCompliance(val);}
    void hygieneMaintainenceSetter(Simulation* sim, double val){sim->setHygieneMaintainence(val);}
    void genStoreRiskSetter(Simulation* sim, double val){sim->setGenStoreRisk(val);}
    void transportRiskSetter(Simulation* sim, double val){sim->setTransportRisk(val);}
    void schoolRiskSetter(Simulation* sim, double val){sim->setSchoolRisk(val);}
    void parkRiskSetter(Simulation* sim, double val){sim->setParkRisk(val);}
    void serviceRiskSetter(Simulation* sim, double val){sim->setServiceRisk(val);}
    void entertainmentRiskSetter(Simulation* sim, double val){sim->setEntertainmentRisk(val);}
    void healthPlaceRiskSetter(Simulation* sim, double val){sim->setHealthPlaceRisk(val);}
    void placeOfWorshipRiskSetter(Simulation* sim, double val){sim->setPlaceOfWorshipRisk(val);}
    void residentialRiskSetter(Simulation* sim, double val){sim->setResidentialRisk(val);}
    void quarantineSeverity(Simulation* sim, double val) {sim->setQuarantineSeverity(val);}
}

#endif