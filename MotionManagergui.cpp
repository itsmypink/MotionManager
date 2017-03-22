#include "MotionManagergui.h"





MotionManagergui::MotionManagergui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initButtons();
	Device.initIOFromXML("./IOConfig.xml");
	int r=Device.init();
	IOInfoMap = Device.getIOinfoMap();
	setIOinfoToBtns();

	connect(&timerAxisPosUpdate, SIGNAL(timeout()), this, SLOT(onAxisPosUpdate()));
	connect(&timerAxisLimUpdate, SIGNAL(timeout()), this, SLOT(onAxisLimUpdate()));

	connect(ui.pb_XRelativeGo, &QPushButton::clicked, [&](){qDebug() << "ui.le_XRelativeValue:" << ui.le_XRelativeValue->text().toDouble();Device.axisMoveRelative(0, ui.le_XRelativeValue->text().toDouble(), 2000); });
	connect(ui.pb_YRelativeGo, &QPushButton::clicked, [&](){Device.axisMoveRelative(1, ui.le_YRelativeValue->text().toDouble(), 2000); });
	connect(ui.pb_ZRelativeGo, &QPushButton::clicked, [&](){Device.axisMoveRelative(2, ui.le_ZRelativeValue->text().toDouble(), 2000); });

	connect(ui.pb_AxisStop1, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStop2, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStop3, &QPushButton::clicked, [&](){Device.stop(); });

	connect(ui.pb_XAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(0, ui.le_XAbsolute->text().toDouble(), 2000); });
	connect(ui.pb_YAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(1, ui.le_YAbsolute->text().toDouble(), 2000); });
	connect(ui.pb_ZAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(2, ui.le_ZAbsolute->text().toDouble(), 2000); });

	connect(ui.pb_AxisStopAbso1, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStopAbso2, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStopAbso3, &QPushButton::clicked, [&](){Device.stop(); });

	connect(ui.pb_3AxisGo, &QPushButton::clicked, [&](){Device.moveTo(0, ui.le_3AxisXpos->text().toDouble(), 1, ui.le_3AxisYpos->text().toDouble(), 2, ui.le_3AxisZpos->text().toDouble(),2000); });
	connect(ui.pb_3AxisStop, &QPushButton::clicked, [&](){Device.stop(); });

	connect(&pg_Outputs, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onOutputClicked(QAbstractButton*)));

	if(r==0)startPosAndLimUpdate(100);
}

MotionManagergui::~MotionManagergui()
{
	Device.close();
}

void MotionManagergui::initButtons()
{
	pg_Outputs.addButton(ui.pb_output1, 0);
	pg_Outputs.addButton(ui.pb_output2, 1);
	pg_Outputs.addButton(ui.pb_output3, 2);
	pg_Outputs.addButton(ui.pb_output4, 3);
	pg_Outputs.addButton(ui.pb_output5, 4);
	pg_Outputs.addButton(ui.pb_output6, 5);
	pg_Outputs.addButton(ui.pb_output7, 6);
	pg_Outputs.addButton(ui.pb_output8, 7);
	pg_Outputs.addButton(ui.pb_output9, 8);
	pg_Outputs.addButton(ui.pb_output10, 9);
	pg_Outputs.addButton(ui.pb_output11, 10);
	pg_Outputs.addButton(ui.pb_output12, 11);
	pg_Outputs.addButton(ui.pb_output13, 12);
	pg_Outputs.addButton(ui.pb_output14, 13);
	pg_Outputs.addButton(ui.pb_output15, 14);
	pg_Outputs.addButton(ui.pb_output16, 15);

	pg_Inputs.addButton(ui.pb_input1, 0);
	pg_Inputs.addButton(ui.pb_input2, 1);
	pg_Inputs.addButton(ui.pb_input3, 2);
	pg_Inputs.addButton(ui.pb_input4, 3);
	pg_Inputs.addButton(ui.pb_input5, 4);
	pg_Inputs.addButton(ui.pb_input6, 5);
	pg_Inputs.addButton(ui.pb_input7, 6);
	pg_Inputs.addButton(ui.pb_input8, 7);
	pg_Inputs.addButton(ui.pb_input9, 8);
	pg_Inputs.addButton(ui.pb_input10, 9);
	pg_Inputs.addButton(ui.pb_input11, 10);
	pg_Inputs.addButton(ui.pb_input12, 11);
	pg_Inputs.addButton(ui.pb_input13, 12);
	pg_Inputs.addButton(ui.pb_input14, 13);
	pg_Inputs.addButton(ui.pb_input15, 14);
	pg_Inputs.addButton(ui.pb_input16, 15);

	pg_Outputs.setExclusive(false);
	pg_Outputs.setExclusive(false);
	for (int index = 0; index < 16; index++)
	{
		pg_Outputs.button(index)->setCheckable(true);
		pg_Inputs.button(index)->setCheckable(false);
	}
}


