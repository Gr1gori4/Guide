#include "phonebook.h"
#include "formentities.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QWidget(parent)
{
    CreateMenu();

    auto * pvbxlMain = new QVBoxLayout();
    pvbxlMain->setContentsMargins(10, 10, 10, 10);
    pvbxlMain->setSpacing(10);

    auto  *pgbTop = new QGroupBox();
    auto  *pgbMedium = new QGroupBox();
    pgbLower = new QGroupBox();

    pvbxlMain->addWidget(pgbTop);
    pvbxlMain->addWidget(pgbMedium);
    pvbxlMain->addWidget(pgbLower);

    setLayout(pvbxlMain);

    //====================================================//
    //Компановка pgbTop

    plState = new QLabel(tr("Справочник готов к работе"));
    plDirIndividual = new QLabel(tr("Справочник физических лиц"));
    plDirEntitie = new QLabel(tr("Справочник юридических лиц"));

    plState->setStyleSheet("* {font-size: 20px;}");
    plDirIndividual->setStyleSheet("* {font-size: 20px;}");
    plDirEntitie->setStyleSheet("* {font-size: 20px;}");

    auto * phbxlTop = new QHBoxLayout();
    phbxlTop->addStretch();
    phbxlTop->addWidget(plState);
    phbxlTop->addWidget(plDirIndividual);
    phbxlTop->addWidget(plDirEntitie);
    phbxlTop->addStretch();

    plDirIndividual->hide();
    plDirEntitie->hide();

    pgbTop->setLayout(phbxlTop);
    //====================================================//


    //====================================================//
    //Компановка pgbMedium
    auto   *phbxMedium = new QHBoxLayout();
    auto   *pvbxMedium = new QVBoxLayout();


    ptvSQL = new QTableView();
    ptwXML= new QTableWidget();

    ppbIndividuals = new QPushButton (tr("Физические лица"));
    ppbLegalEntities = new QPushButton (tr("Юридические лица"));

    ppbIndividuals->setStyleSheet("* {font-size: 20px;}");
    ppbLegalEntities->setStyleSheet("* {font-size: 20px;}");

    ppbforward = new QPushButton (tr("Вперед"));
    ppbback = new QPushButton (tr("Назад"));

    auto* pvhbxlTop = new QHBoxLayout();
    pvhbxlTop->addStretch();
    pvhbxlTop->addWidget(ppbback);
    pvhbxlTop->addWidget(ppbforward);
    pvhbxlTop->addStretch();

    phbxMedium->addWidget(ptvSQL);
    phbxMedium->addWidget(ptwXML);
    phbxMedium->addWidget(ppbIndividuals);
    phbxMedium->addWidget(ppbLegalEntities);

    pvbxMedium->addLayout(phbxMedium);
    pvbxMedium->addLayout(pvhbxlTop);

    pgbMedium->setLayout(pvbxMedium);

    ptvSQL->hide();
    ptwXML->hide();
    ppbforward->hide();
    ppbback->hide();
    //====================================================//


    //====================================================//
    //Компановка pgbLower
    auto *phbxlLower = new QHBoxLayout();

    auto *pgbSearch = new QGroupBox();

    auto *ppbAddrecord = new QPushButton (tr("Добавить запись"));
    auto *ppbEditrecord = new QPushButton (tr("Редактировать запись"));
    auto *ppbDeleterecord = new QPushButton (tr("Удалить запись"));

    auto *pvbxlEditing = new QVBoxLayout();

    pvbxlEditing->addWidget(ppbAddrecord);
    pvbxlEditing->addWidget(ppbEditrecord);
    pvbxlEditing->addWidget(ppbDeleterecord);

    phbxlLower->addLayout(pvbxlEditing);

    auto *phbxSearch = new QHBoxLayout();

    auto *pvbxlSearchRadioButton = new QVBoxLayout();
    auto *pvbxlSearchInput = new QVBoxLayout();

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

    auto  *plinput= new QLabel(tr("Введите критерий поиска"));
    pleSearch = new QLineEdit();
    auto  *ppbsearch = new QPushButton (tr("Искать"));
    auto  *ppbbshow = new QPushButton (tr("Показать все записи"));
    ppbmap = new QPushButton (tr("Показать записи картой"));

    auto   *phbxSearchInput = new QHBoxLayout();

    phbxSearchInput->addWidget(ppbsearch);
    phbxSearchInput->addWidget(ppbbshow);
    phbxSearchInput->addWidget(ppbmap);

    pvbxlSearchInput->addWidget(plinput);
    pvbxlSearchInput->addWidget(pleSearch);
    pvbxlSearchInput->addLayout(phbxSearchInput);

    phbxSearch->addLayout(pvbxlSearchRadioButton);
    phbxSearch->addLayout(pvbxlSearchInput);

    pgbSearch->setLayout(phbxSearch);
    phbxlLower->addWidget(pgbSearch);

    auto *ppbbexit = new QPushButton (tr("Выход"));
    auto *ppbbgomain = new QPushButton (tr("На главную"));

    auto *pvbxlbuttons = new QVBoxLayout();

    pvbxlbuttons->addWidget(ppbbgomain);
    pvbxlbuttons->addWidget(ppbbexit);
    phbxlLower->addLayout(pvbxlbuttons);

    pgbLower->setLayout(phbxlLower);

    pgbLower->hide();
    //====================================================//


    //====================================================//

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

    connect(ptwXML,SIGNAL(cellClicked(int,int)),this,SLOT(CellClickedTable(int,int)));

    //====================================================//


    //====================================================//
    // Настройка таблицы ptvSQL
    ptvSQL->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ptvSQL->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ptvSQL->setItemDelegate(new QSqlRelationalDelegate(this));
    ptvSQL->setSelectionBehavior(QAbstractItemView::SelectRows);
    ptvSQL->resizeColumnsToContents();
    //====================================================//


    //====================================================//
    // Настройка таблицы ptwXML
    ptwXML->setColumnCount(9);
    QStringList columns = { "Название", "ФИО директора", "Телефон директора", "Контактное лицо","Телефон контанктного лица","ОГРН","Адрес","Отрасль","Описание" };
    ptwXML->setHorizontalHeaderLabels(columns);
    ptwXML->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ptwXML->columnCount();i++)
        ptwXML->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    //====================================================//


    //====================================================//
    // Подключение базы данных
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/d.andronychev/study/Qt/PhoneBookV2/db/PhoneRecordIndividuals.db");
    if(!database.open())
    {
        Message("Ошибка при открытии базы данных");
        qDebug() << database.lastError().text();
    }
    modeldatabase= new QSqlTableModel(this,database);
    modeldatabase->setTable("Records");
    ptvSQL->setModel(modeldatabase);
    modeldatabase->select();
    //====================================================//


    //====================================================//
    // Подключение файла XML и запись его в QMap
    QDomDocument domDoc;
    QFile file("C:/Users/d.andronychev/study/Qt/Guide/Entities.xml") ;
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            TraverseNode(domElement);
        }
        file. close ();
    }

}

