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
	<���ƿ���ʼ������>
	��  ������
	����ֵ��	��ʼ�����ɹ��򷵻�-1
			yk6000���ɹ��򷵻ؿ���
			IMCnet���ɹ��򷵻�1
	*/
	int	 init();


	/*
	<��������>
	��	��:Axis1,Axis2,Axis3��ʾ���
		   _1Target~_3Target��ʾ��������߼�λ�ã�������ִ�л���ʵ��ִ�о���
		   MoveSpeed�����ٶ�
	����ֵ��void
	��	ע�����������汾��һ���Զ����ٶȣ�һ���������ڱ���i_moveSpeed
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed);								// 3������ ��λstep
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target);

	/*
	<��������>
	��	����Axis1~Axis5��ʾ���
			1Target~_5Target��ʾ����߼�λ�ã�������ִ�л�����ʵ�ʾ���
			MoveSpeed�����ٶ�
	����ֵ��void
	��	ע�����������汾��һ���Զ����ٶȣ�һ���������ڱ���i_moveSpeed
	*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed);
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target);

	/*
	<��������˶�>
	��	����	axis:���
			pos:����λ�õ㣬���߼�λ�õ�λ
			speed:�����ٶ�
	����ֵ��void
	*/
	void axisMoveAbsolute(int axis, int pos, int speed);


	/*
	<��������˶�>
	��	����axis:���
			steps:���λ�Ƴ���
			speed:�����ٶ�
	����ֵ��void
	*/
	void axisMoveRelative(int axis, int steps, int speed);


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
/*******************************************************************

io operation...

********************************************************************/


	/*
	<ioע��>
	��	����devName����˿�����
			devPort�˿ں�
	����ֵ���ɹ��򷵻�0�����򷵻�-1
	*/
	int registerIoDev(QString devName, int devPort);


	/*
	<д�˿�>
	��	����port_bit�˿ںŻ�devName�˿�����
			valueֵ
	��	�أ��ɹ���0�����ɹ���-1
	��	ע���������ذ汾������Ϊ devName�ַ��� �� һ��port_bit����
	*/
	int portWrite(QString devName, int value);
	int portWrite(int port_bit, int value);


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
	*/
	int ioDevTogg(QString devName);
	int ioDevTogg(int  port_bit);


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
	int		i_jogspeed;
	int		i_moveSpeed;
	int		i_zeroSpeed;

	QMap<QString, int>		IOInfoMap;

	QTimer	timerAxisPos;
	QTimer	timerAxisLim;

signals:

	/*�������λ����Ϣ*/
	void sigAxisPosUpdate(QByteArray);
	
	/*���������λ��Ϣ*/
	void sigAxisLimUpdate(QByteArray);


private slots:


	/*
	<�������λ����Ϣ>
	��	������
	����ֵ��void
	��ע�����¸������λ����Ϣ��ͨ��sigAxisPosUpdate�źŷ���
	*/
	void onAxisPosUpdate();

	/*
	<���������λ��Ϣ>
	��	������
	����ֵ��void
	��ע�����¸��������λ��Ϣ��ͨ��sigAxisLimUpdate�źŷ���
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