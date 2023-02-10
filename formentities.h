#ifndef FORMENTITIES_H
#define FORMENTITIES_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QXmlStreamReader>
#include <QValidator>


struct Company
    {
        QString title;
        QString director;
        QString phone_director;
        QString contact_person;
        QString phone_contact_person;
        QString adress;
        QString branch;
        QString description;
    };

class FormEntities : public QWidget
{
    Q_OBJECT

public:
    explicit FormEntities(QWidget *parent = nullptr);
    ~FormEntities();

private:
    QLineEdit *pletitle;
    QLineEdit *pledirector;
    QLineEdit *plephone_director;
    QLineEdit *plecontact_person;
    QLineEdit *plephone_contact_person;
    QLineEdit *pleOGRN;
    QLineEdit *pleadress;
    QLineEdit *plebranch;
    QLineEdit *pledescription;

    QLabel *pltitle;
    QLabel *pldirector;
    QLabel *plphone_director;
    QLabel *plcontact_person;
    QLabel *plphone_contact_person;
    QLabel *plOGRN;
    QLabel *pladress;
    QLabel *plbranch;
    QLabel *pldescription;

    QPushButton *ppbinsert;
    QPushButton *ppbedit;
    QPushButton *ppbdelete;
    QPushButton *ppbsearch;

    QRegExpValidator phone_validator;
    QRegExpValidator text_validator;
    QRegExpValidator fio_validator;
    QRegExpValidator mail_validator;



//    void Close_msg(QString);
//    void Search_menu();


//private slots:
//    void AddRecord(QSqlDatabase,QSqlTableModel *);
//    void EditRecord(QSqlDatabase,QSqlTableModel *);
//    void DeleteRecord(QSqlDatabase,QSqlTableModel *);
//    void SearchRecord(QSqlDatabase,QSqlTableModel *);


};

#endif // FORMENTITIES_H
