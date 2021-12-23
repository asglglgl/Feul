#include "Dial.h"
#include "QPainter"
#include <QConicalGradient>
Dial::Dial(QWidget* patent)
    :QWidget(patent)
{
    oobkColor = QColor(Qt::white);
    obkColor =  QColor(Qt::white);
    ScaleColor = QColor(Qt::white);
    slideScaleColor = QColor(Qt::white);
    PointerColor = QColor(Qt::red);
    SingleSlideColor = QColor(Qt::red);
    TextColor = QColor(Qt::white);
    QPoint p;
    p.setX(3);
    p.setY(3);
    offest.resize(7);

    alingns.resize(7);
    for(int i =0;i<7;++i)
    {
        offest[i] = p;
        alingns[i] = 5;
    }
}

Dial::~Dial()
{

}

void Dial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.translate(width()/2,height()/2);
    radius = qMin(width(),height())/2;
    centerR=radius*0.4;       //设置中心圆大小
    drawObkColor(painter);           //外圆盘
    drawScalebkColor(painter);      //画刻度圆
    drawslideScaleColor(painter);   //画划过的颜色
//        drawShade(painter);            //画阴影
//        drawScaleColor(painter);
//        drawbkColor(painter);          //画内圆
        drawScaleTextColor(painter);   //画刻度值
        drawTick(painter);
        drawPointColor(painter);
       // drawCenterColor(painter);      //绘制中心圆
       // drawIconValueColor(painter);
         drawlabelColor(painter);
}

void Dial::drawObkColor(QPainter &paint)
{
    paint.save();
    QConicalGradient  Conical(0,0,90);
    Conical.setColorAt(0,oobkColor);
    Conical.setColorAt(0.5,oobkColor);
    Conical.setColorAt(0.12,oobkColor.darker(40));
    Conical.setColorAt(0.88,oobkColor.darker(40));
    Conical.setColorAt(0.4,oobkColor.darker(30));
    Conical.setColorAt(0.6,oobkColor.darker(30));
    Conical.setColorAt(0.25,oobkColor.darker(160));
    Conical.setColorAt(0.75,oobkColor.darker(160));
    Conical.setColorAt(1,oobkColor);
    paint.setBrush(Conical);
    paint.drawEllipse(QPointF(0,0), radius*0.96,radius*0.98);
    Conical.setAngle(270);
    Conical.setColorAt(0,obkColor.darker(40));
    Conical.setColorAt(0.5,obkColor.darker(40));
    Conical.setColorAt(0.25,obkColor.darker(160));
    Conical.setColorAt(0.75,obkColor.darker(160));
    paint.setBrush(Conical);
    paint.drawEllipse(QPointF(0,0), radius*0.93,radius*0.94);
    paint.restore();
}

void Dial::drawScalebkColor(QPainter &paint)
{
   paint.save();
   paint.setBrush(Qt::black);
   paint.drawEllipse(QPointF(0,0), radius*0.90,radius*0.90);

   paint.restore();
}

void Dial::drawslideScaleColor(QPainter &paint)
{
    /*单一颜色*/

        int Star_Angle= 210*16-(int)((m_dAbortValue/(maxvalue-minvalue))*240*16);

        int spanAngle  =  210*16 - Star_Angle;

        qreal SlideBottom =  ((qreal)radius*0.77)/((qreal)radius*0.90);

        qreal SlideCenterTop = 1-(1-SlideBottom)/3;
        qreal SlideCenterBottom = SlideBottom+(1-SlideBottom)/3+0.01;

        paint.save();

        QColor Tint_SlideColor = SingleSlideColor;


        QRadialGradient Radial(0,0,radius*0.90);


        Tint_SlideColor.setAlpha(40);
        Radial.setColorAt(1,Tint_SlideColor);
        Radial.setColorAt(SlideBottom-0.005,Tint_SlideColor);
        Radial.setColorAt(0,Qt::transparent);
        Radial.setColorAt(SlideBottom-0.006,Qt::transparent);


        Tint_SlideColor = SingleSlideColor;
        Tint_SlideColor.setAlpha(50);


        Radial.setColorAt(SlideCenterBottom-0.03,Tint_SlideColor);
        Radial.setColorAt(SlideCenterTop+0.03,Tint_SlideColor);

        Tint_SlideColor = SingleSlideColor;
        Tint_SlideColor.setAlpha(50);
        Radial.setColorAt(SlideCenterBottom-0.01,SingleSlideColor.darker(200));
        Radial.setColorAt(SlideCenterTop+0.01,SingleSlideColor.darker(200));

        Radial.setColorAt(SlideCenterBottom,SingleSlideColor);
        Radial.setColorAt(SlideCenterTop,SingleSlideColor);

        paint.setPen(Qt::NoPen);
        paint.setBrush(Radial);

        paint.drawPie(QRectF((qreal)-radius*0.90,(qreal)-radius*0.90,(qreal)radius*1.80,(qreal)radius*1.80),Star_Angle,spanAngle);

        paint.restore();
}

