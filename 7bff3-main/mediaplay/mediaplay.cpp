#include "mediaplay.h"
#include "ui_mediaplay.h"
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMediaContent>
#include <QTimer>
#include <QPixmap>

mediaplay::mediaplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mediaplay)
{
    ui->setupUi(this);
    cur_vol = 100;

    //初始化变量
    layer = new QVBoxLayout;
    player = new QMediaPlayer;
    VideoWidget = new QVideoWidget;
    playlist = new QMediaPlaylist;
    fullflag = false;
    plindex = 0;
    for(int i=0; i<100; i++)
        srcpath[i] = "-2";

    ui->volumn->setValue(100);  //初始化音量为100
    ui->progress_bar->setMinimum(0);  //设置进度条最小为零
    ui->progress_bar->setSingleStep(1);  //设置进度条每步走的大小
    playlist->setPlaybackMode(QMediaPlaylist::Loop);  //设置播放模式一开始为列表循环
    ui->playmode->setText("列表循环");
    player->setPlaybackRate(1.0);  //设置一开始的播放速度为1.0倍，即正常速度
    ui->playrate->setText("1.0");
    before.setRect(width()*645/794,0,width()*151/796,height()*40/47);  //记录播放列表框listwidget的位置
    start_up = true;  //设置当前为第一次打开状态
    ui->show_hide->setStyleSheet("QPushButton{color:#ffffff}");  //设置按钮文字颜色为白色

    //连接槽函数
    //获取当前播放的视频流的总时间
    QObject::connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(getduration(qint64)));

    //设置播放进度
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(myautosetValue(qint64)));
    QObject::connect(ui->progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(mymanualsetValue(int)));

    //设置音量
    QObject::connect(ui->volumn,SIGNAL(sliderMoved(int)),this,SLOT(setvolvalue(int)));

    //listwidget双击事件槽函数
    QObject::connect(ui->videolist,
                     SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                     this,
                     SLOT(doubleclick_play(QListWidgetItem *)));

    //设置窗口标题栏，实现实时显示当前播放的文件名字
    QObject::connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(setwindowtitle(int)));

}

mediaplay::~mediaplay()
{
    delete ui;
}

//获取视频的时间长度，并用label显示
void mediaplay::getduration(qint64 playtime)
{
    int h,m,s;
    playtime = player->duration();
    playtime /= 1000;
    h = playtime/3600;
    m = (playtime-h*3600)/60;
    s = playtime-h*3600-m*60;
    ui->label_time->setText(QString("%1:%2:%3").arg(h).arg(m).arg(s));
    ui->label_time->setStyleSheet("color:white");
    if(playtime != 0)
    {
        ui->progress_bar->setMaximum(playtime);
    }
}

//播放视频的初始化操作
void mediaplay::startplayer()
{
    VideoWidget->installEventFilter(this);  //把VideoWidget加入到过滤器中，以捕获键盘/鼠标事件

    layer->setMargin(0);

    //指定视频播放的位置为screen的位置，screen为label控件
    VideoWidget->resize(ui->screen->size());
    layer->addWidget(VideoWidget);
    ui->screen->setLayout(layer);

    //设置输出
    player->setVideoOutput(VideoWidget);  //将QVideoWidget视频输出附加到媒体播放器。
                                          //如果媒体播放器已经附加了视频输出，它将被替换为一个新的。

    player->setPlaylist(playlist);  //设置播放器的播放列表

    player->setPosition(0);  //设置播放器的播放进度，一开始置为0

    player->play();  //开始播放

    //设置按键的图片
    ui->pushButton_begin->setStyleSheet("QPushButton"
                                        "{ border-image: url(:/pause.jpg); }");

    //设置焦点
    VideoWidget->setFocus();
}

