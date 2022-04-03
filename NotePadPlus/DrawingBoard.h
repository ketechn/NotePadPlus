/***********************************************************************************
 * �ļ��� : DrawingBoard.h
 * ������ :
 * �������� :
 * �ļ����� : ��ͼ����
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
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
    QList<DrawParam> m_drawList;/*�Ѿ����ƽ�����ͼ��*/
    DrawParam m_current;/*��ǰ���ڻ��Ƶ�ͼ��*/

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
