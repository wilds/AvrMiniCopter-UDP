/*
 * Copyright (C) 2014-2015 Wilds
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AVRSPI_COMMANDS_H
#define AVRSPI_COMMANDS_H


#define COMMAND_NONE 0
#define COMMAND_SET_LOG_MODE 2
#define COMMAND_SET_FLY_MODE 3
#define COMMAND_SET_ORIENTATION 4
#define COMMAND_SET_MOTOR_PIN_FL 5
#define COMMAND_SET_MOTOR_PIN_BL COMMAND_SET_MOTOR_PIN_FL + 1
#define COMMAND_SET_MOTOR_PIN_FR COMMAND_SET_MOTOR_PIN_FL + 2
#define COMMAND_SET_MOTOR_PIN_BR COMMAND_SET_MOTOR_PIN_FL + 3
#define COMMAND_SET_MPU_ADDRESS 9
#define COMMAND_SET_YAW 10
#define COMMAND_SET_PITCH 11
#define COMMAND_SET_ROLL 12
#define COMMAND_SET_THROTTLE 13
#define COMMAND_SET_ALTITUDE 14         //send the baro value
#define COMMAND_SET_ALTITUDE_HOLD 15    //enable altitude holder
#define COMMAND_INCREMENT_ALTITUDE_TARGET 16
//#define COMMAND_SET_ALTITUDE_TARGET 20
#define COMMAND_SET_MOTOR_PWM_MIN 17
#define COMMAND_SET_MOTOR_PWM_INFLIGHT_THREASHOLD 18
#define COMMAND_SET_BC 69   //bc??

#define BASE_COMMAND_SET_PID_ACCEL 70
#define COMMAND_SET_PID_ACCEL_MAX BASE_COMMAND_SET_PID_ACCEL + 0
#define COMMAND_SET_PID_ACCEL_IMAX BASE_COMMAND_SET_PID_ACCEL + 1
#define COMMAND_SET_PID_ACCEL_KP BASE_COMMAND_SET_PID_ACCEL + 2
#define COMMAND_SET_PID_ACCEL_KI BASE_COMMAND_SET_PID_ACCEL + 3
#define COMMAND_SET_PID_ACCEL_KD BASE_COMMAND_SET_PID_ACCEL + 4

#define BASE_COMMAND_SET_PID_ALT 80
#define COMMAND_SET_PID_ALT_MAX BASE_COMMAND_SET_PID_ALT + 0
#define COMMAND_SET_PID_ALT_IMAX BASE_COMMAND_SET_PID_ALT + 1
#define COMMAND_SET_PID_ALT_KP BASE_COMMAND_SET_PID_ALT + 2
#define COMMAND_SET_PID_ALT_KI BASE_COMMAND_SET_PID_ALT + 3
#define COMMAND_SET_PID_ALT_KD BASE_COMMAND_SET_PID_ALT + 4

#define BASE_COMMAND_SET_PID_VZ 90
#define COMMAND_SET_PID_VZ_MAX BASE_COMMAND_SET_PID_VZ + 0
#define COMMAND_SET_PID_VZ_IMAX BASE_COMMAND_SET_PID_VZ + 1
#define COMMAND_SET_PID_VZ_KP BASE_COMMAND_SET_PID_VZ + 2
#define COMMAND_SET_PID_VZ_KI BASE_COMMAND_SET_PID_VZ + 3
#define COMMAND_SET_PID_VZ_KD BASE_COMMAND_SET_PID_VZ + 4

#define BASE_COMMAND_SET_PID_RATE 100

#define BASE_COMMAND_SET_PID_RATE_YAW BASE_COMMAND_SET_PID_RATE + 0
#define COMMAND_SET_PID_RATE_YAW_MAX BASE_COMMAND_SET_PID_RATE_YAW + 0
#define COMMAND_SET_PID_RATE_YAW_IMAX BASE_COMMAND_SET_PID_RATE_YAW + 1
#define COMMAND_SET_PID_RATE_YAW_KP BASE_COMMAND_SET_PID_RATE_YAW + 2
#define COMMAND_SET_PID_RATE_YAW_KI BASE_COMMAND_SET_PID_RATE_YAW + 3
#define COMMAND_SET_PID_RATE_YAW_KD BASE_COMMAND_SET_PID_RATE_YAW + 4

#define BASE_COMMAND_SET_PID_RATE_PITCH BASE_COMMAND_SET_PID_RATE + 10
#define COMMAND_SET_PID_RATE_PITCH_MAX BASE_COMMAND_SET_PID_RATE_PITCH + 0
#define COMMAND_SET_PID_RATE_PITCH_IMAX BASE_COMMAND_SET_PID_RATE_PITCH + 1
#define COMMAND_SET_PID_RATE_PITCH_KP BASE_COMMAND_SET_PID_RATE_PITCH + 2
#define COMMAND_SET_PID_RATE_PITCH_KI BASE_COMMAND_SET_PID_RATE_PITCH + 3
#define COMMAND_SET_PID_RATE_PITCH_KD BASE_COMMAND_SET_PID_RATE_PITCH + 4

#define BASE_COMMAND_SET_PID_RATE_ROLL BASE_COMMAND_SET_PID_RATE + 20
#define COMMAND_SET_PID_RATE_ROLL_MAX BASE_COMMAND_SET_PID_RATE_ROLL + 0
#define COMMAND_SET_PID_RATE_ROLL_IMAX BASE_COMMAND_SET_PID_RATE_ROLL + 1
#define COMMAND_SET_PID_RATE_ROLL_KP BASE_COMMAND_SET_PID_RATE_ROLL + 2
#define COMMAND_SET_PID_RATE_ROLL_KI BASE_COMMAND_SET_PID_RATE_ROLL + 3
#define COMMAND_SET_PID_RATE_ROLL_KD BASE_COMMAND_SET_PID_RATE_ROLL + 4

#define COMMAND_SET_PID_ACRO_P 130

#define BASE_COMMAND_SET_PID_STABLE 200

#define BASE_COMMAND_SET_PID_STABLE_YAW BASE_BASE_COMMAND_SET_PID_STABLE + 0
#define COMMAND_SET_PID_STABLE_YAW_MAX BASE_COMMAND_SET_PID_STABLE_YAW + 0
#define COMMAND_SET_PID_STABLE_YAW_IMAX BASE_COMMAND_SET_PID_STABLE_YAW + 1
#define COMMAND_SET_PID_STABLE_YAW_KP BASE_COMMAND_SET_PID_STABLE_YAW + 2
#define COMMAND_SET_PID_STABLE_YAW_KI BASE_COMMAND_SET_PID_STABLE_YAW + 3
#define COMMAND_SET_PID_STABLE_YAW_KD BASE_COMMAND_SET_PID_STABLE_YAW + 4

#define BASE_COMMAND_SET_PID_STABLE_PITCH BASE_COMMAND_SET_PID_STABLE + 10
#define COMMAND_SET_PID_STABLE_PITCH_MAX BASE_COMMAND_SET_PID_STABLE + 0
#define COMMAND_SET_PID_STABLE_PITCH_IMAX BASE_COMMAND_SET_PID_STABLE + 1
#define COMMAND_SET_PID_STABLE_PITCH_KP BASE_COMMAND_SET_PID_STABLE + 2
#define COMMAND_SET_PID_STABLE_PITCH_KI BASE_COMMAND_SET_PID_STABLE + 3
#define COMMAND_SET_PID_STABLE_PITCH_KD BASE_COMMAND_SET_PID_STABLE + 4

#define BASE_COMMAND_SET_PID_STABLE_ROLL BASE_COMMAND_SET_PID_STABLE + 20
#define COMMAND_SET_PID_STABLE_ROLL_MAX BASE_COMMAND_SET_PID_STABLE_ROLL + 0
#define COMMAND_SET_PID_STABLE_ROLL_IMAX BASE_COMMAND_SET_PID_STABLE_ROLL + 1
#define COMMAND_SET_PID_STABLE_ROLL_KP BASE_COMMAND_SET_PID_STABLE_ROLL + 2
#define COMMAND_SET_PID_STABLE_ROLL_KI BASE_COMMAND_SET_PID_STABLE_ROLL + 3
#define COMMAND_SET_PID_STABLE_ROLL_KD BASE_COMMAND_SET_PID_STABLE_ROLL + 4

#define COMMAND_PING 249
#define COMMAND_TESTMOTOR_FL 250
#define COMMAND_TESTMOTOR_BL 251
#define COMMAND_TESTMOTOR_FR 252
#define COMMAND_TESTMOTOR_BR 253
#define COMMAND_INITMOTOR 254
#define COMMAND_GET 255

#define PARAMETER_SET_FLY_MODE_STABLE 0
#define PARAMETER_SET_FLY_MODE_ACRO 1

#define PARAMETER_GET_STATUS 0
#define PARAMETER_GET_CRC 1
#define PARAMETER_GET_ARM_MOTOR 2
#define PARAMETER_GET_DUMMY 254
#define PARAMETER_GET_RESET_AVR 255

#define STATUS_INIT 0
#define STATUS_AWAITING_CONFIG_OR_COMMAND 1
#define STATUS_ARM_MOTORS 2
#define STATUS_INIT_MPU 3
#define STATUS_CALIBRATE_GYRO 4
#define STATUS_RUNNING 5
#define STATUS_MPU_ERROR 253
#define STATUS_AVR_LAG 254
#define STATUS_GYRO_CALIBRATION FAILED 255


#define PARAMETER_LOG_MODE_DISABLED 0
#define PARAMETER_LOG_MODE_ACCEL 1
#define PARAMETER_LOG_MODE_GYRO_AND_MOTOR 2
#define PARAMETER_LOG_MODE_QUATERNION_AND_MOTOR 3
#define PARAMETER_LOG_MODE_ALTITUDE 4
#define PARAMETER_LOG_MODE_QUATERNION_AND_ALTITUDE 5

#define LOG_GYRO_YAW 1
#define LOG_GYRO_PITCH 2
#define LOG_GYRO_ROLL 3
#define LOG_QUATERNION_YAW 4
#define LOG_QUATERNION_PITCH 5
#define LOG_QUATERNION_ROLL 6
#define LOG_QUATERNION_TARGET_YAW 7
#define LOG_MOTOR_FL 8
#define LOG_MOTOR_BL 9
#define LOG_MOTOR_FR 10
#define LOG_MOTOR_BR 11
#define LOG_ACCEL_1 12
#define LOG_ACCEL_2 13
#define LOG_ACCEL_3 14
#define LOG_ACCEL_MIN_1 15
#define LOG_ACCEL_MIN_2 16
#define LOG_ACCEL_MIN_3 17
#define LOG_ALTITUDE_HOLD_TARGET 18
#define LOG_ALTITUDE 19
#define LOG_ALTITUDE_VZ 20
#define LOG_ALTITUDE_PID_ACCEL 21
#endif	/* AVRSPI_COMMANDS_H */

