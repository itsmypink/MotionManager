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

//yk6000系列控制卡的函数

**************************************************************************/
	
	class Driveryk6000
	{
	public:
		//constructor...
		Driveryk6000();
		
		/*
		<控制卡初始化>
		返回值：0成功 -1无法打开配置文件 -2控制卡open失败 
		内部：获取控制卡号，设置脉冲输出方式
		*/
		int	 init(int axis,int mode,int logic,int dir_logic);

		
		/*
		三轴联动
		Axis1,Axis2,Axis3代表了哪个轴
		这里的_1Target，_2Target，_3Target都代表的是逻辑地址，并不是执行机构的实际距离
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int yTarget, int Axis3, int zTarget, int MoveSpeed);
		

		/*
		单轴绝对运动模块，此模块值负责计算出到绝对位置需要的逻辑脉冲数，然后调用axisMoveRelative
		axis:轴号
		pos:绝对位置点，以逻辑位置单位
		speed:运行速度
		*/
		void axisMoveAbsolute(int aixs, int pos, int speed);			
		

		/*
		相对运动速度模块
		axis:轴号
		steps:相对位移长度
		speed:运行速度
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/*
		单轴持续运动
		axis:轴号
		dir:方向
		speed:运行速度
		*/
		void axisMoveVel(int axis,int dir,int speed);


		/*
		停止所有轴的运行
		*/
		void stop();


		/*
		暂停所有轴的运行
		其实调用的是stop()函数
		*/
		void hold();

		/*
		关闭控制卡
		*/
		void close();

		/*
		手动点动开始
		调用yk6000的持续运动函数
		axis:轴号
		dir:方向
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/*
		手动电动结束
		调用yk6000的停止函数yk6000_Dec_Stop
		*/
		void jogStop(int);


	//getters....

		/*
		<获取当前逻辑位置>
		参	数：轴号
		返回值：返回当前逻辑位置值
		*/
		int getCurPos(int axis);


		/*
		<读取限位值>
		参	数：axis轴号
		返回值：-1无法获取,0无限位，1负向限位，2正向限位
		*/
		int getAxisLimitStatus(int axis);


		/*
		<获取原点值>
		参	数：axis轴号
		返回值：-1无法获取，0无效，1有效
		*/
		int getAxisORGstatus(int axis);
	

	//io...
		/*
		<写输出端口>
		参数：bit端口
			  onoff端口值
		返回值：void
		*/
		int writeBit(int bit,int value);
		
		/*
		<读端口>
		参	数：bit端口号
		返回值：端口值
		*/
		int readBit(int bit);

		

	private:
		int				m_cardID;
	
	};

/*************************************************************************


//IMCnet系列控制卡的函数


**************************************************************************/
	
	class DriverIMCnet
	{
	public:
		//constructor...
		DriverIMCnet();

		/*
		初始化函数
		返回值：初始化状态 -1为不成功 1为成功
		*/
		int	 init();


		/*
		三轴联动
		Axis1,Axis2,Axis3代表了哪个轴
		这里的_1Target~_3Target都代表的是逻辑地址，并不是执行机构的实际距离
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed);								// 3轴联动 单位step
		

		/*
		五轴联动
		Axis1~Axis5代表了5个轴
		1Target~_5Target代表5个轴的位置点
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed);


		/*
		单轴绝对运动模块，此模块值负责计算出到绝对位置需要的逻辑脉冲数，然后调用axisMoveRelative
		axis:轴号
		pos:绝对位置点，以逻辑位置单位
		speed:运行速度
		*/
		void axisMoveAbsolute(int axis, int pos, int speed);


		/*
		相对运动速度模块
		axis:轴号
		steps:相对位移长度,注意
		speed:运行速度
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/*
		单轴持续运动
		axis:轴号
		dir:方向
		speed:运行速度
		*/
		void axisMoveVel(int axis, int dir, int speed);


		/*
		停止所有轴的运行
		*/
		void stop();


		/*
		暂停所有轴的运行
		其实调用的是stop()函数
		*/
		void hold();

		/*
		关闭控制卡
		*/
		void close();

		/*
		手动点动开始
		调用IMCnet的IMC_MoveVelocity
		axis:轴号
		dir:方向
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/*
		手动点动结束
		调用IMCnet的IMC_MoveVelocity，并将速度设为0
		*/
		void jogStop(int axis);



//getters....

		/*
		<获取当前逻辑位置>
		参	数：轴号
		返回值：返回当前逻辑位置值
		*/
		int getCurPos(int axis);


		/*
		<读取限位值>
		参	数：axis轴号
		返回值：-1获取出错,0无限位，1正向限位，2负向限位，3正负向限位
		*/
		int getAxisLimitStatus(int axis);


		/*
		<获取原点值>
		参	数：axis轴号
		返回值：-1无法获取，0无效，1有效
		*/
		int getAxisORGstatus(int axis);

//io...
		/*
		<写输出端口>
		参数：bit端口
		onoff端口值
		返回值：void
		*/
		int writeBit(int bit, int value);

		/*
		<读端口>
		参	数：bit端口号
		返回值：端口值
		*/
		int readBit(int bit);



		


	private:

		IMC_HANDLE m_imcHandle;


	};

	/*************************************************************************


	//轴及状态的相关自定义参数


	**************************************************************************/

	/*
	包含轴及丝杆的相关信息：
	每转脉冲数、每脉冲毫米数、丝杆导程等
	*/
	struct MotionInfo
	{
		int	   Axis = -1;
		double m_screwPitchX;		// 丝杆导程
		double m_xPPR;				// 每转脉冲数
		double m_xPPM;				// 每mm脉冲数
		double m_xMPP;				// 每个脉冲多少mm
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

		UNKNOWN, // 系统初始化后回零前 以及各轴限位和急停后的状态设定为unknown
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