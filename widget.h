#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QFileDialog;
class QProcess;
class QFile;
class QTextStream;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pb_Run_clicked();
    void on_process_started();
    void on_process_finished();
    void on_process_readReady();
    void on_pb_WinDeploy_clicked();

    void on_pb_GccPath_clicked();

    void on_pb_ExecPath_clicked();

    void on_pb_SaveConfig_clicked();

    void on_pb_Editpaths_clicked();

private:
    Ui::Widget *ui;
    QFileDialog *fileDialog;
    QProcess *process; 
    QFile *initFile;
    QString gccPath = "C:/Qt/Tools/mingw530_32/bin";
    QString winDeployPath = "C:/Qt/5.10.0/mingw53_32/bin/windeployqt.exe";
    QString configFile = "config.ini";
    QTextStream *out;
    bool init_paths();
    bool init_file(void);
};

#endif // WIDGET_H
