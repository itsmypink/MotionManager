#ifndef FRMDRIVERSPACE_H
#define FRMDRIVERSPACE_H

#include<qdom.h>
#include<qfile.h>
#include<qbytearray.h>
#include<qjsonobject.h>
#include<qjsonarray.h>
#include<qjsondocument.h>
#include<qdebug.h>

#include <Windows.h>
#include<IMCnet.h>
#include<ParamDef.h>
#include<IMC_Def.h>
#include<PackageFun.h>


namespace DriverSpace
{

/*************************************************************************

//yk6000ϵ�п��ƿ��ĺ���

**************************************************************************/
	
	class Driveryk6000
	{
	public:
		//constructor...
		Driveryk6000();
		
		/*
		<���ƿ���ʼ��>
		����ֵ��0�ɹ� -1�޷��������ļ� -2���ƿ�openʧ�� 
		�ڲ�����ȡ���ƿ��ţ��������������ʽ
		*/
		int	 init(int axis,int mode,int logic,int dir_logic);

		
		/*
		��������
		Axis1,Axis2,Axis3�������ĸ���
		�����_1Target��_2Target��_3Target����������߼���ַ��������ִ�л�����ʵ�ʾ���
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int yTarget, int Axis3, int zTarget, int MoveSpeed);
		

		/*
		��������˶�ģ�飬��ģ��ֵ��������������λ����Ҫ���߼���������Ȼ�����axisMoveRelative
		axis:���
		pos:����λ�õ㣬���߼�λ�õ�λ
		speed:�����ٶ�
		*/
		void axisMoveAbsolute(int aixs, int pos, int speed);			
		

		/*
		����˶��ٶ�ģ��
		axis:���
		steps:���λ�Ƴ���
		speed:�����ٶ�
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/*
		��������˶�
		axis:���
		dir:����
		speed:�����ٶ�
		*/
		void axisMoveVel(int axis,int dir,int speed);


		/*
		ֹͣ�����������
		*/
		void stop();


		/*
		��ͣ�����������
		��ʵ���õ���stop()����
		*/
		void hold();

		/*
		�رտ��ƿ�
		*/
		void close();

		/*
		�ֶ��㶯��ʼ
		����yk6000�ĳ����˶�����
		axis:���
		dir:����
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/*
		�ֶ��綯����
		����yk6000��ֹͣ����yk6000_Dec_Stop
		*/
		void jogStop(int);


	//getters....

		/*
		<��ȡ��ǰ�߼�λ��>
		��	�������
		����ֵ�����ص�ǰ�߼�λ��ֵ
		*/
		int getCurPos(int axis);


		/*
		<��ȡ��λֵ>
		��	����axis���
		����ֵ��-1�޷���ȡ,0����λ��1������λ��2������λ
		*/
		int getAxisLimitStatus(int axis);


		/*
		<��ȡԭ��ֵ>
		��	����axis���
		����ֵ��-1�޷���ȡ��0��Ч��1��Ч
		*/
		int getAxisORGstatus(int axis);
	

	//io...
		/*
		<д����˿�>
		������bit�˿�
			  onoff�˿�ֵ
		����ֵ��void
		*/
		int writeBit(int bit,int value);
		
		/*
		<���˿�>
		��	����bit�˿ں�
		����ֵ���˿�ֵ
		*/
		int readBit(int bit);

		

	private:
		int				m_cardID;
	
	};

/*************************************************************************


//IMCnetϵ�п��ƿ��ĺ���


**************************************************************************/
	
	class DriverIMCnet
	{
	public:
		//constructor...
		DriverIMCnet();

		/*
		��ʼ������
		����ֵ����ʼ��״̬ -1Ϊ���ɹ� 1Ϊ�ɹ�
		*/
		int	 init();


