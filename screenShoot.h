#ifndef SCREENSHOOT_H
#define SCREENSHOOT_H

#include <QtWidgets/QWidget>
#include <qtimer.h>
#include <qpainter.h>
#include <qdesktopwidget.h>
#include <qapplication.h>

#include "screenCamera.h"
#include "screen.h"


class screenShoot : public QWidget
{
	Q_OBJECT

public:
	screenShoot(QWidget *parent = 0);
	~screenShoot();

	void setValue(int x, int y, int w, int h);
	void reset();
signals:
	//void startThread();
public slots:
void startThread();
private:
	QTimer* timer;
	ScreenCamera* m_screenCamera;
	Screen* screen;

	int m_x, m_y, m_width, m_height;
protected:
	bool event(QEvent *event);
};

#endif // SCREENSHOOT_H
