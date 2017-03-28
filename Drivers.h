/**
* @file				驱动模板类
* @brief			本类集成了常用的运动形式，包括：多轴运动、相对位置运动、绝对位置运动、点动以及IO等。通过本模板与对应的驱动器类绑定，可以简化驱动器类型变更与配置。
* @author			Jay_Jou
* @date				2017-03-27
* @version			v1.0.0
* @par History:
*					v1.0.0:Jay_Jou,2017-03-27\n
*/


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

#include"DriverSpace.h"
using namespace DriverSpace;

template<class T>
class DRIVERS
{

public:


/** 类模板构造函数
*
*	类模板构造函数，构造函数中会初始化三个内部变量，分别为：i_jogspeed,i_moveSpeed,i_zeroSpeed	
*/
	DRIVERS<T>();

/*******************************************************************
	
Axis functional funcs...
	
********************************************************************/


/** 初始化函数
*	初始化轴参数和IO，分别从AxisXML和IOXML中读取参数，然后通过initFromAxisXML和initFromAxisXML进行配置
*	@param	AxisXMLpath	轴参数配置文件（XML格式）的存储路径
*	@param	IOXMLpath	IO配置文件（XML格式）的存储路径
*	@return	0成功，-1轴配置不成功，-2配置文件读取失败
*	@see	initFromAxisXML(QString path)
*	@see	initFromIOXML(QString path)
*	@note	建议在创建实例后即进行该初始化函数，根据返回值判断后续运行。
*/
	int	 init(QString AxisXMLpath = "./AxisConfig.xml",QString IOXMLpath="./IOConfig.xml");



/** 读取轴配置文件函数
*	根据提供的路径参数path，读取该XML格式文件，并将轴参数通过QList<QByteArray>的格式返回给轴初始化函数进行配置。
*	@param	path	轴参数配置文件（XML格式）的存储路径
*	@return	返回值：轴配置参数QList<QByteArray>，若path文件不存在或文件内容错误，则返回空的QList<QByteArray>().
*	@note
*/
	QList<QByteArray>  initFromAxisXML(QString path);

/** 读取IO配置文件函数
*	根据提供的路径参数path，读取该XML格式文件，并将IO以QMap容器进行保存
*	@param	path	轴参数配置文件（XML格式）的存储路径
*	@return	0成功，-1失败
*	@see	getOutputMap()
*	@see	getInputMap()
*	@note	path路径文件中应包含<OUTPUT>和<INPUT>两类IO配置。
*/
	int  initFromIOXML(QString path);


/** 三轴联动函数
*	根据提供的轴号、轴位置、运行速度进行三轴联动
*	@param	Axis1	第一个轴轴号
*	@param	_1Target	第一个轴目标位置
*	@param	Axis2	第二个轴轴号
*	@param	_2Target	第二个轴目标位置
*	@param	Axis3	第三个轴轴号
*	@param	_3Target	第三个轴目标位置
*	@return	void
*	@see	moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int MoveSpeed = i_moveSpeed)
*	@note	该函数中目标位置为驱动器逻辑位置，并非执行机构实际物理位置。
*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed=i_moveSpeed);


/** 三轴联动函数
*	重载版本
*	@param	Axis1	第一个轴轴号
*	@param	_1Target	第一个轴目标位置
*	@param	Axis2	第二个轴轴号
*	@param	_2Target	第二个轴目标位置
*	@param	Axis3	第三个轴轴号
*	@param	_3Target	第三个轴目标位置
*	@return	void
*	@see	moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed=i_moveSpeed)
*	@note	该函数中目标位置为执行机构实际物理目标位置；函数根据轴配置参数PPR和MPP将执行机构实际物理目标位置转换成驱动器逻辑位置，再调用moveTo（int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int MoveSpeed=i_moveSpeed)来实现
*/
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int MoveSpeed = i_moveSpeed);


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
*	@see	moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int Axis4, double _4Target, int Axis5, double _5Target, int MoveSpeed = i_moveSpeed)
*	@note	该函数中目标位置为驱动器逻辑位置，并非执行机构实际物理位置。
*/
	void moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed=i_moveSpeed);



