#ifndef TYPEWISE_ALERT_H_
#define TYPEWISE_ALERT_H_

#include <malloc.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/** @brief  Type of colling in Enum */
typedef enum
{
  PASSIVE_COOLING = 0,
  HI_ACTIVE_COOLING = 1,
  MED_ACTIVE_COOLING = 2
} CoolingType;

/** @brief  Battery temperature state */
typedef enum
{
  NORMAL = 0,
  TOO_LOW = 1,
  TOO_HIGH = 2
} BreachType;

/** @brief  Based on alert set, Battery status to be communicated */
typedef enum
{
  TO_CONTROLLER = 0,
  TO_EMAIL = 1
} AlertTarget;

/** @brief  Battery charector to be stored */
typedef struct
{
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

/**
 * @brief Interface for battery temperature value based on temperature state return.
 * @param value Current battery heat value
 * @param lowerLimit Defined min temperature value
 * @param upperLimit Defined maximum temperature value
 */
BreachType inferBreach(double value, double lowerLimit, double upperLimit);

/**
 * @brief Classify temperature battery reach state.
 * @param coolingType Type of colling in battery
 * @param temperatureInC CSB event message
 */
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

/**
 * @brief Check battery temeprature and notify to controller/Email.
 * @param alertTarget Specify alert either controlelr/Email
 * @param batteryChar Structure has colling trpe and name of the battery
 * @param temperatureInC Current temperature of the battery
 */
void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter *batteryChar, double temperatureInC);

/**
 * @brief Notify to controller about battery state.
 * @param breachType Temeprature state of the battery
 */
void sendToController(BreachType breachType);
/**
 * @brief Notify to Email about battery state.
 * @param breachType Temeprature state of the battery
 */
void sendToEmail(BreachType breachType);

#endif // TYPEWISE_ALERT_H_