#include "drunkardOwnedStates.h"
#include "fsm/State.h"
#include "Locations.h"
#include "drunkard.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif



/************************************************************/
/************************************************************/
/************************************************************/

/* Methods for GotToTheBarAndDrink*/
GoToTheBarAndDrink* GoToTheBarAndDrink::Instance()
{
    static GoToTheBarAndDrink instance;

    return &instance;
}


void GoToTheBarAndDrink::Enter(drunkard* pDrunkard)
{
    /* if not at the bar, change location*/
    if (pDrunkard->Location() != saloon)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Going to the Saloon !";

        pDrunkard->ChangeLocation(saloon);
    }
}


void GoToTheBarAndDrink::Execute(drunkard* pDrunkard)
{
    //The drunkard has strated to drink at the bar till he changes state when he's really drunk
    pDrunkard->addDrankBeer();

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Drinking a beer... ";

    //if drunkard drank too much, he can start picking up on people
    if (pDrunkard->wantToPee())
    {
        pDrunkard->GetFSM()->ChangeState(GoToToilet::Instance());
    }
    // if too drunk he goes home
    if (pDrunkard->isSick())
    {
        pDrunkard->GetFSM()->ChangeState(GoAtHomeToRest::Instance());
    }
}


void GoToTheBarAndDrink::Exit(drunkard* pDrunkard)
{

}


bool GoToTheBarAndDrink::OnMessage(drunkard* pDrunkard, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_enteringBar:

        cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        pDrunkard->GetFSM()->ChangeState(GoToToilet::Instance());
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunkard->ID(),    //ID of sender
            ent_Miner_Bob,      //ID of recipient
            Msg_GoingToToilet,  //the message
            NO_ADDITIONAL_INFO);

        return true;

    }//end switch
    //send msg to global message handler
    return false;
}

/************************************************************/
/*The drunkard reached his maximum alcohol level and decides*/
/* to go home so it goes down                               */
/************************************************************/

/* Methods for GoAtHomeToRest */

GoAtHomeToRest* GoAtHomeToRest::Instance()
{
    static GoAtHomeToRest instance;

    return &instance;
}

void GoAtHomeToRest::Enter(drunkard* pDrunkard)
{
    /* if not at his house, change location*/
    if (pDrunkard->Location() != d_house)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Going back home to sleep... *throw up*";

        pDrunkard->ChangeLocation(d_house);
    }
}

void GoAtHomeToRest::Execute(drunkard* pDrunkard)
{
    pDrunkard->reduceAlcoholLevel();
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Zzzz... ";

    // if the drunkard isn't drunk anymore he can go back drink 
    if (pDrunkard->getAlcoholLevel() == 0.0)
    {
        pDrunkard->GetFSM()->ChangeState(GoToTheBarAndDrink::Instance());
    }
}

void GoAtHomeToRest::Exit(drunkard* pDrunkard)
{
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
        << "Time to go drink at the saloon";
}

bool GoAtHomeToRest::OnMessage(drunkard* agent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

/****************************************************************/
/* This state is called when the miner enters the bar to force  */
/* the altercation situation or just when the variable m_pee    */
/* reaches needToilet                                           */
/* It informs the miner with a message that the drunkard is     */
/* leaving to the toilets so the miner can take his seat        */
/****************************************************************/

/* Methods for gettinOutOfToilet*/

GoToToilet* GoToToilet::Instance()
{
    static GoToToilet instance;

    return &instance;
}

void GoToToilet::Enter(drunkard* pDrunkard)
{
    /* if not at his house, change location*/
    if (pDrunkard->Location() != saloon_toilets)
    {
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
            << "I need to go pee";
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*opens the toilet's door*";

        pDrunkard->ChangeLocation(saloon_toilets);
    }
}

void GoToToilet::Execute(drunkard* pDrunkard)
{
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*peeing*... ";
    pDrunkard->resetPee();
    pDrunkard->GetFSM()->ChangeState(gettinOutOfToilet::Instance());
}

void GoToToilet::Exit(drunkard* pDrunkard)
{
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Aye i m feeling better, where was my stool already";
}

bool GoToToilet::OnMessage(drunkard* pDrunkard, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_enteringBar:

        cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunkard->ID(),    //ID of sender
            ent_Miner_Bob,      //ID of recipient
            Msg_GoingToToilet,  //the message
            NO_ADDITIONAL_INFO);

        return true;

    }//end switch
    return false;
}

/****************************************************************/
/* When the drunkard gets out of the toilets, sends a           */
/* message to the miner, if he answers that he took it's        */
/* seat then the drunkard goes into the state altercation       */
/* else he just continues to drink (state : GoToTheBarAndDrink )*/
/****************************************************************/

/* Methods for gettinOutOfToilet*/
gettinOutOfToilet* gettinOutOfToilet::Instance()
{
    static gettinOutOfToilet instance;

    return &instance;
}


void gettinOutOfToilet::Enter(drunkard* pDrunkard)
{
    if (pDrunkard->Location() != saloon) {

        pDrunkard->ChangeLocation(saloon);

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunkard->ID(),    //ID of sender
            ent_Miner_Bob,      //ID of recipient
            Msg_gettingOutOfToilet,  //the message
            NO_ADDITIONAL_INFO);
    }
}
void gettinOutOfToilet::Execute(drunkard* pDrunkard)
{
    // The miner didn't take his seats while he was gone so he just sits back at the bar
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Back to drinking !";
    pDrunkard->GetFSM()->ChangeState(GoToTheBarAndDrink::Instance());
}

void gettinOutOfToilet::Exit(drunkard* pDrunkard)
{
}

bool gettinOutOfToilet::OnMessage(drunkard* pDrunkard, const Telegram& msg)
{
    // if when getting out, miner sends back a message with tookstool, then we start an altercation
    switch (msg.Msg)
    {
    case Msg_tookStool:

        cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        pDrunkard->GetFSM()->ChangeState(altercation::Instance());

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunkard->ID(),        //ID of sender
            ent_Miner_Bob,            //ID of recipient
            Msg_altercation,   //the message
            NO_ADDITIONAL_INFO);

        return true;
    }//end switch
    return false;
}

/****************************************************************/
/* If the miner decides to getmad the drunkard will react with  */
/* an angry message, else he'll offer to buy the miner a drink  */
/* state changes to GoToTheBarAndDrink either way               */
/****************************************************************/

/* Methods for altercation*/
altercation* altercation::Instance()
{
    static altercation instance;

    return &instance;
}

void altercation::Enter(drunkard* pDrunkard)
{

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "That's my place mate";
}

void altercation::Execute(drunkard* pDrunkard)
{
    pDrunkard->GetFSM()->ChangeState(GoToTheBarAndDrink::Instance());
}

void altercation::Exit(drunkard* pDrunkard)
{

}

bool altercation::OnMessage(drunkard* pDrunkard, const Telegram& msg)
{
    
    switch (msg.Msg)
    {
    case Msg_getmad:
        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "you saw me getting out the toilets 5 seconds ago you wanna fight or what";
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "That's my drink aswell in front of ya";
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunkard->ID(),    //ID of sender
            ent_Miner_Bob,      //ID of recipient
            Msg_getmad,  //the message
            NO_ADDITIONAL_INFO);
        return true;
    case Msg_giveBackSeat:
        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "No worries mate let me get something to drink for you";
        return true;
    }
    return false;
}