#include "typewise-alert.h"

using namespace std;

BreachType inferBreach(double tempValue, double lowerLimit, double upperLimit)
{
  BreachType batteryTemp;

  if (tempValue < lowerLimit)
  {
    batteryTemp = TOO_LOW;
  }
  else if (tempValue > upperLimit)
  {
    batteryTemp = TOO_HIGH;
  }
  else
  {
    batteryTemp = NORMAL;
  }

  return batteryTemp;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC)
{
  int lowerLimit = 0;
  int upperLimit = 0;

  switch (coolingType)
  {
  case PASSIVE_COOLING:
    upperLimit = 35;
    break;
  case HI_ACTIVE_COOLING:
    upperLimit = 45;
    break;
  case MED_ACTIVE_COOLING:
    upperLimit = 40;
    break;
  default:
    std::cout << "Not matches with any battery colling type!!!" << std::endl;
    break;
  }

  BreachType batteryTemp = inferBreach(temperatureInC, lowerLimit, upperLimit);

  return batteryTemp;
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter *batteryChar, double temperatureInC)
{

  BreachType breachType = classifyTemperatureBreach(
      batteryChar->coolingType, temperatureInC);

  switch (alertTarget)
  {
  case TO_CONTROLLER:
    sendToController(breachType);
    break;
  case TO_EMAIL:
    sendToEmail(breachType);
    break;
  default:
    break;
  }
}

void sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  std::cout << header << ":" << breachType << std::endl;
}

void sendToEmail(BreachType breachType)
{
  const char *recepient = "a.b@c.com";
  std::cout << "To: " << recepient << std::endl;

  switch (breachType)
  {
  case TOO_LOW:
    std::cout << "Hi, the temperature is too low" << std::endl;
    break;
  case TOO_HIGH:
    std::cout << "Hi, the temperature is too high" << std::endl;
    break;
  case NORMAL:
    std::cout << "Hi, the temperature is normal" << std::endl;
    break;
  default:
    break;
  }
}
