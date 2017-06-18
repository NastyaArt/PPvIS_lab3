#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include "coordinateslist.h"

class DrawWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWindow(QWidget *parent = 0);

    void SetCoordinates(CoordinatesList list);
    void ScaledGraph(int scale);

private:
    CoordinatesList coordinates;
    QLabel *outputGraph;
    const int onePixel=100;
    const int numShift=3;
    const int traitsDist=10;
    int OxLength;
    int OyLength;
    int OxMin;
    int OyMin;
    int OxMax;
    int OyMax;
    double scl=1.0;
    const float h=0.5f;
protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // DRAWWINDOW_H
