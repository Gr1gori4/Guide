#include "phonebook.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QWidget(parent)
{
    CreateMenu(/*this*/);

    QVBoxLayout* pvbxlMain = new QVBoxLayout();
    pvbxlMain->setContentsMargins(10, 10, 10, 10);
    pvbxlMain->setSpacing(10);

    QGroupBox *pgbTop = new QGroupBox();
    QGroupBox *pgbMedium = new QGroupBox();
    pgbLower = new QGroupBox();

    pvbxlMain->addWidget(pgbTop);
    pvbxlMain->addWidget(pgbMedium);
    pvbxlMain->addWidget(pgbLower);

    //pgbTop
    plState = new QLabel(tr("Справочник готов к работе"));
    plDirIndividual = new QLabel(tr("Справочник физических лиц"));
    plDirEntitie = new QLabel(tr("Справочник юридических лиц"));

    QHBoxLayout* phbxlTop = new QHBoxLayout();
    phbxlTop->addStretch();
    phbxlTop->addWidget(plState);
    phbxlTop->addWidget(plDirIndividual);
    phbxlTop->addWidget(plDirEntitie);
    phbxlTop->addStretch();

    plDirIndividual->hide();
    plDirEntitie->hide();

    pgbTop->setLayout(phbxlTop);

    //pgbMedium
    QHBoxLayout  *phbxMedium = new QHBoxLayout();

    ptable = new QTableView();
    ptable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ptable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);


    ptable1= new QTableWidget();
    ptable1->setRowCount(3);
    ptable1->setColumnCount(9);

    QStringList columns = { "Название", "ФИО директора", "Телефон директора", "Контактное лицо","Телефон контанктного лица","ОГРН","Адрес","Отрасль","Описание" };
    ptable1->setHorizontalHeaderLabels(columns);

    ptable1->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирование ячеек

    for(int i=0;i<ptable1->columnCount();i++)
        ptable1->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch); //Выравнивание по всей ширине виджета


    ppbIndividuals = new QPushButton (tr("Физические лица"));
    ppbLegalEntities = new QPushButton (tr("Юридические лица"));

    phbxMedium->addWidget(ptable);
    phbxMedium->addWidget(ptable1);
    phbxMedium->addWidget(ppbIndividuals);
    phbxMedium->addWidget(ppbLegalEntities);

    pgbMedium->setLayout(phbxMedium);

    ptable->hide();
    ptable1->hide();

    //pgbLower
    QHBoxLayout  *phbxlLower = new QHBoxLayout();

    QGroupBox *pgbSearch = new QGroupBox();

    QPushButton *ppbAddrecord = new QPushButton (tr("Добавить запись"));
    QPushButton *ppbEditrecord = new QPushButton (tr("Редактировать запись"));
    QPushButton *ppbDeleterecord = new QPushButton (tr("Удалить запись"));

    QVBoxLayout  *pvbxlEditing = new QVBoxLayout();

    pvbxlEditing->addWidget(ppbAddrecord);
    pvbxlEditing->addWidget(ppbEditrecord);
    pvbxlEditing->addWidget(ppbDeleterecord);

    phbxlLower->addLayout(pvbxlEditing);

    QHBoxLayout  *phbxSearch = new QHBoxLayout();

    QVBoxLayout  *pvbxlSearchRadioButton = new QVBoxLayout();
    QVBoxLayout  *pvbxlSearchInput = new QVBoxLayout();

    prbname = new QRadioButton (tr("По имени"));
    prbsurname = new QRadioButton (tr("По фамилии"));
    prbnumber = new QRadioButton (tr("По номеру телефона"));
    prbtitle = new QRadioButton (tr("По названию"));
    prbFIO = new QRadioButton (tr("По ФИО директора"));
    prbOGRN = new QRadioButton (tr("По ОГРН"));
    prbbranch = new QRadioButton (tr("По отрасли"));

    pvbxlSearchRadioButton->addWidget(prbname);
    pvbxlSearchRadioButton->addWidget(prbsurname);
    pvbxlSearchRadioButton->addWidget(prbnumber);
    pvbxlSearchRadioButton->addWidget(prbtitle);
    pvbxlSearchRadioButton->addWidget(prbFIO);
    pvbxlSearchRadioButton->addWidget(prbOGRN);
    pvbxlSearchRadioButton->addWidget(prbbranch);

    QLabel *plinput= new QLabel(tr("Введите критерий поиска"));
    plename = new QLineEdit();
    QPushButton *ppbsearch = new QPushButton (tr("Искать"));
    QPushButton *ppbbshow = new QPushButton (tr("Показать все записи"));
    QPushButton *ppbmap = new QPushButton (tr("Показать записи картой"));

    QHBoxLayout  *phbxSearchInput = new QHBoxLayout();

    phbxSearchInput->addWidget(ppbsearch);
    phbxSearchInput->addWidget(ppbbshow);
    phbxSearchInput->addWidget(ppbmap);

    pvbxlSearchInput->addWidget(plinput);
    pvbxlSearchInput->addWidget(plename);
    pvbxlSearchInput->addLayout(phbxSearchInput);

    phbxSearch->addLayout(pvbxlSearchRadioButton);
    phbxSearch->addLayout(pvbxlSearchInput);

    pgbSearch->setLayout(phbxSearch);
    phbxlLower->addWidget(pgbSearch);

    QPushButton *ppbbexit = new QPushButton (tr("Выход"));
    QPushButton *ppbbgomain = new QPushButton (tr("На главную"));

    QVBoxLayout  *pvbxlbuttons = new QVBoxLayout();

    pvbxlbuttons->addWidget(ppbbgomain);
    pvbxlbuttons->addWidget(ppbbexit);
    phbxlLower->addLayout(pvbxlbuttons);

    pgbLower->setLayout(phbxlLower);

    pgbLower->hide();

    setLayout(pvbxlMain);

    connect(ppbAddrecord,SIGNAL(clicked()),SLOT(AddRecord()));
    connect(ppbEditrecord,SIGNAL(clicked()),SLOT(EditRecord()));
    connect(ppbDeleterecord,SIGNAL(clicked()),SLOT(DeleteRecord()));
    connect(prbname,SIGNAL(clicked()),SLOT(SortName()));
    connect(prbsurname,SIGNAL(clicked()),SLOT(SortSurname()));
    connect(prbnumber,SIGNAL(clicked()),SLOT(SortNumber()));
    connect(ppbsearch,SIGNAL(clicked()),SLOT(Search()));
    connect(ppbbshow,SIGNAL(clicked()),SLOT(Show()));
    connect(ppbmap,SIGNAL(clicked()),SLOT(Map()));
    connect(ppbbexit,SIGNAL(clicked()),SLOT(Exit()));
    connect(ppbbgomain,SIGNAL(clicked()),SLOT(GoMain()));
    connect(ppbIndividuals,SIGNAL(clicked()),SLOT(OpenIndividuals()));
    connect(ppbLegalEntities,SIGNAL(clicked()),SLOT(OpenLegalEntities()));

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/d.andronychev/study/Qt/PhoneBookV2/db/PhoneRecordIndividuals.db");
    if(!db.open())
    {
        Close_msg("Ошибка при открытии базы данных");
        qDebug() << db.lastError().text();
    }
    modeldb= new QSqlTableModel(this,db);
    modeldb->setTable("Records");
    modeldb->select();

