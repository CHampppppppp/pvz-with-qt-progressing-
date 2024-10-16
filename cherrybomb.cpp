#include "cherrybomb.h"
#include "button.h"


Cherrybomb::Cherrybomb()
{
    hp=50;
    atk=400;
    state=1;//准备爆炸
    setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\cb.gif");
    movie->setSpeed(50);
    counter=0;
    time=50;//爆炸前摇
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::shovel_activate||Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0){
        delete this;
    }
    else if(state==1&&movie->currentFrameNumber()==movie->frameCount()-1)
    {
        state=2;
        setMovie("C:\\Users\\champ\\Documents\\pvzfresh\\boom.gif");
        QList<QGraphicsItem*> items=collidingItems();
        if(!items.isEmpty())
        {
            foreach(QGraphicsItem* item,items)
            {
                Zombie* zombie=qgraphicsitem_cast<Zombie*>(item);
                if(zombie)
                {
                    //qDebug()<<"zombie_x:"<<zombie->x();
                    //qDebug()<<"cherrybomb_x:"<<x();
                    zombie->SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\burn.gif");
                    zombie->state=BURN;
                }
            }
        }
    }else if(state==2&&movie->currentFrameNumber()==movie->frameCount()-1) delete this;
}

bool Cherrybomb::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type&&qAbs(other->y()-y())<=GAP_Y&&((other->x()-x()>=0&&other->x()-x()<=GAP_X)||(other->x()-x()>=-1.5*GAP_X&&other->x()-x()<=0));
}


void Cherrybomb::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
