#ifndef DRIVERS_H
#define DRIVERS_H

#include<qobject.h>
#include<qmap.h>
#include<qtimer.h>
#include<qjsonobject.h>
#include<qjsondocument.h>

#include<iostream>

using namespace std;


#include"DriverSpace.h"
using namespace DriverSpace;

template<class T>
class DRIVERS:public QObject
{
	Q_OBJECT

public:

	DRIVERS<T>();


/*******************************************************************
	
Axis functional funcs...
	
********************************************************************/


	/*
	<控制卡初始化函数>
	参  数：无
	返回值：	初始化不成功则返回-1
			yk6000，成功则返回卡号
			IMCnet，成功则返回1
	*/
	int	 init();


	/*
	<三轴联动>
	参	数:Axis1,Axis2,Axis3表示轴号
		   _1Target~_3Target表示三个轴的逻辑位置，并不是执行机构实际执行距离
		   MoveSpeed运行速度
	返回值：void
	备	注：重载两个版本，一个自定义速度，一个采用类内变量i_moveSpeed
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed);								// 3轴联动 单位step
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target);

	/*
	<五轴联动>
	参	数：Axis1~Axis5表示轴号
			1Target~_5Target表示轴的逻辑位置，并不是执行机构的实际距离
			MoveSpeed运行速度
	返回值：void
	备	注：重载两个版本，一个自定义速度，一个采用类内变量i_moveSpeed
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed);
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target);

	/*
	<单轴绝对运动>
	参	数：	axis:轴号
			pos:绝对位置点，以逻辑位置单位
			speed:运行速度
	返回值：void
	*/
	void axisMoveAbsolute(int axis, int pos, int speed);


	/*
	<单轴相对运动>
	参	数：axis:轴号
			steps:相对位移长度
			speed:运行速度
	返回值：void
	*/
	void axisMoveRelative(int axis, int steps, int speed);


	/*
	<单轴持续运动>
	参	数：axis:轴号
			dir:方向
			speed:运行速度
	返回值：void
	*/
	void axisMoveVel(int axis, int dir, int speed);


	/*
	<停止>
	参	数：无
	返回值：void
	*/
	void stop();


	/*
	<暂停>
	参	数：无
	返回值：void
	备	注：其实调用的是stop()函数
	*/
	void hold();

	/*
	<关闭控制卡>
	参	数：无
	返回值：void
	*/
	void close();

	/*
	<点动开始>
	参	数：axis轴号
			dir方向
	返回值：void
	*/
	void jogStart(int axis, int dir,int jogspeed);

	/*
	<点动结束>
	参	数：axis轴号
	返回值：void
	*/
	void jogStop(int axis);



	/*
	<开始更新轴位置信息>
	参	数：msec计时器时间，单位毫秒
	返回值：void
	备	注：开始timerAxisPos计时器
	*/
	void startAxisPosUpdate(int msec=50);

	/*
	<停止更新轴位置信息>
	参	数：无
	返回值：void
	备	注：停止timerAxisPos计时器
	*/
	void stopAxisPosUpdate();



	/*
	<开始更新轴限位信息>
	参	数：msec计时器时间，单位毫秒
	返回值：void
	备	注：开始timerAxisLim计时器
	*/
	void startAxisLimUpdate(int msec = 50);
	
	/*
	<停止更新轴限位信息>
	参	数：无
	返回值：void
	备	注：停止timerAxisLim计时器
	*/
	void stopAxisLimUpdate();

/*******************************************************************

AxisInfoMap operations...

int	   Axis = -1;
double m_screwPitchX;		// 丝杆导程
double m_xPPR;				// 每转脉冲数
double m_xPPM;				// 每mm脉冲数
double m_xMPP;				// 每个脉冲多少mm

********************************************************************/

	/*
	<添加轴>
	参	数：AxisName轴名称，字符串格式
			Axis轴号
			m_screwPitchX轴丝杆导程
			m_xPPR轴每转脉冲数
	返回值：void
	*/
	void AxisInfoInsertItem(QString AxisName,int axis,double m_screwPitchX, double m_xPPR);


	/*
	<删除某个轴信息>
	参	数：AxisName轴名称，字符串格式
	返回值：返回删除的item数，通常为1或0
	*/
	int AxisInfoDeleteItem(QString AxisName);