PhoneBook::~PhoneBook()
{

}

void PhoneBook::CreateMenu()
{
    auto *menuBar= new QMenuBar(this);
    auto * pmDirIndividual = menuBar->addMenu(tr("Справочник физических лиц"));
    auto * paSearchRecord = new QMenu(tr("Поиск"));
    auto * paDisplayRecord = new QMenu(tr("Отобразить все записи"));
    auto * pmDirEntitie= menuBar->addMenu(tr("Справочник юридических лиц"));
    auto * paSearchRecordEntitie = new QMenu(tr("Поиск"));
    auto * paDisplayRecordEntitie = new QMenu(tr("Отобразить все записи"));
    auto * paExit = menuBar->addAction(tr("Выход"));

    menuBar->show();
    connect(paExit,SIGNAL(triggered()),SLOT(Exit()));

    //====================================================//
    // Подменю справочника физических лиц

    auto *paAddRecord = new QAction(tr("Добавить запись"), this);
    auto *paEditRecord = new QAction(tr("Редактировать запись"), this);
    auto *paDeleteRecord = new QAction(tr("Удалить запись"), this);
    auto *paSearchRecordName = new QAction(tr("По имени"), this);
    auto *paSearchRecordSurname = new QAction(tr("По фамилии"), this);
    auto *paSearchRecordNumber = new QAction(tr("По номеру"), this);
    auto *paDisplayRecordList = new QAction(tr("Списком"), this);
    auto *paSearcheRecordMap = new QAction(tr("Картой"), this);

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
    connect(paSearcheRecordMap,SIGNAL(triggered()),SLOT(Map()));

    //====================================================//


    //====================================================//
    // Подменю справочника юридических лиц

    auto *paAddRecordEntitie = new QAction(tr("Добавить запись"), this);
    auto *paSearchRecordTitle = new QAction(tr("По названию"), this);
    auto *paSearchRecordDirector = new QAction(tr("По ФИО директора"), this);
    auto *paSearchRecordOGRN = new QAction(tr("По ОГРН"), this);
    auto *paSearchRecordBranch = new QAction(tr("По названию отрасли"), this);
    auto *paDisplayRecordListEntitie = new QAction(tr("Списком"), this);

    paSearchRecordEntitie->addAction(paSearchRecordTitle);
    paSearchRecordEntitie->addAction(paSearchRecordDirector);
    paSearchRecordEntitie->addAction(paSearchRecordOGRN);
    paSearchRecordEntitie->addAction(paSearchRecordBranch);

    paDisplayRecordEntitie->addAction(paDisplayRecordListEntitie);

    pmDirEntitie->addAction(paAddRecordEntitie);
    pmDirEntitie->addMenu(paSearchRecordEntitie);
    pmDirEntitie->addMenu(paDisplayRecordEntitie);

    connect(paAddRecordEntitie,SIGNAL(triggered()),SLOT(AddRecordEntitie()));
    connect(paSearchRecordTitle,SIGNAL(triggered()),SLOT(SearchRecordTitle()));
    connect(paSearchRecordDirector,SIGNAL(triggered()),SLOT(SearchRecordDirector()));
    connect(paSearchRecordOGRN,SIGNAL(triggered()),SLOT(SearchRecordOGRN()));
    connect(paSearchRecordBranch,SIGNAL(triggered()),SLOT(SearchRecordBranch()));
    connect(paDisplayRecordListEntitie,SIGNAL(triggered()),SLOT(DisplayRecordListEntitie()));
}
    //====================================================//


    //====================================================//
    // Функции подменю справочника физических лиц

