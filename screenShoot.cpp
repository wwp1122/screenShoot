#include "screenshoot.h"
#include <qdatetime.h>

screenShoot::screenShoot(QWidget *parent)
	: QWidget(parent)
{
	ScreenCameraInfo info = ScreenCameraInfo::defaultCamera();

	m_screenCamera = new ScreenCamera(info);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(startThread()));
}

screenShoot::~screenShoot()
{

}

void screenShoot::startThread()
{
	m_screenCamera->start();
	m_screenCamera->wait();
	m_screenCamera->quit();
	//show();
}

bool screenShoot::event(QEvent *event)
{
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
	{
		QMouseEvent* mEvent = (QMouseEvent*)event;
		m_x = mEvent->pos().x();
		m_y = mEvent->pos().y();
		
		m_width = 0;
		m_height = 0;
		setValue(m_x, m_y, m_width, m_height);
		timer->stop();
		
		break;
	}
	case QEvent::MouseMove:
	{
		QMouseEvent* mEvent = (QMouseEvent*)event;
		bool ctrlDown = ((mEvent->modifiers()&Qt::ControlModifier) != 0);
		if (ctrlDown)
		{
			m_width = mEvent->pos().x() - m_x;
			m_height = mEvent->pos().y() - m_y;
			setValue(m_x, m_y, m_width, m_height);
		}
		else
		{
			reset();
		}
		break;
	}
	case QEvent::MouseButtonRelease:
	{
		QMouseEvent* mEvent = (QMouseEvent*)event;	
		bool ctrlDown = ((mEvent->modifiers()&Qt::ControlModifier) != 0);
		if (ctrlDown)
		{
			m_width = mEvent->pos().x() - m_x;
			m_height = mEvent->pos().y() - m_y;
			setValue(m_x, m_y, m_width, m_height);
		}
		else
		{
			reset();
		}
		timer->start(600);
		break;
	}
	case QEvent::KeyPress:
	{
		QKeyEvent* kEvent = (QKeyEvent*)event;

		if ((kEvent->key()) == Qt::Key_Escape)
		{
			reset();
			timer->stop();
		}
		else if ((kEvent->key()) == Qt::Key_Alt)
		{
			timer->stop();
			//��ͼ֮ǰ��ȥ���壬��Ȼ��ͼ֮�оͻ��д���Ĵ���
			if (windowState() != Qt::WindowMinimized)
			{
				setWindowState(Qt::WindowMinimized);//��С��������
			}
			//��ʱ�ȴ���������С�� ��ʱ250����
			QTime _Timer = QTime::currentTime().addMSecs(250);
			while (QTime::currentTime() < _Timer)
			{
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}
			screen = new Screen();
			screen->fullScreen = QPixmap::grabWindow(QApplication::desktop()->winId());//����Ҫ��һ�������浱ǰȫ��ΪQPixmap���ڴ˻����Ͻ�ȡ����ͼƬ��
			screen->showFullScreen();
		}
		break;
	}
	case QEvent::Paint:
	{
		QPainter painter(this);
		QPen pen;
		pen.setBrush(Qt::yellow);
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(1);
		painter.setPen(pen);

		painter.drawRect(m_x, m_y, m_width, m_height);
		update();
		break;
	}
	default:
		break;
	}
	return QWidget::event(event);
}

void screenShoot::setValue(int x, int y, int w, int h)
{
	m_screenCamera->setValue(x, y, w, h);
}

void screenShoot::reset()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}
