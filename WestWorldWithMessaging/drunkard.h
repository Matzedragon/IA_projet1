#pragma once
#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name:   drunkard.h
//
//  Desc:   A class defining a drunk person at the bar interacting with the miner.
//
//  Author: Mathieu Capo 2021
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>
#include <time.h>
#include "Locations.h"
#include "BaseGameEntity.h"
#include "misc/ConsoleUtils.h"
#include "drunkardOwnedStates.h"
#include "fsm/StateMachine.h"

//the alcohol level to be considered drunk to have an argument
const float AlcoholLevelForDrunk = 0.6;
// before drunkard goes home
const float MaxAlcoholBeforeSick = 2.0;
// the drunkard's alcohol level incrase by 0.2 for each beer.
const float AmountAlcoholPerBeer = 0.2;

const int needToilet = 10;

class drunkard : public BaseGameEntity
{
private:
	// an instance of the state machine class
	StateMachine<drunkard>* m_pStateMachine;

    //current amount of beer drank by the bot
	int m_beerDrank;
    float m_alcoholLevel;
    int m_pee;

    location_type m_Location;

public: 
    drunkard(int id) :m_Location(saloon),
        m_beerDrank(0),
        m_alcoholLevel(0.0),
        m_pee(0),
        BaseGameEntity(id)

    {
        srand(time(0));
        //set up state machine
        m_pStateMachine = new StateMachine<drunkard>(this);

        //default state is the drunkard going to to bar.
        m_pStateMachine->SetCurrentState(GoToTheBarAndDrink::Instance());

    }

    ~drunkard() { delete m_pStateMachine; }

    void Update();
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<drunkard>* GetFSM()const { return m_pStateMachine; }

    // Accessors 
    location_type Location()const { return m_Location; } // could be needed if we do a case where the drunkard isn't at the saloon.
    void ChangeLocation(location_type loc) { m_Location = loc; }

    void drinkBeers(int d) { m_beerDrank = d; };
    void addDrankBeer();
    bool isDrunk()const;
    bool isSick()const;
    bool wantToPee() const;
    void reduceAlcoholLevel(); // TODO reduce by random between 0.1 and 0.4
    void resetPee();
    float getAlcoholLevel() { return m_alcoholLevel; };
    void resetAlcoholLevel() { m_alcoholLevel = 0.0; m_beerDrank = 0; }; // if rested and ready to go back to the saloon

};

#endif