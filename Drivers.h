#ifndef DRIVERS_H
#define DRIVERS_H

#include<qobject.h>
#include<qmap.h>
#include<qtimer.h>
#include<qjsonobject.h>
#include<qjsondocument.h>
#include<qdom.h>
#include<qfile.h>
#include<qbytearray.h>

#include<iostream>
#include<typeinfo>
using namespace std;

#include"DriverSpace.h"
using namespace DriverSpace;

template<class T>
class DRIVERS
{

public:

	DRIVERS<T>();

/*******************************************************************
	
Axis functional funcs...
	
********************************************************************/


	/*
	<控制卡初始化函数>
	参  数：无
	返回值：	0成功,-1控制卡初始化失败，-2配置文件不正确或打开失败
	*/
	int	 init();
	int  initFromYk6000XML();
	int  initFromIMCnetXML(QString path="./AxisConfig.xml");

	/*
	<从XML中获取IO配置>
	参	数：文件路径
	返回值：0成功，-1失败
	*/
	int  initIOFromXML(QString path="./IOConfig.xml");


	/*
	<三轴联动>
	参	数:Axis1,Axis2,Axis3表示轴号
		   _1Target~_3Target表示三个轴的 逻辑位置 或 执行机构实际执行距离
		   MoveSpeed运行速度
	返回值：void
	备	注：重载两个版本，一个目标位置值为逻辑位置，一个为执行机构实际位置
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed=i_moveSpeed);								// 3轴联动 单位step
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int MoveSpeed = i_moveSpeed);


	/*
	<五轴联动>
	参	数：Axis1~Axis5表示轴号
			1Target~_5Target表示轴的 逻辑位置 或 执行机构实际执行距离
			MoveSpeed运行速度
	返回值：void
	备	注：重载两个版本，一个目标位置值为逻辑位置，一个为执行机构实际位置
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed=i_moveSpeed);
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int Axis4, double _4Target, int Axis5, double _5Target, int MoveSpeed = i_moveSpeed);

	/*
	<单轴绝对运动>
	参	数：	axis:轴号
			pos:绝对位置点，以逻辑位置单位
			speed:运行速度
	返回值：void
	*/
	void axisMoveAbsolute(int axis, int pos, int speed);
	void axisMoveAbsolute(int axis, double pos, int speed);


	/*
	<单轴相对运动>
	参	数：axis:轴号
			steps:相对位移长度
			speed:运行速度
	返回值：void
	*/
	void axisMoveRelative(int axis, int steps, int speed);
	void axisMoveRelative(int axis, double steps, int speed);

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
	void jogStart(int axis,int dir);

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


	/*
	<获取原点值>
	参	数：axis轴号 或 axisName轴名称
	返回值：-1无法获取，0无效，1有效
	备	注：2个重载版本，参数为 axis轴号 或 axisName轴名称
	*/
	int getAxisORGstatus(int axis);
	int getAxisORGstatus(QString axisName);



	/*
	<更新轴的位置信息>
	参	数：无
	返回值：void
	备注：更新各个轴的位置信息，通过sigAxisPosUpdate信号发送
	*/
	QByteArray getAxisPosUpdate();

	/*
	<更新轴的限位信息>
	参	数：无
	返回值：void
	备注：更新各个轴的限位信息，通过sigAxisLimUpdate信号发送
	*/
	QByteArray getAxisLimUpdate();

	/*
	<获取io定义信息>
	参	数：无
	返回值：io和端口的map
	*/
	QMap<QString, IOInfo>	getIOinfoMap();

/*******************************************************************

io operation...

********************************************************************/


	/*
	<io注册>
	参	数：devName定义端口名称
			devPort端口号
	返回值：void
	*/
	void registerIoDev(QString devName, IOInfo dev);
	void registerIoDev(QString devName,int PORT,int VALUE);

	/*
	<写端口>
	参	数：port_bit端口号或devName端口名称
	返	回：成功则0，不成功则-1
	备	注：两个重载版本，参数为 devName字符串 或 一个port_bit整型
	*/
	int portWrite(QString devName);
	int portWrite(int port_bit);


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
	
	int ioDevTogg(QString devName);
	int ioDevTogg(int  port_bit);
	*/

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
	QMap<QString, IOInfo>	  IOInfoMap;

