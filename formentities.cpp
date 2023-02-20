#include "formentities.h"
#include "phonebook.h"


FormEntities::FormEntities(QWidget *parent) :
    QWidget(parent),
    phone_validator(QRegExp("^\\+7\\d{10}$")),
    text_validator(QRegExp("^[А-Яа-я]{1,}$")),
    fio_validator(QRegExp("^[А-Я][а-я]{1,}\\s[А-Я][а-я]{1,}\\s[А-Я][а-я]{1,}$")),
    mail_validator(QRegExp("^\\w+@[a-zA-Z]{1,}\\.[a-zA-Z]{1,3}$"))
{
    setWindowTitle("Добавление");

    pletitle = new QLineEdit ();
    pledirector = new QLineEdit ();
    plephone_director = new QLineEdit ();
    plecontact_person = new QLineEdit ();
    plephone_contact_person = new QLineEdit ();
    pleOGRN = new QLineEdit ();
    pleadress = new QLineEdit ();
    plebranch = new QLineEdit ();
    pledescription = new QLineEdit ();

    pltitle = new QLabel(tr("Название:"));
    pldirector = new QLabel(tr("ФИО директора:"));
    plphone_director = new QLabel(tr("Телефон директора:"));
    plcontact_person = new QLabel(tr("ФИО заместителя директора:"));
    plphone_contact_person = new QLabel(tr("Телефон заместителя директора:"));
    plOGRN = new QLabel(tr("Номер ОГРН:"));
    pladress = new QLabel(tr("Адрес:"));
    plbranch = new QLabel(tr("Отрасль:"));
    pldescription = new QLabel(tr("Описание:"));

    pletitle->setPlaceholderText(tr("Название компании"));
    pledirector->setPlaceholderText(tr("Фамилия Имя Отчество"));
    plephone_director->setPlaceholderText(tr("+7__________"));
    plecontact_person->setPlaceholderText(tr("Фамилия Имя Отчество"));
    plephone_contact_person->setPlaceholderText(tr("+7__________"));
    pleOGRN->setPlaceholderText(tr("_____________"));
    pleadress->setPlaceholderText(tr("г.__,ул.___, д.__"));
    plebranch->setPlaceholderText(tr("Отрасль"));
    pledescription->setPlaceholderText(tr("Описание"));

    pletitle->setValidator(&text_validator);
    plebranch->setValidator(&text_validator);
    pledirector->setValidator(&fio_validator);
    plecontact_person->setValidator(&fio_validator);
    plephone_director->setValidator(&phone_validator);
    plephone_contact_person->setValidator(&phone_validator);
    pleadress->setValidator(&mail_validator);

    ppbinsert = new QPushButton (tr("Добавить"));

    auto *pvbxlform = new QVBoxLayout();

    auto *pgrdLayout = new QGridLayout;
    pgrdLayout->setContentsMargins(5, 5, 5, 5);
    pgrdLayout->setSpacing(15);

    pgrdLayout->addWidget(pltitle, 0, 0);
    pgrdLayout->addWidget(pletitle, 0, 1) ;
    pgrdLayout->addWidget(pldirector, 1, 0);
    pgrdLayout->addWidget(pledirector, 1, 1);
    pgrdLayout->addWidget(plphone_director, 2, 0);
    pgrdLayout->addWidget(plephone_director, 2, 1);
    pgrdLayout->addWidget(plcontact_person, 3, 0);
    pgrdLayout->addWidget(plecontact_person, 3, 1) ;
    pgrdLayout->addWidget(plphone_contact_person, 4, 0);
    pgrdLayout->addWidget(plephone_contact_person, 4, 1);
    pgrdLayout->addWidget(plOGRN, 5, 0);
    pgrdLayout->addWidget(pleOGRN, 5, 1) ;
    pgrdLayout->addWidget(pladress, 6, 0);
    pgrdLayout->addWidget(pleadress, 6, 1) ;
    pgrdLayout->addWidget(plbranch, 7, 0);
    pgrdLayout->addWidget(plebranch, 7, 1) ;
    pgrdLayout->addWidget(pldescription, 8, 0);
    pgrdLayout->addWidget(pledescription, 8, 1) ;

    pvbxlform->addLayout(pgrdLayout);
    pvbxlform->addWidget(ppbinsert);

    setLayout(pvbxlform);

    connect(ppbinsert,SIGNAL(clicked()),SLOT(AddRecord()));
}

FormEntities::~FormEntities()
{

}

void FormEntities::AddRecord()
{
    emit signalForm(pletitle->text(), pledirector->text(),plephone_director->text(),plecontact_person->text(),plephone_contact_person->text(),pleOGRN->text(),pleadress->text(),plebranch->text(),pledescription->text());
    close();
}


