#include "screen.h"


Screen::Screen(QWidget* parent) :QWidget(parent)
{
	beginPos = QPoint(-1,-1);
	endPos = QPoint(-1, -1);
	leftMousePress = false;
}


Screen::~Screen()
{
}

void Screen::mousePressEvent(QMouseEvent* mEvent)
{
	beginPos = mEvent->pos();
	leftMousePress = true;
}

void Screen::mouseReleaseEvent(QMouseEvent* mEvent)
{
	endPos = mEvent->pos();
	leftMousePress = false;
}

void Screen::mouseMoveEvent(QMouseEvent* mEvent)
{
	endPos = mEvent->pos();
	update();
}

void Screen::paintEvent(QPaintEvent* pEvent)
{

	QPainter painter(this); //����ǰ�����������Ϊ����
	QPen pen;
	pen.setColor(Qt::red);//���ñ�ɫ
	pen.setWidth(1);     //������������
	painter.setPen(pen);//���û���

	int lx = beginPos.x()<endPos.x() ? beginPos.x() : endPos.x();//���ν�ͼ�������Ͻ�x����
	int ly = beginPos.y()<endPos.y() ? beginPos.y() : endPos.y();//���ν�ͼ�������Ͻ�x����
	int w = beginPos.x()<endPos.x() ? endPos.x() - beginPos.x() : beginPos.x() - endPos.x();//���ν�ͼ�������
	int h = beginPos.y()<endPos.y() ? endPos.y() - beginPos.y() : beginPos.y() - endPos.y();//���ν�ͼ����߶�

	QRect rect = QRect(lx, ly, w, h);//���ν�ͼ����
	if (lx != -1 && w>0 && h>0)//��ֹ��һ�ξ��ػ� ���ҿ��ߴ���0ʱ�Ž��н�ͼ����
	{

		painter.drawPixmap(rect, fullScreen, rect);//�ػ��ͼ���β��֣����ָ�ԭͼ���ﵽȥ��Ļ��Ч��
		painter.drawRect(lx, ly, w, h);//����ͼ����
		//��ͼ�����Сλ����ʾ
		if (ly>10)//���⿴������ʾ,�ڽ�ͼ�����ϱ߲��ӽ���Ļ�ϱ�ʱ����ʾ�ڽ�ͼ���ε��ϱߵ�����
		{
			painter.drawText(lx + 2, ly - 8, tr("range:(%1,%2) - (%3,%4)  size:(%5 x %6)").arg(lx).arg(ly).arg(lx + w).arg(ly + h).arg(w).arg(h));
		}
		else//�ڽ�ͼ�����ϱ߽ӽ���Ļ�ϱ�ʱ����ʾ�ڽ�ͼ���ε��ϱߵ�����
		{
			painter.drawText(lx + 2, ly + 12, tr("range:(%1,%2) - (%3,%4)  size:(%5 x %6)").arg(lx).arg(ly).arg(lx + w).arg(ly + h).arg(w).arg(h));
		}
	}


}

void Screen::showEvent(QShowEvent* sEvent)
{
	setWindowOpacity(0.6);//ģ��qq��ģ����
}

void Screen::keyPressEvent(QKeyEvent* kEvent)
{
	/// Esc ���˳���ͼ;
	if (kEvent->key() == Qt::Key_Escape)
	{
		close();
	}

}
