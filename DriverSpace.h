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

		/** 构造函数
		*
		*	Driveryk6000构造函数，构造函数中会初始化m_cardID为-1
		*/
		Driveryk6000();
		

		/** 初始化函数
		*	初始化轴参数，从QList<QByteArray>中读取参数，QByteArray内容格式为JSON，通过解析JSON数据来进行轴参数设置
		*	@param	QList<QByteArray>	已JSON形式保存的轴参数，QList的一个值保存了一个轴的参数
		*	@return	0成功 -2控制卡open失败
		*	@note	该函数会在类模板中的init()函数进行调用
		*/
		int	 init(QList<QByteArray>);

		
		/** 三轴联动函数
		*	根据提供的轴号、轴位置、运行速度进行三轴联动
		*	@param	Axis1	第一个轴轴号
		*	@param	_1Target	第一个轴目标位置
		*	@param	Axis2	第二个轴轴号
		*	@param	_2Target	第二个轴目标位置
		*	@param	Axis3	第三个轴轴号
		*	@param	_3Target	第三个轴目标位置
		*	@return	void
		*	@note	该函数会在类模板中的moveTo函数进行调用。
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int yTarget, int Axis3, int zTarget, int MoveSpeed);
		

		/** 单轴绝对位置运动
		*	轴号为axis的轴以speed的速度匀速运行至位置pos
		*	@param	axis	轴号
		*	@param	pos		轴目标位置
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	该函数会在类模板中的axisMoveAbsolute函数进行调用。
		*/
		void axisMoveAbsolute(int aixs, int pos, int speed);			
		

		/** 单轴相对位移运动
		*	轴号为axis的轴以speed的速度做相对位移距离steps
		*	@param	axis	轴号
		*	@param	steps	轴目标位置
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	参数中steps为逻辑位置，类型为int，调用时请注意类型匹配
		*	@note	该函数会在类模板中的axisMoveRelative函数进行调用。
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/** 单轴持续位移运动
		*	轴号为axis的轴以speed的速度匀速朝着dir方向持续运动
		*	@param	axis	轴号
		*	@param	dir		轴运行方向
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	该函数通常可以用于点动功能
		*	@note	该函数会在类模板中的axisMoveVel函数进行调用。
		*/
		void axisMoveVel(int axis,int dir,int speed);


		/** 停止所有轴运动
		*	停止所有轴运动
		*	@return	void
		*	@note	该函数会在类模板中的stop函数进行调用。
		*/
		void stop();


		/** 暂停所有轴运动
		*	暂停所有轴运动
		*	@return	void
		*	@note	该函数会在类模板中的hold函数进行调用。
		*/
		void hold();

		/** 关闭控制卡句柄
		*	该函数会调用具体轴实现的close()函数
		*	@return	void
		*	@note	该函数会在类模板中的close函数进行调用。
		*/
		void close();

		/** 单轴点动运动
		*	轴号为axis的轴以jogspeed的速度匀速朝着dir方向持续运动
		*	@param	axis	轴号
		*	@param	dir		轴运行方向
		*	@param	jogspeed轴运行速度
		*	@return	void
		*	@note	该函数会在类模板中的jogStart函数进行调用。
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/** 单轴点动停止
		*	轴号为axis的轴停止运动
		*	@param	axis	轴号
		*	@return	返回值：void
		*	@note	该函数会在类模板中的jogStop函数进行调用。
		*/
		void jogStop(int);


	//getters....

		/** 获取轴当前逻辑位置
		*	获取轴号为axis的轴的当前位置
		*	@param	axis	轴号
		*	@return	返回值：轴的当前逻辑位置值，类型int
		*	@note	该函数会在类模板中的getCurPos函数进行调用。
		*/
		int getCurPos(int axis);



		/** 获取轴限位信息
		*	获取轴号为axis的轴的限位信息
		*	@param	axis	轴号
		*	@return	返回值：-1获取出错,0无限位，1正向限位，2负向限位
		*	@note	该函数会在类模板中的getAxisLimitStatus函数进行调用。
		*/
		int getAxisLimitStatus(int axis);


		/** 获取原点位信息
		*	获取轴号为axis的轴的原点信息
		*	@param	axis	轴号
		*	@return	返回值：-1无法获取，0无效，1有效
		*	@note	该函数会在类模板中的getAxisORGstatus函数进行调用。
		*/
		int getAxisORGstatus(int axis);
	

	//io...
		/** 写输出端口
		*	往端口号为port_bit的输出端口写数据value
		*	@param	bit		端口号
		*	@param	value	值
		*	@return	返回值：成功为0，不成功为-1
		*	@see	readBit(int bit)
		*	@note	该函数会在类模板中的portWrite函数进行调用。
		*/
		int writeBit(int bit,int value);
		
		/** 读输入端口
		*	重载版本，读取端口号为port_bit的输入端口的值
		*	@param	port_bit	端口号
		*	@return	返回值：成功时返回读取到的值，不成功为-1
		*	@see	writeBit(int bit,int value)
		*	@note	该函数会在类模板中的portRead函数进行调用。
		*/
		int readBit(int bit);

		

	private:
		/**控制卡卡号，创建实例时会初始化为-1*/
		int				m_cardID;
	
	};

