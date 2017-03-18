#pragma once

#include <QtWidgets/QWidget>
#include "ui_MotionManagergui.h"
#include<qdebug.h>
#include<qthread.h>
#include<qtimer.h>
#include"Drivers.h"



class MotionManagergui : public QWidget
{
    Q_OBJECT

public:
    MotionManagergui(QWidget *parent = Q_NULLPTR);
	~MotionManagergui();

	void startPosAndLimUpdate(int msec);



private:
    Ui::MotionManagerguiClass ui;

	QTimer timerAxisPosUpdate;
	QTimer timerAxisLimUpdate;

	DRIVERS<DriverSpace::Driveryk6000> Device;



signals:



private slots:
	void onAxisPosUpdate();
	void onAxisLimUpdate();

	void onMoveRelative();

};
