#include "formmapindividuals.h"
#include "phonebook.h"


FormMapIndividuals::FormMapIndividuals(QSqlDatabase db,QWidget *parent) :
    QWidget(parent)
{
    ptable = new QTableView();
    ptable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    modeldb= new QSqlTableModel(this,db);
    modeldb->setTable("Records");
    modeldb->select();

    ptable->setModel(modeldb);

    QHBoxLayout* phbxlTop = new QHBoxLayout();
    phbxlTop->addWidget(ptable);


    QPushButton *ppbforward = new QPushButton (tr("Вперед"));
    QPushButton *ppbback = new QPushButton (tr("Назад"));

    QVBoxLayout* pvhbxlTop = new QVBoxLayout();
    pvhbxlTop->addStretch();
    pvhbxlTop->addWidget(ppbforward);
    pvhbxlTop->addWidget(ppbback);
    pvhbxlTop->addStretch();

    phbxlTop->addLayout(pvhbxlTop);

    setLayout(phbxlTop);

    QSqlQuery query(db);

    //========================================================// Число различных записей
    query.prepare("SELECT COUNT(DISTINCT Статус) as count FROM Records");

    query.exec();
    query.next();
    int count_status = query.value(0).toInt();
    qDebug()<<count_status;
    //========================================================// Получение статусов

//     query.prepare("SELECT DISTINCT Статус  FROM Records");
//     if(query.exec())
//         while( query.next())
//            qDebug()<<query.value(0).toString();
    //===============================================================//
    query.prepare("SELECT DISTINCT Статус  FROM Records");
    query.exec();
    query.next();
    QString str = query.value(5).toString();
     //=====================================================/
     modeldb->setFilter("Статус = '"+str+"'");
     modeldb->select();
}

FormMapIndividuals::~FormMapIndividuals()
{

}
