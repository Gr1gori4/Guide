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
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QtXml>
#include <QMap>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QHeaderView>
#include "formindividuals.h"
#include "formmapindividuals.h"
#include "formEntities.h"

class PhoneBook : public QWidget
{
    Q_OBJECT

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
    QTableView *ptvSQL;
    QTableWidget   *ptwXML;
    QLineEdit* pleSearch;
    QRadioButton *prbname;
    QRadioButton *prbsurname;
    QRadioButton *prbnumber;
    QRadioButton *prbtitle;
    QRadioButton *prbFIO;
    QRadioButton *prbOGRN;
    QRadioButton *prbbranch;

    QSqlDatabase db;
    QSqlTableModel *modeldb;

    void CreateMenu(/*QWidget *parent*/);
    void Close_msg(QString);
    void TraverseNode(const QDomNode&);
    void Print_Table();
    //QTableWidgetItem* MyTableWidgetFactory::createTableWidgetItem( const QString& text ) const;

    FormIndividuals *formAddIndividuals;
    FormMapIndividuals *formMapIndividuals;

    FormEntities *formEntities;

//    struct Company
//        {
//            QString title;
//            QString director;
//            QString phone_director;
//            QString contact_person;
//            QString phone_contact_person;
//            QString adress;
//            QString branch;
//            QString description;
//        };

    QMap<QString, Company> mapCompany;


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
