#include "cuegenerator.h"
#include "ui_cuegenerator.h"

CUEGenerator::CUEGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CUEGenerator)
{
    ui->setupUi(this);
    btnGroupType=new QButtonGroup(this);
    btnGroupType->addButton(ui->flacButton,0);
    btnGroupType->addButton(ui->apeButton,1);
    btnGroupType->addButton(ui->wavButton,2);

    connect(ui->flacButton,SIGNAL(clicked(bool)),this,SLOT(on_RadioButton_clicked()));
    connect(ui->apeButton,SIGNAL(clicked(bool)),this,SLOT(on_RadioButton_clicked()));
    connect(ui->wavButton,SIGNAL(clicked(bool)),this,SLOT(on_RadioButton_clicked()));

    fileType=FLAC;
    ui->statusBar->showMessage("Welcole! This software is developed by wuyhthu.");
}

CUEGenerator::~CUEGenerator()
{
    delete ui;
}

void CUEGenerator::on_RadioButton_clicked()
{
    fileType=btnGroupType->checkedId();
}

void CUEGenerator::on_generate_clicked()
{
    if (ui->dirText->text().isEmpty())
    {
        ui->statusBar->showMessage(QString("Please Set target Dir"));
        return ;
    }
    if (ui->albumText->text().isEmpty())
    {
        ui->statusBar->showMessage(QString("Please input the album name"));
        return ;
    }
    QDir pwd;
    pwd.setCurrent(ui->dirText->text());
    QStringList typelist;
    if (fileType==FLAC)
        typelist<<"*.flac";
    else if(fileType==APE)
        typelist<<"*.ape";
    else
        typelist<<"*.wav";

    pwd.setNameFilters(typelist);
    QStringList fileList=pwd.entryList(typelist,QDir::Files,QDir::Name);

    QString filename(ui->albumText->text());
    filename.append(".cue");
    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ui->statusBar->showMessage("Open failed.");
        return;
    }
    QTextStream txtOutput(&f);
    txtOutput<<"PERFORMER \""<<ui->artistText->text()<<"\""<<endl;
    txtOutput<<"TITLE \""<<ui->albumText->text()<<"\""<<endl;

    for(int i=0;i<fileList.count();i++)
    {
        txtOutput<<"FILE \""<<fileList.at(i)<<"\" WAVE"<<endl;

//        txtOutput.setFieldWidth(2);
//        txtOutput.setPadChar('0');
//        txtOutput<<i+1;
//        txtOutput.setFieldWidth(0);
//        txtOutput<<" AUDIO"<<endl;
        QString filename=fileList.at(i);
        QString number=filename.section(".",0,0);
        filename.remove(QRegExp("[0-9]+\."));
        filename.remove(QRegExp("^ "));
        if (fileType==FLAC)
            filename.remove(QRegExp("\.flac"));
        else if(fileType==APE)
            filename.remove(QRegExp("\.ape"));
        else
            filename.remove(QRegExp("\.wav"));

        txtOutput<<"  TRACK "<<number<<" AUDIO"<<endl;
        txtOutput<<"    TITLE \""<<filename<<"\""<<endl;
        txtOutput<<"    PERFORMER \""<<ui->artistText->text()<<"\""<<endl;
        txtOutput<<"    INDEX 01 00:00:00"<<endl;
    }
    f.close();
    ui->statusBar->showMessage(QString("Succeed"));
}

void CUEGenerator::on_open_clicked()
{
    QString dirPath=QFileDialog::getExistingDirectory(this,tr("Select Dir"),QString(""),QFileDialog::ShowDirsOnly);
    ui->dirText->setText(dirPath);
}
