#include "wallnut.h"
#include "button.h"

Wallnut::Wallnut()
{
    hp=350;
    atk=0;
    state=1;
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\wallnut1.gif");
}

void Wallnut::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=250&&state==1)
    {
        state=2;
        setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\wallnut2.gif");
    }
    else if(hp<=100&&state==2)
    {
        state=3;
        setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\wallnut3.gif");
    }else if(hp<=0&&state==3)
    {
        delete this;
        return;
    }
}

void Wallnut::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(810,40);
    QGraphicsItem* item=scene()->itemAt(pos,QTransform());
    Button* button=qgraphicsitem_cast<Button*>(item);
    if(button)
    {
        if(event->button()==Qt::LeftButton)
        {
            if(button->shovel_activate)
            {
                button->shovel_activate=false;
                button->counter=0;
                delete this;
            }
            else if(button->power_activate)
            {

            }
        }

    }
}
