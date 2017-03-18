#include"DriverSpace.h"
using namespace DriverSpace;


DriverIMCnet::DriverIMCnet()
{
	m_imcHandle = NULL;

}



int	 DriverIMCnet::init()
{

	int ret = -1;
	NIC_INFO info;
	int num = 0;

	do {
		// ��������
		if (IMC_FindNetCard(&info, &num) != IMC_OK)
			break;
		// �򿪿��ƿ�
		if (IMC_Open(&m_imcHandle, 0, 0) != IMC_OK)
			break;
		// clearimcLoc
		if (IMC_SetParam16(m_imcHandle, clearimcLoc, -1, 0, SEL_IFIFO) != IMC_OK)
			break;
		for (int axis = 0; axis < 6; axis++) {
			// ��������λ��ֵ��״̬������clear����������ڵ�һ
			if (IMC_SetParam16(m_imcHandle, clearLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;

			// �����ٶ����ƣ�������������
			if (IMC_SetParam32(m_imcHandle, accellimLoc, 20000000, axis, SEL_IFIFO) != IMC_OK)break;
			// ����ٶ����ƣ�������������
			if (IMC_SetParam32(m_imcHandle, vellimLoc, 50000000, axis, SEL_IFIFO) != IMC_OK)break;

			// �㵽���˶��Ĺ滮�ٶ�
			if (IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, 200000000, axis, SEL_IFIFO) != IMC_OK)break;
			// ������ϵ���ٶ�
			if (IMC_SetParam32(m_imcHandle, mcsaccelLoc, 100000, axis, SEL_IFIFO) != IMC_OK)break;
			// ������ϵ���ٶ�
			if (IMC_SetParam32(m_imcHandle, mcsdecelLoc, 100000, axis, SEL_IFIFO) != IMC_OK)break;

			// �㵽���˶�ƽ������
			if (IMC_SetParam16(m_imcHandle, smoothLoc, 16, axis, SEL_IFIFO) != IMC_OK)break;

			// ���������ʱ�򣬸��᲻�˳�����
			if (IMC_SetParam16(m_imcHandle, exitfiltLoc, 0, axis, SEL_IFIFO) != IMC_OK)break;
			// �����κδ����ʱ�򣬸���ֹͣ����
			if (IMC_SetParam16(m_imcHandle, stopfiltLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;

			// �������巢��ģʽ ����+���� ����ͷ����źŵļ���Ϊ�ߵ�ƽ��Ч
			if (IMC_SetParam16(m_imcHandle, stepmodLoc, 0x0006, axis, SEL_IFIFO) != IMC_OK)break;
			// ������������������ָ�����裬һ���ŷ�Ϊ20���ϣ�����Ϊ100����
			if (IMC_SetParam16(m_imcHandle, steptimeLoc, 50, axis, SEL_IFIFO) != IMC_OK)break;

			// ��IO���ã�ʹ������Ӳ��λIO��ʹ���ŷ���λ���ŷ�����IO����ֹ����λ���ŷ������ߵ�ƽ��Ч
			if (IMC_SetParam16(m_imcHandle, aioctrLoc, 0x058A, axis, SEL_IFIFO) != IMC_OK)break;

			// ��ֹ���ڣ��������ڴ�ֵ��iMC��������ֹ����Ϊ�ŷ���������һ��Ӧ����0
			if (IMC_SetParam16(m_imcHandle, settlewinLoc, 1, axis, SEL_IFIFO) != IMC_OK)break;

			// �����ٶȣ�Ϊ0��ֹ������ȡֵ��Χ0~65535��
			// �����ŷ��������ܳ����˶��ͺ���˲����ٶȹ�����ܻᵼ�»�е��
			if (IMC_SetParam16(m_imcHandle, fixvelLoc, 0, axis, SEL_IFIFO) != IMC_OK)break;
			// λ���������ֵ ������ֵ������Ĵ����ж�Ӧ��λ����1
			if (IMC_SetParam16(m_imcHandle, poserrlimLoc, 5000, axis, SEL_IFIFO) != IMC_OK)break;

			// �����������üĴ�����bit15=0Ϊʹ���ⲿ���������ṩ�����źţ�����ο����ƿ�˵����
			if (IMC_SetParam16(m_imcHandle, encpctrLoc, 0x000E, axis, SEL_IFIFO) != IMC_OK)break;

			// ������Ѱԭ����ٶ�
			if (IMC_SetParam32(m_imcHandle, highvelLoc, 800000, axis, SEL_IFIFO) != IMC_OK)break;
			// ������Ѱԭ����ٶ�
			if (IMC_SetParam32(m_imcHandle, lowvelLoc, 100000, axis, SEL_IFIFO) != IMC_OK)break;

			if (IMC_SetParam32(m_imcHandle, homeposLoc, 0, axis, SEL_IFIFO) != IMC_OK)break;

			// ʹ�ܸ��ᣬ�����Ƿ��������ʹ�ܣ�ena������д�����ֵ�������������
			if (IMC_SetParam16(m_imcHandle, enaLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;
			// ���и��᣻ֻ�����и�����ܽ����˶��滮��������������˳����У�run���㣬���ᴦ��ֹͣ����״̬
			if (IMC_SetParam16(m_imcHandle, runLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;

			if (IMC_SetParam16(m_imcHandle, pathabsLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;
		}

		// A��Ϊ������� �޷��� ���ŷ���λ���ŷ������ź� ��㼰��λ�źŸߵ�ƽ��Ч
		if (IMC_SetParam16(m_imcHandle, aioctrLoc, 0x0010, A_AXIS, SEL_IFIFO) != IMC_OK)break;

		// A������ڲ����ⷴ��
		if (IMC_SetParam16(m_imcHandle, encpctrLoc, 0x800E, A_AXIS, SEL_IFIFO) != IMC_OK)break;

		// �岹�ռ�1 ·�����ٶ�
		if (IMC_SetParam32(m_imcHandle, pathacc1Loc, 100000, 0, SEL_IFIFO) != IMC_OK)break;
		// �岹�ռ�1 ��������1:1
		if (IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO) != IMC_OK)break;
		// ���ò岹�˶��ռ�1
		if (IMC_SetParam16(m_imcHandle, startpath1Loc, -1, 0, SEL_IFIFO) != IMC_OK)break;

		// ���PFIFO1����ָ��
		if (IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO) != IMC_OK)break;
		// ӳ��X��
		if (IMC_SetParam16(m_imcHandle, segmap_x1Loc, X_AXIS, 0, SEL_IFIFO) != IMC_OK)break;
		// ӳ��Y��
		if (IMC_SetParam16(m_imcHandle, segmap_y1Loc, Y_AXIS, 0, SEL_IFIFO) != IMC_OK)break;
		// ӳ��Z��
		if (IMC_SetParam16(m_imcHandle, segmap_z1Loc, Z_AXIS, 0, SEL_IFIFO) != IMC_OK)break;
		// ���öε������ٶ�
		if (IMC_SetParam32(m_imcHandle, segtgvel1Loc, 5000 / 1000.0 * 65536, 0, SEL_IFIFO) != IMC_OK)break;
		// ���ö�ĩ���ٶ�
		if (IMC_SetParam32(m_imcHandle, segendvel1Loc, 0, 0, SEL_IFIFO) != IMC_OK)break;

		ret = 1;
		break;
		// ���������Ĳ���
	} while (false);

	return ret;
}

void DriverIMCnet::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed)
{
	IMC_SetParam16(m_imcHandle, startpath1Loc, 0, 0, SEL_IFIFO);
	PFIFOSegData segdata;
	IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, pathacc1Loc, 300000, 0, SEL_IFIFO); // �Ӽ�������
	IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_x1Loc, X_AXIS, 0, SEL_IFIFO);	//ӳ��X��
	IMC_SetParam16(m_imcHandle, segmap_y1Loc, Y_AXIS, 0, SEL_IFIFO);	//ӳ��Y��
	IMC_SetParam16(m_imcHandle, segmap_z1Loc, Z_AXIS, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, segtgvel1Loc, MoveSpeed / 1000.0 * 65536, 0, SEL_IFIFO);        //���öε������ٶ�
	IMC_SetParam32(m_imcHandle, segendvel1Loc, 0, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, startpath1Loc, -1, 0, SEL_IFIFO);
	segdata.datanum = 3;
	segdata.SegEndData[0] = _1Target;
	segdata.SegEndData[1] = _2Target;
	segdata.SegEndData[2] = _3Target;
	IMC_AddLineN(m_imcHandle, &segdata, SEL_PFIFO1);
}

void DriverIMCnet::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed)
{
	IMC_SetParam16(m_imcHandle, startpath1Loc, 0, 0, SEL_IFIFO);
	PFIFOSegData segdata;
	IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, pathacc1Loc, 300000, 0, SEL_IFIFO);

	IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_x1Loc, X_AXIS, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_y1Loc, Y_AXIS, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_z1Loc, Z_AXIS, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_a1Loc, A_AXIS, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_b1Loc, B_AXIS, 0, SEL_IFIFO); 
	IMC_SetParam32(m_imcHandle, segtgvel1Loc, MoveSpeed / 1000.0 * 65536, 0, SEL_IFIFO);        //���öε������ٶ�
	IMC_SetParam32(m_imcHandle, segendvel1Loc, 0, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, startpath1Loc, -1, 0, SEL_IFIFO);

	segdata.datanum = 5;
	segdata.SegEndData[0] = _1Target;
	segdata.SegEndData[1] = _2Target;
	segdata.SegEndData[2] = _3Target;
	segdata.SegEndData[3] = _4Target;
	segdata.SegEndData[4] = _5Target;
	IMC_AddLineN(m_imcHandle, &segdata, SEL_PFIFO1);
}


void DriverIMCnet::axisMoveAbsolute(int axis, int pos, int speed)
{
	if (m_imcHandle == NULL)return;
	int vel = speed / 1000.0 * 65536; // תΪpulse/ms
	IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, vel, axis, SEL_IFIFO);
	IMC_MoveAbsolute(m_imcHandle, pos, axis, SEL_IFIFO);
}