void PhoneBook::AddRecordIndividuals()
{
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(0,database,modeldatabase);
    formAddIndividuals->show();
}

void PhoneBook::EditRecordIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    if(!modelIndex.isEmpty())
    {
        formindividualsEdit = new FormindividualsEdit(0,database,modeldatabase,modelIndex);
        formindividualsEdit->show();
    }
    else
    {
        Message("Выберите запись в таблице для редактирования");
    }
}

void PhoneBook::DeleteRecordIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    if(!modelIndex.isEmpty())
    {
        formindividualsEdit = new FormindividualsEdit(1,database,modeldatabase,modelIndex);
        formindividualsEdit->show();
    }
    else
    {
        Message("Выберите запись в таблице для удаления");
    }
}

void PhoneBook::SearchRecordNameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(1,database,modeldatabase);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordSurnameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(2,database,modeldatabase);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNumberIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(3,database,modeldatabase);
    formAddIndividuals->show();
}


void PhoneBook::DisplayRecordListIndividuals()
{
    OpenIndividuals();
    modeldatabase->setTable("Records");
    modeldatabase->select();
}
    //====================================================//


    //====================================================//
    // Функции подменю справочника физических лиц

void PhoneBook::AddRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities();

    connect(formEntities,SIGNAL(signalForm(QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString)),
            this, SLOT(dataForm(QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString)));

    formEntities->show();

}

void PhoneBook::SearchRecordTitle()
{
    OpenLegalEntities();
    if(!pleSearch->text().isEmpty())
    {
        ptwXML->clearContents();
        ptwXML->setRowCount(0);
        QMapIterator<QString, Company> iteratorMap (mapCompany);

        while (iteratorMap.hasNext())
        {
            iteratorMap.next();
            if(iteratorMap.value().title==pleSearch->text())
                PrintRecordMap(iteratorMap);
        }
        if(ptwXML->rowCount()==0)
            Message("Запись не найдена");
    }
    else
    {
        pleSearch->setPlaceholderText("Введите слово для поиска");
    }
}

