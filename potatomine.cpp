#include "potatomine.h"
#include "button.h"

Potatomine::Potatomine()
{
    hp=80;
    atk=300;
    state=1;//地里 state2->地上 state3->爆炸
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\pttm1.gif");
    movie->setSpeed(50);
    counter=0;
    time=200;
}

void Potatomine::advance(int phase)
{
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(!phase) return;
    update();
    if(hp<=0)
    {
        delete this;
        return;
    }
    if(state==1&&++counter>=time)
    {
        counter=0;
        state=2;
        setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\pttm2.gif");
    }
    if(state==2)
    {  
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            bool iszombie;
            foreach(QGraphicsItem* item,items)
            {
                iszombie=false;
                Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                if(zombie)
                {
                    iszombie=true;
                    zombie->hp-=atk;
                }
            }
            if(iszombie)
            {
                state=3;
                setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\pttm3.gif");
            }
        }
    }
    if(state==3&&movie->currentFrameNumber()==movie->frameCount()-1) delete this;
}

bool Potatomine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode)const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&qAbs(other->x()-x())<=30&&other->y()==y();
}


void Potatomine::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
