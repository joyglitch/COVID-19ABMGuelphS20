 /****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the hospital class
 ***************/


#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <string>
#include <iostream>

using namespace std;

//Declare simulation class
class Hospital {
    private:
    int totalBedCount;
    int icuBedCount;
    int numberPpl;
    int icuCount;

    public:
    Hospital();
    void FreeIcuBeds();
    void FreeHospitalBeds();
    void IndicateOverflow();
    void IncreaseHospitalCount();
    void increaseIcuCount();
};

#endif