void DriverIMCnet::axisMoveRelative(int axis, int steps, int speed)
{
	if (m_imcHandle == NULL)return;
	int vel = speed / 1000.0 * 65536; // תΪpulse/ms
	IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, vel, axis, SEL_IFIFO);
	IMC_MoveRelative(m_imcHandle, steps, axis, SEL_IFIFO);
}


void DriverIMCnet::axisMoveVel(int axis, int dir, int speed)
{
	double vel = speed / 1000.0 * 65536;
	if (dir == 0) {
		vel = -vel;
	}
	IMC_MoveVelocity(m_imcHandle, vel, axis, SEL_IFIFO);
}


void DriverIMCnet::stop()
{
	if (m_imcHandle == NULL)return;
	IMC_SetParam32(m_imcHandle, hpauseLoc, -1, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, hpauseLoc, 0, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, startpath1Loc, 0, 0, SEL_IFIFO); // ǿ��ֹͣ�岹�˶�
}

void DriverIMCnet::hold()
{
	IMC_SetParam32(m_imcHandle, feedrate1Loc, 0, 0, SEL_IFIFO); // ��ͣ�岹�ռ�1
}


void DriverIMCnet::close()
{
	if (m_imcHandle != NULL) 
	{
		IMC_Close(m_imcHandle);
		m_imcHandle = NULL;
	}
}


