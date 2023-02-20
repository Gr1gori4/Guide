#include "formindividualsedit.h"
#include "phonebook.h"

FormindividualsEdit::FormindividualsEdit(int work_variant,QSqlDatabase database, QSqlTableModel *modeldatabase,QModelIndexList modelIndex,
                                         QWidget *parent) :
    QWidget(parent),
    phone_validator(QRegExp("^\\+7\\d{10}$")),
    text_validator(QRegExp("^[А-Я][а-я]{1,15}$")),
    mail_validator(QRegExp("^\\w+@[a-zA-Z]{1,}\\.[a-zA-Z]{1,3}$"))

{
    setWindowTitle("Редактирование");

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

    ppbedit = new QPushButton (tr("Редактировать"));
    ppbdelete = new QPushButton (tr("Удалить"));

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
    pvbxlform->addWidget(ppbedit);
    pvbxlform->addWidget(ppbdelete);

    setLayout(pvbxlform);

    if(work_variant)
    {
        ppbedit->hide();
        plesurname->setEnabled(false);
        plename->setEnabled(false);
        plepatronymic->setEnabled(false);
        plenumber->setEnabled(false);
        pleadress->setEnabled(false);
        plestatus->setEnabled(false);
        pledescription->setEnabled(false);
        PrintInLineEdit(modelIndex.begin()->row(),modeldatabase);
    }
    else {
        ppbdelete->hide();
        PrintInLineEdit(modelIndex.begin()->row(),modeldatabase);
    }

    connect(ppbedit,&QPushButton::clicked, [=](){ this->EditRecord(database,modeldatabase); });
    connect(ppbdelete, &QPushButton::clicked, [=](){ this->DeleteRecord(database,modeldatabase); });

}

FormindividualsEdit::~FormindividualsEdit()
{

}

void FormindividualsEdit::Close_msg(QString str)
{
    QMessageBox msg;
    msg.setText(str);
    if(msg.exec())
        QWidget::close();
}

void FormindividualsEdit::PrintInLineEdit(int row_count,QSqlTableModel *modeldb)
{
    plesurname->setText((new QVariant(modeldb->data(modeldb->index(row_count,0))))->toString());
    plename->setText((new QVariant(modeldb->data(modeldb->index(row_count,1))))->toString());
    plepatronymic->setText((new QVariant(modeldb->data(modeldb->index(row_count,2))))->toString());
    plenumber->setText((new QVariant(modeldb->data(modeldb->index(row_count,3))))->toString());
    pleadress->setText((new QVariant(modeldb->data(modeldb->index(row_count,4))))->toString());
    plestatus->setText((new QVariant(modeldb->data(modeldb->index(row_count,5))))->toString());
    pledescription->setText((new QVariant(modeldb->data(modeldb->index(row_count,6))))->toString());
}

void FormindividualsEdit::EditRecord(QSqlDatabase database, QSqlTableModel *modeldatabase)
{
    QSqlQuery query(database);

    query.prepare("UPDATE Records SET 'Фамилия' = \""+plesurname->text()+"\", 'Имя' = \""+plename->text()+"\", "
                  "'Отчество' = \""+plepatronymic->text()+"\",  'Телефон' = \""+plenumber->text()+"\", 'Почта' = \""
                   ""+pleadress->text()+"\", 'Статус' = \""+plestatus->text()+"\", 'Описание' = \""+pledescription->text()+
                  "\"  WHERE Имя =\""+plename->text()+"\"AND Фамилия =\""+plesurname->text()+"\"" );

    query.exec();

    if(query.first()!=0)
    {
        modeldatabase->select();
        Close_msg("Данные записи обновлены");
    }
    else

    {
        query.prepare("UPDATE Records SET 'Фамилия' = \""+plesurname->text()+"\", 'Имя' = \""+plename->text()+"\", 'Отчество' = \""
                      ""+plepatronymic->text()+"\",  'Телефон' = \""+plenumber->text()+"\", 'Почта' = \""+pleadress->text()+
                      "\", 'Статус' = \""+plestatus->text()+"\", 'Описание' = \""+pledescription->text()+"\"  WHERE Телефон =\""
                      +plenumber->text()+"\"" );

        query.exec();
        modeldatabase->select();
        if(!query.first())
            Close_msg("Данные записи обновлены");
        else
            Close_msg("Данные записи необновлены");
    }
}

void FormindividualsEdit::DeleteRecord(QSqlDatabase database, QSqlTableModel *modeldatabase)
{
    QSqlQuery query(database);
    int prev=query.numRowsAffected();

    query.prepare("DELETE FROM Records WHERE Телефон = ? ");
    query.addBindValue(plenumber->text());
    query.exec();

    if(prev!=query.numRowsAffected())
    {
        modeldatabase->select();
        Close_msg("Запись удалена");
    }
    else
        Close_msg("Неуспешная попытка удаления записи\n");
}