/*************************************************************************


//IMCnet系列控制卡的函数


**************************************************************************/
	
	class DriverIMCnet
	{
	public:
		/** 构造函数
		*
		*	DriverIMCnet构造函数，构造函数中会初始化num为0
		@var	DriverIMCnet::num
		*/
		DriverIMCnet();

		/** 初始化函数
		*	初始化轴参数，从QList<QByteArray>中读取参数，QByteArray内容格式为JSON，通过解析JSON数据来进行轴参数设置
		*	@param	QList<QByteArray>	以JSON形式保存的轴参数，QList的一个值保存了一个轴的参数
		*	@return	0成功 -1控制卡open失败，-2控制卡参数设置失败
		*	@note	该函数会在类模板中的init()函数进行调用
		*/
		int	 init(QList<QByteArray>);


		/** 三轴联动函数
		*	根据提供的轴号、轴位置、运行速度进行三轴联动
		*	@param	Axis1	第一个轴轴号
		*	@param	_1Target	第一个轴目标位置
		*	@param	Axis2	第二个轴轴号
		*	@param	_2Target	第二个轴目标位置
		*	@param	Axis3	第三个轴轴号
		*	@param	_3Target	第三个轴目标位置
		*	@return	void
		*	@note	该函数会在类模板中的moveTo函数进行调用。
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed);								// 3轴联动 单位step
		

		/** 五轴联动函数
		*	根据提供的轴号、轴位置、运行速度进行五轴联动
		*	@param	Axis1	第一个轴轴号
		*	@param	_1Target	第一个轴目标位置
		*	@param	Axis2	第二个轴轴号
		*	@param	_2Target	第二个轴目标位置
		*	@param	Axis3	第三个轴轴号
		*	@param	_3Target	第三个轴目标位置
		*	@param	Axis4	第四个轴轴号
		*	@param	_4Target	第四个轴目标位置
		*	@param	Axis4	第五个轴轴号
		*	@param	_4Target	第五个轴目标位置
		*	@return	void
		*	@see	moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed)
		*	@note	该函数会在类模板中的moveTo函数进行调用。
		*/
		void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed);


		/** 单轴绝对位置运动
		*	轴号为axis的轴以speed的速度匀速运行至位置pos
		*	@param	axis	轴号
		*	@param	pos		轴目标位置
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	该函数会在类模板中的axisMoveAbsolute函数进行调用。
		*/
		void axisMoveAbsolute(int axis, int pos, int speed);


		/** 单轴相对位移运动
		*	轴号为axis的轴以speed的速度做相对位移距离steps
		*	@param	axis	轴号
		*	@param	steps	轴目标位置
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	参数中steps为逻辑位置，类型为int，调用时请注意类型匹配
		*	@note	该函数会在类模板中的axisMoveRelative函数进行调用。
		*/
		void axisMoveRelative(int axis, int steps, int speed);


		/** 单轴持续位移运动
		*	轴号为axis的轴以speed的速度匀速朝着dir方向持续运动
		*	@param	axis	轴号
		*	@param	dir		轴运行方向
		*	@param	speed	轴运行速度
		*	@return	void
		*	@note	该函数通常可以用于点动功能
		*	@note	该函数会在类模板中的axisMoveVel函数进行调用。
		*/
		void axisMoveVel(int axis, int dir, int speed);


		/** 停止所有轴运动
		*	停止所有轴运动
		*	@return	void
		*	@note	该函数会在类模板中的stop函数进行调用。
		*/
		void stop();


		/** 暂停所有轴运动
		*	暂停所有轴运动
		*	@return	void
		*	@note	该函数会在类模板中的hold函数进行调用。
		*/
		void hold();

		/** 关闭控制卡句柄
		*	该函数会调用具体轴实现的close()函数
		*	@return	void
		*	@note	该函数会在类模板中的close函数进行调用。
		*/
		void close();

		/** 单轴点动运动
		*	轴号为axis的轴以jogspeed的速度匀速朝着dir方向持续运动
		*	@param	axis	轴号
		*	@param	dir		轴运行方向
		*	@param	jogspeed轴运行速度
		*	@return	void
		*	@note	该函数会在类模板中的jogStart函数进行调用。
		*/
		void jogStart(int axis, int dir,int jogspeed);

		/** 单轴点动停止
		*	轴号为axis的轴停止运动
		*	@param	axis	轴号
		*	@return	返回值：void
		*	@note	该函数会在类模板中的jogStop函数进行调用。
		*/
		void jogStop(int axis);



