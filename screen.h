#pragma once
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>//�Ҽ��˵�
#include <QPaintEvent>
#include <QPainter>//����
#include <QPixmap>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>
#include <QShowEvent>
#include <QClipboard>
#include <QKeyEvent>
#include <QRect>
#include <QFile>

class Screen :public QWidget
{
	Q_OBJECT
public:
	Screen(QWidget* parent = 0);
	~Screen();
	QPixmap fullScreen;

private:
	QPoint beginPos;
	QPoint endPos;
	bool leftMousePress;

protected:
	void mousePressEvent(QMouseEvent* mEvent);
	void mouseReleaseEvent(QMouseEvent* mEvent);
	void mouseMoveEvent(QMouseEvent* mEvent);
	void paintEvent(QPaintEvent* pEvent);

	void showEvent(QShowEvent* sEvent);
	void keyPressEvent(QKeyEvent* kEvent);
};
