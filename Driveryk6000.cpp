
#include"DriverSpace.h"
#include<iostream>
#include<yk\yk6000.h>

using namespace DriverSpace;
using namespace std;


//constructor...
Driveryk6000::Driveryk6000():
m_cardID(-1)
{

}

//functional funcs...
int Driveryk6000::init()
{
	if (m_cardID<0)m_cardID = yk6000_Open();
	if (m_cardID > 0) 
	{
		yk6000_Set_Pulse_Mode(m_cardID, X_AXIS, 1, 0, 0);
		yk6000_Set_Pulse_Mode(m_cardID, Y_AXIS, 1, 0, 1);
		yk6000_Set_Pulse_Mode(m_cardID, Z_AXIS, 1, 0, 0);
	}
	
	return m_cardID;
}

void Driveryk6000::moveTo(int Axis1, int xTarget, int Axis2, int yTarget, int Axis3, int zTarget, int MoveSpeed)			// 3轴联动 单位step
{
	if (m_cardID < 0)return;
	yk6000_Set_L_Profile(m_cardID, Axis1, 100, MoveSpeed, 100, 100);
	yk6000_Set_L_Profile(m_cardID, Axis2, 100, MoveSpeed, 100, 100);
	yk6000_Set_L_Profile(m_cardID, Axis3, 100, MoveSpeed, 100, 100);
	int x_shift = xTarget - yk6000_Get_Command_Pos(m_cardID, Axis1);
	int y_shift = yTarget - yk6000_Get_Command_Pos(m_cardID, Axis2);
	int z_shift = zTarget - yk6000_Get_Command_Pos(m_cardID, Axis3);

	yk6000_Inp_Line3(m_cardID, Axis1, Axis2, Axis3, x_shift, y_shift, z_shift, 100, MoveSpeed, 100, 100, 0, 0, 1, false);
}


void Driveryk6000::axisMoveAbsolute(int axis, int pos, int speed)															//单轴绝对运动,原来的函数名 axisMoveTo
{
	if (m_cardID <= 0) return;
	int CurCommandPos = yk6000_Get_Command_Pos(m_cardID, axis);
	int LengthFromCur = pos - CurCommandPos;
	axisMoveRelative(axis, LengthFromCur,speed);
}

void Driveryk6000::axisMoveRelative(int axis, int steps, int speed)															//单轴相对运动 x y z a b c,原来的函数名axisMove
{
	if (m_cardID <= 0) return;
	cout << "steps :" << steps << endl;
	yk6000_Set_L_Profile(m_cardID, axis, 10, speed, 200, 200);
	yk6000_DMC_HS_PMove(m_cardID, axis, steps, 0);
}

void Driveryk6000::stop()
{

	if (m_cardID <= 0)return;
	// 停止所有轴
	yk6000_Dec_Stop(m_cardID, X_AXIS);
	yk6000_Dec_Stop(m_cardID, Y_AXIS);
	yk6000_Dec_Stop(m_cardID, Z_AXIS);

}

void Driveryk6000::hold()
{
	stop();
}

void Driveryk6000::close()
{
	if (m_cardID > 0)yk6000_Close();
}

void Driveryk6000::jogStart(int axis, int dir,int jogspeed)
{
	yk6000_Set_L_Profile(m_cardID, axis, 100, jogspeed, 100, 100);
	yk6000_DMC_LS_VMove(m_cardID, axis, axis, jogspeed);
}

void Driveryk6000::jogStop(int axis)
{
	yk6000_Dec_Stop(m_cardID, axis);												//指定卡和轴减速停止
}

void Driveryk6000::axisMoveVel(int axis, int dir, int speed)
{
	if (m_cardID < 0)return;
	yk6000_Set_L_Profile(m_cardID, axis, 100, speed, 100, 100);
	yk6000_DMC_LS_VMove(m_cardID, axis, dir, speed);
}


//getters...


int Driveryk6000::getCurPos(int axis)
{
	if (m_cardID < 0)return 0;
	return yk6000_Get_Command_Pos(m_cardID, axis);
}


int Driveryk6000::getAxisLimitStatus(int axis)
{
	if (m_cardID < 0)return -1;
	return yk6000_Get_EL_Status(m_cardID,axis);
}


int Driveryk6000::getAxisORGstatus(int axis)
{
	if (m_cardID < 0)return -1;
	return yk6000_Get_ORG_Status(m_cardID,axis);
}


//io...
int Driveryk6000::writeBit(int bit, int value)
{
	if (m_cardID > 0)
	{
		yk6000_WriteBit(m_cardID, bit, value);
		return 0;
	}
	else
		return -1;
}

int Driveryk6000::readBit(int bit)
{
	int port_value = -1;
	if (m_cardID > 0)
		port_value = yk6000_ReadBit(m_cardID, bit);
	return port_value;
}