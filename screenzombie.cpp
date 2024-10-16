#include "screenzombie.h"
#include "button.h"

screenzombie::screenzombie()
{
    hp=250;
    speed=0.7;
    atk=0.3;
    state=WALK;
    slow=NO_SLOW;
    time=120;
    SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\szbw.gif");
}

void screenzombie::advance(int phase)
{
    if(!phase) return;
    update();
    if(Button::power_activate) setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);
    if(hp<=0)
    {
        if(Button::power_activate) setCursor(Qt::PointingHandCursor);
        else setCursor(Qt::ArrowCursor);
        if(state==ATTACK||state==WALK)
        {
            state=DEAD;
            Sethead("C:\\Users\\champ\\Documents\\pvzfresh\\zh.gif");
            SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\zd.gif");
            movie->setSpeed(50);
        }
        if(state==DEAD&&movie->frameCount()==movie->currentFrameNumber()+1)
        {
            delete this;//播放完gif顺带连head一起删除
        }
        return;
    }
    QList<QGraphicsItem*> items=collidingItems();
    if(!items.isEmpty())//有碰撞
    {
        Plants *plant= qgraphicsitem_cast<Plants *>(items[0]);//安全起见
        if(plant)
        {
            plant->hp-=atk;
            if(state!=ATTACK)
            {
                if(hp>100)
                SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\szba.gif");
                else if(hp>0)
                    SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\za.gif");
                state=ATTACK;
            }
            return;
        }
    }

    if(state==ATTACK)//吃完后继续walk
    {
        state=WALK;
        if(hp>100)
        SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\szbw.gif");
        else if(hp<=100)
            SetMovie("C:\\Users\\champ\\Documents\\pvzfresh\\zw1.gif");
    }

    if(slow)
    {
        if(++counter>time)
        {
            snowfree();
            return;
        }
        speed=0.5;
        movie->setSpeed(60);
    }

    if(state==BURN)
    {
        speed=0;
        if(movie->currentFrameNumber()==movie->frameCount()-1)
        {
            delete this;
            return;
        }
    }
    if(x()<100) {
        delete this;
        return;
    }
    setX(x()-speed);
}

void screenzombie::snowfree()
{
        slow=NO_SLOW;
        speed=0.7;
        movie->setSpeed(100);
        return;
}


void screenzombie::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(930,60);
    QGraphicsItem* item=scene()->itemAt(pos,QTransform());
    Button* button=qgraphicsitem_cast<Button*>(item);
    if(button)
    {
        if(event->button()==Qt::LeftButton&&button->power_activate)
        {
            setCursor(Qt::PointingHandCursor);
            button->power_activate=false;
            button->counter=0;
            snowfree();
            speed=2.0;
            movie->setSpeed(250);
            qDebug()<<"powerscreenzombie";
        }
    }
}
