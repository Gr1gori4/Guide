#ifndef FORMENTITIES_H
#define FORMENTITIES_H
# define emit

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QValidator>

class FormEntities : public QWidget
{
    Q_OBJECT

public:
    explicit FormEntities(QWidget *parent = nullptr);
    ~FormEntities();
    QString OGRN;
    QList<QString> company;

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

    QRegExpValidator phone_validator;
    QRegExpValidator text_validator;
    QRegExpValidator fio_validator;
    QRegExpValidator mail_validator;

private slots:
    void AddRecord();
signals:
    void signalForm( QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString);

};

#endif // FORMENTITIES_H