void PhoneBook::SearchRecordDirector()
{
    OpenLegalEntities();
    if(!pleSearch->text().isEmpty())
    {
        ptwXML->clearContents();
        ptwXML->setRowCount(0);
        QMapIterator<QString, Company> iteratorMap (mapCompany);

        while (iteratorMap.hasNext())
        {
            iteratorMap.next();
            if(iteratorMap.value().director==pleSearch->text())
                PrintRecordMap(iteratorMap);
        }
        if(ptwXML->rowCount()==0)
            Message("Запись не найдена");
    }
    else
    {
        pleSearch->setPlaceholderText("Введите слово для поиска");
    }
}

void PhoneBook::SearchRecordOGRN()
{
    OpenLegalEntities();
    if(!pleSearch->text().isEmpty())
    {
        ptwXML->clearContents();
        ptwXML->setRowCount(0);
        QMapIterator<QString, Company> iteratorMap (mapCompany);

        while (iteratorMap.hasNext())
        {
            iteratorMap.next();
            if(iteratorMap.key()==pleSearch->text())
                PrintRecordMap(iteratorMap);
        }
        if(ptwXML->rowCount()==0)
            Message("Запись не найдена");
    }
    else
    {
        pleSearch->setPlaceholderText("Введите слово для поиска");
    }
}

void PhoneBook::SearchRecordBranch()
{
    OpenLegalEntities();
    if(!pleSearch->text().isEmpty())
    {
        ptwXML->clearContents();
        ptwXML->setRowCount(0);
        QMapIterator<QString, Company> iteratorMap (mapCompany);

        while (iteratorMap.hasNext())
        {
            iteratorMap.next();
            if(iteratorMap.value().branch==pleSearch->text())
                PrintRecordMap(iteratorMap);
        }
        if(ptwXML->rowCount()==0)
            Message("Запись не найдена");
    }
    else {
        pleSearch->setPlaceholderText("Введите слово для поиска");
    }
}



void PhoneBook::DisplayRecordListEntitie()
{
    OpenLegalEntities();
    Print_Table();
}

//====================================================//


//====================================================//
// Функции в pgbLower

void PhoneBook::Exit()
{
    WriteFailXML();
    close();
}

void PhoneBook::GoMain()
{
    pgbLower->hide();
    plDirIndividual->hide();
    ptvSQL->hide();
    ptwXML->hide();
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
    modeldatabase->setSort(1, Qt::AscendingOrder);
    modeldatabase->select();
}

void PhoneBook::SortSurname()
{
    modeldatabase->setSort(0, Qt::AscendingOrder);
    modeldatabase->select();
}

void PhoneBook::SortNumber()
{
    modeldatabase->setSort(3, Qt::AscendingOrder);
    modeldatabase->select();
}

void PhoneBook::Search()
{
    if(plDirIndividual->isVisible())
        SearchIndividuals();
    else
        SearchEntities();
}

void PhoneBook::Show()
{
    if(plDirIndividual->isVisible())
    {
        modeldatabase->setTable("Records");
        modeldatabase->select();
    }
    else
    {
        ppbforward->hide();
        ppbback->hide();
        Print_Table();
    }
}

void PhoneBook::Map()
{
    formMapIndividuals = new FormMapIndividuals(database);
    formMapIndividuals->show();

}
void PhoneBook::EditRecordEntitie()
{
    OpenLegalEntities();
    if(numberRowSelectedPtwXML>-1)
    {
        formEntitiesEdit = new FormEntitiesEdit(ptwXML->item(numberRowSelectedPtwXML,0)->text(),ptwXML->item(numberRowSelectedPtwXML,1)->text(),
                                                ptwXML->item(numberRowSelectedPtwXML,2)->text(),ptwXML->item(numberRowSelectedPtwXML,3)->text(),
                                                ptwXML->item(numberRowSelectedPtwXML,4)->text(),ptwXML->item(numberRowSelectedPtwXML,5)->text(),
                                                ptwXML->item(numberRowSelectedPtwXML,6)->text(),ptwXML->item(numberRowSelectedPtwXML,7)->text(),
                                                ptwXML->item(numberRowSelectedPtwXML,8)->text());

        connect(formEntitiesEdit,SIGNAL(signalForm(QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString)),
                this, SLOT(dataForm(QString,QString , QString ,QString ,QString ,QString ,QString ,QString , QString)));

        formEntitiesEdit->show();

        QMapIterator<QString, Company> iterator_map (mapCompany);
        mapCompany.remove(ptwXML->item(numberRowSelectedPtwXML,5)->text());
    }
    else
        Message("Выберите строку в таблице для редактирования");
}

