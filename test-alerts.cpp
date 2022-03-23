#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits Temp High")
{
  REQUIRE(inferBreach(50, 0.0, 30.0) == BreachType::TOO_HIGH);
}

TEST_CASE("infers the breach according to limits check Temp Low")
{
  REQUIRE(inferBreach(10, 20, 30.0) == BreachType::TOO_LOW);
}

TEST_CASE("infers the breach according to limits check Temp Normal")
{
  REQUIRE(inferBreach(10, 0, 30.0) == BreachType::NORMAL);
}

TEST_CASE("infers the breach according to negative value check Temp Low")
{
  REQUIRE(inferBreach(-20, 0, 30.0) == BreachType::TOO_LOW);
}

TEST_CASE("Check Cassify Method Battery state as Normal")
{
  REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 20) == BreachType::NORMAL);
  REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 20) == BreachType::NORMAL);
  REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 20) == BreachType::NORMAL);
}

TEST_CASE("Check Cassify Method Battery state as Low")
{
  REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, -1) == BreachType::TOO_LOW);
  REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, -2) == BreachType::TOO_LOW);
  REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, -3) == BreachType::TOO_LOW);
}

TEST_CASE("Check Cassify Method Battery state as High")
{
  REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 50) == BreachType::TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 50) == BreachType::TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 50) == BreachType::TOO_HIGH);
}

TEST_CASE("Check battery temperature and alert target as Email")
{

  AlertTarget alertTarget = AlertTarget::TO_EMAIL;
  BatteryCharacter *batteryCharactor = (BatteryCharacter *)malloc(sizeof(BatteryCharacter));
  batteryCharactor->coolingType = CoolingType::HI_ACTIVE_COOLING;
  double temperatureInC = 50.1;

  checkAndAlert(
      alertTarget, batteryCharactor, temperatureInC);

  delete batteryCharactor;
}

TEST_CASE("Check battery temperature and alert target as Controller")
{

  AlertTarget alertTarget = AlertTarget::TO_CONTROLLER;
  BatteryCharacter *batteryCharactor = (BatteryCharacter *)malloc(sizeof(BatteryCharacter));
  batteryCharactor->coolingType = CoolingType::HI_ACTIVE_COOLING;
  double temperatureInC = 50.1;

  checkAndAlert(
      alertTarget, batteryCharactor, temperatureInC);

  delete batteryCharactor;
}

TEST_CASE("Send Battery normal temperature state To Controller ")
{
  sendToController(BreachType::NORMAL);
}

TEST_CASE("Send Battery Low temperature state To Controller ")
{
  sendToController(BreachType::TOO_LOW);
}

TEST_CASE("Send Battery High temperature state To Controller ")
{
  sendToController(BreachType::TOO_HIGH);
}

TEST_CASE("Send Battery Normal state To Given Email ")
{
  sendToEmail(BreachType::NORMAL);
}

TEST_CASE("Send Battery Low temperature state To Given Email ")
{
  sendToEmail(BreachType::TOO_LOW);
}

TEST_CASE("Send Battery High temperature state To Given Email ")
{
  sendToEmail(BreachType::TOO_HIGH);
}
