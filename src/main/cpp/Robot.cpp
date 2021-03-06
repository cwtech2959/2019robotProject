/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
// #include <cameraserver/CameraServer.h>

#include "../../../../2019RaspPIRoboRioShared/Shared.hpp"
#include <iostream>

// create instance of subsystems
DriveTrainSubsystem Robot::m_driveTrainSubsystem;
HatchSubsystem Robot::m_hatchSubsystem;
CargoControlSubsystem Robot::m_cargoControlSubsystem;
CargoArmSubsystem Robot::m_cargoArmSubsystem;
LiftAndShuttleSubsystem Robot::m_liftAndShuttleSubsystem;
ClimbSubsystem Robot::m_climbSubsystem;
std::shared_ptr<nt::NetworkTable> Robot::m_networkTable;
// create instance of OI
OI Robot::m_oi;

void Robot::RobotInit() {
  // m_chooser.SetDefaultOption("Default Auto", &m_myAuto);
  // m_chooser.AddOption("My Auto", &m_myAuto);
  // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  // frc::CameraServer::GetInstance()->StartAutomaticCapture();
  m_networkTable = nt::NetworkTableInstance::GetDefault().GetTable(Rpi2959Shared::Tables::TableName);
  
  m_driveTrainSubsystem.OnRobotInit();
  m_liftAndShuttleSubsystem.OnRobotInit();
  m_cargoArmSubsystem.OnRobotInit();
  m_cargoControlSubsystem.OnRobotInit();
  m_hatchSubsystem.OnRobotInit();
  m_climbSubsystem.OnRobotInit();

  m_debugDrive = false;
  m_debugLiftAndShuttle = false;
  m_debugCargoArm = false;
  m_debugCargoControl = false;
  m_debugHatch = false;
  m_debugClimb = false;

  frc::SmartDashboard::PutBoolean("Debug Drive", m_debugDrive);
  frc::SmartDashboard::PutBoolean("Debug Lift", m_debugLiftAndShuttle);
  frc::SmartDashboard::PutBoolean("Debug Cargo Arm", m_debugCargoArm);
  frc::SmartDashboard::PutBoolean("Debug Cargo Control", m_debugCargoControl);
  frc::SmartDashboard::PutBoolean("Debug Hatch", m_debugHatch);
  frc::SmartDashboard::PutBoolean("Debug Climb", m_debugClimb);

  // Drive to Port Tape command adjustments
  // frc::SmartDashboard::PutNumber("Auto Rotation", 250.0);
  // frc::SmartDashboard::PutNumber("Auto Forward", 1500.0);
  // frc::SmartDashboard::PutNumber("Accel", 100.0);
  // frc::SmartDashboard::PutNumber("Separation Limit", 0.3);

  frc::SmartDashboard::PutNumber("Auto Rotation", 250.0);
  frc::SmartDashboard::PutNumber("Auto Forward", 1500.0);
  frc::SmartDashboard::PutNumber("Accel", 100.0);
  frc::SmartDashboard::PutNumber("Separation Limit", 0.3);

  // Tell the Raspberry PI that we don't need it looking for anything on the front camera yet
  m_networkTable->PutNumber(Rpi2959Shared::Keys::FrontTargets, 0.0);

  // Tell the Raspberry PI that we don't need it to look for anything on the back camera
  m_networkTable->PutNumber(Rpi2959Shared::Keys::BackTargets, 0.0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
/*  double frameNumber = m_networkTable->GetNumber(Rpi2959Shared::Keys::FrontFrameNumber, 0.0);
  double targets = m_networkTable->GetNumber(Rpi2959Shared::Keys::FrontTargets, 0.0);
  auto targetRect = m_networkTable->GetNumberArray(Rpi2959Shared::Keys::FrontPortTapeResults, std::vector<double>{});

  // Testing of Raspberry Pi info through network tables
  std::cout<<"front framenumber = "<<frameNumber<<"\n";
  std::cout <<"front targets = " << targets << "\n";
  for(auto i = 0; i < targetRect.size(); ++i)
    std::cout << "front tape targetRect[" << i << "] = " << targetRect[i] << "\n"; */

  m_periodic++;
  
  if (m_periodic == 2)
  {
    m_driveTrainSubsystem.OnRobotPeriodic(m_debugDrive);
  }
  else if (m_periodic == 4)
  {
    m_cargoArmSubsystem.OnRobotPeriodic(m_debugCargoArm);
    m_cargoControlSubsystem.OnRobotPeriodic(m_debugCargoControl);
  }
  else if (m_periodic == 8)
  {
    m_hatchSubsystem.OnRobotPeriodic(m_debugHatch);
    m_climbSubsystem.OnRobotPeriodic(m_debugClimb);
  }
  else if (m_periodic >= 10)
  { 
    m_liftAndShuttleSubsystem.OnRobotPeriodic(m_debugLiftAndShuttle);
    m_periodic = 0;
  }
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{
  m_climbSubsystem.ClimbSolenoidDisengage();
}

void Robot::DisabledPeriodic()
{
  m_driveTrainSubsystem.DisabledWatchDog();
  if (m_periodic == 9)
  {
    m_debugDrive = frc::SmartDashboard::GetBoolean("Debug Drive", false);
    m_debugLiftAndShuttle = frc::SmartDashboard::GetBoolean("Debug Lift", false);
    m_debugCargoArm = frc::SmartDashboard::GetBoolean("Debug Cargo Arm", false);
    m_debugCargoControl = frc::SmartDashboard::GetBoolean("Debug Cargo Control", false);
    m_debugHatch = frc::SmartDashboard::GetBoolean("Debug Hatch", false);
    m_debugClimb = frc::SmartDashboard::GetBoolean("Debug Climb", false);
  }
  frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit()
{
  m_cargoArmSubsystem.MoveCargoArmToPosition(0);
  m_liftAndShuttleSubsystem.MoveLiftToPosition(0);
  m_climbSubsystem.ClimbWheelsSetPosition(0);
  if (m_cargoControlSubsystem.CargoIn())
  {
    m_cargoControlSubsystem.ChangeWheelsSpeed(kHoldCargoSpeed);
  }
  else
  {
    m_autonomousCommand = &m_hatchAuto;
  }
  
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

  // m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr)
  {
    m_autonomousCommand->Start();
  }
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit()
{
  m_climbSubsystem.ClimbWheelsSetPosition(0);

  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr)
  {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