void DriverIMCnet::jogStart(int axis, int dir,int jogspeed)
{
	axisMoveVel(axis, dir, jogspeed);
}


void DriverIMCnet::jogStop(int axis)
{
	axisMoveVel(axis, 0, 0);
}





//getters....
int DriverIMCnet::getCurPos(int axis)
{
	if (!m_imcHandle)return 0;
	int curStep = 0;
	if (IMC_GetParam32(m_imcHandle, curposLoc, &curStep, axis) == IMC_OK) 
		return curStep;
	else
		return 0;
}


int DriverIMCnet::getAxisLimitStatus(int axis)
{
	WR_MUL_DES m_limit;
	m_limit.addr = errorLoc;
	m_limit.axis = axis;
	m_limit.len = 1;

	//����ֵ��-1����0������λ��1������λ��2������λ��3������λ
	if (IMC_GetMulParam(m_imcHandle, &m_limit, 1) == IMC_OK)
	{
		if (m_limit.data[0] & 0x0003 == 0x0003)return 3;
		else
		{
			if (m_limit.data[0] & 0x0001)return 1;
			else if (m_limit.data[0] & 0x0002) return 2;
			else return 0;
		}
	}
	return -1;
}


int DriverIMCnet::getAxisORGstatus(int axis)
{
	WR_MUL_DES m_aio;
	m_aio.addr = aioLoc;
	m_aio.axis = axis;
	m_aio.len = 1;
	if (IMC_GetMulParam(m_imcHandle, &m_aio, 1) == IMC_OK)
	{
		if ((m_aio.data[0] & 0x4) != 0)return 1;
		else return 0;
	}
	else
		return -1;
}


//io...
int DriverIMCnet::writeBit(int bit, int value)
{
	if (bit < 1 || bit > 16) return -1;
	if (m_imcHandle != NULL)
	{
		IMC_SetParamBit(m_imcHandle, gout1Loc, bit - 1, value, X_AXIS, SEL_IFIFO);				//���IO�Ƿ�������أ�����readBit����
		return 0;
	}
	return -1;
}


int DriverIMCnet::readBit(int port_bit)
{
	if (port_bit < 1 || port_bit > 16) return -1;
	IMC16 port_value = -1;
	if (m_imcHandle != NULL)IMC_GetParamBit(m_imcHandle, gin1Loc, &port_value, port_bit - 1, X_AXIS);
	return port_value;
}