//    modeldb->setEditStrategy(QSqlTableModel::OnFieldChange);


    QFile file("C:/Users/d.andronychev/study/Qt/Guide/Entities.xml") ;
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader sr(&file);
        do {
        sr.readNext();
        qDebug () << sr.tokenString ()<<sr.name ()<<sr.text();
        }while (!sr.atEnd());
        if (sr.hasError())
            qDebug() << "Error:" << sr.errorString();
        file.close() ;
    }
    else
        Close_msg("Ошибка открытия xml");






}

PhoneBook::~PhoneBook()
{

}

void PhoneBook::CreateMenu(/*QWidget *parent*/)
{
    QMenuBar *menuBar= new QMenuBar(this);
    QMenu * pmDirIndividual = menuBar->addMenu(tr("Справочник физических лиц"));
    QMenu * paSearchRecord = new QMenu(tr("Поиск"));
    QMenu * paDisplayRecord = new QMenu(tr("Отобразить все записи"));
    QMenu * pmDirEntitie= menuBar->addMenu(tr("Справочник юридических лиц"));
    QMenu * paSearchRecordEntitie = new QMenu(tr("Поиск"));
    QMenu * paDisplayRecordEntitie = new QMenu(tr("Отобразить все записи"));
    QAction * paExit = menuBar->addAction(tr("Выход"));

    menuBar->show();
    connect(paExit,SIGNAL(triggered()),SLOT(Exit()));

    QAction *paAddRecord = new QAction(tr("Добавить запись"), this);
    QAction *paEditRecord = new QAction(tr("Редактировать запись"), this);
    QAction *paDeleteRecord = new QAction(tr("Удалить запись"), this);
    QAction *paSearchRecordName = new QAction(tr("По имени"), this);
    QAction *paSearchRecordSurname = new QAction(tr("По фамилии"), this);
    QAction *paSearchRecordNumber = new QAction(tr("По номеру"), this);
    QAction *paDisplayRecordList = new QAction(tr("Списком"), this);
    QAction *paSearcheRecordMap = new QAction(tr("Картой"), this);

    paSearchRecord->addAction(paSearchRecordName);
    paSearchRecord->addAction(paSearchRecordSurname);
    paSearchRecord->addAction(paSearchRecordNumber);

    paDisplayRecord->addAction(paDisplayRecordList);
    paDisplayRecord->addAction(paSearcheRecordMap);

    pmDirIndividual->addAction(paAddRecord);
    pmDirIndividual->addAction(paEditRecord);
    pmDirIndividual->addAction(paDeleteRecord);
    pmDirIndividual->addMenu(paSearchRecord);
    pmDirIndividual->addMenu(paDisplayRecord);

    connect(paAddRecord,SIGNAL(triggered()),SLOT(AddRecordIndividuals()));
    connect(paEditRecord,SIGNAL(triggered()),SLOT(EditRecordIndividuals()));
    connect(paDeleteRecord,SIGNAL(triggered()),SLOT(DeleteRecordIndividuals()));
    connect(paSearchRecordName,SIGNAL(triggered()),SLOT(SearchRecordNameIndividuals()));
    connect(paSearchRecordSurname,SIGNAL(triggered()),SLOT(SearchRecordSurnameIndividuals()));
    connect(paSearchRecordNumber,SIGNAL(triggered()),SLOT(SearchRecordNumberIndividuals()));
    connect(paDisplayRecordList,SIGNAL(triggered()),SLOT(DisplayRecordListIndividuals()));
    connect(paSearcheRecordMap,SIGNAL(triggered()),SLOT(SearcheRecordMapIndividuals()));

    QAction *paAddRecordEntitie = new QAction(tr("Добавить запись"), this);
    QAction *paEditRecordEntitie = new QAction(tr("Редактировать запись"), this);
    QAction *paDeleteRecordEntitie = new QAction(tr("Удалить запись"), this);
    QAction *paSearchRecordTitle = new QAction(tr("По названию"), this);
    QAction *paSearchRecordDirector = new QAction(tr("По ФИО директора"), this);
    QAction *paSearchRecordOGRN = new QAction(tr("По ОГРН"), this);
    QAction *paSearchRecordBranch = new QAction(tr("По названию отрасли"), this);
    QAction *paDisplayRecordListEntitie = new QAction(tr("Списком"), this);
    QAction *paSearcheRecordMapEntitie = new QAction(tr("Картой"), this);

    paSearchRecordEntitie->addAction(paSearchRecordTitle);
    paSearchRecordEntitie->addAction(paSearchRecordDirector);
    paSearchRecordEntitie->addAction(paSearchRecordOGRN);
    paSearchRecordEntitie->addAction(paSearchRecordBranch);

    paDisplayRecordEntitie->addAction(paDisplayRecordListEntitie);
    paDisplayRecordEntitie->addAction(paSearcheRecordMapEntitie);

    pmDirEntitie->addAction(paAddRecordEntitie);
    pmDirEntitie->addAction(paEditRecordEntitie);
    pmDirEntitie->addAction(paDeleteRecordEntitie);
    pmDirEntitie->addMenu(paSearchRecordEntitie);
    pmDirEntitie->addMenu(paDisplayRecordEntitie);

    connect(paAddRecordEntitie,SIGNAL(triggered()),SLOT(AddRecordEntitie()));
    connect(paEditRecordEntitie,SIGNAL(triggered()),SLOT(EditRecordEntitie()));
    connect(paDeleteRecordEntitie,SIGNAL(triggered()),SLOT(DeleteRecordEntitie()));
    connect(paSearchRecordTitle,SIGNAL(triggered()),SLOT(SearchRecordTitle()));
    connect(paSearchRecordDirector,SIGNAL(triggered()),SLOT(SearchRecordDirector()));
    connect(paSearchRecordOGRN,SIGNAL(triggered()),SLOT(SearchRecordOGRN()));
    connect(paSearchRecordBranch,SIGNAL(triggered()),SLOT(SearchRecordBranch()));
    connect(paDisplayRecordListEntitie,SIGNAL(triggered()),SLOT(DisplayRecordListEntitie()));
    connect(paSearcheRecordMapEntitie,SIGNAL(triggered()),SLOT(SearcheRecordMapEntitie()));
}

