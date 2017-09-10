#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tracy.h"

class Tracy : public QMainWindow
{
	Q_OBJECT

public:
	Tracy(QWidget *parent = Q_NULLPTR);

private:
	Ui::TracyClass ui;
};
