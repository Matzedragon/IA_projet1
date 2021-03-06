#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_GoingToToilet,
  Msg_gettingOutOfToilet,
  Msg_tookStool,
  Msg_altercation,
  Msg_enteringBar,
  Msg_getmad,
  Msg_giveBackSeat
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

      return "LeftToToilet";

  case 3:

      return "LeavingToilet";

  case 4:

      return "stoolTaken";

  case 5:

      return "altercation";

  case 6:
      return "MinerEnteringBar";

  case 7: 
      return "GetsMad";

  case 8:
      return "GiveBackDrunkardsSeat";

  default:

    return "Not recognized!";
  }
}

#endif