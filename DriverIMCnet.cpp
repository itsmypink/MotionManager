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
		
		// 清除各轴的位置值及状态，配置clear参数必须放在第一
		if (IMC_SetParam16(m_imcHandle, clearLoc, -1, axis, SEL_IFIFO) != IMC_OK)break;

		// 最大加速度限制，根据需求设置
		if (IMC_SetParam32(m_imcHandle, accellimLoc, json_Obj.value("ACCELIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 最大速度限制，根据需求设置
		if (IMC_SetParam32(m_imcHandle, vellimLoc, json_Obj.value("VELLIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 点到点运动的规划速度
		if (IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, json_Obj.value("MCSMAXVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 主坐标系加速度
		if (IMC_SetParam32(m_imcHandle, mcsaccelLoc, json_Obj.value("MCSACCEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 主坐标系减速度
		if (IMC_SetParam32(m_imcHandle, mcsdecelLoc, json_Obj.value("MCSDECEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 点到点运动平滑因子
		if (IMC_SetParam16(m_imcHandle, smoothLoc, json_Obj.value("SMOOTH").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 发生错误的时候，该轴不退出运行
		if (IMC_SetParam16(m_imcHandle, exitfiltLoc, json_Obj.value("EXITFILT").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 发生任何错误的时候，该轴停止运行
		if (IMC_SetParam16(m_imcHandle, stopfiltLoc, json_Obj.value("STOPFILT").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 设置脉冲发生模式 脉冲+方向 脉冲和方向信号的极性为高电平有效
		if (IMC_SetParam16(m_imcHandle, stepmodLoc, json_Obj.value("STEPMOD").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 根据驱动器的脉冲宽度指标来设，一般伺服为20以上，步进为100以上
		if (IMC_SetParam16(m_imcHandle, steptimeLoc, json_Obj.value("STEPTIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 轴IO设置，使能正负硬限位IO，使能伺服到位和伺服报警IO，禁止软限位；伺服报警高电平有效
		if (IMC_SetParam16(m_imcHandle, aioctrLoc, json_Obj.value("AIOCTRL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 静止窗口，若误差大于此值，iMC将补偿静止误差；若为伺服驱动器，一般应大于0
		if (IMC_SetParam16(m_imcHandle, settlewinLoc, json_Obj.value("SETTLEW").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 误差补偿速度，为0禁止补偿，取值范围0~65535；
		// 由于伺服机构可能出现运动滞后，因此补偿速度过大可能会导致机械振动
		if (IMC_SetParam16(m_imcHandle, fixvelLoc, json_Obj.value("FIXVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 位置误差限制值 超出该值，错误寄存器中对应的位域置1
		if (IMC_SetParam16(m_imcHandle, poserrlimLoc, json_Obj.value("POSERRLIM").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 主编码器设置寄存器，bit15=0为使用外部反馈部件提供反馈信号，具体参考控制卡说明书
		if (IMC_SetParam16(m_imcHandle, encpctrLoc, json_Obj.value("ENCPCTRL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 高速搜寻原点的速度
		if (IMC_SetParam32(m_imcHandle, highvelLoc, json_Obj.value("HIGHVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 低速搜寻原点的速度
		if (IMC_SetParam32(m_imcHandle, lowvelLoc, json_Obj.value("LOWVEL").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam32(m_imcHandle, homeposLoc, json_Obj.value("HOMEPOS").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		// 使能该轴，无论是否接驱动器使能，ena都必须写入非零值，否则不输出脉冲
		if (IMC_SetParam16(m_imcHandle, enaLoc, json_Obj.value("ENA").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;
		// 运行该轴；只有运行该轴才能进行运动规划；若该轴因错误退出运行，run清零，该轴处于停止运行状态
		if (IMC_SetParam16(m_imcHandle, runLoc, json_Obj.value("RUN").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam16(m_imcHandle, pathabsLoc, json_Obj.value("PATHABS").toString().toInt(), axis, SEL_IFIFO) != IMC_OK)break;

		if (IMC_SetParam16(m_imcHandle, json_Obj.value("SEGMAP").toString().toInt(), axis, 0, SEL_IFIFO) != IMC_OK);

		// 插补空间1 路径加速度
		if (IMC_SetParam32(m_imcHandle, pathacc1Loc, 100000, 0, SEL_IFIFO) != IMC_OK);
		// 插补空间1 进给倍率1:1
		if (IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO) != IMC_OK);
		// 启用插补运动空间1
		if (IMC_SetParam16(m_imcHandle, startpath1Loc, -1, 0, SEL_IFIFO) != IMC_OK);
		// 清空PFIFO1所有指令
		if (IMC_SetParam16(m_imcHandle, clrPFIFO1Loc, -1, 0, SEL_IFIFO) != IMC_OK);
		// 设置段的运行速度
		if (IMC_SetParam32(m_imcHandle, segtgvel1Loc, 5000 / 1000.0 * 65536, 0, SEL_IFIFO) != IMC_OK);
		// 设置段末的速度
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
	IMC_SetParam32(m_imcHandle, pathacc1Loc, 300000, 0, SEL_IFIFO); // 加减速设置
	IMC_SetParam32(m_imcHandle, feedrate1Loc, 65536, 0, SEL_IFIFO);
	IMC_SetParam16(m_imcHandle, segmap_x1Loc, Axis1, 0, SEL_IFIFO);	//映射X轴
	IMC_SetParam16(m_imcHandle, segmap_y1Loc, Axis2, 0, SEL_IFIFO);	//映射Y轴
	IMC_SetParam16(m_imcHandle, segmap_z1Loc, Axis3, 0, SEL_IFIFO);
	IMC_SetParam32(m_imcHandle, segtgvel1Loc, MoveSpeed / 1000.0 * 65536, 0, SEL_IFIFO);        //设置段的运行速度
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
	IMC_SetParam32(m_imcHandle, segtgvel1Loc, MoveSpeed / 1000.0 * 65536, 0, SEL_IFIFO);        //设置段的运行速度
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
	int vel = speed / 1000.0 * 65536; // 转为pulse/ms
	IMC_SetParam32(m_imcHandle, mcsmaxvelLoc, vel, axis, SEL_IFIFO);
	IMC_MoveAbsolute(m_imcHandle, pos, axis, SEL_IFIFO);
}


void DriverIMCnet::axisMoveRelative(int axis, int steps, int speed)
{
	if (m_imcHandle == NULL)return;
	int vel = speed / 1000.0 * 65536; // 转为pulse/ms
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
	IMC_SetParam16(m_imcHandle, startpath1Loc, 0, 0, SEL_IFIFO); // 强制停止插补运动
}

void DriverIMCnet::hold()
{
	IMC_SetParam32(m_imcHandle, feedrate1Loc, 0, 0, SEL_IFIFO); // 暂停插补空间1
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
	//返回值：-1出错，0，无限位，1正向限位，2负向限位，3正负限位
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
		IMC_SetParamBit(m_imcHandle, gout1Loc, bit - 1, value, X_AXIS, SEL_IFIFO);				//这个IO是否与轴相关？包括readBit函数
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