void Dial::drawScaleTextColor(QPainter &paint)
{
    /*绘制文字刻度*/
        paint.save();

        paint.setPen(ScaleColor);

        QString text("%1");

        int size;           //动态计算文字大小

        if(radius<=120)
           size = 10;
        else if((radius>120)&&(radius<500))
           size = 13+(radius-120)/30;
        else if(radius>=500)
           size = 13+(radius-120)/40;

        paint.setFont(QFont("Euphemia",size,QFont::DemiBold));

        QPoint TextPoint(0,radius*0.77-size*0.9);        //设置90°的文字
        QPoint TextPoint1(0,radius-size*0.9);        //设置90°的文字

        TextPoint = CustomRotate(TextPoint,90,240);   //获取点=210°的文字位置
        TextPoint1 = CustomRotate(TextPoint1,90,240);   //获取点=210°的文字位置

        qreal TextRotate=210;

         for(int i=0;i<7;i++)              //设置7个刻度值
        {
              qreal Current_Value =(qreal)i*((maxvalue-minvalue)/6);

              if((Current_Value>value&&(paint.pen().color()!=ScaleColor)))
              {
                  paint.setPen(ScaleColor);

              }
              else if((Current_Value<=value&&(paint.pen().color()!=slideScaleColor)))
              {
                  paint.setPen(slideScaleColor);
              }
//              for(int j = 0;j<3;++j)
//              {
//                 paint.drawLine(TextPoint2,TextPoint1);
//                 TextPoint1 = CustomRotate(TextPoint1,TextRotate,10);
//                 TextPoint2 = CustomRotate(TextPoint2,TextRotate,10);
//              }

           paint.drawText(QRect(TextPoint.x()-size*1.5+offest[i].x(),TextPoint.y()-size*1.2+offest[i].y(),size*3,size*2.4),alingns[i],text.arg((maxvalue-minvalue)*i/6));
           paint.setPen(QPen(Qt::white,3));
           paint.drawLine(TextPoint,TextPoint1);
           TextPoint = CustomRotate(TextPoint,TextRotate,40);   //获取点=210°的文字位置
           TextPoint1 = CustomRotate(TextPoint1,TextRotate,40);
           TextRotate-=40;
        }

         paint.restore();
}

void Dial::drawTick(QPainter &paint)
{
    paint.save();

    paint.setPen(QPen(Qt::white,1));

    QString text("%1");

    int size;           //动态计算文字大小

    if(radius<=120)
       size = 10;
    else if((radius>120)&&(radius<500))
       size = 13+(radius-120)/30;
    else if(radius>=500)
       size = 13+(radius-120)/40;

    paint.setFont(QFont("Euphemia",size,QFont::DemiBold));

    QPoint TextPoint(0,radius*0.88-size*0.9);        //设置90°的文字
    QPoint TextPoint1(0,radius-size*0.9);        //设置90°的文字

    TextPoint = CustomRotate(TextPoint,90,240);   //获取点=210°的文字位置
    TextPoint1 = CustomRotate(TextPoint1,90,240);   //获取点=210°的文字位置

    qreal TextRotate=210;

     for(int i=0;i<25;i++)              //设置7个刻度值
    {
       paint.drawLine(TextPoint,TextPoint1);
       TextPoint = CustomRotate(TextPoint,TextRotate,10);   //获取点=210°的文字位置
       TextPoint1 = CustomRotate(TextPoint1,TextRotate,10);
       TextRotate-=10;
    }

     paint.restore();
}

void Dial::drawPointColor(QPainter &paint)
{
    qreal PointTop;                //动态计算指针头
        qreal PointBottom;             //动态计算指针底部
        if(radius<=120)
        {
            PointTop = 2;
            PointBottom = 6;
        }
        else if((radius>120)&&(radius<500))
        {
            PointTop = 2 + (radius-120)/100;
            PointBottom = PointTop*3;
        }
        else if(radius>=500)
        {
            PointTop = 2 + (radius-120)/140;
            PointBottom = PointTop*3;
        }

        //指针
        const QPointF  Pointer[4] = {
            QPointF(- PointTop / 2, radius*0.80),
            QPointF(PointTop / 2, radius*0.80),
            QPointF(PointBottom /2, centerR*0.9),
            QPointF(-PointBottom/2 , centerR*0.9)
        };

        paint.save();


        paint.setBrush(PointerColor);
        paint.setPen(PointerColor.darker(300));


        qreal Current_Angle =60+(int)((value/(maxvalue-minvalue))*240);

        paint.rotate(Current_Angle);

        paint.drawConvexPolygon(Pointer, 4);

        paint.restore();
}

void Dial::drawlabelColor(QPainter &paint)
{

    paint.save();
    QFont font;
    font.setFamily("Microsoft YaHei");
    // 大小
    font.setPointSize(20);
    paint.setBrush(TextColor);
    paint.setPen(TextColor.darker(300));
    paint.setFont(font);
    paint.drawText(-30,0+height()/4.0,QStringLiteral("油量表"));
    paint.restore();
}

QPoint Dial::CustomRotate(QPointF point, qreal from_angle, qreal rotate)
{
    qreal PI=3.141592653589;
    QPointF Tmp;
    qreal arc = (rotate-from_angle)/180*PI;
    qreal Length = sqrt(point.x()*point.x() +point.y()*point.y());
    Tmp.setX(Length*cos(arc));
    Tmp.setY(Length*sin(arc));
    return Tmp.toPoint();
}

void Dial::setAbortValue(double value)
{
    m_dAbortValue = value;
}

void Dial::setRange(double _minValue, double _maxValue)
{
    maxvalue = _maxValue;
    minvalue = _minValue;
}

void Dial::setTextColor(QColor color)
{
    TextColor = color;
}

void Dial::setCurrentValue(double _value)
{
    value = _value;
}

