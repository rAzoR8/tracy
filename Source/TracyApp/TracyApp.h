#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TracyApp.h"

class TracyApp : public QMainWindow
{
	Q_OBJECT

public:
	TracyApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::TracyAppClass ui;
};
