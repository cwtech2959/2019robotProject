/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc/Solenoid.h"
#include "frc/Spark.h"
#include "RobotMap.h"

class CargoArmSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Spark m_wheels {kCargoArmWheelsMotorPWM};
  frc::Solenoid m_armExtend {kCargoArmExtendSolenoid};

 public:
  CargoArmSubsystem();

  void Extend();
  void Retract();
  void WheelsOn();
  void WheelsOff();
};