	/*
	<清空轴信息>
	参	数：无
	返回值：void
	*/
	void AxisInfoClear();
	


/*******************************************************************

setters...

jogspeed	点动速度
i_moveSpeed 运行速度
i_zeroSpeed 回零速度

********************************************************************/
	


	/*
	<设置点动速度>
	参	数：点动速度，驱动器逻辑速度
	返回值：void
	*/
	void setJogSpeed(int jogspeed);

	/*
	<设置运行速度>
	参	数：运行速度值
	返回值：void
	*/
	void setMoveSpeed(int movespeed);

	/*
	<设置回零速度>
	参	数：回零速度值
	返回值：void
	*/
	void setZeroSpeed(int zerospeed);



/*******************************************************************

getters...

jogspeed 点动速度
int		i_moveSpeed;
int		i_zeroSpeed;

********************************************************************/

	/*
	<获取点动速度>
	参	数：无
	返回值：i_jogspeed的值,const int &类型
	*/
	const int & getJogSpeed() const;

	/*
	<获取运行速度>
	参	数：无
	返回值：返回i_moveSpeed的值，const int &类型
	*/
	const int & getMoveSpeed() const;

	/*
	<获取回零速度>
	参	数：无
	返回值：i_zeroSpeed的值，const int &类型
	*/
	const int & getZeroSpeed() const;



	/*
	<获取当前位置>
	参	数：轴号或轴名称
	返回值：当前逻辑位置值
	备	注：重载2个版本，参数位轴号或轴名称
	*/
	int		getCurPos(int axis);
	int		getCurPos(QString axisName);


	/*
	<获取当前位置>
	参	数：轴号或轴名称
	返回值：当前执行机构实际位置值
	备	注：重载2个版本，参数为轴号或轴名称
	*/
	double  getCurPosmm(int axis);
	double  getCurPosmm(QString axisName);



	/*
	<获取轴限位信息>
	参	数：axisName轴名称 或 axis轴号
	返回值：-1获取出错,0无限位，1正向限位，2负向限位，3正负向限位
	备	注：两个重载函数，参数为 axisName轴名称 或 axis轴编号
	*/
	int getAxisLimitStatus(QString axisName);
	int getAxisLimitStatus(int axis);
/*******************************************************************

io operation...

********************************************************************/


	/*
	<io注册>
	参	数：devName定义端口名称
			devPort端口号
	返回值：成功则返回0，否则返回-1
	*/
	int registerIoDev(QString devName, int devPort);


	/*
	<写端口>
	参	数：port_bit端口号或devName端口名称
			value值
	返	回：成功则0，不成功则-1
	备	注：两个重载版本，参数为 devName字符串 或 一个port_bit整型
	*/
	int portWrite(QString devName, int value);
	int portWrite(int port_bit, int value);


	/*
	<读端口>
	参	数：port_bit
	返回值：端口值
	备	注：两个重载版本，参数为 devName字符串 或 一个port_bit整型
	*/
	int portRead(int port_bit);
	int portRead(QString devName);

	/*
	<置反端口>
	参	数：devName端口名称或port_bit端口号
	返回值：成功则0，不成功则-1；
	备	注：两个重载版本，参数为 devName端口名称 或 port_bit端口号
	*/
	int ioDevTogg(QString devName);
	int ioDevTogg(int  port_bit);


	/*
	<清空注册IO>
	参	数：无
	返回值：void
	*/
	void ClearIoDev();

	/*
	<剔除某IO>
	参	数：io名称
	返回值：void
	*/
	void DeleteIoDev(QString devName);

private:
	T device;

	QMap<QString, MotionInfo> AxisInfoMap;
	int		i_jogspeed;
	int		i_moveSpeed;
	int		i_zeroSpeed;

	QMap<QString, int>		IOInfoMap;

	QTimer	timerAxisPos;
	QTimer	timerAxisLim;

signals:

	/*发送轴的位置信息*/
	void sigAxisPosUpdate(QByteArray);
	
	/*发送轴的限位信息*/
	void sigAxisLimUpdate(QByteArray);


private slots:


	/*
	<更新轴的位置信息>
	参	数：无
	返回值：void
	备注：更新各个轴的位置信息，通过sigAxisPosUpdate信号发送
	*/
	void onAxisPosUpdate();

	/*
	<更新轴的限位信息>
	参	数：无
	返回值：void
	备注：更新各个轴的限位信息，通过sigAxisLimUpdate信号发送
	*/
	void onAxisLimUpdate();


public slots:

};