//重写事件过滤器
bool mediaplay::eventFilter(QObject *recv,QEvent *e)
{
    //定义播放状态标志位，可以用QMediaPlayer::StoppedState这些来代替
    static bool pause_flag = false;

    //判断被观察者是否为视频
    if(recv == VideoWidget)
    {
        //判断事件是否为键盘事件
        if(e->type() == QEvent::KeyPress)
        {
            QKeyEvent *mykey = (QKeyEvent *)e;
            //判断是哪一类键盘事件
            switch(mykey->key())
            {
                //回车键，控制是否全屏
                case Qt::Key_Enter:
                        if(fullflag == true)
                            fullflag = false;
                        else
                            fullflag = true;
                        VideoWidget->setFullScreen(fullflag);
                    break;

                //方向键左，控制播放进度，快退
                case Qt::Key_Left:
                        curpos = player->position();
                        curpos -= 5000;
                        player->setPosition(curpos);
                    break;

                //方向键右，控制播放进度，快进
                case Qt::Key_Right:
                        curpos = player->position();
                        curpos += 5000;
                        player->setPosition(curpos);
                     break;

                //方向键上，控制音量，增大
                case Qt::Key_Up:
                        if(cur_vol < 100)
                            cur_vol++;
                        player->setVolume(cur_vol);
                        ui->volumn->setValue(cur_vol);
                    break;

                //方向键下，控制音量，减少
                case Qt::Key_Down:
                        if(cur_vol > 0)
                            cur_vol--;
                        ui->volumn->setValue(cur_vol);
                        player->setVolume(cur_vol);
                     break;

                //控制键，控制播放/暂停
                case Qt::Key_Space:
                        if(pause_flag == false)
                        {
                            player->pause();
                            pause_flag = true;
                            ui->pushButton_begin->setStyleSheet("QPushButton"
                                                                "{ border-image: url(:/bofang.jpg); }");
                        }
                        else if(pause_flag == true)
                        {
                            player->play();
                            pause_flag = false;
                            ui->pushButton_begin->setStyleSheet("QPushButton"
                                                                "{ border-image: url(:/pause.jpg); }");
                        }
                 break;
            }
        }
    }

    //判断是否为鼠标双击事件，用于鼠标双击控制全屏显示
    if(e->type() == QEvent::MouseButtonDblClick)
    {
        //因为双击事件也会触发单击事件，导致视频暂停，所以双击事件需要让视频继续播放
        player->play();
        if(fullflag == true)
            fullflag = false;
        else
            fullflag = true;
        VideoWidget->setFullScreen(fullflag);  //设置全屏
    }

    //判断是否为鼠标按下事件，用于鼠标单击控制暂停/播放
    if(e->type() == QEvent::MouseButtonPress)
    {
        if(pause_flag == false)
        {
            player->pause();
            pause_flag = true;
        }
        else if(pause_flag == true)
        {
            player->play();
            pause_flag = false;
        }
    }
    return QObject::eventFilter(recv,e);
}

//打开按钮槽函数，用于打开流文件
void mediaplay::on_pushButton_open_clicked()
{
    //用string链表存储打开的文件的路径，并设置打开时能看到的文件类型
    srcFilePath = QFileDialog::getOpenFileNames(
                this, "choose file", "E:\\", "file (*.mp4 *.flv *.jpg *.qlv *.mp3)");
    //判断是否有该路径
    if(srcFilePath.isEmpty())
        return;

    //打开文件成功，让第一次运行标志置为false
    start_up = false;

    //遍历路径链表，把流文件加入到播放列表，并把文件名存储到string数组srcpath中，以便后续操作
    QStringList::Iterator it = srcFilePath.begin();
    while(it != srcFilePath.end())
    {
        //设置插入到播放列表的文件的路径和插入位置
        playlist->insertMedia(plindex,QMediaContent(QUrl::fromLocalFile(*it)));
        QString filename;
        QFileInfo f(*it);
        filename = f.fileName();  //获取文件名
        //把文件名和位置存储到string数组srcpath中
        for(int i=0; i<100; i++)
        {
            if(srcpath[i] == "-2")
            {
                srcpath[i] = QString("%1").arg(plindex);
                srcpath[i+1] = filename;
                break;
            }
        }
        plindex++;  //让插入的位置加一

        //把文件名加入到listwidget列表框
        QListWidgetItem *item1 = new QListWidgetItem(filename);
        item1->setForeground(Qt::white);
        ui->videolist->addItem(item1);

        //把文件名拆分，判断是什么后缀（类型）的文件
        filename = filename.section(".",1,1);
        if(filename == "mp3")
        {
            QPixmap pix(":/music.jpg");
            pix = pix.scaled(ui->screen->size());
            ui->screen->setPixmap(pix);
        }
        ++it;
    }

    //开始播放刚打开的视频
    startplayer();
    playlist->setCurrentIndex(plindex-1);
}

