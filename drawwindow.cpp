#include "drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 400);

}

void DrawWindow::paintEvent(QPaintEvent *) {

    QPainter p(this); // Создаём новый объект рисовальщика
    p.setPen(QPen(Qt::red, 1, Qt::SolidLine)); // Настройки рисования

    if (coordinates.GetPointsList().length()>0)
    {
        setFixedSize((abs(coordinates.GetMinX())+abs(coordinates.GetMaxX()))*onePixel, (abs(coordinates.GetMinY())+abs(coordinates.GetMaxY()))*onePixel);
        p.setWindow(QRect(coordinates.GetMinX()*onePixel, coordinates.GetMinY()*onePixel, (abs(coordinates.GetMinX())+abs(coordinates.GetMaxX()))*onePixel, (abs(coordinates.GetMinY())+abs(coordinates.GetMaxY()))*onePixel));
        for (int i=0; i<coordinates.GetPointsList().length()-1; i++)
        {
           // p.drawPoint(coordinates.GetPointsList().at(i).GetX(),coordinates.GetPointsList().at(i).GetY());
             p.drawLine(coordinates.GetPointsList().at(i).GetX()*onePixel,coordinates.GetPointsList().at(i).GetY()*onePixel,coordinates.GetPointsList().at(i+1).GetX()*onePixel,coordinates.GetPointsList().at(i+1).GetY()*onePixel);
        }
        p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        for (int i=0; i<coordinates.GetPointsList().length(); i++)
        {
            p.drawPoint(coordinates.GetPointsList().at(i).GetX()*onePixel,coordinates.GetPointsList().at(i).GetY()*onePixel);
        }
       // p.drawPoint(0,0);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        p.drawLine(-p.window().width()/2, 0, p.window().width()/2, 0);
        p.drawLine(0, -p.window().height()/2, 0, p.window().height()/2);

    }

}

void DrawWindow::SetCoordinates(CoordinatesList list)
{
    coordinates = list;
    repaint();
}