#endif



template<class T>
DRIVERS<T>::DRIVERS<T>():
i_jogspeed(0),
i_moveSpeed(0),
i_zeroSpeed(0)
{


	connect(&timerAxisPos, SIGNAL(timerout()), this, SLOT(onAxisPosUpdate()));
	connect(&timerAxisLim, SIGNAL(timerout()), this, SLOT(onAxisLimUpdate()));
}


/*******************************************************************

Motion functional funcs

********************************************************************/
template<class T>
int	 DRIVERS<T>::init()
{
	return device.init();
}


template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed)
{
	device.moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, MoveSpeed);
}


template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target)
{
	device..moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, i_moveSpeed);
}


template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed)
{
	device.moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, Axis4, _4Target, Axis5, _5Target, MoveSpeed);
}

template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target)
{
	device.moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, Axis4, _4Target, Axis5, _5Target, i_moveSpeed);
}


template<class T>
void DRIVERS<T>::axisMoveAbsolute(int axis, int pos, int speed)
{
	device.axisMoveAbsolute(axis, pos, speed);
}

template<class T>
void axisMoveRelative(int axis, int steps, int speed)
{
	device.axisMoveRelative(axis, steps, speed);
}

template<class T>
void DRIVERS<T>::axisMoveVel(int axis, int dir, int speed)
{
	device.axisMoveVel(axis, dir, speed);
}


template<class T>
void DRIVERS<T>::stop()
{
	device.stop();
}

template<class T>
void DRIVERS<T>::hold()
{
	device.hold();
}


template<class T>
void DRIVERS<T>::close()
{
	device.close();
}

template<class T>
void DRIVERS<T>::jogStart(int axis, int dir)
{
	device.jogStart(axis, dir, i_jogspeed);
}


template<class T>
void DRIVERS<T>::jogStop(int axis, int dir)
{
	device.jogStop(axis, dir);
}

template<class T>
void DRIVERS<T>::startAxisPosUpdate(int msec)
{
	timerAxisPos.start(msec);
}

template<class T>
void DRIVERS<T>::stopAxisPosUpdate()
{
	timerAxisPos.stop();
}


template<class T>
void DRIVERS<T>::startAxisLimUpdate(int msec)
{
	timerAxisLim.start(msec);
}

template<class T>
void DRIVERS<T>::stopAxisLimUpdate()
{
	timerAxisLim.stop();
}

/*******************************************************************

AxisInfoMap operations

********************************************************************/

template<class T>
void DRIVERS<T>::AxisInfoInsertItem(QString AxisName,int axis,double m_screwPitchX, double m_xPPR)
{
	if (AxisName.isEmpty() || m_screwPitchX <= 0 || m_xPPR <= 0 || axis<0)return;
	double m_xPPM = m_xPPR / m_screwPitchX;
	double m_xMPP = m_screwPitchX / m_xPPR;		

	MotionInfo info;
	info.Axis = axis;
	info.m_screwPitchX = m_screwPitchX;
	info.m_xPPR = m_xPPR;
	info.m_xPPM = m_xppm;
	info.m_xMPP = m_xMPP;
	
	AxisInfoMap.insert(AxisName, info);
}

template<class T>
int DRIVERS<T>::AxisInfoDeleteItem(QString AxisName)
{
	return AxisInfoMap.remove(AxisName);
}

template<class T>
void DRIVERS<T>::AxisInfoClear()
{
	AxisInfoMap.clear();
}




/*******************************************************************

setters...

********************************************************************/

template<class T>
void DRIVERS<T>::setJogSpeed(int jogspeed)
{
	i_jogspeed = jogspeed;
}

template<class T>
void DRIVERS<T>::setMoveSpeed(int movespeed)
{
	i_moveSpeed = movespeed;
}

template<class T>
void DRIVERS<T>::setZeroSpeed(int zerospeed)
{
	setZeroSpeed = zerospeed;
}



/*******************************************************************

getters...

********************************************************************/
template<class T>
const int & DRIVERS<T>::getJogSpeed() const
{
	return i_jogspeed;
}

template<class T>
const int & DRIVERS<T>::getMoveSpeed() const
{
	return i_moveSpeed;
}


template<class T>
const int & DRIVERS<T>::getZeroSpeed() const
{
	return i_zeroSpeed;
}


