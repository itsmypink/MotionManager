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
	<���ƿ���ʼ������>
	��  ������
	����ֵ��	0�ɹ�,-1���ƿ���ʼ��ʧ�ܣ�-2�����ļ�����ȷ���ʧ��
	*/
	int	 init();
	int  initFromYk6000XML();
	int  initFromIMCnetXML(QString path="./AxisConfig.xml");

	/*
	<��XML�л�ȡIO����>
	��	�����ļ�·��
	����ֵ��0�ɹ���-1ʧ��
	*/
	int  initIOFromXML(QString path="./IOConfig.xml");


	/*
	<��������>
	��	��:Axis1,Axis2,Axis3��ʾ���
		   _1Target~_3Target��ʾ������� �߼�λ�� �� ִ�л���ʵ��ִ�о���
		   MoveSpeed�����ٶ�
	����ֵ��void
	��	ע�����������汾��һ��Ŀ��λ��ֵΪ�߼�λ�ã�һ��Ϊִ�л���ʵ��λ��
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed=i_moveSpeed);								// 3������ ��λstep
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int MoveSpeed = i_moveSpeed);


	/*
	<��������>
	��	����Axis1~Axis5��ʾ���
			1Target~_5Target��ʾ��� �߼�λ�� �� ִ�л���ʵ��ִ�о���
			MoveSpeed�����ٶ�
	����ֵ��void
	��	ע�����������汾��һ��Ŀ��λ��ֵΪ�߼�λ�ã�һ��Ϊִ�л���ʵ��λ��
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed=i_moveSpeed);
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int Axis4, double _4Target, int Axis5, double _5Target, int MoveSpeed = i_moveSpeed);

	/*
	<��������˶�>
	��	����	axis:���
			pos:����λ�õ㣬���߼�λ�õ�λ
			speed:�����ٶ�
	����ֵ��void
	*/
	void axisMoveAbsolute(int axis, int pos, int speed);
	void axisMoveAbsolute(int axis, double pos, int speed);


	/*
	<��������˶�>
	��	����axis:���
			steps:���λ�Ƴ���
			speed:�����ٶ�
	����ֵ��void
	*/
	void axisMoveRelative(int axis, int steps, int speed);
	void axisMoveRelative(int axis, double steps, int speed);

	/*
	<��������˶�>
	��	����axis:���
			dir:����
			speed:�����ٶ�
	����ֵ��void
	*/
	void axisMoveVel(int axis, int dir, int speed);


	/*
	<ֹͣ>
	��	������
	����ֵ��void
	*/
	void stop();


	/*
	<��ͣ>
	��	������
	����ֵ��void
	��	ע����ʵ���õ���stop()����
	*/
	void hold();

	/*
	<�رտ��ƿ�>
	��	������
	����ֵ��void
	*/
	void close();

	/*
	<�㶯��ʼ>
	��	����axis���
			dir����
	����ֵ��void
	*/
	void jogStart(int axis, int dir,int jogspeed);
	void jogStart(int axis,int dir);

	/*
	<�㶯����>
	��	����axis���
	����ֵ��void
	*/
	void jogStop(int axis);



	/*
	<��ʼ������λ����Ϣ>
	��	����msec��ʱ��ʱ�䣬��λ����
	����ֵ��void
	��	ע����ʼtimerAxisPos��ʱ��
	*/
	void startAxisPosUpdate(int msec=50);

	/*
	<ֹͣ������λ����Ϣ>
	��	������
	����ֵ��void
	��	ע��ֹͣtimerAxisPos��ʱ��
	*/
	void stopAxisPosUpdate();



	/*
	<��ʼ��������λ��Ϣ>
	��	����msec��ʱ��ʱ�䣬��λ����
	����ֵ��void
	��	ע����ʼtimerAxisLim��ʱ��
	*/
	void startAxisLimUpdate(int msec = 50);
	
	/*
	<ֹͣ��������λ��Ϣ>
	��	������
	����ֵ��void
	��	ע��ֹͣtimerAxisLim��ʱ��
	*/
	void stopAxisLimUpdate();

/*******************************************************************

AxisInfoMap operations...

int	   Axis = -1;
double m_screwPitchX;		// ˿�˵���
double m_xPPR;				// ÿת������
double m_xPPM;				// ÿmm������
double m_xMPP;				// ÿ���������mm

********************************************************************/

	/*
	<�����>
	��	����AxisName�����ƣ��ַ�����ʽ
			Axis���
			m_screwPitchX��˿�˵���
			m_xPPR��ÿת������
	����ֵ��void
	*/
	void AxisInfoInsertItem(QString AxisName,int axis,double m_screwPitchX, double m_xPPR);


	/*
	<ɾ��ĳ������Ϣ>
	��	����AxisName�����ƣ��ַ�����ʽ
	����ֵ������ɾ����item����ͨ��Ϊ1��0
	*/
	int AxisInfoDeleteItem(QString AxisName);


	/*
	<�������Ϣ>
	��	������
	����ֵ��void
	*/
	void AxisInfoClear();
	


