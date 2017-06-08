#ifndef COORDINATESLIST_H
#define COORDINATESLIST_H

#include <QObject>
#include "point.h"

class CoordinatesList //: public QObject
{
   // Q_OBJECT
public:
   // explicit CoordinatesList(QObject *parent = 0);
    CoordinatesList();
    QList<Point> GetPointsList();
    void CalculatePoints(int A, int B, int XMin, int XMax);

private:
    QList<Point> pointslist;
    int a;
    int b;
    int xMin;
    int xMax;
    float h=0.1f;
    float eps=0.0001f;

    void AddPoint(float X, float Y);

signals:

public slots:
};

#endif // COORDINATESLIST_H