void PhoneBook::DeleteRecordEntitie()
{
    OpenLegalEntities();
    if(numberRowSelectedPtwXML>-1)
    {
        if(mapCompany.remove(ptwXML->item(numberRowSelectedPtwXML,5)->text()))
        {
            Print_Table();
            Message("Запись успешно удалена");
        }
        else
            Message("Запись не удалось удалить");
    }
    else
        Message("Выберите строку в таблице для удаления");
}

void PhoneBook::WriteFailXML()
{
    QFile file("C:/Users/d.andronychev/study/Qt/Guide/Entities.xml") ;
    int numberCompany = 1;
    QMapIterator<QString, Company> iterator_map (mapCompany);
    if(file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("entities");

        while (iterator_map.hasNext())
        {
            iterator_map.next();
            xmlWriter.writeStartElement("company");
            xmlWriter.writeAttribute("number",QString::number(numberCompany));


            xmlWriter.writeStartElement("title");
            xmlWriter.writeCharacters(iterator_map.value().title);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("director");
            xmlWriter.writeCharacters(iterator_map.value().director);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("phone_director");
            xmlWriter.writeCharacters(iterator_map.value().phone_director);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("contact_person");
            xmlWriter.writeCharacters(iterator_map.value().contact_person);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("phone_contact_person");
            xmlWriter.writeCharacters(iterator_map.value().contact_person);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("OGRN");
            xmlWriter.writeCharacters(iterator_map.key());
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("adress");
            xmlWriter.writeCharacters(iterator_map.value().adress);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("branch");
            xmlWriter.writeCharacters(iterator_map.value().branch);
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("description");
            xmlWriter.writeCharacters(iterator_map.value().description);
            xmlWriter.writeEndElement();

            xmlWriter.writeEndElement();
            numberCompany++;
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}
//====================================================//


//====================================================//
// Функции смены отображения справочников

void PhoneBook::OpenIndividuals()
{
    pgbLower->show();
    plDirIndividual->show();
    plState->hide();
    plDirEntitie->hide();
    ppbIndividuals->hide();
    ppbLegalEntities->hide();
    ptvSQL->show();
    ptwXML->hide();
    prbname->show();
    prbsurname->show();
    prbnumber->show();
    prbtitle->hide();
    prbFIO->hide();
    prbOGRN->hide();
    prbbranch->hide();
    ppbmap->show();
}

void PhoneBook::OpenLegalEntities()
{
    pgbLower->show();
    ptwXML->show();
    ptvSQL->hide();
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
    ppbmap->hide();
    Print_Table();
}

void PhoneBook::CellClickedTable(int row, int column)
{
    numberRowSelectedPtwXML=row;
}

void PhoneBook::dataForm(QString title,QString director, QString phone_director,QString contact_person,QString phone_contact_person,QString OGRN,QString adress,QString branch, QString description)
{
    Company *company= new Company();
    company->title=title;
    company->director=director;
    company->phone_director=phone_director;
    company->contact_person=contact_person;
    company->phone_contact_person=phone_contact_person;
    company->adress=adress;
    company->branch=branch;
    company->description=description;
    mapCompany.insert(OGRN,*company);
    QMapIterator<QString, Company> iterator_map (mapCompany);
    Print_Table();
    Message("Запись успешно добавлена");

}
//====================================================//


//====================================================//
// Вспомогательные функции


void PhoneBook::Message(QString notificationText)
{
    QMessageBox msg;
    msg.setText(notificationText);
    msg.exec();
}

// Запись из файла XML в QMap
void PhoneBook::TraverseNode(const QDomNode& node)
{
    QString *OGRN = new QString();
    Company *company = new Company();
    QDomNode domNode = node.firstChild();

    while (!domNode.isNull() )
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull())
            {
                if( domElement.tagName () == "company" ){
                    OGRN = new QString();
                    company = new Company();}

                else if(domElement.tagName() == "title"){
                    company->title=domElement.text();}

                else if(domElement.tagName() == "director"){
                    company->director=domElement.text();}

                else if(domElement.tagName() == "phone_director"){
                    company->phone_director=domElement.text();}

                else if(domElement.tagName() == "contact_person"){
                    company->contact_person=domElement.text();}

                else if(domElement.tagName() == "phone_contact_person"){
                    company->phone_contact_person=domElement.text();}

                else if(domElement.tagName() == "OGRN"){
                    *OGRN=domElement.text();}

                else if(domElement.tagName() == "adress"){
                    company->adress=domElement.text();}

                else if(domElement.tagName() == "branch"){
                    company->branch=domElement.text();}

                else if(domElement.tagName() == "description"){
                    company->description=domElement.text();
                    mapCompany.insert(*OGRN,*company);}
            }
        }
        TraverseNode(domNode);
        domNode=domNode.nextSibling();
    }
}