/*******************************************************************

setters...

jogspeed	�㶯�ٶ�
i_moveSpeed �����ٶ�
i_zeroSpeed �����ٶ�

********************************************************************/
	


	/*
	<���õ㶯�ٶ�>
	��	�����㶯�ٶȣ��������߼��ٶ�
	����ֵ��void
	*/
	void setJogSpeed(int jogspeed);

	/*
	<���������ٶ�>
	��	���������ٶ�ֵ
	����ֵ��void
	*/
	void setMoveSpeed(int movespeed);

	/*
	<���û����ٶ�>
	��	���������ٶ�ֵ
	����ֵ��void
	*/
	void setZeroSpeed(int zerospeed);



/*******************************************************************

getters...

jogspeed �㶯�ٶ�
int		i_moveSpeed;
int		i_zeroSpeed;

********************************************************************/

	/*
	<��ȡ�㶯�ٶ�>
	��	������
	����ֵ��i_jogspeed��ֵ,const int &����
	*/
	const int & getJogSpeed() const;

	/*
	<��ȡ�����ٶ�>
	��	������
	����ֵ������i_moveSpeed��ֵ��const int &����
	*/
	const int & getMoveSpeed() const;

	/*
	<��ȡ�����ٶ�>
	��	������
	����ֵ��i_zeroSpeed��ֵ��const int &����
	*/
	const int & getZeroSpeed() const;



	/*
	<��ȡ��ǰλ��>
	��	������Ż�������
	����ֵ����ǰ�߼�λ��ֵ
	��	ע������2���汾������λ��Ż�������
	*/
	int		getCurPos(int axis);
	int		getCurPos(QString axisName);


	/*
	<��ȡ��ǰλ��>
	��	������Ż�������
	����ֵ����ǰִ�л���ʵ��λ��ֵ
	��	ע������2���汾������Ϊ��Ż�������
	*/
	double  getCurPosmm(int axis);
	double  getCurPosmm(QString axisName);



	/*
	<��ȡ����λ��Ϣ>
	��	����axisName������ �� axis���
	����ֵ��-1��ȡ����,0����λ��1������λ��2������λ��3��������λ
	��	ע���������غ���������Ϊ axisName������ �� axis����
	*/
	int getAxisLimitStatus(QString axisName);
	int getAxisLimitStatus(int axis);


	/*
	<��ȡԭ��ֵ>
	��	����axis��� �� axisName������
	����ֵ��-1�޷���ȡ��0��Ч��1��Ч
	��	ע��2�����ذ汾������Ϊ axis��� �� axisName������
	*/
	int getAxisORGstatus(int axis);
	int getAxisORGstatus(QString axisName);



	/*
	<�������λ����Ϣ>
	��	������
	����ֵ��void
	��ע�����¸������λ����Ϣ��ͨ��sigAxisPosUpdate�źŷ���
	*/
	QByteArray getAxisPosUpdate();

	/*
	<���������λ��Ϣ>
	��	������
	����ֵ��void
	��ע�����¸��������λ��Ϣ��ͨ��sigAxisLimUpdate�źŷ���
	*/
	QByteArray getAxisLimUpdate();

	/*
	<��ȡio������Ϣ>
	��	������
	����ֵ��io�Ͷ˿ڵ�map
	*/
	QMap<QString, IOInfo>	getIOinfoMap();

/*******************************************************************

io operation...

********************************************************************/


	/*
	<ioע��>
	��	����devName����˿�����
			devPort�˿ں�
	����ֵ��void
	*/
	void registerIoDev(QString devName, IOInfo dev);
	void registerIoDev(QString devName,int PORT,int VALUE);

	/*
	<д�˿�>
	��	����port_bit�˿ںŻ�devName�˿�����
	��	�أ��ɹ���0�����ɹ���-1
	��	ע���������ذ汾������Ϊ devName�ַ��� �� һ��port_bit����
	*/
	int portWrite(QString devName);
	int portWrite(int port_bit);


	/*
	<���˿�>
	��	����port_bit
	����ֵ���˿�ֵ
	��	ע���������ذ汾������Ϊ devName�ַ��� �� һ��port_bit����
	*/
	int portRead(int port_bit);
	int portRead(QString devName);

	/*
	<�÷��˿�>
	��	����devName�˿����ƻ�port_bit�˿ں�
	����ֵ���ɹ���0�����ɹ���-1��
	��	ע���������ذ汾������Ϊ devName�˿����� �� port_bit�˿ں�
	
	int ioDevTogg(QString devName);
	int ioDevTogg(int  port_bit);
	*/

	/*
	<���ע��IO>
	��	������
	����ֵ��void
	*/
	void ClearIoDev();

	/*
	<�޳�ĳIO>
	��	����io����
	����ֵ��void
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

	/*�������λ����Ϣ*/
	//void sigAxisPosUpdate(QByteArray);
	
	/*���������λ��Ϣ*/
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
	//����ֵ��	0�ɹ�, -1���ƿ���ʼ��ʧ�ܣ� - 2�����ļ�����ȷ���ʧ��
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
	//����ֵ��	0�ɹ�, -1���ƿ���ʼ��ʧ�ܣ� - 2�����ļ�����ȷ���ʧ��
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





