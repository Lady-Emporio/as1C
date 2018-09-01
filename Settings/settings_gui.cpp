#include "settings_gui.h"

Settings_gui::Settings_gui(QWidget *parent) : QWidget(parent)
{
makeGui();
setValue();
}

void Settings_gui::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    //********** start add params ******************
    QHBoxLayout *row1=new QHBoxLayout(this);
    mainLayout->addLayout(row1);
    row1->addWidget(new QLabel("path/to/db",this));
    QLineEdit *pathToDB=new QLineEdit(this);
    edits.insert("path/to/db",pathToDB);
    row1->addWidget(pathToDB);


    QHBoxLayout *row2=new QHBoxLayout(this);
    mainLayout->addLayout(row2);
    row2->addWidget(new QLabel("app/image",this));
    QLineEdit *pathImage=new QLineEdit(this);
    edits.insert("app/image",pathImage);
    row2->addWidget(pathImage);

    //********** end add params ********************
    QHBoxLayout *lastRow=new QHBoxLayout(this);
    mainLayout->addLayout(lastRow);
    QPushButton *commitButton=new QPushButton("Commit",this);
    QPushButton *clearButton=new QPushButton("clear",this);
    lastRow->addWidget(commitButton);
    lastRow->addWidget(clearButton);

    QPushButton *dialogdb=new QPushButton("Choose file",this);
    row1->addWidget(dialogdb);
    QPushButton *dialogImageApp=new QPushButton("Choose file",this);
    row2->addWidget(dialogImageApp);

    connect(dialogdb, SIGNAL(clicked()), this, SLOT(choosedb()));
    connect(dialogImageApp, SIGNAL(clicked()), this, SLOT(chooseImageApp()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(setValue()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(writeInSettingsValue()));
}


void Settings_gui::setValue()
{
    for(QString key:Settings::keys()){
        edits.value(key)->setText(Settings::get(key));
    }
}

void Settings_gui::choosedb()
{
    QString str = QFileDialog::getOpenFileName(this,"Choose db","./");
    edits.value("path/to/db")->setText(str);
}

void Settings_gui::chooseImageApp()
{
    QString str = QFileDialog::getOpenFileName(this,"Choose db","./");
    edits.value("app/image")->setText(str);
}

void Settings_gui::writeInSettingsValue()
{
    QStringList keys=edits.keys();
    QMap<QString,QString>needAdd;
    for(QString key:keys){
        needAdd.insert(key,edits.value(key)->text());
    }
    Settings::set(needAdd);
}
