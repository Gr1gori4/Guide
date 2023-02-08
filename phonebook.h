#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableView>
#include <QtXml>
#include "formindividuals.h"
#include "formmapindividuals.h"

class PhoneBook : public QWidget
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = 0);
    ~PhoneBook();
private:
    QGroupBox *pgbLower;
    QLabel *plDirIndividual;
    QLabel *plState;
    QLabel *plDirEntitie;
    QPushButton *ppbIndividuals;
    QPushButton *ppbLegalEntities;
    QTableView *ptable;
    QLineEdit* plename;
    QRadioButton *prbname;
    QRadioButton *prbsurname;
    QRadioButton *prbnumber;

    QSqlDatabase db;
    QSqlTableModel *modeldb;

    void CreateMenu(/*QWidget *parent*/);
    void Close_msg(QString);
    void TraverseNode(const QDomNode&);

    FormIndividuals *formAddIndividuals;
    FormMapIndividuals *formMapIndividuals;


private slots:
    void AddRecordIndividuals();
    void EditRecordIndividuals();
    void DeleteRecordIndividuals();
    void SearchRecordNameIndividuals();
    void SearchRecordSurnameIndividuals();
    void SearchRecordNumberIndividuals();
    void DisplayRecordListIndividuals();
    void SearcheRecordMapIndividuals();

    void AddRecordEntitie();
    void EditRecordEntitie();
    void DeleteRecordEntitie();
    void SearchRecordTitle();
    void SearchRecordDirector();
    void SearchRecordOGRN();
    void SearchRecordBranch();
    void DisplayRecordListEntitie();
    void SearcheRecordMapEntitie();

    void Exit();
    void GoMain();

    void AddRecord();
    void EditRecord();
    void DeleteRecord();
    void SortName();
    void SortSurname();
    void SortNumber();
    void Search();
    void Show();
    void Map();
    void OpenIndividuals();
    void OpenLegalEntities();
};

#endif // PHONEBOOK_H
