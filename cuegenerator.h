#ifndef CUEGENERATOR_H
#define CUEGENERATOR_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

#define FLAC 0
#define APE 1
#define WAV 2

namespace Ui {
class CUEGenerator;
}

class CUEGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit CUEGenerator(QWidget *parent = 0);
    ~CUEGenerator();

private:
    Ui::CUEGenerator *ui;
    QButtonGroup *btnGroupType;
    int fileType;

private slots:
    void on_RadioButton_clicked();
    void on_generate_clicked();
    void on_open_clicked();
};

#endif // CUEGENERATOR_H