//上一个（首）按钮槽函数
void mediaplay::on_pushButton_last_clicked()
{
    //判断列表索引是否已越界
    if(playlist->previousIndex() == -1)
       return;

    //上一个（首）
    playlist->previous();

    //判断当前状态，如果是停止状态，就让视频开始播放
    if(player->state() != QMediaPlayer::PlayingState)
    {
        player->play();
        ui->pushButton_begin->setStyleSheet("QPushButton"
                                            "{ border-image: url(:/pause.jpg); }");
    }

    //设置屏幕显示图片
    QPixmap pix(":/music.jpg");
    pix = pix.scaled(ui->screen->size());
    ui->screen->setPixmap(pix);
}

//开始/暂停按钮槽函数
void mediaplay::on_pushButton_begin_clicked()
{
    //判断是否第一次打开本软件
    if(start_up == true)
        return;

    //判断当前状态，决定是开始播放还是暂停
    if(player->state() == QMediaPlayer::StoppedState)
        startplayer();
    else if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->pushButton_begin->setStyleSheet("QPushButton"
                                            "{ border-image: url(:/bofang.jpg); }");
    }
    else if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        ui->pushButton_begin->setStyleSheet("QPushButton"
                                            "{ border-image: url(:/pause.jpg); }");
    }
}

//下一首（个）按钮槽函数
void mediaplay::on_pushButton_next_clicked()
{
    //判断列表索引是否已越界
    if(playlist->nextIndex() == -1)
        return;

    //下一首（个）
    playlist->next();
    QPixmap pix(":/music.jpg");
    pix = pix.scaled(ui->screen->size());
    ui->screen->setPixmap(pix);
    if(player->state() != QMediaPlayer::PlayingState)
    {
        player->play();
        ui->pushButton_begin->setStyleSheet("QPushButton"
                                            "{ border-image: url(:/pause.jpg); }");
    }
}

//停止按钮槽函数
void mediaplay::on_pushButton_stop_clicked()
{
    //停止播放
    player->stop();

    //设置屏幕显示初始时的图片
    QPixmap pix(":/video.jpg");
    pix = pix.scaled(ui->screen->size());
    ui->screen->setPixmap(pix);
    ui->pushButton_begin->setStyleSheet("QPushButton"
                                        "{ border-image: url(:/bofang.jpg); }");
}

//全屏按钮槽函数
void mediaplay::on_pushButton_fullscreen_clicked()
{
    if(fullflag == true)
        fullflag = false;
    else
        fullflag = true;
    VideoWidget->setFullScreen(fullflag);
}

//重写窗口尺寸变化事件，实时更新screen的大小
void mediaplay::resizeEvent(QResizeEvent * event)
{
    before.setRect(width()*645/794,0,width()*151/796,height()*40/47);
    if(judge_str == "mp3")
    {
        QPixmap pix(":/music.jpg");
        pix = pix.scaled(ui->screen->size());
        ui->screen->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/video.jpg");
        pix = pix.scaled(ui->screen->size());
        ui->screen->setPixmap(pix);
    }
    QWidget::resizeEvent(event);
}

//重写listwidget的双击事件，实现双击播放
void mediaplay::doubleclick_play(QListWidgetItem *item)
{
    QPixmap pix(":/music.jpg");
    pix = pix.scaled(ui->screen->size());

    //从srcpath数组里面依次取出文件名与用户双击listwidget的item的text比较，相同则取出该文件的位置，然后设置为当前播放
    for(int i=0; i<100; i++)
    {
        if(i%2 != 0)
            if(srcpath[i] == item->text())
            {
                playlist->setCurrentIndex(srcpath[i-1].toInt());
                judge_str = srcpath[i].section('.', 1, 1);
                if(judge_str == "mp3")
                    ui->screen->setPixmap(pix);

                //如果当前状态为停止或者暂停，都让视频开始播放
                if(player->state() == QMediaPlayer::StoppedState)
                     player->play();
                else if(player->state() == QMediaPlayer::PausedState)
                    player->play();

            }
    }
    ui->pushButton_begin->setStyleSheet("QPushButton"
                                        "{ border-image: url(:/pause.jpg); }");
}

