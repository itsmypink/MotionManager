#include "MotionManagergui.h"





MotionManagergui::MotionManagergui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Device.AxisInfoInsertItem("X", 1, 10, 10000);
	Device.AxisInfoInsertItem("Y", 2, 10, 10000);
	Device.AxisInfoInsertItem("Z", 3, 10, 10000);

	Device.init();

	connect(&timerAxisPosUpdate, SIGNAL(timeout()), this, SLOT(onAxisPosUpdate()));
	connect(&timerAxisLimUpdate, SIGNAL(timeout()), this, SLOT(onAxisLimUpdate()));

	connect(ui.pb_XRelativeGo, &QPushButton::clicked, [&](){qDebug() << "ui.le_XRelativeValue:" << ui.le_XRelativeValue->text().toDouble();Device.axisMoveRelative(1, ui.le_XRelativeValue->text().toDouble(), 2000); });
	connect(ui.pb_YRelativeGo, &QPushButton::clicked, [&](){Device.axisMoveRelative(2, ui.le_YRelativeValue->text().toDouble(), 2000); });
	connect(ui.pb_ZRelativeGo, &QPushButton::clicked, [&](){Device.axisMoveRelative(3, ui.le_ZRelativeValue->text().toDouble(), 2000); });

	connect(ui.pb_AxisStop1, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStop2, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStop3, &QPushButton::clicked, [&](){Device.stop(); });

	connect(ui.pb_XAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(1, ui.le_XAbsolute->text().toDouble(), 2000); });
	connect(ui.pb_YAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(2, ui.le_YAbsolute->text().toDouble(), 2000); });
	connect(ui.pb_ZAbsoluteGo, &QPushButton::clicked, [&](){Device.axisMoveAbsolute(3, ui.le_ZAbsolute->text().toDouble(), 2000); });

	connect(ui.pb_AxisStopAbso1, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStopAbso2, &QPushButton::clicked, [&](){Device.stop(); });
	connect(ui.pb_AxisStopAbso3, &QPushButton::clicked, [&](){Device.stop(); });

	connect(ui.pb_3AxisGo, &QPushButton::clicked, [&](){Device.moveTo(1, ui.le_3AxisXpos->text().toDouble(), 2, ui.le_3AxisYpos->text().toDouble(), 3, ui.le_3AxisZpos->text().toDouble(),2000); });
	connect(ui.pb_3AxisStop, &QPushButton::clicked, [&](){Device.stop(); });

	startPosAndLimUpdate(100);
}

MotionManagergui::~MotionManagergui()
{
	Device.close();
}

void MotionManagergui::startPosAndLimUpdate(int msec)
{
	timerAxisPosUpdate.start(msec);
	timerAxisLimUpdate.start(msec);
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

	if (obj_Json.value("X").toInt() == 1)ui.pb_XLimtN->setIcon(QIcon("./images/greenled.png"));
	else if (obj_Json.value("X").toInt() == 2)ui.pb_XLimtN->setIcon(QIcon("./images/purple.png"));
	else if (obj_Json.value("X").toInt() == 0)ui.pb_XLimtN->setIcon(QIcon("./images/seagreen.png"));
	else qDebug() << "Axis X Lim update failed.";

	if (obj_Json.value("Y").toInt() == 1)ui.pb_YLimtN->setIcon(QIcon("./images/greenled.png"));
	else if (obj_Json.value("Y").toInt() == 2)ui.pb_YLimtN->setIcon(QIcon("./images/purple.png"));
	else if (obj_Json.value("Y").toInt() == 0)ui.pb_YLimtN->setIcon(QIcon("./images/seagreen.png"));
	else qDebug() << "Axis Y Lim update failed.";

	if (obj_Json.value("Z").toInt() == 1)ui.pb_ZLimtN->setIcon(QIcon("./images/greenled.png"));
	else if (obj_Json.value("Z").toInt() == 2)ui.pb_ZLimtN->setIcon(QIcon("./images/purple.png"));
	else if (obj_Json.value("Z").toInt() == 0)ui.pb_ZLimtN->setIcon(QIcon("./images/seagreen.png"));
	else qDebug() << "Axis Z Lim update failed.";

	Device.getAxisORGstatus("X") ? ui.pb_XORG->setIcon(QIcon("./images/purple.png")) : ui.pb_XORG->setIcon(QIcon("./images/greenled.png"));
	Device.getAxisORGstatus("Y") ? ui.pb_YORG->setIcon(QIcon("./images/purple.png")) : ui.pb_YORG->setIcon(QIcon("./images/greenled.png"));
	Device.getAxisORGstatus("Z") ? ui.pb_ZORG->setIcon(QIcon("./images/purple.png")) : ui.pb_ZORG->setIcon(QIcon("./images/greenled.png"));
}

void MotionManagergui::onMoveRelative()
{

}