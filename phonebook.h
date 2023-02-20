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
#include <QHash>
#include "formindividuals.h"
#include "formindividualsedit.h"
#include "formmapindividuals.h"
#include "formentities.h"
#include "formentitiesedit.h"

class PhoneBook : public QWidget
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = 0);
    ~PhoneBook();
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
private:
    QGroupBox *pgbLower;
    QLabel *plDirIndividual;
    QLabel *plState;
    QLabel *plDirEntitie;
    QPushButton *ppbIndividuals;
    QPushButton *ppbLegalEntities;
    QPushButton *ppbforward;
    QPushButton *ppbback;
    QPushButton  *ppbmap;
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

    QSqlDatabase database;
    QSqlTableModel *modeldatabase;

    void CreateMenu();
    void Message(QString);
    void TraverseNode(const QDomNode&);
    void Print_Table();
    void SearchIndividuals();
    void SearchEntities();
    void PrintRecordMap(QMapIterator<QString, Company>);
    void EditRecordEntitie();
    void DeleteRecordEntitie();
    void WriteFailXML();



    FormIndividuals *formAddIndividuals;
    FormMapIndividuals *formMapIndividuals;
    FormindividualsEdit *formindividualsEdit;
    FormEntities *formEntities;
    FormEntitiesEdit *formEntitiesEdit;

    QList<QString>::const_iterator it;

    QMap<QString, Company> mapCompany;

    int numberRowSelectedPtwXML=-1;


private slots:
    void AddRecordIndividuals();
    void EditRecordIndividuals();
    void DeleteRecordIndividuals();
    void SearchRecordNameIndividuals();
    void SearchRecordSurnameIndividuals();
    void SearchRecordNumberIndividuals();
    void DisplayRecordListIndividuals();

    void AddRecordEntitie();
    void SearchRecordTitle();
    void SearchRecordDirector();
    void SearchRecordOGRN();
    void SearchRecordBranch();
    void DisplayRecordListEntitie();

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

    void CellClickedTable(int row,int column);

public slots:
    void dataForm(QString ,QString , QString ,QString ,QString ,QString ,QString ,QString , QString );

};

#endif // PHONEBOOK_H
