#include "repeater.h"
#include "button.h"

Repeater::Repeater()
{
    hp=150;
    state=1;
    time=100;
    counter=0;
    atk=15;
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\rp.gif");
    movie->setSpeed(50);
}

void Repeater::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
        delete this;
    else if(state==1&&++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            Pea* pea1=new Pea(atk,NO_SNOW);
            pea1->setX(x()+32);
            pea1->setY(y());

            scene()->addItem(pea1);
            state=2;
            return;
        }
    }
    if(state==2&&++counter>=time/25)
    {
        counter=0;
        Pea* pea2=new Pea(atk,NO_SLOW);
        pea2->setX(x()+32);
        pea2->setY(y());
        scene()->addItem(pea2);
        state=1;
        return;
    }
}

bool Repeater::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->y()==y()&&other->type()==Zombie::Type&&other->x()>x();
}

void Repeater::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
