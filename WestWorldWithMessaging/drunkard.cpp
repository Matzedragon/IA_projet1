#include "drunkard.h"
#include <iostream>
using std::cout;

void drunkard::Update()
{
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
	// TODO see if something needed
	m_pStateMachine->Update();
}

bool drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void drunkard::addDrankBeer()
{
	int randNum = rand() % (5 - 1 + 1) + 1;
	m_pee += randNum;
	m_beerDrank += 1;
	m_alcoholLevel = m_beerDrank * AmountAlcoholPerBeer;
}

bool drunkard::isDrunk() const
{
	// if current alcohol level is higher or equals to the amount to be considered drunk, returns true
	if (m_alcoholLevel >= AlcoholLevelForDrunk) {
		return true;
	}
	else {
		return false;
	}
}

bool drunkard::isSick() const
{
	// if current alcohol level is higher or equals to the amount to be considered sick, returns true
	if (m_alcoholLevel >= MaxAlcoholBeforeSick) {
		return true;
	}
	else {
		return false;
	}
}

bool drunkard::wantToPee() const
{
	if (m_pee >= needToilet) {
		return true;
	}
	return false;
}

void drunkard::resetPee() {
	m_pee = 0;
}
void drunkard::reduceAlcoholLevel()
{
	if (m_alcoholLevel >= 0.1) {
		m_alcoholLevel -= 0.4;
	} 
	// ex: 0.4 - 0.4 != 0.0 but it's < 0.1  
	if (m_alcoholLevel < 0.1) {
		resetAlcoholLevel();
	}
}