/** 五轴联动函数
*	重载版本，函数内部通过轴配置参数PPR和MPP将执行机构实际物理目标位置转换成驱动器逻辑位置进行实现。
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
*	@see	moveTo(int Axis1, int _1Target, int Axis2, int _2Target, int Axis3, int _3Target, int Axis4, int _4Target, int Axis5, int _5Target, int MoveSpeed=i_moveSpeed)
*	@note	该函数中目标位置为执行机构实际物理目标位置；
*/
	void moveTo(int Axis1, double _1Target, int Axis2, double _2Target, int Axis3, double _3Target, int Axis4, double _4Target, int Axis5, double _5Target, int MoveSpeed = i_moveSpeed);

/** 单轴绝对位置运动
*	轴号为axis的轴以speed的速度匀速运行至位置pos
*	@param	axis	轴号
*	@param	pos		轴目标位置
*	@param	speed	轴运行速度
*	@return	void
*	@see	axisMoveAbsolute(int axis, double pos, int speed)
*	@note	参数中pos为逻辑位置，类型为int，并非执行机构的实际位置
*/
	void axisMoveAbsolute(int axis, int pos, int speed);


/** 单轴绝对位置运动
*	重载版本，函数内部通过调用axisMoveAbsolute(int axis, int pos, int speed)实现
*	@param	axis	轴号
*	@param	pos		轴目标位置
*	@param	speed	轴运行速度
*	@return	void
*	@see	axisMoveAbsolute(int axis, int pos, int speed)
*	@note	参数中pos为执行机构实际位置，类型为double，调用时请注意类型匹配
*/
	void axisMoveAbsolute(int axis, double pos, int speed);


/** 单轴相对位移运动
*	轴号为axis的轴以speed的速度做相对位移距离steps
*	@param	axis	轴号
*	@param	steps	轴目标位置
*	@param	speed	轴运行速度
*	@return	void
*	@see	axisMoveRelative(int axis, double steps, int speed)
*	@note	参数中steps为逻辑位置，类型为int，调用时请注意类型匹配
*	@note	调用函数时，请注意执行机构限位位置。
*/
	void axisMoveRelative(int axis, int steps, int speed);



/** 单轴相对位移运动
*	重载版本，函数内部通过调用axisMoveRelative(int axis, int steps, int speed)来实现
*	@param	axis	轴号
*	@param	steps	轴目标位置
*	@param	speed	轴运行速度
*	@return	void
*	@see	axisMoveRelative(int axis, double steps, int speed)
*	@note	参数中steps为执行机构实际位置，类型为double，调用时请注意类型匹配
*	@note	调用函数时，请注意执行机构限位位置。
*/
	void axisMoveRelative(int axis, double steps, int speed);


/** 单轴持续位移运动
*	轴号为axis的轴以speed的速度匀速朝着dir方向持续运动
*	@param	axis	轴号
*	@param	dir		轴运行方向
*	@param	speed	轴运行速度
*	@return	void
*	@note	该函数通常可以用于点动功能
*	@note	调用函数时，请注意执行机构限位位置。
*/
	void axisMoveVel(int axis, int dir, int speed);


/** 停止所有轴运动
*	该函数会调用具体轴实现的stop()函数
*	@return	void
*/
	void stop();


/** 暂停所有轴运动
*	该函数会调用具体轴实现的hold()函数
*	@return	void
*/
	void hold();

/** 关闭控制卡句柄
*	该函数会调用具体轴实现的close()函数
*	@return	void
*/
	void close();


/** 单轴点动运动
*	轴号为axis的轴以jogspeed的速度匀速朝着dir方向持续运动
*	@param	axis	轴号
*	@param	dir		轴运行方向
*	@param	jogspeed轴运行速度
*	@return	void
*	@see	setJogSpeed(int jogspeed)
*	@note	jogspeed默认值为i_jogspeed,值i_jogspeed可以通过setJogSpeed函数进行设置
*/
	void jogStart(int axis, int dir,int jogspeed=i_jogspeed);

