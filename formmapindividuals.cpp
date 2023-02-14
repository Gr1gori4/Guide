#include "formmapindividuals.h"
#include "phonebook.h"

FormMapIndividuals::FormMapIndividuals(QSqlDatabase db,QWidget *parent) :
    QWidget(parent)
{
    //resize(780, 300);
    ptable = new QTableView();
    ptable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ptable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


    modeldb= new QSqlTableModel(this,db);
    modeldb->setTable("Records");

    ptable->setModel(modeldb);

    auto* phbxlTop = new QVBoxLayout();
    phbxlTop->addWidget(ptable);

    auto *ppbforward = new QPushButton (tr("Вперед"));
    auto *ppbback = new QPushButton (tr("Назад"));

    auto* pvhbxlTop = new QHBoxLayout();
    pvhbxlTop->addStretch();
    pvhbxlTop->addWidget(ppbback);
    pvhbxlTop->addWidget(ppbforward);
    pvhbxlTop->addStretch();

    phbxlTop->addLayout(pvhbxlTop);

    setLayout(phbxlTop);

    QSqlQuery *query=new QSqlQuery(db);

    //========================================================// Число различных записей
//    query.prepare("SELECT COUNT(DISTINCT Статус) as count FROM Records");

//    query.exec();
//    query.next();
//    int count_status = query.value(0).toInt();
//    qDebug()<<count_status;
    //========================================================// Получение статусов

//     query->prepare("SELECT DISTINCT Статус  FROM Records");
//     if(query->exec())
//         while( query->next())
//            qDebug()<<query->value(0).toString();
    //===============================================================//
    query->prepare("SELECT DISTINCT Статус  FROM Records");
    query->exec();

    query->first();
    query->next();
    modeldb->setFilter("Статус = '"+query->value(0).toString()+"'");
    modeldb->select();
//    query.next();
//    QString str = query.value(5).toString();
//     //=====================================================/
//     modeldb->setFilter("Статус = '"+str+"'");
//     modeldb->select();

    connect(ppbforward,&QPushButton::clicked, [=](){ this->Forward(query); });
    connect(ppbback,&QPushButton::clicked, [=](){ this->Back(query); });
//    connect(ppbforward,SIGNAL(clicked()),SLOT(Forward(query)));
//    connect(ppbback,SIGNAL(clicked()),SLOT(Back(query)));
}

FormMapIndividuals::~FormMapIndividuals()
{

}

void FormMapIndividuals::Forward(QSqlQuery *query)
{
    if(query->next()) {
        modeldb->select();
        modeldb->setFilter("Статус = '"+query->value(0).toString()+"'");
    }


}

void FormMapIndividuals::Back(QSqlQuery *query)
{
    if(query->previous()){
        modeldb->select();
        modeldb->setFilter("Статус = '"+query->value(0).toString()+"'");
    }
}
