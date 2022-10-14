#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Year
{
    public:
        // GET //

        int GetNumber();
        int GetNumberMAX();
        bool GetGameOverState();

        // SET //

        void SetSeed();

        // PROPOSE TO SAVE/LOAD //

        void IfPossibleProposeToLoad();
        bool ProposeToSave();

        // YEAR CYCLE //

        void AboutTheYear();
        void SetOrder();
        void YearPasses();
        void ActIfGameOver();

    private:
        // RANDOM //

        int seed = 0;
        int randomActions = 0;

        // GENERAL //

        int number = 1;
        float deathRatesSum = 0;
        bool isGameOver = false;

        // RESOURCES WITH THE DETAILS //

        int citizens = 100;
        int citizensStarved = 0;
        int citizensArrived = 0;

        int wheat = 2800;
        int wheatHarvested = 0;
        int wheatHarvestedPerAcre = 0;
        int wheatEatenByRats = 0;

        int acres = 1000;
        int acrePrice = 0;

        bool plague = false;

        // THE ORDER //

        int acresToBuy = 0;
        int acresToSell = 0;
        int acresToSow = 0;
        int wheatToEat = 0;

        // CONSTANT SETTINGS //

        const int numberMAX = 10;

        const int wheatHarvestedPerAcreMIN = 1;
        const int wheatHarvestedPerAcreMAX = 6;
        const float wheatRatShare = 0.07f;

        const int citizenHungerForWheat = 20;
        const int citizenCanHandleAcres = 10;

        const float acreSowPrice = 0.5f;
        const int acrePriceMIN = 17;
        const int acrePriceMAX = 26;

        const int plaugueChance = 15;

        const float lostConditionStarvation = 0.45f;

        // GRADES CONDITIONS //

        const float averageDeathRateA = 0.03f;
        const float averageDeathRateB = 0.1f;
        const float averageDeathRateC = 0.33f;

        const int acresPerCitizenA = 10;
        const int acresPerCitizenB = 9;
        const int acresPerCitizenC = 7;

        // CONSTRUCT YEAR DETAILS //

        std::string AboutCitizenShift();
        std::string AboutPlague();
        std::string AboutHarvest();
        std::string AboutWheat();
        std::string AboutAcres();

        // SAVE/LOAD //

        void SaveGame();
        void LoadGame();

        // CHECK THE ORDER //

        void HearTheOrder(int &order, std::string ask);
        bool isOrderImpossible();

        // EVENTS DURING YEAR //

        void SowAndHarvest();
        void FeastAndStarve();
        void NewCitizensArrive();
        void PlagueInfection();

        // GAME RESULT //

        void GiveGrade();
};

// UTILITY //
std::string ProperOutputForm(int number, std::string form1, std::string form2, std::string form5);
bool HearYesOrNo(std::string question);
bool isNumber(std::string string);