#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    fileDialog(new QFileDialog(this)),
    process(new QProcess(this)),
    initFile(new QFile(this)),
    out(new QTextStream(stdout))
{
    ui->setupUi(this);
    init_paths();
    ui->groupBox->setVisible(false);
    QObject::connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(on_process_readReady()));
    QObject::connect(process,SIGNAL(started()),this,SLOT(on_process_started()));
    QObject::connect(process, SIGNAL(finished(int)),this,SLOT(on_process_finished()));
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::init_paths()
{
    if(!init_file()){
    ui->ln_GccPath->setText(gccPath);
    ui->ln_WinDeploy->setText(winDeployPath);

    }
    return true;
}

void Widget::on_pb_Run_clicked()
{
    QString program = ui->ln_WinDeploy->text();
    QStringList arguments;
    arguments << ui->ln_ExecPath->text();
    process->start(program, arguments);
}

void Widget::on_process_started()
{
    ui->pb_Run->setEnabled(false);
    ui->logWindow->appendPlainText(tr("Starting..."));
}

void Widget::on_process_finished()
{
    QMessageBox::information(this,"All files processed", "OK!");
    ui->pb_Run->setEnabled(true);
    ui->logWindow->appendPlainText(tr("Finished!"));
}

void Widget::on_process_readReady()
{
    ui->logWindow->appendPlainText(QString::fromLocal8Bit(process->readAllStandardOutput()));
}
void Widget::on_pb_WinDeploy_clicked()
{
    QStringList selected;

    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("windeployqt.exe");
    fileDialog->show();

    if(fileDialog->exec()){
        selected = fileDialog->selectedFiles();
        ui->ln_WinDeploy->setText(selected.at(0));
    }
}

void Widget::on_pb_GccPath_clicked()
{
    QStringList selected;

    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::DirectoryOnly);
    fileDialog->setDirectory(gccPath);
    fileDialog->show();

    if(fileDialog->exec()){
        selected = fileDialog->selectedFiles();
        ui->ln_GccPath->setText(selected.at(0));
    }

}

void Widget::on_pb_ExecPath_clicked()
{
    QStringList selected;

    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::ExistingFile);

    fileDialog->setNameFilter("*.exe");
    fileDialog->show();

    if(fileDialog->exec()){
        selected = fileDialog->selectedFiles();
        ui->ln_ExecPath->setText(selected.at(0));
    }
}

bool Widget::init_file()
{

    QTextStream out(initFile);
    initFile->setFileName(configFile);
    if(!initFile->exists()){
        initFile->open(QIODevice::ReadWrite | QIODevice::Text);
        out << gccPath << endl << winDeployPath << endl;
        initFile->close();
        return false;
    }
    else{
        initFile->open(QIODevice::ReadWrite | QIODevice::Text);
        ui->ln_GccPath->setText(out.readLine());
        ui->ln_WinDeploy->setText(out.readLine());
        initFile->close();
    }
    return true;
}

void Widget::on_pb_SaveConfig_clicked()
{
    gccPath = ui->ln_GccPath->text();
    winDeployPath = ui->ln_WinDeploy->text();
    QTextStream out(initFile);
    initFile->setFileName(configFile);
    if(initFile->open(QIODevice::ReadWrite | QIODevice::Text)){
        out << gccPath << endl << winDeployPath << endl;
        initFile->close();
        QMessageBox::information(this,tr("Save"),"OK");
    }
    else
        QMessageBox::warning(this,tr("Save"),tr("Error"));
}

void Widget::on_pb_Editpaths_clicked()
{
    if(!ui->groupBox->isVisible())
        ui->groupBox->setVisible(true);
    else
        ui->groupBox->setVisible(false);
}