	int		i_jogspeed;
	int		i_moveSpeed;
	int		i_zeroSpeed;

	//QTimer	timerAxisPos;
	//QTimer	timerAxisLim;

//signals:

	/*发送轴的位置信息*/
	//void sigAxisPosUpdate(QByteArray);
	
	/*发送轴的限位信息*/
	//void sigAxisLimUpdate(QByteArray);






public slots:

};

#endif



template<class T>
DRIVERS<T>::DRIVERS():
i_jogspeed(2000),
i_moveSpeed(2000),
i_zeroSpeed(2000)
{


}


/*******************************************************************

Motion functional funcs

********************************************************************/
template<class T>
int	 DRIVERS<T>::init()
{
	int result;
	//if (QString(typeid(T).name()) == "class DriverSpace::Driveryk6000")result = initFromYk6000XML();
	//else if (typeid(T).name() == "class DriverSpace::DriverIMCnet")result = initFromIMCnetXML();
	result = initFromIMCnetXML();
	qDebug() << "result:" << result;
	return result;
}

template<class T>
int DRIVERS<T>::initFromYk6000XML()
{
	//返回值：	0成功, -1控制卡初始化失败， - 2配置文件不正确或打开失败
	QFile file("./AxisConfig.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))return -2;

	QDomDocument doc_XML;
	QString err;
	int row = 0, col = 0;
	if (!doc_XML.setContent(&file, false, &err, &row, &col))return -2;
	if (doc_XML.isNull())return -2;

	QDomElement root = doc_XML.documentElement();
	if (root.tagName() == "CONFIG")
	{
		QDomNodeList _1Nodes = root.childNodes();
		for (int _1Nodes_Index = 0; _1Nodes_Index < _1Nodes.count(); _1Nodes_Index++)
		{
			QDomNode _1Node = _1Nodes.at(_1Nodes_Index);
			QDomElement _1NodeEle = _1Node.toElement();
			if (_1NodeEle.tagName() == "AXISCONFIG")
			{
				QDomNodeList _2Nodes = _1NodeEle.childNodes();
				for (int _2Nodes_Index = 0; _2Nodes_Index < _2Nodes.count(); _2Nodes_Index++)
				{
					QDomNode _2Node = _2Nodes.at(_2Nodes_Index);
					QDomElement _2NodeEle = _2Node.toElement();
					if (_2NodeEle.tagName() == "AXIS")
					{
						QString NAME, NUMB, PMODE, PLOGIC, DLOGIC, PPR, SCREW;
						QDomNodeList _3Nodes = _2NodeEle.childNodes();
						for (int _3Node_Index = 0; _3Node_Index < _3Nodes.count(); _3Node_Index++)
						{
							QDomNode _3Node = _3Nodes.at(_3Node_Index);
							QDomElement _3NodeEle = _3Node.toElement();

							if (_3NodeEle.tagName() == "NAME")NAME = _3NodeEle.text();
							if (_3NodeEle.tagName() == "NUMB"){ NUMB = _3NodeEle.text(); }
							if (_3NodeEle.tagName() == "PMODE")PMODE = _3NodeEle.text();
							if (_3NodeEle.tagName() == "PLOGIC")PLOGIC = _3NodeEle.text();
							if (_3NodeEle.tagName() == "DLOGIC")DLOGIC = _3NodeEle.text();
							if (_3NodeEle.tagName() == "PPR")PPR = _3NodeEle.text();
							if (_3NodeEle.tagName() == "SCREW")SCREW = _3NodeEle.text();
						}
						if (NAME.isEmpty() || NUMB.isEmpty() || PMODE.isEmpty() || PLOGIC.isEmpty() || DLOGIC.isEmpty() || PPR.isEmpty() || SCREW.isEmpty())return -2;
						AxisInfoInsertItem(NAME, NUMB.toInt(), SCREW.toDouble(), PPR.toDouble());
						if (device.init(NUMB.toInt(), PMODE.toInt(), PLOGIC.toInt(), DLOGIC.toInt()))return -1;
					}
				}
			}
			else
				return -2;
		}
	}
	else
		return -2;
	return 0;
}


template<class T>
int DRIVERS<T>::initFromIMCnetXML(QString path)
{
	//返回值：	0成功, -1控制卡初始化失败， - 2配置文件不正确或打开失败
	QFile file(path);
	if (!file.open(QFile::ReadOnly | QFile::Text))return -2;

	QDomDocument doc_XML;
	QString err;
	int row = 0, col = 0;
	if (!doc_XML.setContent(&file, false, &err, &row, &col))return -3;
	if (doc_XML.isNull())return -4;

	QDomElement root = doc_XML.documentElement();
	if (root.tagName() == "CONFIG")
	{
		QDomNodeList _1Nodes = root.childNodes();
		for (int _1Nodes_Index = 0; _1Nodes_Index < _1Nodes.count(); _1Nodes_Index++)
		{
			QDomNode _1Node = _1Nodes.at(_1Nodes_Index);
			QDomElement _1NodeEle = _1Node.toElement();
			if (_1NodeEle.tagName() == "AXISCONFIG")
			{
				QDomNodeList _2Nodes = _1NodeEle.childNodes();
				for (int _2Nodes_Index = 0; _2Nodes_Index < _2Nodes.count(); _2Nodes_Index++)
				{
					QDomNode _2Node = _2Nodes.at(_2Nodes_Index);
					QDomElement _2NodeEle = _2Node.toElement();
					if (_2NodeEle.tagName() == "AXIS")
					{
						QMap<QString, QString> ParaMap;
						//QString NAME, NUMB, PPR, SCREW, ACCELIM, VELLIM, MCSMAXVEL, MCSACCEL, MCSDECEL, SMOOTH, EXITFILT, STOPFILT, STEPMOD, STEPTIM, AIOCTRL, SETTLEW, FIXVEL, POSERRLIM, ENCPCTRL, HIGHVEL, LOWVEL, HOMEPOS, ENA, RUN, PATHABS ;
						QDomNodeList _3Nodes = _2NodeEle.childNodes();
						for (int _3Node_Index = 0; _3Node_Index < _3Nodes.count(); _3Node_Index++)
						{
							QDomNode _3Node = _3Nodes.at(_3Node_Index);
							QDomElement _3NodeEle = _3Node.toElement();
							if (!_3NodeEle.tagName().isEmpty())ParaMap.insert(_3NodeEle.tagName(), _3NodeEle.text());
							qDebug() << "tagName:" << _3NodeEle.tagName() << " text:" << _3NodeEle.text();
						}
						QMapIterator<QString, QString>it(ParaMap);
						while (it.hasNext())
						{
							
							it.next();
							qDebug() << it.key();
							if (it.value().isEmpty()){ qDebug()<<it.key(); return -5; }
						}
							
						AxisInfoInsertItem(ParaMap.value("NAME"), ParaMap.value("NUMB").toInt(), ParaMap.value("SCREW").toDouble(), ParaMap.value("PPR").toDouble());
						if (device.init(ParaMap.value("NUMB").toInt()) != 1){ qDebug() << "NUMB" << ParaMap.value("NUMB").toInt(); return -1; }
					}
				}
			}
			else
				return -6;
		}
	}
	else
		return -2;
	return 0;

}


template<class T>
int DRIVERS<T>::initIOFromXML(QString path)
{
	QFile file(path);
	if (!file.open(QFile::ReadOnly | QFile::Text))return -1;

	QDomDocument doc_XML;
	QString err;
	int row = 0, col = 0;
	if ((!doc_XML.setContent(&file, false, &err, &row, &col)))return -1;
	if (doc_XML.isNull())return -1;

	QDomElement root = doc_XML.documentElement();
	if (root.tagName() == "CONFIG")
	{
		QDomNodeList _1Nodes = root.childNodes();
		for (int _1Nodes_Index = 0; _1Nodes_Index < _1Nodes.count(); _1Nodes_Index++)
		{
			QDomElement _1NodeEle = _1Nodes.at(_1Nodes_Index).toElement();
			if (_1NodeEle.tagName() == "OUTPUTCONFIG")
			{
				QDomNodeList _2Nodes = _1NodeEle.childNodes();
				for (int _2Nodes_Index = 0; _2Nodes_Index < _2Nodes.count(); _2Nodes_Index++)
				{
					QDomElement _2NodeEle = _2Nodes.at(_2Nodes_Index).toElement();
					if (_2NodeEle.tagName() == "OUTPUT")
					{
						QString Nme, PORT, VALUE;
						QDomNodeList _3Nodes = _2NodeEle.childNodes();
						for (int _3Nodes_Index = 0; _3Nodes_Index < _3Nodes.count(); _3Nodes_Index++)
						{
							QDomElement _3NodeEle = _3Nodes.at(_3Nodes_Index).toElement();
							if (_3NodeEle.tagName() == "NAME")Nme = _3NodeEle.text();
							else if (_3NodeEle.tagName() == "PORT")PORT = _3NodeEle.text();
							else if (_3NodeEle.tagName() == "VALUE")VALUE = _3NodeEle.text();
						}
						if (Nme.isEmpty() || PORT.isEmpty() || VALUE.isEmpty())return -1;
						registerIoDev(Nme, PORT.toInt(), VALUE.toInt());
					}
				}
			}
			else if (_1NodeEle.tagName() == "INPUTCONFIG")
			{

			}
			else
				return -1;
		}
	}
	else
		return -1;
	return 0;
}



template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed)
{
	device.moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, MoveSpeed);
}

