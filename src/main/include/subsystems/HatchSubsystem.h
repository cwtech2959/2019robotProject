/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>
#include "RobotMap.h"

class HatchSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Solenoid m_attach  {kAttachSolenoid};
  frc::Solenoid m_release {kReleaseSolenoid};
  frc::Solenoid m_safety  {kSafetySolenoid};

 public:
  HatchSubsystem();
  void InitDefaultCommand() override;

  void PrepForHatch();
  void SecureHatch();
  void AttachHatch();
  void ReleaseHatch();
  void RetractMechanism();
};
