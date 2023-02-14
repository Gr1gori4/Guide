#ifndef FORMINDIVIDUALSEDIT_H
#define FORMINDIVIDUALSEDIT_H

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


class FormindividualsEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FormindividualsEdit(int, QSqlDatabase, QSqlTableModel *,QModelIndexList, QWidget *parent = nullptr);
    ~FormindividualsEdit();

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

    QPushButton *ppbedit;
    QPushButton *ppbdelete;

    QRegExpValidator phone_validator;
    QRegExpValidator text_validator;
    QRegExpValidator mail_validator;

    void Close_msg(QString);
    void PrintInLineEdit(int,QSqlTableModel *);


private slots:
    void EditRecord(QSqlDatabase,QSqlTableModel *);
    void DeleteRecord(QSqlDatabase,QSqlTableModel *);
};

#endif // FORMINDIVIDUALSEDIT_H
