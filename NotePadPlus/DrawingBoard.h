/***********************************************************************************
 * 文件名 : DrawingBoard.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 画图板类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _DRAWINGBOARD_H_
#define _DRAWINGBOARD_H_

#include <QtGui/QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QList>
#include <QPoint>

class DrawingBoard : public QWidget
{
    Q_OBJECT

    enum DrawType
    {
        NONE,
        FREE,
        LINE,
        RECT,
        ELLIPSE
    };

    struct DrawParam
    {
        DrawType type;
        Qt::GlobalColor color;
        QList<QPoint> points;
    };

    QGroupBox m_group;
    QRadioButton m_freeBtn;
    QRadioButton m_lineBtn;
    QRadioButton m_rectBtn;
    QRadioButton m_ellipseBtn;
    QComboBox m_colorBox;
    QList<DrawParam> m_drawList;/*已经绘制结束的图形*/
    DrawParam m_current;/*当前正在绘制的图形*/

    DrawType drawType();
    Qt::GlobalColor drawColor();
    void draw(QPainter& painter, DrawParam& param);
    void append(QPoint p);

protected:
    void mousePressEvent(QMouseEvent* evt);
    void mouseMoveEvent(QMouseEvent* evt);
    void mouseReleaseEvent(QMouseEvent* evt);
    void paintEvent(QPaintEvent* evt);

public:
    DrawingBoard(QWidget* parent = 0);
    ~DrawingBoard();
};

#endif //_DRAWINGBOARD_H_