void MotionManagergui::startPosAndLimUpdate(int msec)
{
	timerAxisPosUpdate.start(msec);
	timerAxisLimUpdate.start(msec);
}

void MotionManagergui::setIOinfoToBtns()
{
	QMapIterator<QString,IOInfo> it(IOInfoMap);
	int index = 0;
	while (it.hasNext())
	{
		it.next();
		pg_Outputs.button(index++)->setText(it.key());
	}
}

void MotionManagergui::onAxisPosUpdate()
{
	QByteArray AxisPos = Device.getAxisPosUpdate();
	QJsonDocument doc_Json = QJsonDocument::fromJson(AxisPos);
	QJsonObject obj_Json = doc_Json.object();
	
	ui.le_XActPos->setText(QString("%1").arg(obj_Json.value("X").toDouble(),0,'f',5));
	ui.le_YActPos->setText(QString("%1").arg(obj_Json.value("Y").toDouble(), 0, 'f', 5));
	ui.le_ZActPos->setText(QString("%1").arg(obj_Json.value("Z").toDouble(), 0, 'f', 5));
}


void MotionManagergui::onAxisLimUpdate()
{
	QByteArray AxisLim = Device.getAxisLimUpdate();
	QJsonDocument doc_Json = QJsonDocument::fromJson(AxisLim);
	QJsonObject obj_Json = doc_Json.object();

	//-1无法获取, 0无限位，1负向限位，2正向限位
	qDebug() << "obj_Json.valueX.toInt():" << obj_Json.value("X").toInt();
	obj_Json.value("X").toInt() == 1 ? ui.pb_XLimtN->setIcon(QIcon("./images/purple.png")) : ui.pb_XLimtN->setIcon(QIcon("./images/greenled.png"));
	obj_Json.value("X").toInt() == 2 ? ui.pb_XLimtP->setIcon(QIcon("./images/purple.png")) : ui.pb_XLimtP->setIcon(QIcon("./images/greenled.png"));
	if (obj_Json.value("X").toInt() == 0){ ui.pb_XLimtN->setIcon(QIcon("./images/greenled.png")); ui.pb_XLimtP->setIcon(QIcon("./images/greenled.png")); }
	//else qDebug() << "Axis X Lim update failed.";

	obj_Json.value("Y").toInt() == 1 ? ui.pb_YLimtN->setIcon(QIcon("./images/purple.png")) : ui.pb_YLimtN->setIcon(QIcon("./images/greenled.png"));
	obj_Json.value("Y").toInt() == 2 ? ui.pb_YLimtP->setIcon(QIcon("./images/purple.png")) : ui.pb_YLimtP->setIcon(QIcon("./images/greenled.png"));
	if (obj_Json.value("Y").toInt() == 0){ ui.pb_YLimtN->setIcon(QIcon("./images/greenled.png")); ui.pb_YLimtP->setIcon(QIcon("./images/greenled.png")); }
	//else qDebug() << "Axis Y Lim update failed.";

	obj_Json.value("Z").toInt() == 1 ? ui.pb_ZLimtN->setIcon(QIcon("./images/purple.png")) : ui.pb_ZLimtN->setIcon(QIcon("./images/greenled.png"));
	obj_Json.value("Z").toInt() == 2 ? ui.pb_ZLimtP->setIcon(QIcon("./images/purple.png")) : ui.pb_ZLimtP->setIcon(QIcon("./images/greenled.png"));
	if (obj_Json.value("Z").toInt() == 0){ui.pb_ZLimtN->setIcon(QIcon("./images/greenled.png")); ui.pb_ZLimtP->setIcon(QIcon("./images/greenled.png"));}
	//else qDebug() << "Axis Z Lim update failed.";

	Device.getAxisORGstatus("X") ? ui.pb_XORG->setIcon(QIcon("./images/purple.png")) : ui.pb_XORG->setIcon(QIcon("./images/greenled.png"));
	Device.getAxisORGstatus("Y") ? ui.pb_YORG->setIcon(QIcon("./images/purple.png")) : ui.pb_YORG->setIcon(QIcon("./images/greenled.png"));
	Device.getAxisORGstatus("Z") ? ui.pb_ZORG->setIcon(QIcon("./images/purple.png")) : ui.pb_ZORG->setIcon(QIcon("./images/greenled.png"));
}

void MotionManagergui::onMoveRelative()
{

}

void MotionManagergui::onOutputClicked(QAbstractButton*b)
{
	bool isChecked = b->isChecked();
	if (IOInfoMap.keys().contains(b->text())){ Device.portWrite(b->text()); }
}

void MotionManagergui::keyPressEvent(QKeyEvent *event)
{

}
void MotionManagergui::keyReleaseEvent(QKeyEvent *event)
{

}


