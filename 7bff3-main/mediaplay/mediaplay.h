#ifndef MEDIAPLAY_H
#define MEDIAPLAY_H

#include <QWidget>
#include <QEvent>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QList>
#include <QListWidgetItem>
#include <QStringList>

namespace Ui {
class mediaplay;
}

class mediaplay : public QWidget
{
    Q_OBJECT

public:
    explicit mediaplay(QWidget *parent = 0);
    ~mediaplay();
    void startplayer();

private slots:
    void on_pushButton_begin_clicked();  //开始按钮槽函数

    void on_pushButton_next_clicked();  //下一首槽函数

    void on_pushButton_open_clicked();  //打开文件按钮槽函数

    void on_pushButton_fullscreen_clicked();  //全屏按钮槽函数

    void on_pushButton_last_clicked();  //上一首按钮槽函数

    void on_pushButton_stop_clicked();  //停止按钮槽函数

    void getduration(qint64 playtime);  //获取音视频流的总时间槽函数

    void myautosetValue(qint64 cur_val);  //自动调节进度槽函数

    void mymanualsetValue(int cur_val);  //手动调节进度槽函数

    void setvolvalue(int cur_val);  //调节音量槽函数

    void doubleclick_play(QListWidgetItem *item);  //双击列表播放槽函数

    void setwindowtitle(int pos);  //设置窗口标题实时显示播放内容槽函数

    void on_playmode_clicked();  //设置播放模式槽函数——随机播放 . . .

    void on_playrate_clicked();  //设置播放速度槽函数

    void on_trumpet_clicked();  //设置喇叭（音量）图标槽函数——点击静音，再次点击恢复

    void on_show_hide_clicked();  //播放列表显示/隐藏按钮槽函数

protected:
    virtual bool eventFilter(QObject *recv,QEvent *e);  //重写事件过滤器，捕捉各种事件、如键盘，鼠标，可拓展

    virtual void resizeEvent(QResizeEvent * event);  //重写窗口大小调节事件，窗口大小改变，其他部件尺寸也跟着改变

private:
    Ui::mediaplay *ui;
    QVBoxLayout *layer;  //视频布局显示相关的对象
    QMediaPlayer* player;  //解析音视频流文件的对象
    QVideoWidget* VideoWidget;  //播放视频对象
    QMediaPlaylist *playlist;  //播放列表对象
    bool fullflag;  //全屏标志位
    QStringList srcFilePath;  //存储所打开文件的路径（一个或多个文件）
    qint64 curpos;  //记录当前播放位置
    qint64 playtime;  //记录音视频的总时间
    int cur_vol;  //记录当前音量
    QString srcpath[100];  //记录文件名和文件在播放列表中的位置的数组
    qint8 plindex;  //设置打开的视频在播放列表中的位置
    QString judge_str;  //记录文件名，用于判断是什么类型的文件
    QRect before;  //记录listwidget控件显示时的位置，
    bool start_up;  //是否开始播放的标志位
};

#endif // MEDIAPLAY_H
