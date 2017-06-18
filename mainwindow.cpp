#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QToolBar *> toolbars = this->findChildren<QToolBar *>();
        for (int i = 0; i < toolbars.length(); i++)
            toolbars.at(i)->hide();

    group = new QGroupBox;

    scaleLbl = new QLabel("Масштаб, %");
    parALbl = new QLabel("Параметр А:");
    parBLbl= new QLabel("Параметр В:");
    parXMinLbl = new QLabel("Значения X от: ");
    parXMaxLbl= new QLabel(" до: ");

    scaleLine = new QLineEdit("100");
    parALine = new QLineEdit;
    parBLine = new QLineEdit;
    parXMinLine = new QLineEdit;
    parXMaxLine = new QLineEdit;

    setScaleBut = new QPushButton("Изменить");
    buildGraphBut = new QPushButton("Построить график");

    table = new GraphTable;
    drawWind = new DrawWindow;

    QHBoxLayout *layParAB = new QHBoxLayout;
    layParAB->addWidget(parALbl);
    layParAB->addWidget(parALine);
    layParAB->addWidget(parBLbl);
    layParAB->addWidget(parBLine);

    QHBoxLayout *layParX = new QHBoxLayout;
    layParX->addWidget(parXMinLbl);
    layParX->addWidget(parXMinLine);
    layParX->addWidget(parXMaxLbl);
    layParX->addWidget(parXMaxLine);

    QHBoxLayout *layScale = new QHBoxLayout;
    layScale->addWidget(scaleLbl);
    layScale->addWidget(scaleLine);
    layScale->addWidget(setScaleBut);
    layScale->addStretch(1);

    QVBoxLayout *layData = new QVBoxLayout;
    layData->addLayout(layParAB);
    layData->addLayout(layParX);
    layData->addWidget(buildGraphBut);
    layData->addWidget(table);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(drawWind);
    scrollArea->setFixedSize(410, 410);

    QVBoxLayout *layGraph = new QVBoxLayout;
    layGraph->addWidget(scrollArea);
    layGraph->addLayout(layScale);
    //+виджет с графиком

    QHBoxLayout *layAll = new QHBoxLayout;
    layAll->addLayout(layGraph);
    layAll->addLayout(layData);

    group->setLayout(layAll);
    setCentralWidget(group);

    connect(buildGraphBut, SIGNAL(clicked(bool)), this, SLOT(PushButtonBuildGraph()));
    connect(setScaleBut, SIGNAL(clicked(bool)), this, SLOT(PushButtonScale()));
}

bool MainWindow::CheckInput()
{
    bool ok = true, checkLine = true;

    parALine->text().toInt(&ok, 10);
    if (ok == false || parALine->text()==NULL) checkLine = false;
    else{
        parBLine->text().toInt(&ok, 10);
        if (ok == false || parBLine->text()==NULL) checkLine = false;
        else{
            parXMinLine->text().toInt(&ok, 10);
            if (ok == false || parXMinLine->text()==NULL) checkLine = false;
            else{
                parXMaxLine->text().toInt(&ok, 10);
                if (ok == false || parXMaxLine->text()==NULL) checkLine = false;
                else{
                    if (parXMinLine->text().toInt(&ok, 10) >= parXMaxLine->text().toInt(&ok, 10)) checkLine = false;
                }
            }
        }
    }

    if (checkLine==false)
        QMessageBox::warning(this, "Ошибка!", "Введите корректные данные!", QMessageBox::Ok);
    else
        return true;
    return false;
}

void MainWindow::PushButtonBuildGraph()
{
    bool ok;
    if (CheckInput()==true)
    {
        CoordinatesList list;
        list.CalculatePoints(parALine->text().toInt(&ok, 10), parBLine->text().toInt(&ok, 10), parXMinLine->text().toInt(&ok, 10), parXMaxLine->text().toInt(&ok, 10));
        table->SetData(list.GetPointsList());
        drawWind->SetCoordinates(list);
    }

}

bool MainWindow::CheckScaleInput()
{
    bool ok;
    scaleLine->text().toInt(&ok, 10);
    if (ok==false || scaleLine->text().toInt(&ok, 10)<10 || scaleLine->text().toInt(&ok, 10)>500)
        QMessageBox::warning(this, "Ошибка!", "Введите корректные данные! /n Масштаб должен быть в интервале от 10% до 500%", QMessageBox::Ok);
    else
        return true;
    return false;
}

void MainWindow::PushButtonScale()
{
    bool ok;
    if (CheckScaleInput()==true)
        drawWind->ScaledGraph(scaleLine->text().toInt(&ok, 10));
}

MainWindow::~MainWindow()
{
    delete ui;
}