template<class T>
int		DRIVERS<T>::getCurPos(int axis)
{
	return device.getCurPos(axis);
}

template<class T>
int		DRIVERS<T>::getCurPos(QString axisName)
{
	return device.getCurPos(AxisInfoMap.value(axisName).Axis);
}

template<class T>
double  DRIVERS<T>::getCurPosmm(int axis)
{
	double	mpp = 0;

	QMapIterator<QString, MotionInfo> it(AxisInfoMap);
	while (it.hasNext())
	{
		QMap<QString, MotionInfo>temp = it.next();
		if (temp.value().Axis == axis)
		{
			mpp = temp.value().m_xMPP;
			break;
		}
	}
	return device.getCurPos(axis)*mpp;
	
}

template<class T>
double  DRIVERS<T>::getCurPosmm(QString axisName)
{
	int		axis = AxisInfoMap.value(axisName).Axis;
	double	mpp = AxisInfoMap.value(axisName).m_xMPP;
	return device.getCurPos(axis)*mpp;
}


template<class T>
int DRIVERS<T>::getAxisLimitStatus(QString axisName)
{
	return device.getAxisLimitStatus(AxisInfoMap.value(axisName).Axis);
}

template<class T>
int DRIVERS<T>::getAxisLimitStatus(int axis)
{
	return device.getAxisLimitStatus(axis);
}



/*******************************************************************

io operations...

********************************************************************/

template<class T>
int DRIVERS<T>::registerIoDev(QString devName, int devPort)
{
	IOInfoMap.insert(devName, devPort);
}


template<class T>
int DRIVERS<T>::portWrite(QString devName, int value)
{
	if (IOInfoMap.keys().contains(devName))
	{
		return device.writeBit(IOInfoMap.value(devName),value);
	}
	return -1;
}

template<class T>
int DRIVERS<T>::portWrite(int port_bit, int value)
{
	return device.writeBit(port_bit,value);
}

template<class T>
int DRIVERS<T>::portRead(int port_bit)
{
	return device.readBit(port_bit);
}


template<class T>
int DRIVERS<T>::portRead(QString devName)
{
	if (IOInfoMap.keys().contains(devName))
	{
		return device.readBit(IOInfoMap.value(devName));
	}
	return -1;
}

template<class T>
int DRIVERS<T>::ioDevTogg(QString devName)
{
	int portValue = portRead(devName);
	if (portValue != -1)
	{
		return portWrite(devName, !portvalue);
	}
	else
		return -1;
}

template<class T>
int DRIVERS<T>::ioDevTogg(int  port_bit)
{
	int portValue = portRead(port_bit);
	if (portValue != -1)
	{
		return portWrite(port_bit, !portvalue);
	}
	else
		return -1;
}

template<class T>
void DRIVERS<T>::ClearIoDev()
{
	IOInfoMap.clear();
}


template<class T>
void DRIVERS<T>::DeleteIoDev(QString devName)
{
	IOInfoMap.remove(devName);
}



//private slots...

template<class T>
void DRIVERS<T>::onAxisPosUpdate()
{
	if (AxisInfoMap.isEmpty())return;
	
	QJsonObject obj_AxisPos;
	QMapIterator<QString, MotionInfo>it(AxisInfoMap);
	while (it.hasNext())
	{
		QMap < QString, MotionInfo>tmp = it.next();
		obj_AxisPos.insert(tmp.key(), getCurPosmm(tmp.key));
	}

	QJsonDocument doc_AxisPos;
	doc_AxisPos.setObject(obj_AxisPos);

	emit sigAxisPosUpdate(doc_AxisPos.toJson(QJsonDocument::Compact));
}


template<class T>
void DRIVERS<T>::onAxisLimUpdate()
{
	if (AxisInfoMap.isEmpty())return;

	QJsonObject obj_AxisLim;
	QMapIterator<QString, MotionInfo>it(AxisInfoMap);
	while (it.hasNext())
	{
		QMap < QString, MotionInfo>tmp = it.next();
		obj_AxisPos.insert(tmp.key(), getAxisLimitStatus(tmp.key()));
	}

	QJsonDocument doc_AxisLim;
	doc_AxisLim.setObject(obj_AxisLim);

	emit sigAxisLimUpdate(doc_AxisLim.toJson(QJsonDocument::Compact));
}