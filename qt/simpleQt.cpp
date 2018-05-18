#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
	// QApplication handles the event loop for us
	QApplication app (argc, argv);

	QPushButton button;
	button.setText("My text");
	button.setToolTip("A tooltip");

	QFont font("courier");
	button.setFont(font);

	QIcon icon("/tmp/icon.png");
	button.setIcon(icon);

	button.show();

	return app.exec();
}
