#ifndef FORMENTITIESEDIT_H
#define FORMENTITIESEDIT_H

#include <QWidget>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QXmlStreamReader>
#include <QValidator>
#include <QString>

class FormEntitiesEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FormEntitiesEdit(QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString,QWidget *parent = nullptr);
    ~FormEntitiesEdit();

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

    QPushButton *ppbedit;

    QRegExpValidator phone_validator;
    QRegExpValidator text_validator;
    QRegExpValidator fio_validator;
    QRegExpValidator mail_validator;

private slots:
    void EditRecord();
signals:
    void signalForm( QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString );
};

#endif // FORMENTITIESEDIT_H