void PhoneBook::Close_msg(QString str)
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}

//void PhoneBook::TraverseNode(const QDomNode& node)
//{
//    QDomNode domNode = node.firstChild();
//    while ( ! domNode. isNull () ) {
//        if(domNode.isElement()) {
//            QDomElement domElement = domNode.toElement();
//            if (!domElement.isNull()) {
//                if( domElement. tagName ( ) == "company" ) {
//                        qDebug () << "Attr: "
//                        << domElement. attribute ("number" , "");
//                }
//                else {
//                    qDebug () << "Название: " << domElement.tagName()
//                              << "\tText: "<< domElement.text();
//                }
//            }
//        }
//        TraverseNode(domNode);
//        domNode=domNode.nextSibling();
//    }
//}

void PhoneBook::AddRecordIndividuals()
{
    formAddIndividuals = new FormIndividuals(-1,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::EditRecordIndividuals()
{
    formAddIndividuals = new FormIndividuals(0,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::DeleteRecordIndividuals()
{
    formAddIndividuals = new FormIndividuals(1,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNameIndividuals()
{
    OpenIndividuals();
    formAddIndividuals = new FormIndividuals(2,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordSurnameIndividuals()
{
    OpenIndividuals();
    formAddIndividuals = new FormIndividuals(3,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNumberIndividuals()
{
    OpenIndividuals();
    formAddIndividuals = new FormIndividuals(4,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::DisplayRecordListIndividuals()
{
    OpenIndividuals();
    modeldb->setTable("Records");
    modeldb->select();
}

void PhoneBook::SearcheRecordMapIndividuals()
{

}

void PhoneBook::AddRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::EditRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::DeleteRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::SearchRecordTitle()
{

}

void PhoneBook::SearchRecordDirector()
{

}

void PhoneBook::SearchRecordOGRN()
{

}

void PhoneBook::SearchRecordBranch()
{

}

void PhoneBook::DisplayRecordListEntitie()
{

}

void PhoneBook::SearcheRecordMapEntitie()
{

}

void PhoneBook::Exit()
{
    close();
}

void PhoneBook::GoMain()
{
    pgbLower->hide();
    plDirIndividual->hide();
    ptable->hide();
    ptable1->hide();
    plDirEntitie->hide();

    plState->show();
    ppbIndividuals->show();
    ppbLegalEntities->show();

}

void PhoneBook::AddRecord()
{
    if(plDirIndividual->isVisible())
        AddRecordIndividuals();
    else
        AddRecordEntitie();
}

void PhoneBook::EditRecord()
{
    if(plDirIndividual->isVisible())
        EditRecordIndividuals();
    else
        EditRecordEntitie();
    //QModelIndex idIndex = ptable->model()->selectedIndexes()->first();
    //qDebug() << " value "<< ptable->model()->data(ptable->model()->index(index.row(),0)).toInt();

}

void PhoneBook::DeleteRecord()
{
    if(plDirIndividual->isVisible())
        DeleteRecordIndividuals();
    else
        DeleteRecordEntitie();
}

void PhoneBook::SortName()
{
    modeldb->setSort(1, Qt::AscendingOrder);
    modeldb->select();
}

void PhoneBook::SortSurname()
{
    modeldb->setSort(0, Qt::AscendingOrder);
    modeldb->select();
}

void PhoneBook::SortNumber()
{
    modeldb->setSort(3, Qt::AscendingOrder);
    modeldb->select();
}

void PhoneBook::Search()
{
    if(prbname->isChecked())
        modeldb->setFilter("Имя = '"+plename->text()+"'");
    else if(prbsurname->isChecked())
        modeldb->setFilter("Фамилия = '"+plename->text()+"'");
    else
        modeldb->setFilter("Номер телефона = '"+plename->text()+"'"); // не работает
    modeldb->select();
}

void PhoneBook::Show()
{
    modeldb->setTable("Records");
    modeldb->select();
}

void PhoneBook::Map()
{
    formMapIndividuals = new FormMapIndividuals(db);
    formMapIndividuals->show();
}

void PhoneBook::OpenIndividuals()
{
    pgbLower->show();
    plDirIndividual->show();
    plState->hide();
    plDirEntitie->hide();
    ppbIndividuals->hide();
    ppbLegalEntities->hide();
    ptable->show();
    ptable1->hide();
    prbname->show();
    prbsurname->show();
    prbnumber->show();
    prbtitle->hide();
    prbFIO->hide();
    prbOGRN->hide();
    prbbranch->hide();
    ptable->setModel(modeldb);
}

void PhoneBook::OpenLegalEntities()
{
    pgbLower->show();
    ptable1->show();
    ptable->hide();
    plDirIndividual->hide();
    plState->hide();
    plDirEntitie->show();
    ppbIndividuals->hide();
    ppbLegalEntities->hide();
    prbname->hide();
    prbsurname->hide();
    prbnumber->hide();
    prbtitle->show();
    prbFIO->show();
    prbOGRN->show();
    prbbranch->show();


    QString OGRN="1221313";
    Company company;
    company.title="Название 1";
    company.director="Директор 1";
    company.phone_director="Телефон директора 1";
    company.contact_person="Контактный человек 1";
    company.phone_contact_person="Телефон контакного 1";
    company.adress="Адрес 1";
    company.branch="Отсрасль 1";
    company.description="Описание 1";

    QString OGRN1="1221314";
    Company company1;
    company1.title="Название 2";
    company1.director="Директор 2";
    company1.phone_director="Телефон директора 2";
    company1.contact_person="Контактный человек 2";
    company1.phone_contact_person="Телефон контакного 2";
    company1.adress="Адрес 2";
    company1.branch="Отсрасль 2";
    company1.description="Описание 2";

    QString OGRN3="1221315";
    Company company3;
    company3.title="Название 3";
    company3.director="Директор 3";
    company3.phone_director="Телефон директора 3";
    company3.contact_person="Контактный человек 3";
    company3.phone_contact_person="Телефон контакного 3";
    company3.adress="Адрес 3";
    company3.branch="Отсрасль 3";
    company3.description="Описание 3";

    mapCompany.insert(OGRN,company);
    //qDebug()<<mapCompany.size();
    mapCompany.insert(OGRN1,company1);//нужно создать модель
    //qDebug()<<mapCompany.size();
    mapCompany.insert(OGRN3,company3);//нужно создать модель
    //qDebug()<<mapCompany.size();

//    QMapIterator<QString, Company> j(mapCompany);
//    while (j.hasNext()) {
//     j.next();
//           qDebug()<<j.key();
//           qDebug()<<j.value().title;
//           qDebug()<<j.value().director;
//           qDebug()<<j.value().phone_director;
//           qDebug()<<j.value().contact_person;
//           qDebug()<<j.value().phone_contact_person;
//           qDebug()<<j.value().adress;
//           qDebug()<<j.value().branch;
//           qDebug()<<j.value().description;
//        }

    //QStandardItemModel* model = new QStandardItemModel();

    ptable1->clearContents();
    ptable1->setRowCount(0);

    QMapIterator<QString, Company> i (mapCompany);
    while (i.hasNext())
    {
        i.next();
        ptable1->setRowCount(ptable1->rowCount() + 1);

        QTableWidgetItem *newItem;
        ptable1->setItem(ptable1->rowCount() - 1, 0, new QTableWidgetItem(i.value().title));

        ptable1->setItem(ptable1->rowCount() - 1, 1, new QTableWidgetItem(i.value().director));

        ptable1->setItem(ptable1->rowCount() - 1, 2, new QTableWidgetItem(i.value().phone_director));

        ptable1->setItem(ptable1->rowCount() - 1, 3, new QTableWidgetItem(i.value().contact_person));

        ptable1->setItem(ptable1->rowCount() - 1, 4, new QTableWidgetItem(i.value().phone_contact_person));

        ptable1->setItem(ptable1->rowCount() - 1, 5, new QTableWidgetItem(i.key()));

        ptable1->setItem(ptable1->rowCount() - 1, 6, new QTableWidgetItem(i.value().adress));

        ptable1->setItem(ptable1->rowCount() - 1, 7, new QTableWidgetItem(i.value().branch));

        ptable1->setItem(ptable1->rowCount() - 1, 8, new QTableWidgetItem(i.value().description));

        //ptable1->show();

    }
        // устанавливаем модели данных в таблицы
        //ptable1->setModel(model);

}