/** 单轴点动停止
*	轴号为axis的轴停止运动
*	@param	axis	轴号
*	@return	void
*/
	void jogStop(int axis);



/*******************************************************************

AxisInfoMap operations...

int	   Axis = -1;
double m_screwPitchX;		// 丝杆导程
double m_xPPR;				// 每转脉冲数
double m_xPPM;				// 每mm脉冲数
double m_xMPP;				// 每个脉冲多少mm

********************************************************************/

/** 添加轴信息
*	添加轴名称AxisName、轴号axis、丝杆导程m_screwPitchX、每转脉冲数m_xPPR等信息，每个轴的信息会保存在内部变量AxisInfoMap中。
*	@param	AxisName	轴名称
*	@param	axis		轴号
*	@param	m_screwPitchX	轴丝杆导程
*	@param	m_xPPR		轴每转脉冲数
*	@return	void
*	@note	根据m_xPPR、m_screwPitchX参数，函数计算出PPM、MPP等参数值，一并保存。
*	@note	若在函数调用前AxisInfoMap中已存在AxisName名称的轴信息，则函数执行后，已有的AxisName轴信息会被新的参数信息覆盖。
*/
	void AxisInfoInsertItem(QString AxisName,int axis,double m_screwPitchX, double m_xPPR);


/** 删除轴信息
*	删除轴名称为AxisName的相关轴信息
*	@param	AxisName	轴名称
*	@return	删除键值为AxisName的条数，通常为0或1
*/
	int AxisInfoDeleteItem(QString AxisName);


/** 清空轴信息
*	@return	无
*/
	void AxisInfoClear();
	


/*******************************************************************

setters...

jogspeed	点动速度
i_moveSpeed 运行速度
i_zeroSpeed 回零速度

********************************************************************/
	


/** 设置点动速度
*	设置内部变量i_jogspeed为jogspeed
*	@param	jogspeed	点动速度值
*	@return	void
*	@see	getJogSpeed()
*/
	void setJogSpeed(int jogspeed);

/** 设置运行速度
*	设置内部变量i_moveSpeed为movespeed
*	@param	movespeed	运行速度值
*	@return	void
*	@see	getMoveSpeed()
*/
	void setMoveSpeed(int movespeed);

/** 设置回零速度
*	设置内部变量i_zeroSpeed为zerospeed
*	@param	zerospeed	回零速度值
*	@return	void
*	@see	getZeroSpeed()
*/
	void setZeroSpeed(int zerospeed);



/*******************************************************************

getters...

jogspeed 点动速度
int		i_moveSpeed;
int		i_zeroSpeed;

********************************************************************/

/** 获取点动速度
*	获取内部变量i_jogspeed值
*	@return	点动速度值
*	@see	setJogSpeed(int jogspeed)
*/
	const int & getJogSpeed() const;

/** 获取运行速度
*	获取内部变量i_moveSpeed值
*	@return	运行速度值
*	@see	setMoveSpeed(int movespeed)
*/
	const int & getMoveSpeed() const;

/** 获取回零速度
*	获取内部变量i_zeroSpeed值
*	@return	回零速度值
*	@see	setZeroSpeed(int zerospeed)
*/
	const int & getZeroSpeed() const;

/** 获取轴当前逻辑位置
*	获取轴号为axis的轴的当前位置
*	@param	axis	轴号
*	@return	轴的当前逻辑位置值，类型int
*/
	int		getCurPos(int axis);

/** 获取轴当前逻辑位置
*	重载版本，获取轴名称为axisName的轴的当前位置
*	@param	axisName	轴名称
*	@return	轴的当前逻辑位置值，类型int
*/
	int		getCurPos(QString axisName);



/** 获取轴当前实际位置
*	获取轴号为axis的轴的当前位置
*	@param	axis	轴号
*	@return	轴的当前实际位置值，类型double
*/
	double  getCurPosmm(int axis);


/** 获取轴当前实际位置
*	重载版本，获取轴名称为axisName的轴的当前位置
*	@param	axisName	轴名称
*	@return	轴的当前实际位置值，类型double
*/
	double  getCurPosmm(QString axisName);