//自动调节播放进度，显示在滑动条上，并在label上显示时间
void mediaplay::myautosetValue(qint64 cur_val)
{
    static int h,m,s;
    cur_val /= 1000;
    h = cur_val/3600;
    m = (cur_val-h*3600)/60;
    s = cur_val-h*3600-m*60;

    ui->label_playtime->setText(QString("%1:%2:%3 /").arg(h).arg(m).arg(s));
    ui->label_playtime->setStyleSheet("color:white");
    ui->progress_bar->setValue(cur_val);
}

//手动调节播放进度，显示在滑动条上，并在label上显示时间
void mediaplay::mymanualsetValue(int cur_val)
{
    static int h,m,s;
    h = cur_val/3600;
    m = cur_val/60;
    s = cur_val%60;
    ui->label_playtime->setText(QString("%1:%2:%3 /").arg(h).arg(m).arg(s));
    ui->label_playtime->setStyleSheet("color:white");

    player->setPosition(cur_val*1000);
}

//设置音量
void mediaplay::setvolvalue(int cur_val)
{
    cur_val = ui->volumn->value();
    player->setVolume(cur_val);
}

//设置窗口标题
void mediaplay::setwindowtitle(int pos)
{
    for(int i=0; i<100; i+=2)
    {
        if(srcpath[i].toInt() == pos)
        {
            this->setWindowTitle(srcpath[i+1]);
        }
    }
}

//设置播放模式
void mediaplay::on_playmode_clicked()
{
    switch(playlist->playbackMode())
    {
        case QMediaPlaylist::CurrentItemOnce:
               ui->playmode->setText("单循环");
               playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                 break;
        case QMediaPlaylist::CurrentItemInLoop:
               ui->playmode->setText("顺序播放");
               playlist->setPlaybackMode(QMediaPlaylist::Sequential);
                 break;
        case QMediaPlaylist::Sequential:
               ui->playmode->setText("列表循环");
               playlist->setPlaybackMode(QMediaPlaylist::Loop);
                 break;
        case QMediaPlaylist::Loop:
               ui->playmode->setText("随机播放");
               playlist->setPlaybackMode(QMediaPlaylist::Random);
                 break;
        case QMediaPlaylist::Random:
               ui->playmode->setText("播放一次");
               playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
                 break;
    }
}

//设置播放速度
void mediaplay::on_playrate_clicked()
{
    if(player->playbackRate() == 0.5)
    {
        ui->playrate->setText("1.0");
        player->setPlaybackRate(1.0);
    }
    else if(player->playbackRate() == 1.0)
    {
        ui->playrate->setText("1.5");
        player->setPlaybackRate(1.5);
    }
    else if(player->playbackRate() == 1.5)
    {
        ui->playrate->setText("2.0");
        player->setPlaybackRate(2.0);
    }
    else if(player->playbackRate() == 2.0)
    {
        ui->playrate->setText("0.5");
        player->setPlaybackRate(0.5);
    }
}

//音量按钮槽函数
void mediaplay::on_trumpet_clicked()
{
    static bool noiseless = false;
    if(!noiseless)
    {
        player->setVolume(0);
        ui->volumn->setValue(0);
        ui->trumpet->setStyleSheet("QPushButton"
                                  "{ border-image: url(:/silence.jpg); }");
        noiseless = true;
    }
    else
    {
        player->setVolume(cur_vol);
        ui->volumn->setValue(cur_vol);
        ui->trumpet->setStyleSheet("QPushButton"
                                  "{ border-image: url(:/volumn.jpg); }");
        noiseless = false;
    }
}

//播放列表显示/隐藏按钮槽函数
void mediaplay::on_show_hide_clicked()
{
    static bool v_flag = false;
    if(!v_flag)
    {
        ui->videolist->setVisible(false);
        v_flag = true;
        ui->show_hide->setText("《");
    }
    else
    {
        ui->videolist->setVisible(true);
        ui->videolist->setGeometry(before);
        v_flag = false;
        ui->show_hide->setText("》");
    }
    this->resize(this->size() - QSize(1,1));

    if(judge_str == "mp3")
    {
        QPixmap pix(":/music.jpg");
        pix = pix.scaled(ui->screen->size());
        ui->screen->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/video.jpg");
        pix = pix.scaled(ui->screen->size());
        ui->screen->setPixmap(pix);
    }
    this->resize(this->size() + QSize(1,1));
}
