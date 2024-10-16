#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    bk_played=false;
    srand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound_wabiwabu=new QSoundEffect;
    sound_wabiwabu->setSource(QUrl::fromLocalFile("C:\\Users\\champ\\Documents\\pvzfresh\\wabiwabu.wav"));
    sound_wabiwabu->setVolume(0.4f);
    sound_wabiwabu->play();
    sound_bk=new QSoundEffect;
    sound_bk->setSource(QUrl::fromLocalFile("C:\\Users\\champ\\Documents\\pvzfresh\\crazyDave.wav"));
    sound_bk->setLoopCount(QSoundEffect::Infinite);
    sound_bk->setVolume(0.6f);
    //ui->setupUi(this);
    timer=new QTimer;
    scene=new QGraphicsScene(this);
    scene->setSceneRect(100, 0, WIDTH,HEIGHT);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    bk=new QGraphicsPixmapItem;
    bk->setZValue(0);
    bk->setPixmap(QPixmap("C:\\Users\\champ\\Documents\\pvzfresh\\Background.jpg"));
    scene->addItem(bk);
    Plants* ps=new Sunflower;
    Zombie* zb=new Conezombie;
    Shop* shop=new Shop;
    shop->setPos(230,0);
    shop->setZValue(3);
    scene->addItem(shop);
    ps->setPos(PLANT_START+160,ROW1+3*GAP);
    zb->setPos(PLANT_START+20,ROW1+3*GAP);
    //scene->addItem(zb);
    //scene->addItem(ps);
    Map* map=new Map;
    map->setZValue(2);
    map->setPos(618,326);
    scene->addItem(map);
    Button* button1=new Button(FREEZE);
    Button* button2=new Button(POWER);
    Button* button3=new Button(SHOVEL);
    button1->setPos(918,20);
    button1->setZValue(3);
    button2->setPos(918,60);
    button2->setZValue(3);
    button3->setPos(798,40);
    button3->setZValue(3);
    scene->addItem(button1);
    scene->addItem(button2);
    scene->addItem(button3);
    for(int i=0;i<5;i++)
    {
        Car* car=new Car;
        car->setPos(PLANT_START-80,ROW1+i*GAP);
        car->setZValue(3);
        scene->addItem(car);
    }
    for(int i=0;i<7;i++)
    {
        Card* card=new Card(Card::mapping[i]);
        card->setPos( 350+61 * i, 45);
        card->setZValue(3);
        scene->addItem(card);
    }
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer,&QTimer::timeout,this,&MainWindow::playmusic);
    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    connect(timer,&QTimer::timeout,this,&MainWindow::addZombies);//随机生成僵尸,今天加了音效和推车
    //connect(timer,&QTimer::timeout,this,&MainWindow::addPlants);//随机生成植物
    view=new QGraphicsView(scene,this);
    //ui->graphicsView->setScene(scene);
    view->resize(WIDTH+2,HEIGHT+2);
    timer->start(33);
    view->show();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete view;
    delete ui;
}

void MainWindow::addZombies()
{
    int time=100;
    static int counter=0;
    if(++counter>time)
    {
        counter=0;
        int type=rand()%100;
        Zombie* zombie=nullptr;
        if(type<40)
            zombie=new normalzombie;
        else if(type<60)
            zombie=new screenzombie;
        else if(type<75)
            zombie=new Conezombie;
        else if(type<90)
            zombie=new Bucketzombie;
        else if(type<100)
            zombie=new Footballzombie;
        int row=(rand()%5)*GAP+ROW1;
        zombie->setPos(ZOMBIE_START,row);
        zombie->setZValue(2);
        scene->addItem(zombie);
    }
}

void MainWindow::addPlants()
{
    int time=200;
    static int counter=0;
    if(++counter>time)
    {
        counter=0;
        int type=rand()%100;
        Plants* plant=nullptr;
        if(type<20)
            plant=new Sunflower;
        else if(type<40)
            plant=new peashooter;
        else if(type<55)
            plant=new snowpeashooter;
        else if(type<65)
            plant=new Repeater;
        else if(type<80)
            plant=new Wallnut;
        else if(type<90)
            plant=new Potatomine;
        else if(type<100)
            plant= new Cherrybomb;
        QList<QGraphicsItem*> items=scene->items();
        int row=(rand()%5)*GAP+ROW1;
        int col=PLANT_START+(rand()%9)*80;
        if(!items.isEmpty())
        {
            while(true)
            {
                row=(rand()%5)*GAP+ROW1;
                col=PLANT_START+(rand()%9)*80;
                foreach(QGraphicsItem* item,items)
                {
                    if(item->type()==Plants::Type)
                    {
                        if(row==item->y()||col==item->x())
                            break;
                    }
                }break;
            }
        }
        plant->setZValue(2);
        plant->setPos(col,row);
        scene->addItem(plant);
    }
}





void MainWindow::playmusic()
{
    static int counter=0;
    if(!sound_bk->isPlaying()&&++counter>=150)
    {
        sound_bk->play();
    }
}

