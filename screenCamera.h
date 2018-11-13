#pragma once

#include <qthread.h>
#include <qobject.h>
#include <qscreen.h>
#include <qtimer.h>
#include <qimage.h>
#include <qclipboard.h>
#include <qevent.h>

class ScreenCamera;

class ScreenCameraInfo
{
	friend class ScreenCamera;
public:
	explicit ScreenCameraInfo(QScreen* screen = nullptr);
	ScreenCameraInfo(const ScreenCameraInfo &info);
	
	QString description()const;
	QString deciceName()const;
	bool isNull()const;
	bool operator!=(const ScreenCameraInfo &other)const;
	ScreenCameraInfo &operator=(const ScreenCameraInfo &other);
	bool operator==(const ScreenCameraInfo &other)const;

	static QList<ScreenCameraInfo>availableCameras();
	static ScreenCameraInfo defaultCamera();

private:
	QScreen* m_screen;
};

class ScreenCamera :public QThread
{
	Q_OBJECT
public:
	ScreenCamera(QObject* parent=0);
	ScreenCamera(ScreenCameraInfo &info, QObject* parent = 0);

	bool openDevice(const ScreenCameraInfo &info);
	void setFrameRate(double fps);

	void setRoi(int x, int y, int width, int height);
	void run()override;

	void reset();
	void setValue(int x, int y, int w, int h);


	QImage capture();
signals:
	void imageChanged(const QImage &image);
	public slots:
	void start();
	void stop();
	public slots:
	void saveImage(QImage image);
private:
	int m_sleepInterval;
	QClipboard* m_cameraImage;
	QScreen* m_screen;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	bool drawRect;

};

