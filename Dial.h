#ifndef DIAL_H
#define DIAL_H

#include "QWidget"
#include <QColor>
class Dial :public QWidget
{
public:
    Dial(QWidget* patent=nullptr);

    ~Dial();


    void paintEvent(QPaintEvent *);
    //绘制外圆盘
    void drawObkColor(QPainter& paint);
    //
    void drawScalebkColor(QPainter &paint);
    //
    void drawslideScaleColor(QPainter &paint);
    //绘制刻度值
    void drawScaleTextColor(QPainter &paint);
    void drawTick(QPainter &paint);
    //绘制指针
    void drawPointColor(QPainter &paint);

    void  drawlabelColor(QPainter &paint);

    QPoint CustomRotate(QPointF point,qreal from_angle,qreal rotate);

    //设置告警值
    void setAbortValue(double value);
    //设置范围
    void setRange(double _minValue,double _maxValue );
    //设置字体颜色
    void setTextColor(QColor color);
    //设置当前油量
    void setCurrentValue(double _value);
private:
    double radius{0.0};
    double centerR{0.0};
    QColor oobkColor;
    QColor obkColor;
    QColor ScaleColor;
    QColor slideScaleColor;
    QColor PointerColor;
    QColor SingleSlideColor;
    QColor TextColor;           //油量的字体颜色
    double maxvalue{120.0};
    double minvalue{0.0};
    double value = {60.0};
    QVector<QPoint> offest;
    QVector<double> alingns;
    double m_dAbortValue{40.0}; //告警值

};

#endif // DIAL_H