template<class T>
void DRIVERS<T>::moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int MoveSpeed)
{
	QMapIterator<QString, MotionInfo> it(AxisInfoMap);
	double mpp1 = 0;
	double mpp2 = 0;
	double mpp3 = 0;
	while (it.hasNext())
	{
		it.next();
		if (it.value().Axis == Axis1)mpp1 = it.value().m_xMPP;
		if (it.value().Axis == Axis2)mpp2 = it.value().m_xMPP;
		if (it.value().Axis == Axis3)mpp3 = it.value().m_xMPP;
	}
	if (mpp1 != 0 && mpp2 != 0 && mpp3 != 0)device.moveTo(Axis1, static_cast<int>(_1Target / mpp1), Axis2, static_cast<int>(_2Target / mpp2), Axis3, static_cast<int>(_3Target / mpp3), MoveSpeed);
}


template<class T>
void DRIVERS<T>::moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed)
{
	device.moveTo(Axis1, _1Target, Axis2, _2Target, Axis3, _3Target, Axis4, _4Target, Axis5, _5Target, MoveSpeed);
}

template<class T>
void DRIVERS<T>::moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int Axis4, double _4Target, int Axis5, double _5Target, int MoveSpeed)
{
	QMapIterator<QString, MotionInfo> it(AxisInfoMap);
	double mpp1 = 0;
	double mpp2 = 0;
	double mpp3 = 0;
	double mpp4 = 0;
	double mpp5 = 0;
	while (it.hasNext())
	{
		it.next();
		if (it.value().Axis == Axis1)mpp1 = it.value().m_xMPP;
		if (it.value().Axis == Axis2)mpp2 = it.value().m_xMPP;
		if (it.value().Axis == Axis3)mpp3 = it.value().m_xMPP;
		if (it.value().Axis == Axis4)mpp4 = it.value().m_xMPP;
		if (it.value().Axis == Axis5)mpp5 = it.value().m_xMPP;
	}
	device.moveTo(Axis1,static_cast<int>(_1Target/mpp1), Axis2,static_cast<int>(_2Target/mpp2), Axis3,static_cast<int>(_3Target/mpp3), Axis4,static_cast<int>(_4Target/mpp4), Axis5,static_cast<int>(_5Target/mpp5), MoveSpeed);
}


