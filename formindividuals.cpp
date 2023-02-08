#include "formindividuals.h"
#include "phonebook.h"

FormIndividuals::FormIndividuals(int i,QSqlDatabase db, QSqlTableModel *modeldb,QWidget *parent) :
    QWidget(parent)
{
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

    plesurname->setPlaceholderText(tr("Введите фамилию"));
    plename->setPlaceholderText(tr("Введите имя"));
    plepatronymic->setPlaceholderText(tr("Введите отчество"));
    plenumber->setPlaceholderText(tr("Введите номер телефона"));
    pleadress->setPlaceholderText(tr("Введите адрес почты"));
    plestatus->setPlaceholderText(tr("Введите статус"));
    pledescription->setPlaceholderText(tr("Введите описание"));

    ppbinsert = new QPushButton (tr("Добавить"));
    ppbedit = new QPushButton (tr("Редактировать"));
    ppbdelete = new QPushButton (tr("Удалить"));
    ppbsearch = new QPushButton (tr("Поиск"));

    QVBoxLayout  *pvbxlform = new QVBoxLayout();

    QGridLayout* pgrdLayout = new QGridLayout;
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
    pvbxlform->addWidget(ppbedit);
    pvbxlform->addWidget(ppbdelete);
    pvbxlform->addWidget(ppbsearch);
    switch(i)
    {
    case -1:
        ppbedit->hide();
        ppbdelete->hide();
        ppbsearch->hide();
        break;
    case 1:
        ppbinsert->hide();
        ppbedit->hide();
        ppbsearch->hide();
        break;
    case 0:
        ppbinsert->hide();
        ppbdelete->hide();
        ppbsearch->hide();
        break;
    case 2:
        plsurname->hide();
        plesurname->hide();
        plnumber->hide();
        plenumber->hide();
        Search_menu();
        break;
    case 3:
        plname->hide();
        plename->hide();
        plnumber->hide();
        plenumber->hide();
        Search_menu();
        break;
    case 4:
        plname->hide();
        plename->hide();
        plsurname->hide();
        plesurname->hide();
        Search_menu();
        break;
    }

    setLayout(pvbxlform);

    connect(ppbinsert,&QPushButton::clicked, [=](){ this->AddRecord(db,modeldb); });
    connect(ppbedit,&QPushButton::clicked, [=](){ this->EditRecord(db,modeldb); });
    connect(ppbdelete, &QPushButton::clicked, [=](){ this->DeleteRecord(db,modeldb); });
    connect(ppbsearch, &QPushButton::clicked, [=](){ this->SearchRecord(db,modeldb); });


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
    ppbedit->hide();
    ppbdelete->hide();
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

    query.prepare("INSERT INTO Records ('Фамилия', 'Имя', 'Отчество', 'Номер телефона', 'Почта', 'Статус', 'Описание') "
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
void FormIndividuals::EditRecord(QSqlDatabase db, QSqlTableModel *modeldb)// не работает
{
    QSqlQuery query(db);

    //query.prepare("UPDATE Records SET Фамилия = :surname, Имя = :name, Отчество = :patronymic, Номер телефона = :number, Почта = :adress, Статус = :status, Описание = :description WHERE Номер телефона = :number");
//    query.prepare("UPDATE Records SET Фамилия = :surname, Имя = :name, Отчество = :patronymic, Номер телефона = :number, "
//                  "Почта = :adress, Статус = :status, Описание = :description * FROM WHERE Фамилия = :surname AND Имя = :name");
//    query.prepare("INSERT INTO Records('Фамилия', 'Имя', 'Отчество', 'Номер телефона', 'Почта', 'Статус', 'Описание') VALUES (:surname, :name, :patronymic, :number,:adress,:status, :description) ON CONFLICT(Имя) DO UPDATE SET Фамилия = :surname, Отчество = :patronymic, Номер телефона = :number, "
//                  "Почта = :adress, Статус = :status, Описание = :description");
//    query.prepare("INSERT INTO Records ('Фамилия', 'Имя', 'Отчество', 'Номер телефона', 'Почта', 'Статус', 'Описание') "
//                  "VALUES (:surname, :name, :patronymic, :number,:adress,:status, :description)"
//                  "ON CONFLICT(Имя) DO UPDATE SET Фамилия=:'surname'");
//    query.bindValue(":surname",plesurname->text());
    query.bindValue(":name",plename->text());
    query.bindValue(":patronymic",plepatronymic->text());
    query.bindValue(":number",plenumber->text());
    query.bindValue(":adress",pleadress->text());
    query.bindValue(":status",plestatus->text());
    query.bindValue(":description",pledescription->text());

    query.exec();
    Close_msg("Данные записи обновлены");
    modeldb->select();

//    {
//        query.prepare("UPDATE Records SET Отчество = :patronymic,Номер телефона = :number, "
//                      "Почта = :adress, Статус = :status, Описание = :description WHERE Фамилия = surname AND Имя = :name");
//        if(query.exec())
//        {
//            Close_msg("Данные записи отредактированы");
//            modeldb->select();
//        }
//        else
//        {
//            Close_msg("Неуспешная попытка редактирования");
//             modeldb->select();}

//    }
}

void FormIndividuals::DeleteRecord(QSqlDatabase db, QSqlTableModel *modeldb)
{
    QSqlQuery query(db);
    int prev=query.numRowsAffected();

    if(!plenumber->text().isEmpty())
    {
        query.prepare("DELETE FROM Records WHERE Номер телефона = ? "); // не работает
        query.addBindValue(plenumber->text());
        query.exec();
    }
    else if (!plesurname->text().isEmpty() && !plename->text().isEmpty())
    {
        query.prepare("DELETE FROM Records WHERE Фамилия = ? AND Имя = ?");
        query.addBindValue( plesurname->text());
        query.addBindValue( plename->text());
        query.exec();
    }
    else
         Close_msg("Для удаления необходимо заполнить поле с номером телефона, либо поля с фамилией и именем");

    if(prev!=query.numRowsAffected())
    {
        modeldb->select();
        Close_msg("Запись удалена");
    }
    else
       Close_msg("Неуспешная попытка удаления записи\n");

}
void FormIndividuals::SearchRecord(QSqlDatabase db, QSqlTableModel *modeldb)
{
    if(!plename->text().isEmpty())
        modeldb->setFilter("Имя = '"+plename->text()+"'");
    else if(!plesurname->text().isEmpty())
        modeldb->setFilter("Фамилия = '"+plesurname->text()+"'");
    else
        modeldb->setFilter("Номер телефона = '"+plenumber->text()+"'");  // не работает
    modeldb->select();
    Close_msg("Поиск завершен");
}


