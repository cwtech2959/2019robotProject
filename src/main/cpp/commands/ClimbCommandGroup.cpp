/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbCommandGroup.h"
#include "commands/MoveLiftCommand.h"
#include "commands/MoveCargoArmCommand.h"
#include "subsystems/CargoArmPositions.h"
#include "subsystems/ClimbSubsystem.h"
#include "subsystems/DriveTrainSubsystem.h"
#include "commands/ClimbSolenoidCommand.h"
#include "commands/PowerToClimbWheelsCommand.h"
#include "commands/ClimbWheelsSetPositionCommand.h"
#include "commands/DriveSetDistanceCommand.h"
#include <frc/commands/TimedCommand.h>
#include "commands/ReconfigureLiftForClimbCommand.h"
#include "commands/RaiseBotBaseToClimbCommand.h"

ClimbCommandGroup::ClimbCommandGroup(TargetHabLevel targetLevel)
{
  AddParallel(new MoveCargoArmCommand(kArmTiltBackwardPosition));
  if (targetLevel == TargetHabLevel::HabLevel2)
  {
    AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbPrepHab2));
  }
  else
  {
    AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbPrepHab3));
  }
  AddParallel(new ReconfigureLiftForClimbCommand());
  AddParallel(new MoveCargoArmCommand(kArmTiltForwardPosition));
  AddSequential(new ClimbWheelsSetPositionCommand(kClimbArmsDownDistance));
  AddSequential(new PowerToClimbWheelsCommand(kClimbWheelsHoldingCurrent));

  AddSequential(new frc::TimedCommand(5.0));

  if (targetLevel == TargetHabLevel::HabLevel2)
  {
    AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbHab2));
  }
  else
  {
    AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbHab3));
  }
  AddSequential(new ClimbSolenoidCommand(true));
  AddSequential(new frc::TimedCommand(0.25));

  AddSequential(new frc::TimedCommand(5.0));
  
  AddSequential(new RaiseBotBaseToClimbCommand());

  AddSequential(new ClimbWheelsSetPositionCommand(kDriveClimbWheelsDistance));
  AddParallel(new PowerToClimbWheelsCommand(kClimbWheelsHoldingCurrent));
  AddSequential(new DriveSetDistanceCommand());
  AddParallel(new ClimbSolenoidCommand(false));
  AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::RaiseClimbWheels));
}
