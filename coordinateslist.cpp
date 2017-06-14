#include "coordinateslist.h"

//CoordinatesList::CoordinatesList(QObject *parent) : QObject(parent)
CoordinatesList::CoordinatesList()
{

}

void CoordinatesList::CalculatePoints(int A, int B, int XMin, int XMax)
{
    a=A;
    b=B;
    xMin=XMin;
    xMax=XMax;
    //вычисление координат и добавление точек в pointlist

    for (float x=(float)xMin; abs(x - xMax) < eps || x<(float)xMax; x=x+h)
    {
        int i=1;
        float yi=1.0f, y=0;
        while (abs(yi)>eps) {
                yi=pow(-1, i-1)*sin(i*(a*x-b))/i;
                y+=yi;
                i++;
        }
        y = floor(y*pow(10.0,4)+0.5)/pow(10.0,4); //округление
        x = floor(x*pow(10.0,1)+0.5)/pow(10.0,1);

        AddPoint(x, y);
    }

}

float CoordinatesList::GetMinX()
{
    return xMin;
}

float CoordinatesList::GetMinY()
{
    float min=0;
    if (pointslist.length() > 0)
        min = pointslist.at(1).GetY();
    for (int i = 0; i < pointslist.length(); i++)
    {
        if(pointslist.at(i).GetY() < min)
          min = pointslist.at(i).GetY();
    }
    return min;

}

float CoordinatesList::GetMaxX()
{
    return xMax;
}

float CoordinatesList::GetMaxY()
{
    float max=0;
    if (pointslist.length() > 0)
        max = pointslist.at(1).GetY();
    for (int i = 0; i < pointslist.length(); i++)
    {
        if(pointslist.at(i).GetY() > max)
          max = pointslist.at(i).GetY();
    }
    return max;
}

QList<Point> CoordinatesList::GetPointsList()
{
    return pointslist;
}

void CoordinatesList::AddPoint(float X, float Y)
{
    Point point(X,Y);
    pointslist.append(point);
}
