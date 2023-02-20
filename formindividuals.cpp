#include "formindividuals.h"
#include "phonebook.h"

FormIndividuals::FormIndividuals(int work_variant,QSqlDatabase db, QSqlTableModel *modeldb, QWidget *parent) :
    QWidget(parent),

    phone_validator(QRegExp("^\\+7\\d{10}$")),
    text_validator(QRegExp("^[А-Я][а-я]{1,15}$")),
    mail_validator(QRegExp("^\\w+@[a-zA-Z]{1,6}\\.[a-zA-Z]{1,3}$"))
{
    setWindowTitle("Добавление/поиск");

    plsurname = new QLabel(tr("Фамилия:"));
    plname = new QLabel (tr("Имя:"));
    plpatronymic = new QLabel (tr("Отчество:"));
    plnumber = new QLabel (tr("Номер телефона:"));
    pladress = new QLabel (tr("Почта:"));
    plstatus = new QLabel (tr("Статус:"));
    pldescription = new QLabel (tr("Описание:"));

    plename = new QLineEdit ();
    plesurname = new QLineEdit ();
    plepatronymic = new QLineEdit ();
    plenumber = new QLineEdit ();
    pleadress = new QLineEdit ();
    plestatus = new QLineEdit ();
    pledescription = new QLineEdit ();

    plesurname->setPlaceholderText(tr("Иванов"));
    plename->setPlaceholderText(tr("Иван"));
    plepatronymic->setPlaceholderText(tr("Иванович"));
    plenumber->setPlaceholderText(tr("+7__________"));
    pleadress->setPlaceholderText(tr("ivanov@yandex.ru"));
    plestatus->setPlaceholderText(tr("Коллега"));
    pledescription->setPlaceholderText(tr("Описание"));

    plesurname->setValidator(&text_validator);
    plename->setValidator(&text_validator);
    plepatronymic->setValidator(&text_validator);
    plenumber->setValidator(&phone_validator);
    pleadress->setValidator(&mail_validator);

    ppbinsert = new QPushButton (tr("Добавить"));
    ppbsearch = new QPushButton (tr("Поиск"));

    auto  *pvbxlform = new QVBoxLayout();

    auto* pgrdLayout = new QGridLayout;
    pgrdLayout->setContentsMargins(5, 5, 5, 5);
    pgrdLayout->setSpacing(15);

    pgrdLayout->addWidget(plsurname, 0, 0);
    pgrdLayout->addWidget(plesurname, 0, 1) ;
    pgrdLayout->addWidget(plname, 1, 0);
    pgrdLayout->addWidget(plename, 1, 1);
    pgrdLayout->addWidget(plpatronymic, 2, 0);
    pgrdLayout->addWidget(plepatronymic, 2, 1);
    pgrdLayout->addWidget(plnumber, 3, 0);
    pgrdLayout->addWidget(plenumber, 3, 1) ;
    pgrdLayout->addWidget(pladress, 4, 0);
    pgrdLayout->addWidget(pleadress, 4, 1);
    pgrdLayout->addWidget(plstatus, 5, 0);
    pgrdLayout->addWidget(plestatus, 5, 1) ;
    pgrdLayout->addWidget(pldescription, 6, 0);
    pgrdLayout->addWidget(pledescription, 6, 1) ;


    pvbxlform->addLayout(pgrdLayout);
    pvbxlform->addWidget(ppbinsert);
    pvbxlform->addWidget(ppbsearch);

    setLayout(pvbxlform);

    switch(work_variant)
    {
    case 0:
        ppbsearch->hide();
        break;
    case 1:
        plsurname->hide();
        plesurname->hide();
        plnumber->hide();
        plenumber->hide();
        Search_menu();
        break;
    case 2:
        plname->hide();
        plename->hide();
        plnumber->hide();
        plenumber->hide();
        Search_menu();
        break;
    case 3:
        plname->hide();
        plename->hide();
        plsurname->hide();
        plesurname->hide();
        Search_menu();
        break;
    }

    connect(ppbinsert,&QPushButton::clicked, [=](){ this->AddRecord(db,modeldb); });
    connect(ppbsearch, &QPushButton::clicked, [=](){ this->SearchRecord(modeldb); });

}

FormIndividuals::~FormIndividuals()
{

}

void FormIndividuals::Close_msg(QString str)
{
    QMessageBox msg;
    msg.setText(str);
    if(msg.exec())
        QWidget::close();
}

void FormIndividuals::Search_menu()
{
    ppbinsert->hide();
    pladress->hide();
    pleadress->hide();
    plstatus->hide();
    plestatus->hide();
    pldescription->hide();
    pledescription->hide();
    plpatronymic->hide();
    plepatronymic->hide();
}



void FormIndividuals::AddRecord(QSqlDatabase db, QSqlTableModel *modeldb)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO Records ('Фамилия', 'Имя', 'Отчество', 'Телефон', 'Почта', 'Статус', 'Описание') "
                  "VALUES (:surname, :name, :patronymic, :number,:adress,:status, :description)");

    if(!plesurname->text().isEmpty() && !plename->text().isEmpty() && !plenumber->text().isEmpty())
    {
        query.bindValue( ":surname",plesurname->text());
        query.bindValue( ":name",plename->text());
        query.bindValue( ":patronymic",plepatronymic->text());
        query.bindValue( ":number",plenumber->text());
        query.bindValue( ":adress",pleadress->text());
        query.bindValue( ":status",plestatus->text());
        query.bindValue( ":description",pledescription->text());

        if(query.exec())
        {
            modeldb->select();
            Close_msg("Запись успешно добавлена");
        }
        else
           Close_msg("При записи произошла ошибка\n"+db.lastError().text());
    }
    else
        Close_msg("Поля для ввода фамилии, имени и номера обязательны");

}

void FormIndividuals::SearchRecord(QSqlTableModel *modeldb)
{
    if(!plename->text().isEmpty())
        modeldb->setFilter("Имя = '"+plename->text()+"'");

    else if(!plesurname->text().isEmpty())
        modeldb->setFilter("Фамилия = '"+plesurname->text()+"'");

    else if(!plenumber->text().isEmpty())
        modeldb->setFilter("Телефон = '"+plenumber->text()+"'");

    modeldb->select();
    Close_msg("Поиск завершен");
}