		/*
		��������
		Axis1,Axis2,Axis3�������ĸ���
		�����_1Target~_3Target����������߼���ַ��������ִ�л�����ʵ�ʾ���
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed);								// 3������ ��λstep
		

		/*
		��������
		Axis1~Axis5������5����
		1Target~_5Target����5�����λ�õ�
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed);


		/*
		��������˶�ģ�飬��ģ��ֵ��������������λ����Ҫ���߼���������Ȼ�����axisMoveRelative
		axis:���
		pos:����λ�õ㣬���߼�λ�õ�λ
		speed:�����ٶ�
		*/
		void axisMoveAbsolute(int axis, int pos, int speed);


		/*
		����˶��ٶ�ģ��
		axis:���
		steps:���λ�Ƴ���,ע��
		speed:�����ٶ�
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/*
		��������˶�
		axis:���
		dir:����
		speed:�����ٶ�
		*/
		void axisMoveVel(int axis, int dir, int speed);


		/*
		ֹͣ�����������
		*/
		void stop();


		/*
		��ͣ�����������
		��ʵ���õ���stop()����
		*/
		void hold();

		/*
		�رտ��ƿ�
		*/
		void close();

		/*
		�ֶ��㶯��ʼ
		����IMCnet��IMC_MoveVelocity
		axis:���
		dir:����
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/*
		�ֶ��㶯����
		����IMCnet��IMC_MoveVelocity�������ٶ���Ϊ0
		*/
		void jogStop(int axis);



//getters....

		/*
		<��ȡ��ǰ�߼�λ��>
		��	�������
		����ֵ�����ص�ǰ�߼�λ��ֵ
		*/
		int getCurPos(int axis);


		/*
		<��ȡ��λֵ>
		��	����axis���
		����ֵ��-1��ȡ����,0����λ��1������λ��2������λ��3��������λ
		*/
		int getAxisLimitStatus(int axis);


		/*
		<��ȡԭ��ֵ>
		��	����axis���
		����ֵ��-1�޷���ȡ��0��Ч��1��Ч
		*/
		int getAxisORGstatus(int axis);

//io...
		/*
		<д����˿�>
		������bit�˿�
		onoff�˿�ֵ
		����ֵ��void
		*/
		int writeBit(int bit, int value);

		/*
		<���˿�>
		��	����bit�˿ں�
		����ֵ���˿�ֵ
		*/
		int readBit(int bit);



		


	private:

		IMC_HANDLE m_imcHandle;


	};

	/*************************************************************************


	//�ἰ״̬������Զ������


	**************************************************************************/

	/*
	�����ἰ˿�˵������Ϣ��
	ÿת��������ÿ�����������˿�˵��̵�
	*/
	struct MotionInfo
	{
		int	   Axis = -1;
		double m_screwPitchX;		// ˿�˵���
		double m_xPPR;				// ÿת������
		double m_xPPM;				// ÿmm������
		double m_xMPP;				// ÿ���������mm
	};


	enum MotionAixs
	{
		X_AXIS = 1,
		Y_AXIS,
		Z_AXIS,
		A_AXIS,
		B_AXIS,
		C_AXIS,
	};

	enum MotionState
	{

		UNKNOWN, // ϵͳ��ʼ�������ǰ �Լ�������λ�ͼ�ͣ���״̬�趨Ϊunknown
		MOVE,
		STOP,
		ZERO,
		TIMEOUT,
		HOLD,
		JOG_START,
		JOG_STOP,
		HARD_LIMIT,

	};

	enum LimitState
	{

		X_P_LIMIT = 0x00000001,
		X_N_LIMIT = 0x00000002,
		Y_P_LIMIT = 0x00000004,
		Y_N_LIMIT = 0x00000008,
		Z_P_LIMIT = 0x00000010,
		Z_N_LIMIT = 0x00000020,

		A_P_LIMIT = 0x00000100,
		A_N_LIMIT = 0x00000200,
		B_P_LIMIT = 0x00000400,
		B_N_LIMIT = 0x00000800,
		C_P_LIMIT = 0x00001000,
		C_N_LIMIT = 0x00002000,

		EMG_STOP = 0x00000040

	};

	enum Speed{
		LOW_SPEED,
		MID_SPEED,
		HIGH_SPEED,
		ULTRA_SPEED
	};


}


#endif