template<class T>
void DRIVERS<T>::axisMoveAbsolute(int axis, int pos, int speed)
{
	device.axisMoveAbsolute(axis, pos, speed);
}

template<class T>
void DRIVERS<T>::axisMoveAbsolute(int axis, double pos, int speed)
{
	QMapIterator<QString, MotionInfo> it(AxisInfoMap);
	double mpp=0;
	while (it.hasNext())
	{
		it.next();
		if (it.value().Axis == axis)
		{
			mpp = it.value().m_xMPP;
			break;
		}
	}
	if (mpp != 0)device.axisMoveAbsolute(axis, static_cast<int>(pos / mpp), speed);
}


template<class T>
void DRIVERS<T>::axisMoveRelative(int axis, int steps, int speed)
{
	device.axisMoveRelative(axis, steps, speed);
}

template<class T>
void DRIVERS<T>::axisMoveRelative(int axis, double pos, int speed)
{
	QMapIterator<QString, MotionInfo> it(AxisInfoMap);
	double mpp = 0;
	while (it.hasNext())
	{
		it.next();
		if (it.value().Axis == axis)
		{
			mpp = it.value().m_xMPP;
			break;
		}
	}
	if (mpp != 0){ qDebug() << "axisMoveRelative mpp:" << mpp; device.axisMoveRelative(axis, static_cast<int>(pos / mpp), speed); }
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
void DRIVERS<T>::jogStart(int axis, int dir, int jogspeed)
{
	device.jogStart(axis, dir, jogspeed);
}

template<class T>
void DRIVERS<T>::jogStart(int axis, int dir)
{
	device.jogStart(axis, dir, i_jogspeed);
}


template<class T>
void DRIVERS<T>::jogStop(int axis)
{
	device.jogStop(axis, dir);
}
/*
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
*/
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
	info.m_xPPM = m_xPPM;
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
		it.next();
		if (it.value().Axis == axis)
		{
			mpp = it.value().m_xMPP;
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


template<class T>
int DRIVERS<T>::getAxisORGstatus(int axis)
{
	return device.getAxisORGstatus(axis);
}


template<class T>
int DRIVERS<T>::getAxisORGstatus(QString axisName)
{
	if (!AxisInfoMap.keys().contains(axisName))return -1;
	return device.getAxisORGstatus(AxisInfoMap.value(axisName).Axis);
}


template<class T>
QByteArray DRIVERS<T>::getAxisPosUpdate()
{
	if (AxisInfoMap.isEmpty())return QByteArray();

	QJsonObject obj_AxisPos;
	QMapIterator<QString, MotionInfo>it(AxisInfoMap);
	while (it.hasNext())
	{
		QString tmp = it.next().key();
		obj_AxisPos.insert(tmp, getCurPosmm(tmp));
	}

	QJsonDocument doc_AxisPos;
	doc_AxisPos.setObject(obj_AxisPos);

	return doc_AxisPos.toJson(QJsonDocument::Compact);
}


template<class T>
QByteArray DRIVERS<T>::getAxisLimUpdate()
{
	if (AxisInfoMap.isEmpty())return QByteArray();

	QJsonObject obj_AxisLim;
	QMapIterator<QString, MotionInfo>it(AxisInfoMap);
	while (it.hasNext())
	{
		QString tmp = it.next().key();
		obj_AxisLim.insert(tmp, getAxisLimitStatus(tmp));
	}

	QJsonDocument doc_AxisLim;
	doc_AxisLim.setObject(obj_AxisLim);

	return doc_AxisLim.toJson(QJsonDocument::Compact);
}

template<class T>
QMap<QString, IOInfo>	DRIVERS<T>::getIOinfoMap()
{
	return IOInfoMap;
}


/*******************************************************************

io operations...

********************************************************************/

template<class T>
void DRIVERS<T>::registerIoDev(QString devName, IOInfo devPort)
{
	IOInfoMap.insert(devName, devPort);
}

template<class T>
void DRIVERS<T>::registerIoDev(QString devName, int PORT, int VALUE)
{
	IOInfo info;
	info.PORT = PORT;
	info.VALUE = VALUE;
	IOInfoMap.insert(devName, info);
}

template<class T>
int DRIVERS<T>::portWrite(QString devName)
{
	if (IOInfoMap.keys().contains(devName))return device.writeBit(IOInfoMap.value(devName).PORT, IOInfoMap.value(devName).VALUE);
	return -1;
}

template<class T>
int DRIVERS<T>::portWrite(int port_bit)
{
	QMapIterator<QString, IOInfo>it(IOInfoMap);
	while (it.hasNext())
	{
		it.next();
		if (it.value().PORT == port_bit)return device.writeBit(port_bit, value);
	}
	return -1;
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
		return device.readBit(IOInfoMap.value(devName).PORT);
	}
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





