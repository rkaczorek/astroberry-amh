/*******************************************************************************
 Copyright(c) 2017 Radek Kaczorek  <rkaczorek AT gmail DOT com>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License version 2 as published by the Free Software Foundation.
 .
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.
 .
 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
*******************************************************************************/

#ifndef AMHFOCUS_H
#define AMHFOCUS_H

#include "Adafruit_MotorHAT.h"
#include <indifocuser.h>

class IndiAMHFocuser : public INDI::Focuser
{
    protected:
    private:
        ISwitch FocusResetS[1];
        ISwitchVectorProperty FocusResetSP;
        ISwitch MotorDirS[2];
        ISwitchVectorProperty MotorDirSP;
        ISwitch FocusParkingS[2];
        ISwitchVectorProperty FocusParkingSP;
		INumber FocusBacklashN[1];
		INumberVectorProperty FocusBacklashNP;
		INumber MotorSpeedN[1];
		INumberVectorProperty MotorSpeedNP;
    public:
        IndiAMHFocuser();
        virtual ~IndiAMHFocuser();

        const char *getDefaultName();

        virtual bool Connect();
        virtual bool Disconnect();
        virtual bool initProperties();
        virtual bool updateProperties();
        virtual void ISGetProperties (const char *dev);

        virtual bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
        virtual bool ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);
        virtual bool saveConfigItems(FILE *fp);

		virtual IPState MoveFocuser(FocusDirection dir, int duration);
		virtual IPState MoveAbsFocuser(int ticks);
		virtual IPState MoveRelFocuser(FocusDirection dir, int ticks);
		virtual int StepperMotor(int steps, FocusDirection dir);
		virtual bool AbortFocuser();

		Adafruit_MotorHAT hat;
		Adafruit_StepperMotor myStepper = hat.getStepper(1);

		FocusDirection dir;
};

#endif