//getters....

		/** 获取轴当前逻辑位置
		*	获取轴号为axis的轴的当前位置
		*	@param	axis	轴号
		*	@return	返回值：轴的当前逻辑位置值，类型int
		*	@note	该函数会在类模板中的getCurPos函数进行调用。
		*/
		int getCurPos(int axis);


		/** 获取轴限位信息
		*	获取轴号为axis的轴的限位信息
		*	@param	axis	轴号
		*	@return	返回值：-1获取出错,0无限位，1正向限位，2负向限位
		*	@note	该函数会在类模板中的getAxisLimitStatus函数进行调用。
		*/
		int getAxisLimitStatus(int axis);


		/** 获取原点位信息
		*	获取轴号为axis的轴的原点信息
		*	@param	axis	轴号
		*	@return	返回值：-1无法获取，0无效，1有效
		*	@note	该函数会在类模板中的getAxisORGstatus函数进行调用。
		*/
		int getAxisORGstatus(int axis);

//io...
		
		/** 写输出端口
		*	往端口号为port_bit的输出端口写数据value
		*	@param	bit		端口号
		*	@param	value	值
		*	@return	返回值：成功为0，不成功为-1
		*	@see	readBit(int bit)
		*	@note	该函数会在类模板中的portWrite函数进行调用。
		*/
		int writeBit(int bit, int value);

		/** 读输入端口
		*	重载版本，读取端口号为port_bit的输入端口的值
		*	@param	port_bit	端口号
		*	@return	返回值：成功时返回读取到的值，不成功为-1
		*	@see	writeBit(int bit,int value)
		*	@note	该函数会在类模板中的portRead函数进行调用。
		*/
		int readBit(int bit);

	private:

		/**控制卡初始化成功后的返回的句柄*/
		IMC_HANDLE m_imcHandle;

		/**控制卡数量*/
		int		   num;

	};

	/*************************************************************************


	//轴及状态的相关自定义参数


	**************************************************************************/

	/**
	包含轴及丝杆的相关信息：
	每转脉冲数、每脉冲毫米数、丝杆导程等
	*/
	struct MotionInfo
	{
		int	   Axis;				/// 轴号
		double m_screwPitchX;		/// 丝杆导程
		double m_xPPR;				/// 每转脉冲数
		double m_xPPM;				/// 每mm脉冲数
		double m_xMPP;				/// 每个脉冲多少mm
	};

	/**
	输出端口信息
	*/
	struct OutputInfo
	{
		int PORT;					///端口号
		int VALUE;					///端口值
	};

	/**轴号*/
	enum MotionAixs
	{
		X_AXIS = 1,
		Y_AXIS,
		Z_AXIS,
		A_AXIS,
		B_AXIS,
		C_AXIS,
	};


	/**系统状态*/
	enum MotionState
	{

		UNKNOWN,			/// 系统初始化后回零前 以及各轴限位和急停后的状态设定为unknown
		MOVE,				/// 系统中各轴处于运行状态
		STOP,				/// 系统处于停止状态
		ZERO,				/// 系统处于正在回零状态
		TIMEOUT,			/// 系统运行超时
		HOLD,				/// 系统运行暂停
		JOG_START,			/// 系统处于点动开始状态
		JOG_STOP,			/// 系统处于点动结束状态
		HARD_LIMIT,			/// 系统处于硬限位状态
	};

	/**系统信息枚举值*/
	enum LimitState
	{

		X_P_LIMIT = 0x00000001,			/// X轴正向限位
		X_N_LIMIT = 0x00000002,			/// X轴负向限位
		Y_P_LIMIT = 0x00000004,			/// Y轴正向限位
		Y_N_LIMIT = 0x00000008,			/// Y轴负向限位
		Z_P_LIMIT = 0x00000010,			/// Z轴正向限位
		Z_N_LIMIT = 0x00000020,			/// Z轴负向限位

		A_P_LIMIT = 0x00000100,			/// A轴正向限位
		A_N_LIMIT = 0x00000200,			/// A轴负向限位
		B_P_LIMIT = 0x00000400,			/// B轴正向限位
		B_N_LIMIT = 0x00000800,			/// B轴负向限位
		C_P_LIMIT = 0x00001000,			/// C轴正向限位
		C_N_LIMIT = 0x00002000,			/// C轴负向限位

		EMG_STOP = 0x00000040			/// 急停状态

	};

	/**运行速度枚举值*/
	enum Speed{
		LOW_SPEED,			/// 低速
		MID_SPEED,			/// 中速
		HIGH_SPEED,			/// 高速
		ULTRA_SPEED			/// 极速
	};
}


#endif