/** 获取轴限位信息
*	获取轴号为axis的轴的限位信息
*	@param	axis	轴号
*	@return	-1获取出错,0无限位，1正向限位，2负向限位，3正负向限位
*	@see	getAxisLimitStatus(QString axisName)
*/
	int getAxisLimitStatus(int axis);


/** 获取轴限位信息
*	重载版本，获取轴名称为axisName的轴的限位信息
*	@param	axisName	轴名称
*	@return	-1获取出错,0无限位，1正向限位，2负向限位，3正负向限位
*	@see	getAxisLimitStatus(int axis)
*/
	int getAxisLimitStatus(QString axisName);


/** 获取原点位信息
*	获取轴号为axis的轴的原点信息
*	@param	axis	轴号
*	@return	-1无法获取，0无效，1有效
*	@see	getAxisORGstatus(QString axisName)
*/
	int getAxisORGstatus(int axis);

/** 获取原点位信息
*	重载版本，获取轴名称为axisName的轴的原点信息
*	@param	axisName	轴名称
*	@return	-1无法获取，0无效，1有效
*	@see	getAxisORGstatus(int axis)
*/
	int getAxisORGstatus(QString axisName);




	/** 获取各个轴位置信息
	*	获取内部变量AxisInfoMap中各个轴位置信息，该位置为执行机构实际位置数据
	*	@return	以json形式保存轴、轴位置数据，并转化为QByteArray返回
	*	@see	getAxisLimUpdate()
	*	@note	获取返回值后，可以通过QJsonDocument、QJsonObject等类函数进行解析。
	*/
	QByteArray getAxisPosUpdate();


	/** 获取各个轴限位信息
	*	获取内部变量AxisInfoMap中各个轴限位信息
	*	@return	以json形式保存轴、轴限位数据，并转化为QByteArray返回
	*	@see	getAxisPosUpdate()
	*	@note	获取返回值后，可以通过QJsonDocument、QJsonObject等类函数进行解析。
	*/
	QByteArray getAxisLimUpdate();


	/** 获取输出端口信息
	*	获取内部变量OutPutMap的值
	*	@return	QMap<QString, OutputInfo>
	*	@see	getInputMap()
	*	@note	返回值为map结构，QString为端口名称，OutputInfo为结构体，里面存储了输出端口信息
	*/
	QMap<QString, OutputInfo>	getOutputMap();


	/** 获取输入端口信息
	*	获取内部变量InputMap的值
	*	@return	QMap<QString, int>
	*	@see	getOutputMap()
	*	@note	返回值为map结构，QString为端口名称，int为端口号
	*/
	QMap<QString, int>			getInputMap();


