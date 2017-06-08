#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    group = new QGroupBox;

    scaleLbl = new QLabel("Масштаб, %");
    parALbl = new QLabel("Параметр А:");
    parBLbl= new QLabel("Параметр В:");
    parXMinLbl = new QLabel("Значения X от: ");
    parXMaxLbl= new QLabel(" до: ");

    scaleLine = new QLineEdit;
    parALine = new QLineEdit;
    parBLine = new QLineEdit;
    parXMinLine = new QLineEdit;
    parXMaxLine = new QLineEdit;

    setScaleBut = new QPushButton("Изменить");
    buildGraphBut = new QPushButton("Построить график");

    table = new GraphTable;

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

    QVBoxLayout *layData = new QVBoxLayout;
    layData->addLayout(layParAB);
    layData->addLayout(layParX);
    layData->addWidget(buildGraphBut);
    layData->addWidget(table);

    QVBoxLayout *layGraph = new QVBoxLayout;
    layGraph->addLayout(layScale);
    //+виджет с графиком

    QHBoxLayout *layAll = new QHBoxLayout;
    layAll->addLayout(layGraph);
    layAll->addLayout(layData);

    group->setLayout(layAll);
    setCentralWidget(group);

    connect(buildGraphBut, SIGNAL(clicked(bool)), this, SLOT(PushButtonBuildGraph()));
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
   //     QMessageBox::warning(this, "Ошибка!", "Херня", QMessageBox::Ok);
        CoordinatesList list;
        list.CalculatePoints(parALine->text().toInt(&ok, 10), parBLine->text().toInt(&ok, 10), parXMinLine->text().toInt(&ok, 10), parXMaxLine->text().toInt(&ok, 10));
        //+вывести график функции
         table->SetData(list.GetPointsList());

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
