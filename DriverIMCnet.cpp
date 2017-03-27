#include"DriverSpace.h"
using namespace DriverSpace;


DriverIMCnet::DriverIMCnet():
num(0)
{
	m_imcHandle = NULL;

}



int	 DriverIMCnet::init(QList<QByteArray> paras)
{
	if (paras.isEmpty())return -2;

	NIC_INFO info;

	if (IMC_FindNetCard(&info, &num) != IMC_OK)return -1;
	if (IMC_Open(&m_imcHandle, 0, 0) != IMC_OK)return -1; 
	if (IMC_SetParam16(m_imcHandle, clearimcLoc, -1, 0, SEL_IFIFO) != IMC_OK)return -1;
	if (num <= 0 || !m_imcHandle)return -1;

	int ret = -2;
	
	QListIterator<QByteArray> it(paras);
	while (it.hasNext())
	{
		ret = -2;
		QJsonDocument json_Doc=QJsonDocument::fromJson(it.next());
		QJsonObject json_Obj = json_Doc.object();
		int axis = json_Obj.value("NUMB").toString().toInt();
		
		// ��������λ��ֵ��״̬������clear����������ڵ�һ
		if (IMC_SetParam16(m_imcHandle, clearLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;

		// �����ٶ����ƣ�������������
		if (IMC_SetParam32(m_imcHandle, accellimLoc, json_Obj.value("ACCELIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ����ٶ����ƣ�������������
		if (IMC_SetParam32(m_imcHandle, vellimLoc, json_Obj.value("VELLIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// �㵽���˶��Ĺ滮�ٶ�
		if (IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, json_Obj.value("MCSMAXVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ������ϵ���ٶ�
		if (IMC_SetParam32(m_imcHandle, mcsaccelLoc, json_Obj.value("MCSACCEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ������ϵ���ٶ�
		if (IMC_SetParam32(m_imcHandle, mcsdecelLoc, json_Obj.value("MCSDECEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// �㵽���˶�ƽ������
		if (IMC_SetParam16(m_imcHandle, smoothLoc, json_Obj.value("SMOOTH").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// ���������ʱ�򣬸��᲻�˳�����
		if (IMC_SetParam16(m_imcHandle, exitfiltLoc, json_Obj.value("EXITFILT").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// �����κδ����ʱ�򣬸���ֹͣ����
		if (IMC_SetParam16(m_imcHandle, stopfiltLoc, json_Obj.value("STOPFILT").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// �������巢��ģʽ ����+���� ����ͷ����źŵļ���Ϊ�ߵ�ƽ��Ч
		if (IMC_SetParam16(m_imcHandle, stepmodLoc, json_Obj.value("STEPMOD").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ������������������ָ�����裬һ���ŷ�Ϊ20���ϣ�����Ϊ100����
		if (IMC_SetParam16(m_imcHandle, steptimeLoc, json_Obj.value("STEPTIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// ��IO���ã�ʹ������Ӳ��λIO��ʹ���ŷ���λ���ŷ�����IO����ֹ����λ���ŷ������ߵ�ƽ��Ч
		if (IMC_SetParam16(m_imcHandle, aioctrLoc, json_Obj.value("AIOCTRL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// ��ֹ���ڣ��������ڴ�ֵ��iMC��������ֹ����Ϊ�ŷ���������һ��Ӧ����0
		if (IMC_SetParam16(m_imcHandle, settlewinLoc, json_Obj.value("SETTLEW").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// �����ٶȣ�Ϊ0��ֹ������ȡֵ��Χ0~65535��
		// �����ŷ��������ܳ����˶��ͺ���˲����ٶȹ�����ܻᵼ�»�е��
		if (IMC_SetParam16(m_imcHandle, fixvelLoc, json_Obj.value("FIXVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// λ���������ֵ ������ֵ������Ĵ����ж�Ӧ��λ����1
		if (IMC_SetParam16(m_imcHandle, poserrlimLoc, json_Obj.value("POSERRLIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// �����������üĴ�����bit15=0Ϊʹ���ⲿ���������ṩ�����źţ�����ο����ƿ�˵����
		if (IMC_SetParam16(m_imcHandle, encpctrLoc, json_Obj.value("ENCPCTRL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// ������Ѱԭ����ٶ�
		if (IMC_SetParam32(m_imcHandle, highvelLoc, json_Obj.value("HIGHVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ������Ѱԭ����ٶ�
		if (IMC_SetParam32(m_imcHandle, lowvelLoc, json_Obj.value("LOWVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam32(m_imcHandle, homeposLoc, json_Obj.value("HOMEPOS").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// ʹ�ܸ��ᣬ�����Ƿ��������ʹ�ܣ�ena������д�����ֵ�������������
		if (IMC_SetParam16(m_imcHandle, enaLoc, json_Obj.value("ENA").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// ���и��᣻ֻ�����и�����ܽ����˶��滮��������������˳����У�run���㣬���ᴦ��ֹͣ����״̬
		if (IMC_SetParam16(m_imcHandle, runLoc, json_Obj.value("RUN").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam16(m_imcHandle, pathabsLoc, json_Obj.value("PATHABS").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam16(m_imcHandle, json_Obj.value("SEGMAP").toString().toInt(), axis, 0, SEL_IFIFO) != IMC_OK);

		// �岹�ռ�1 ·�����ٶ�
		if (IMC_SetParam32(m_imcHandle, pathacc1Loc, 100000, 0, SEL_IFIFO) != IMC_OK);
		// �岹�ռ�1 ��������1:1
		if (IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO) != IMC_OK);
		// ���ò岹�˶��ռ�1
		if (IMC_SetParam16(m_imcHandle, startpath1Loc, -1, 0, SEL_IFIFO) != IMC_OK);
		// ���PFIFO1����ָ��
		if (IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO) != IMC_OK);
		// ���öε������ٶ�
		if (IMC_SetParam32(m_imcHandle, segtgvel1Loc, 5000 / 1000.0 * 65536, 0, SEL_IFIFO) != IMC_OK);
		// ���ö�ĩ���ٶ�
		if (IMC_SetParam32(m_imcHandle, segendvel1Loc, 0, 0, SEL_IFIFO) != IMC_OK);

		ret = 0;
	}
	
	return ret;
}

void DriverIMCnet::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed)
{
	IMC_SetParam16(m_imcHandle, startpath1Loc, 0, 0, SEL_IFIFO);
	PFIFOSegData segdata;
	IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, pathacc1Loc, 300000, 0, SEL_IFIFO); // �Ӽ�������
	IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_x1Loc, Axis1, 0, SEL_IFIFO);	//ӳ��X��
	IMC_SetParam16(m_imcHandle, segmap_y1Loc, Axis2, 0, SEL_IFIFO);	//ӳ��Y��
	IMC_SetParam16(m_imcHandle, segmap_z1Loc, Axis3, 0, SEL_IFIFO);
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
	IMC_SetParam16(m_imcHandle, segmap_x1Loc, Axis1, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_y1Loc, Axis2, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_z1Loc, Axis3, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_a1Loc, Axis4, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_b1Loc, Axis5, 0, SEL_IFIFO);
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
		if (m_limit.data[0] & 0x03 == 0x03)return 3;
		else
		{
			if (m_limit.data[0] & 0x01)return 1;
			else if (m_limit.data[0] & 0x02) return 2;
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



