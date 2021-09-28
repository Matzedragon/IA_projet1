#pragma once
#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   drunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the drunkard class.
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class drunkard;
struct Telegram;

// drunk enough to cause a quarrel 
class gettinOutOfToilet : public State<drunkard>
{
private:
	gettinOutOfToilet() {};
	gettinOutOfToilet(const gettinOutOfToilet&);
	gettinOutOfToilet& operator=(const gettinOutOfToilet&);

public:
	// to get the pointer to the singleton
	static gettinOutOfToilet* Instance();

	virtual void Enter(drunkard* drunkard);

	virtual void Execute(drunkard* drunkard);

	virtual void Exit(drunkard* drunkard);

	virtual bool OnMessage(drunkard* agent, const Telegram& msg);
};

//chill drunkard
class GoToTheBarAndDrink : public State<drunkard> {
private:
	GoToTheBarAndDrink() {};

	//copy ctor and assignment should be private
	GoToTheBarAndDrink(const GoToTheBarAndDrink&);
	GoToTheBarAndDrink& operator=(const GoToTheBarAndDrink&);

public:
	// to get the pointer to the singleton
	static GoToTheBarAndDrink* Instance();

	virtual void Enter(drunkard* drunkard);

	virtual void Execute(drunkard* drunkard);

	virtual void Exit(drunkard* drunkard);

	virtual bool OnMessage(drunkard* agent, const Telegram& msg);
};

class GoAtHomeToRest : public State<drunkard> {
private:
	GoAtHomeToRest() {};

	//copy ctor and assignment should be private
	GoAtHomeToRest(const GoAtHomeToRest&);
	GoAtHomeToRest& operator=(const GoAtHomeToRest&);

public:
	// to get the pointer to the singleton
	static GoAtHomeToRest* Instance();

	virtual void Enter(drunkard* drunkard);

	virtual void Execute(drunkard* drunkard);

	virtual void Exit(drunkard* drunkard);

	virtual bool OnMessage(drunkard* agent, const Telegram& msg);
};

class GoToToilet :public State<drunkard> {
private:
	GoToToilet() {};

	GoToToilet(const GoToToilet&);
	GoToToilet& operator=(const GoToToilet&);

public:
	static GoToToilet* Instance();
	virtual void Enter(drunkard* drunkard);

	virtual void Execute(drunkard* drunkard);

	virtual void Exit(drunkard* drunkard);

	virtual bool OnMessage(drunkard* agent, const Telegram& msg);

};


class altercation : public State<drunkard> {

private:
	altercation() {};

	altercation(const altercation&);
	altercation& operator=(const altercation&);

public:
	static altercation* Instance();
	virtual void Enter(drunkard* drunkard);

	virtual void Execute(drunkard* drunkard);

	virtual void Exit(drunkard* drunkard);

	virtual bool OnMessage(drunkard* agent, const Telegram& msg);
};
#endif