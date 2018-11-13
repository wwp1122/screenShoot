#include "screenCamera.h"
#include "screenshoot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	screenShoot w;
	w.show();

	a.exec();


}
