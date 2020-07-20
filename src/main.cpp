/****************
 * COVID-19ABMGuelphS20
 * 16/07/20
 * ver 0.06
 * 
 * This is the main for the COVID-19 eABM
 ***************/


#include <iostream>
#include <time.h>
// should be the only thing included after finished
#include "simulation.hh"

//testing
#include "postalCodeHash.hh"
#include "agent.hh"


int main(){

    srand((unsigned int)time(NULL));

    //Simulation sim = Simulation("demographicGuelph.csv");
    // for(int i = 0; i < 131805; i++){
    //     cout << sim.getAgentAt(i).agentToString() << endl;
    // }

    // PostalCodeHash postalCodeStuff = PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
    // for(int i = 0; i < 7000; i++){
    //     if(postalCodeStuff.hashTable[i].getPostalCodeGrouping().compare("") != 0){
    //         cout << postalCodeStuff.hashTable[i].getPostalCodeGrouping() << " ";
    //         for(int k = 0; k < LOCATIONTYPESIZE; k++){
    //             cout << postalCodeStuff.hashTable[i].getLocationCountAt(k) << " ";
    //         }
    //         cout << endl;
    //         for(int j = 0; j < (int)postalCodeStuff.hashTable[i].getPostalCodeListLength(); j++){
    //             cout << postalCodeStuff.hashTable[i].getPostalCodeAt(j) << ", ";
    //         }
    //         cout << endl << endl;
    //     }
    // }

    Agent* tempAgent = new Agent(AgentInfoMap["Male 20-24"]);
    cout << tempAgent->DetermineSeverity() << endl;
    tempAgent->AgentInfected();
    while (tempAgent->DetermineSeverity() != RECOVERED && tempAgent->DetermineSeverity() != DECEASED) {
        cout << tempAgent->DetermineSeverity() << endl;
        tempAgent->SIRTimeStep(1);
    }

    free(tempAgent);
    
    return 0;
}
