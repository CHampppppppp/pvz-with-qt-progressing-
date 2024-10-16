#include "snowpeashooter.h"
#include "button.h"

snowpeashooter::snowpeashooter()
{
    hp=100;
    state=1;
    time=100;
    counter=0;
    atk=12;
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\snowpea.gif");
    movie->setSpeed(50);
}

void snowpeashooter::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
        delete this;
    else if(++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            Pea* pea=new Pea(atk,SNOW);
            pea->setX(x()+32);
            pea->setY(y());
            scene()->addItem(pea);
            return;
        }
    }
}


bool snowpeashooter::collidesWithItem(const QGraphicsItem* other,Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&other->x()>=x()&&other->y()==y();
}


void snowpeashooter::mousePressEvent(QGraphicsSceneMouseEvent *event)
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


