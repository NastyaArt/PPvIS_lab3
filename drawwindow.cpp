#include "drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 400);
    outputGraph = new QLabel;
    outputGraph->setBackgroundRole(QPalette::Light);
    outputGraph->setScaledContents(true);
    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(outputGraph);
    scrollArea->setFixedSize(400, 400);



}
void DrawWindow::CalcParam()
{
    if (coordinates.GetPointsList().length()>0)
    {
        if (coordinates.GetMinX() >= 0) OxMin = -6*traitsDist;
        else OxMin = coordinates.GetMinX()*onePixel-traitsDist;
        if (coordinates.GetMinY() >= 0) OyMin = -6*traitsDist;
        else OyMin = ((int)(coordinates.GetMinY()-0.5))*onePixel-traitsDist;
        if (coordinates.GetMaxX() <= 0) OxMax = 6*traitsDist;
        else OxMax = coordinates.GetMaxX()*onePixel+traitsDist;
        if (coordinates.GetMaxY() <= 0) OyMax = 6*traitsDist;
        else OyMax = ((int)(coordinates.GetMaxY()+0.5))*onePixel+traitsDist;
        OxLength = (abs(OxMin)+abs(OxMax));
        OyLength = (abs(OyMin)+abs(OyMax));
    }
}

void DrawWindow::paintEvent(QPaintEvent *) {

    if (coordinates.GetPointsList().length()>0)
    {

      /*  if (coordinates.GetMinX() >= 0) OxMin = -6*traitsDist;
        else OxMin = coordinates.GetMinX()*onePixel-traitsDist;
        if (coordinates.GetMinY() >= 0) OyMin = -6*traitsDist;
        else OyMin = ((int)(coordinates.GetMinY()-0.5))*onePixel-traitsDist;
        if (coordinates.GetMaxX() <= 0) OxMax = 6*traitsDist;
        else OxMax = coordinates.GetMaxX()*onePixel+traitsDist;
        if (coordinates.GetMaxY() <= 0) OyMax = 6*traitsDist;
        else OyMax = ((int)(coordinates.GetMaxY()+0.5))*onePixel+traitsDist;
        OxLength = (abs(OxMin)+abs(OxMax));
        OyLength = (abs(OyMin)+abs(OyMax));
*/
     //   outputGraph->setFixedSize(scl*OxLength, scl*OyLength);
        CalcParam();
        SetScaled();

        QPixmap graph(scl*OxLength, scl*OyLength);
        graph.fill(QColor(Qt::white));

        QPainter p;
        p.begin(&graph);
        p.setWindow(QRect(OxMin, -OyMax, OxLength, OyLength));

        p.setPen(QPen(Qt::lightGray, 1, Qt::SolidLine));
        for (int i=OxMin; i<=OxMax; i+=traitsDist)
        {
            p.drawLine(i, -OyMax, i, -OyMin);
        }
        for (int i=-OyMax; i<=-OyMin; i+=traitsDist)
        {
            p.drawLine(OxMin, i, OxMax, i);
        }

        p.setPen(QPen(Qt::black, 1, Qt::SolidLine));

        p.drawLine(OxMin, 0, OxMax, 0);
        p.drawLine(0, -OyMin, 0, -OyMax);

        p.drawLine(OxMax, 0, OxMax-10, numShift*2);
        p.drawLine(OxMax, 0, OxMax-10, -numShift*2);
        p.drawLine(0, -OyMax, numShift*2, -OyMax+10);
        p.drawLine(0, -OyMax, -numShift*2, -OyMax+10);

        p.setPen(QPen(Qt::green, 2, Qt::SolidLine));
        for (int i=0; i<coordinates.GetPointsList().length()-1; i++)
        {
            p.drawLine(coordinates.GetPointsList().at(i).GetX()*onePixel,-coordinates.GetPointsList().at(i).GetY()*onePixel,coordinates.GetPointsList().at(i+1).GetX()*onePixel,-coordinates.GetPointsList().at(i+1).GetY()*onePixel);
        }
        p.setPen(QPen(Qt::darkGreen, 3, Qt::SolidLine));
        for (int i=0; i<coordinates.GetPointsList().length(); i++)
        {
            p.drawPoint(coordinates.GetPointsList().at(i).GetX()*onePixel,-coordinates.GetPointsList().at(i).GetY()*onePixel);
        }
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        for (int i=OxMin+traitsDist; i<OxMax; i+=5*traitsDist)
        {
            p.drawLine(i, numShift, i, -numShift);
        }
        for (int i=-OyMax+traitsDist; i<-OyMin; i+=5*traitsDist)
        {
            p.drawLine(numShift, i, -numShift, i);
        }
        float numXMin, numXMax;
        if (coordinates.GetMinX() >= 0) numXMin = -1.0;
        else  numXMin =coordinates.GetMinX();
        if (coordinates.GetMaxX() <= 0) numXMax = 1.0;
        else  numXMax =coordinates.GetMaxX();
        for (float num=numXMin; num<=numXMax; num+=h)
        {
            p.drawText(num*onePixel-2*numShift, numShift, 2*numShift, 2*numShift, Qt::TextDontClip, QString::number(num));
        }
        float numYMin, numYMax;
        if (coordinates.GetMinY() >= 0) numYMin = -1.0;
        else  numYMin =((int)(coordinates.GetMinY()-0.5));
        if (coordinates.GetMaxY() <= 0) numYMax = 1.0;
        else  numYMax =((int)(coordinates.GetMaxY()+0.5));
        for (float num=numYMin; num<=numYMax; num+=h)
        {
           if (num!=0.0f)
           p.drawText(2*numShift, -num*onePixel-2*numShift, 2*numShift, 2*numShift, Qt::TextDontClip, QString::number(num));
        }
        p.end();
        outputGraph->setPixmap(graph);

    }

}

void DrawWindow::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    if (event->modifiers() == Qt::ShiftModifier)
    {
        scl=scl+numSteps*hScl;
        if (scl<minScl) scl = minScl;
        else if (scl>maxScl) scl = maxScl;
        if (scl>=minScl && scl<=maxScl)
        {
            SetScaled();
            emit ResetScale(scl);
        }
    }
   /* else {
        if (event->orientation() == Qt::Horizontal) {
                 scrollHorizontally(numSteps);
             } else {
                 scrollVertically(numSteps);
             }
    }*/
    event->accept();
}

void DrawWindow::mousePressEvent(QMouseEvent *e)
{
    mousePos = e->pos();
}
void DrawWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint diff = e->pos() - mousePos;
    mousePos = e->pos();
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->value() - diff.y());
    scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() - diff.x());
}

void DrawWindow::SetCoordinates(CoordinatesList list)
{
    coordinates = list;
    repaint();
}

void DrawWindow::SetScaled()
{
   outputGraph->setFixedSize(scl*OxLength, scl*OyLength);
}

void DrawWindow::ScaledGraph(int scale)
{
    scl=(double)scale/(double)100;
    SetScaled();

}

