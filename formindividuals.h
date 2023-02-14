#ifndef FORMINDIVIDUALS_H
#define FORMINDIVIDUALS_H

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
#include <QSqlRecord>
#include <QDebug>
#include <QXmlStreamReader>
#include <QValidator>

namespace Ui {
class FormIndividuals;
}

class FormIndividuals : public QWidget
{
    Q_OBJECT

public:
    explicit FormIndividuals(int, QSqlDatabase, QSqlTableModel *,QModelIndexList, QWidget *parent = nullptr);
    ~FormIndividuals();

private:
    QLineEdit *plename;
    QLineEdit *plesurname;
    QLineEdit *plepatronymic;
    QLineEdit *plenumber;
    QLineEdit *pleadress;
    QLineEdit *plestatus;
    QLineEdit *pledescription;

    QLabel* plsurname;
    QLabel* plname;
    QLabel* plpatronymic;
    QLabel* plnumber;
    QLabel* pladress;
    QLabel* plstatus;
    QLabel* pldescription;

    QPushButton *ppbinsert;
    QPushButton *ppbedit;
    QPushButton *ppbdelete;
    QPushButton *ppbsearch;

    QRegExpValidator phone_validator;
    QRegExpValidator text_validator;
    QRegExpValidator mail_validator;

    void Close_msg(QString);
    void Search_menu();


private slots:
    void AddRecord(QSqlDatabase,QSqlTableModel *);
    void EditRecord(QSqlDatabase,QSqlTableModel *);
    void DeleteRecord(QSqlDatabase,QSqlTableModel *);
    void SearchRecord(QSqlTableModel *);

};

#endif // FORMINDIVIDUALS_H
