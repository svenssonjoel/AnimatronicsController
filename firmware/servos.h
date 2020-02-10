/*
    Copyright 2020 Joel Svensson	svenssonjoel@yahoo.se

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SERVOS_H_
#define _SERVOS_H_

#define SERVO1 0x01
#define SERVO2 0x02
#define SERVO3 0x04
#define SERVO4 0x08
#define SERVO5 0x10
#define SERVO6 0x20
#define SERVO7 0x40
#define SERVO8 0x80


extern void servos_init(void);

extern void servos_set_duty(uint8_t servos, unsigned int duty);

#endif
