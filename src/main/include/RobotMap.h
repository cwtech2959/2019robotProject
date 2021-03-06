/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// CAN motor addresses
constexpr int kRight1CanSparkMaxMotor = 1;
constexpr int kRight2CanSparkMaxMotor = 2;
//constexpr int kRight3CanSparkMaxMotor = 3;
constexpr int kLeft1CanSparkMaxMotor = 4;
constexpr int kLeft2CanSparkMaxMotor = 5;
//constexpr int kLeft3CanSparkMaxMotor = 6;

constexpr int kLiftPrimaryCanSparkMaxMotor = 7;
constexpr int kLiftFollower1CanSparkMaxMotor = 8;
constexpr int kLiftFollower2CanSparkMaxMotor = 9;

// constexpr int kLeftCargoShuttleCanTalonSrxMotor = 11;
// constexpr int kRightCargoShuttleCanTalonSrxMotor = 12;
constexpr int kLeftClimbCanTalonSrxMotor = 11;
constexpr int kRightClimbCanTalonSrxMotor = 12;

constexpr int kLeftCargoArmCanTalonSrxMotor = 13;
constexpr int kRightCargoArmCanTalonSrxMotor = 14;

// PWM motor addresses
constexpr int kCargoArmWheelsPwmSparkMotor = 0;
// constexpr int kClimbWheelsPwmSparkMotor = 1;
// constexpr int kClimbEngagePwmSparkMotor = 2;

// PCM solenoid addresses
constexpr int kHatchAttachSolenoid = 0;
constexpr int kHatchReleaseSolenoid = 1;
constexpr int kHatchSafetySolenoid = 2;
constexpr int kClimbEngageSolenoid = 3;

constexpr int kTallClimbEngageSolenoid = 4;
constexpr int kNewClimbEngage1 = 6;
constexpr int kNewClimbEngage2 = 7;

// Digital IO addresses
constexpr int kLiftBottomSwitch = 0;
constexpr int kCargoInSwitch = 1;
// constexpr int kCargoShuttleFrontSwitchTrigger = 2;
// constexpr int kCargoShuttleBackSwitchTrigger = 3;
constexpr int kWhiteTapeSwitch1 = 4;
constexpr int kWhiteTapeSwitch2 = 7;
constexpr int kWhiteTapeSwitch3 = 8;

// Operator input USB ports
constexpr int kLeftDriverUSBController = 0;
constexpr int kRighttDriverUSBController = 1;
constexpr int kCoPilotUSBController = 2;
