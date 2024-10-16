#include "pea.h"
#include "zombie.h"

Pea::Pea(int atk_num,bool snowor)
{
    atk=atk_num;
    speed=7.0;
    snow=snowor;
}

Pea::~Pea()
{

}

QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 24, 24);
}


void Pea::advance(int phase)
{
    if(!phase) return;
    update();
    QList<QGraphicsItem*> items=collidingItems();
    if(!items.empty())
    {
        Zombie* zombie=qgraphicsitem_cast<Zombie*>(items[0]);//第一个碰到的zombie
        if(zombie)
        {
            zombie->hp-=atk;
            if(snow) zombie->counter=0;
            if(!zombie->slow)
            {
                zombie->slow=snow;
                zombie->speed-=snow*0.4;
                if(zombie->slow)
                    zombie->movie->setSpeed(60);
            }
            delete this;
            return;
        }
    }
    setX(x()+speed);
    if(x()>WIDTH||x()<0)
    {
        delete this;
    }
}



bool Pea::collidesWithItem(const QGraphicsItem* other,Qt::ItemSelectionMode mode)const
{
    Q_UNUSED(mode)
    if(qAbs(other->x()-x())<30&&other->type()==Zombie::Type&&other->y()==y()) return true;
    return false;
}


void Pea::paint(QPainter*painter,const QStyleOptionGraphicsItem* option,QWidget*widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!snow)
    painter->drawPixmap(QRect(-12, -28, 24, 24),QPixmap("C:\\Users\\champ\\Documents\\pvzfresh\\pea.png"));
    else
        painter->drawPixmap(boundingRect(),QPixmap("C:\\Users\\champ\\Documents\\pvzfresh\\peasnow.png"),QRectF());
}

