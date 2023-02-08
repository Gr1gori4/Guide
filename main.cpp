#include "phonebook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PhoneBook phonebook;
    phonebook.setWindowTitle("Телефонный справочник");
    phonebook.resize(1250, 600);

    QFile styleF;
    styleF.setFileName(":/style/style.css");
    if (!styleF.open(QFile::ReadOnly))
        qDebug() << "Ошибка при открытии файла чтения CSS";
    app.setStyleSheet(styleF.readAll());

    phonebook.show();
    return app.exec();
}