/*******************************************************************

io operation...

********************************************************************/


	/** 注册输出端口信息
	*	往内部变量OutputMap中添加输出端口信息
	*	@param	devName	端口名称
	*	@param	dev		结构体OutputInfo类型
	*	@return	void
	*	@see	registerOutputDev(QString devName, int PORT, int VALUE)
	*	@note	内部变量OutputMap为QMap容器，因此注册相同 端口名称 的信息时，原有的信息会被新的信息所覆盖。
	*/
	void registerOutputDev(QString devName, OutputInfo dev);


	/** 注册输出端口信息
	*	重载版本，往内部变量OutputMap中添加输出端口信息
	*	@param	devName	端口名称
	*	@param	PORT	端口号
	*	@param	VALUE	值
	*	@return	void
	*	@see	registerOutputDev(QString devName, OutputInfo dev)
	*	@note	内部变量OutputMap为QMap容器，因此注册相同 端口名称 的信息时，原有的信息会被新的信息所覆盖。
	*/
	void registerOutputDev(QString devName, int PORT, int VALUE);


	/** 删除某个输出端口信息
	*	从内部变量OutPutMap中删除键值为devName的信息
	*	@param	devName	端口名称
	*	@return	删除掉的条数，一般为0或1
	*	@see	DeleteInputDev(QString devName)
	*/
	int DeleteOutputDev(QString devName);

	/** 注册输入端口信息
	*	重载版本，往内部变量InputMap中添加输入端口信息
	*	@param	devName	端口名称
	*	@param	PORT	端口号
	*	@return	void
	*	@see	registerOutputDev(QString devName, OutputInfo dev)
	*	@see	registerOutputDev(QString devName, int PORT, int VALUE)
	*	@note	内部变量InputMap为QMap容器，因此注册相同 端口名称 的信息时，原有的值信息会被新的值信息所覆盖。
	*/
	void registerInputDev(QString devName, int port);


	/** 删除某个输入端口信息
	*	从内部变量InputMap中删除键值为devName的信息
	*	@param	devName	端口名称
	*	@return	删除掉的条数，一般为0或1
	*	@see	DeleteOutputDev(QString devName)
	*/
	int DeleteInputDev(QString devName);


	/** 写输出端口
	*	往端口名称为devName的输出端口写数据，数据为OutputMap中保存的相应的value
	*	@param	devName	端口名称
	*	@return	成功为0，不成功为-1
	*	@see	portWrite(int port_bit)
	*	@note	当名称devName不存在时，不会有任何动作，返回值为-1。
	*/
	int portWrite(QString devName);

	/** 写输出端口
	*	往端口号为port_bit的输出端口写数据，数据为OutputMap中保存的相应的value
	*	@param	port_bit	端口号
	*	@return	成功为0，不成功为-1
	*	@see	portWrite(QString devName)
	*	@note	当名称port_bit不存在时，不会有任何动作，返回值为-1。
	*/
	int portWrite(int port_bit);


/** 读输入端口
*	读取端口名称为devName的输入端口的值
*	@param	devName	端口名称
*	@return	成功时返回读取到的值，不成功为-1
*	@see	portRead(int port_bit)
*	@note	当名称devName不存在时，不会有任何动作，返回值为-1。
*/
	int portRead(QString devName);


/** 读输入端口
*	重载版本，读取端口号为port_bit的输入端口的值
*	@param	port_bit	端口号
*	@return	成功时返回读取到的值，不成功为-1
*	@see	portRead(int port_bit)
*	@note	当名称port_bit不存在时，不会有任何动作，返回值为-1。
*/
	int portRead(int port_bit);

	/** 清空端口信息
	*	清空内部变量InputMap和OutPutMap的键值
	*	@return	返回值：void
	*/
	void ClearIoDev();

private:
	/**模板绑定的类型，模板中的函数均会调用device的同名函数，其需要在额外的类中实现*/
	T device;

	/**轴参数信息保存容器，QString为轴名称，MotionInfo为轴参数结构体*/
	QMap<QString, MotionInfo>	AxisInfoMap;

	/**输出端口信息保存容器，QString为端口名称，OutputInfo为输出端口参数结构体*/
	QMap<QString, OutputInfo>	OutPutMap;

	/**输入端口信息保存容器，QString为端口名称，int为输出端口号*/
	QMap<QString, int>			InputMap;

	/**点动速度值*/
	int		i_jogspeed;

	/**运行速度值*/
	int		i_moveSpeed;

	/**回零速度值*/
	int		i_zeroSpeed;

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
int	 DRIVERS<T>::init(QString AxisXMLpath, QString IOXMLpath)
{
	int AxisInitResult = device.init(initFromAxisXML(AxisXMLpath));
	int IOInitResult = initFromIOXML(IOXMLpath);
	if (0 == AxisInitResult && 0 == IOInitResult)
		return 0;
	else if	(-1 == IOInitResult)
		return -1;
	else
		return AxisInitResult;
}