// Печать всех записей QMap
void PhoneBook::Print_Table()
{
    ptwXML->clearContents();
    ptwXML->setRowCount(0);

    QMapIterator<QString, Company> iterator_map (mapCompany);
    while (iterator_map.hasNext())
    {
        iterator_map.next();
        ptwXML->setRowCount(ptwXML->rowCount() + 1);

        ptwXML->setItem(ptwXML->rowCount() - 1, 0, new QTableWidgetItem(iterator_map.value().title));

        ptwXML->setItem(ptwXML->rowCount() - 1, 1, new QTableWidgetItem(iterator_map.value().director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 2, new QTableWidgetItem(iterator_map.value().phone_director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 3, new QTableWidgetItem(iterator_map.value().contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 4, new QTableWidgetItem(iterator_map.value().phone_contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 5, new QTableWidgetItem(iterator_map.key()));

        ptwXML->setItem(ptwXML->rowCount() - 1, 6, new QTableWidgetItem(iterator_map.value().adress));

        ptwXML->setItem(ptwXML->rowCount() - 1, 7, new QTableWidgetItem(iterator_map.value().branch));

        ptwXML->setItem(ptwXML->rowCount() - 1, 8, new QTableWidgetItem(iterator_map.value().description));
    }
    for(int i=0;i<ptwXML->columnCount();i++)
        ptwXML->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void PhoneBook::SearchIndividuals()
{
    if(prbname->isChecked())
        modeldatabase->setFilter("Имя = '"+pleSearch->text()+"'");

    else if(prbsurname->isChecked())
        modeldatabase->setFilter("Фамилия = '"+pleSearch->text()+"'");

    else if(prbnumber->isChecked())
        modeldatabase->setFilter("Телефон = '"+pleSearch->text()+"'");
    else
    {
        Message("Выберите критерий поиска");
    }

    modeldatabase->select();
}

void PhoneBook::SearchEntities()
{
    if(prbtitle->isChecked())
        SearchRecordTitle();

    else if (prbFIO->isChecked())
        SearchRecordDirector();

    else if (prbOGRN->isChecked())
        SearchRecordOGRN();

    else if (prbbranch->isChecked())
        SearchRecordBranch();
}

void PhoneBook::PrintRecordMap(QMapIterator<QString, PhoneBook::Company> iteratorMap)
{
    ptwXML->setRowCount(ptwXML->rowCount() + 1);

    ptwXML->setItem(ptwXML->rowCount() - 1, 0, new QTableWidgetItem(iteratorMap.value().title));

    ptwXML->setItem(ptwXML->rowCount() - 1, 1, new QTableWidgetItem(iteratorMap.value().director));

    ptwXML->setItem(ptwXML->rowCount() - 1, 2, new QTableWidgetItem(iteratorMap.value().phone_director));

    ptwXML->setItem(ptwXML->rowCount() - 1, 3, new QTableWidgetItem(iteratorMap.value().contact_person));

    ptwXML->setItem(ptwXML->rowCount() - 1, 4, new QTableWidgetItem(iteratorMap.value().phone_contact_person));

    ptwXML->setItem(ptwXML->rowCount() - 1, 5, new QTableWidgetItem(iteratorMap.key()));

    ptwXML->setItem(ptwXML->rowCount() - 1, 6, new QTableWidgetItem(iteratorMap.value().adress));

    ptwXML->setItem(ptwXML->rowCount() - 1, 7, new QTableWidgetItem(iteratorMap.value().branch));

    ptwXML->setItem(ptwXML->rowCount() - 1, 8, new QTableWidgetItem(iteratorMap.value().description));
}
