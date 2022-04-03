/***********************************************************************************
 * 文件名 : DrawingBoard.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 画图板类的实现
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "DrawingBoard.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>

DrawingBoard::DrawingBoard(QWidget *parent) : QWidget(parent)
{
    m_group.setParent(this);
    m_group.setTitle("绘图设置");
    m_group.resize(370, 65);
    m_group.move(5, 10);

    m_freeBtn.setParent(&m_group);
    m_freeBtn.setText("自由绘制");
    m_freeBtn.resize(70, 35);
    m_freeBtn.move(5, 20);
    m_freeBtn.setChecked(true);

    m_lineBtn.setParent(&m_group);
    m_lineBtn.setText("线段");
    m_lineBtn.resize(60, 35);
    m_lineBtn.move(90, 20);

    m_rectBtn.setParent(&m_group);
    m_rectBtn.setText("矩形");
    m_rectBtn.resize(60, 35);
    m_rectBtn.move(160, 20);

    m_ellipseBtn.setParent(&m_group);
    m_ellipseBtn.setText("椭圆");
    m_ellipseBtn.resize(60, 35);
    m_ellipseBtn.move(230, 20);

    m_colorBox.setParent(&m_group);
    m_colorBox.resize(60, 35);
    m_colorBox.move(300, 20);
    m_colorBox.addItem("黑色");
    m_colorBox.addItem("蓝色");
    m_colorBox.addItem("绿色");
    m_colorBox.addItem("红色");
    m_colorBox.addItem("黄色");

    setFixedSize(400, 600);

    m_current.type = NONE;
    m_current.color = Qt::white;
    m_current.points.clear();
}

DrawingBoard::DrawType DrawingBoard::drawType()
{
    DrawType ret = NONE;

    if( m_freeBtn.isChecked() )
    {
        ret = FREE;
    }

    if( m_lineBtn.isChecked() )
    {
        ret = LINE;
    }

    if( m_rectBtn.isChecked() )
    {
        ret = RECT;
    }

    if( m_ellipseBtn.isChecked() )
    {
        ret = ELLIPSE;
    }

    return ret;
}

Qt::GlobalColor DrawingBoard::drawColor()
{
    Qt::GlobalColor ret = Qt::black;

    if( m_colorBox.currentText() == "黑色" )
    {
        ret = Qt::black;
    }

    if( m_colorBox.currentText() == "蓝色" )
    {
        ret = Qt::blue;
    }

    if( m_colorBox.currentText() == "绿色" )
    {
        ret = Qt::green;
    }

    if( m_colorBox.currentText() == "红色" )
    {
        ret = Qt::red;
    }

    if( m_colorBox.currentText() == "黄色" )
    {
        ret = Qt::yellow;
    }

    return ret;
}

void DrawingBoard::mousePressEvent(QMouseEvent* evt)
{
    m_current.type = drawType();
    m_current.color = drawColor();
    m_current.points.append(evt->pos());
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* evt)
{
    append(evt->pos());

    update();
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* evt)
{
    append(evt->pos());

    m_drawList.append(m_current);

    m_current.type = NONE;
    m_current.color = Qt::white;
    m_current.points.clear();

    update();
}

void DrawingBoard::append(QPoint p)
{
    if( m_current.type != NONE)
    {
        if( m_current.type == FREE)
        {
            m_current.points.append(p);
        }
        else
        {
            if( m_current.points.count() == 2)
            {
                m_current.points.removeLast();
            }

            m_current.points.append(p);
        }
    }
}

void DrawingBoard::paintEvent(QPaintEvent* evt)
{
    QPainter painter(this);

    for(int i = 0;i < m_drawList.count();i++)
    {
        draw(painter, m_drawList[i]);
    }

    draw(painter, m_current);
}

void DrawingBoard::draw(QPainter& painter, DrawParam& param)
{
    if( (param.type != NONE) && (param.points.count() >= 2) )
    {
        int x = (param.points[0].x() < param.points[1].x()) ? param.points[0].x() : param.points[1].x();
        int y = (param.points[0].y() < param.points[1].y()) ? param.points[0].y() : param.points[1].y();
        int w = qAbs(param.points[0].x()-param.points[1].x()) + 1;
        int h = qAbs(param.points[0].y()-param.points[1].y()) + 1;
        painter.setPen(QPen(param.color));
        painter.setBrush(QBrush(param.color));

        switch(param.type)
        {
        case FREE:
            for(int i = 0; i < param.points.count() - 1; i++)
            {
                painter.drawLine(param.points[i], param.points[i+1]);
            }
            break;

        case LINE:
            painter.drawLine(param.points[0], param.points[1]);
            break;

        case RECT:
            painter.drawRect(x, y, w, h);
            break;

        case ELLIPSE:
            painter.drawEllipse(x, y, w, h);
            break;

        default:
            break;
        }
    }
}

DrawingBoard::~DrawingBoard()
{

}