template<class T>
QList<QByteArray> DRIVERS<T>::initFromAxisXML(QString path)
{
	QList<QByteArray> lPara;
	QList<QByteArray> ErroPara;

	QFile file(path);
	if (!file.open(QFile::ReadOnly | QFile::Text))return ErroPara;

	QDomDocument doc_XML;
	QString err;
	int row = 0, col = 0;
	if (!doc_XML.setContent(&file, false, &err, &row, &col))return ErroPara;
	if (doc_XML.isNull())return ErroPara;

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
						QJsonObject json_Obj;
						QJsonDocument doc_Obj;
						QDomNodeList _3Nodes = _2NodeEle.childNodes();
						for (int _3Node_Index = 0; _3Node_Index < _3Nodes.count(); _3Node_Index++)
						{
							QDomNode _3Node = _3Nodes.at(_3Node_Index); 
							QDomElement _3NodeEle = _3Node.toElement(); 
							QString tagName = _3NodeEle.tagName();
							if (!tagName.isEmpty() && !_3NodeEle.text().isEmpty())json_Obj.insert(tagName, _3NodeEle.text());
							else if (!tagName.isEmpty() && _3NodeEle.text().isEmpty()) return ErroPara;//有参数名称，但没有参数值
						}
						doc_Obj.setObject(json_Obj);
						lPara.append(doc_Obj.toJson());
						AxisInfoInsertItem(json_Obj.value("NAME").toString(), json_Obj.value("NUMB").toString().toInt(), json_Obj.value("SCREW").toString().toDouble(), json_Obj.value("PPR").toString().toInt());
					}
				}
			}
			else
				return ErroPara;
		}
	}
	else
		return ErroPara;
	return lPara;
}

template<class T>
int DRIVERS<T>::initFromIOXML(QString path)
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
			if (_1NodeEle.tagName() == "OUTPUTCONFIG" || _1NodeEle.tagName() == "INPUTCONFIG")
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
						registerOutputDev(Nme, PORT.toInt(), VALUE.toInt());
					}
					else if (_2NodeEle.tagName() == "INPUT")
					{
						QString Nme, PORT;
						QDomNodeList _3Nodes = _2NodeEle.childNodes();
						for (int _3Nodes_Index = 0; _3Nodes_Index < _3Nodes.count(); _3Nodes_Index++)
						{
							QDomElement _3NodeEle = _3Nodes.at(_3Nodes_Index).toElement();
							if (_3NodeEle.tagName() == "NAME")Nme = _3NodeEle.text();
							else if (_3NodeEle.tagName() == "PORT")PORT = _3NodeEle.text();
						}
						if (Nme.isEmpty() || PORT.isEmpty())return -1;
						registerInputDev(Nme, PORT.toInt());
					}
				}
			}
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
	qDebug() << "axisMoveRelative axis:" << axis;
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
QMap<QString, OutputInfo>	DRIVERS<T>::getOutputMap()
{
	return OutPutMap;
}

template<class T>
QMap<QString, int>	DRIVERS<T>::getInputMap()
{
	return InputMap;
}


/*******************************************************************

io operations...

********************************************************************/

template<class T>
void DRIVERS<T>::registerOutputDev(QString devName, OutputInfo devPort)
{
	OutPutMap.insert(devName, devPort);
}

template<class T>
void DRIVERS<T>::registerOutputDev(QString devName, int PORT, int VALUE)
{
	OutputInfo info;
	info.PORT = PORT;
	info.VALUE = VALUE;
	OutPutMap.insert(devName, info);
}

template<class T>
void DRIVERS<T>::registerInputDev(QString devName, int port)
{
	InputMap.insert(devName, port);
}



template<class T>
int DRIVERS<T>::portWrite(QString devName)
{
	if (OutPutMap.keys().contains(devName))return device.writeBit(OutPutMap.value(devName).PORT, OutPutMap.value(devName).VALUE);
	return -1;
}

template<class T>
int DRIVERS<T>::portWrite(int port_bit)
{
	QMapIterator<QString, IOInfo>it(OutPutMap);
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
	if (InputMap.keys().contains(devName))
	{
		return device.readBit(InputMap.value(devName));
	}
	return -1;
}

template<class T>
void DRIVERS<T>::ClearIoDev()
{
	OutputMap.clear();
	InputMap.clear();
}


template<class T>
int DRIVERS<T>::DeleteOutputDev(QString devName)
{
	return OutputMap.remove(devName);
}

template<class T>
int DRIVERS<T>::DeleteInputDev(QString devName)
{
	return InputMap.remove(devName);
}