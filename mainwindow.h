#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>

#include "graphtable.h"
#include "coordinateslist.h"
#include "drawwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GraphTable *table;
    CoordinatesList list;
    DrawWindow *drawWind;

    QGroupBox *group;

    QLabel *scaleLbl;
    QLabel *parALbl;
    QLabel *parBLbl;
    QLabel *parXMinLbl;
    QLabel *parXMaxLbl;

    QLineEdit *scaleLine;
    QLineEdit *parALine;
    QLineEdit *parBLine;
    QLineEdit *parXMinLine;
    QLineEdit *parXMaxLine;

    QPushButton *setScaleBut;
    QPushButton *buildGraphBut;

    bool CheckInput();
    bool CheckScaleInput();

public slots:

    void PushButtonBuildGraph();
    void PushButtonScale();
};

#endif // MAINWINDOW_H
