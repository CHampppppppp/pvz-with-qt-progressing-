#include "peashooter.h"
#include "button.h"


peashooter::peashooter()
{
    hp=100;
    state=1;
    time=100;
    counter=0;
    atk=15;
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\ps.gif");
    movie->setSpeed(50);
}

void peashooter::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
    {
        delete this;
    }
    else if(++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())// 当前行有僵尸
        {
            Pea* pea=new Pea(atk,NO_SNOW);
            pea->setX(x()+32);
            pea->setY(y());
            scene()->addItem(pea);//scene()返回该item当前所在的scene指针
            return;
        }
    }
}

bool peashooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->y()==y()&&other->type()==Zombie::Type&&other->x()>x();
}


void peashooter::mousePressEvent(QGraphicsSceneMouseEvent *event)
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






