#pragma once

#include <QtWidgets/QWidget>
#include "ui_MotionManagergui.h"
#include<qdebug.h>
#include<qthread.h>
#include<qtimer.h>
#include<qmap.h>
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

	DRIVERS<DriverSpace::DriverIMCnet> Device;


	void initButtons();
	QButtonGroup pg_Outputs;
	QButtonGroup pg_Inputs;

	QMap<QString, MotionInfo> AxisInfoMap;

	void setIOinfoToBtns();
	QMap<QString, IOInfo>		IOInfoMap;

signals:

private slots:
	void onAxisPosUpdate();
	void onAxisLimUpdate();

	void onMoveRelative();

	void onOutputClicked(QAbstractButton*);

protected:

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);



};
