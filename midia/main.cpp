#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

class VideoPlayer : public QWidget {
    Q_OBJECT

public:
      QMediaPlayer *m_player;
    VideoPlayer(const QString &videoPath, QWidget *parent = nullptr)
        : QWidget(parent), m_videoPath(videoPath), m_isPlaying(false) {

        // 创建视频显示控件
        m_videoWidget = new QVideoWidget(this);
        m_videoWidget->setFullScreen(true); // 全屏播放

        // 创建媒体播放器
        m_player = new QMediaPlayer(this);
        m_player->setVideoOutput(m_videoWidget);

        // 创建布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(m_videoWidget);
        setLayout(layout);

        // 设置视频文件
        m_player->setMedia(QUrl::fromLocalFile(m_videoPath));

        // 连接信号槽
        connect(m_player, &QMediaPlayer::stateChanged, this, &VideoPlayer::onStateChanged);
        connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &VideoPlayer::onError);
    }

    void start() {
        m_player->play();
        m_isPlaying = true;
    }

private slots:
    void onStateChanged(QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState) {
            // 视频播放结束，重新开始播放
            m_player->play();
        }
    }

    void onError(QMediaPlayer::Error error) {
        qDebug() << "播放错误:" << m_player->errorString();
    }

    void onTimerTimeout() {
        if (m_isPlaying) {
            // 停止当前播放
            m_player->stop();
            // 重新开始播放
            m_player->play();
        }
    }

private:
    QVideoWidget *m_videoWidget;

    QString m_videoPath;
    bool m_isPlaying;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 指定视频文件路径
    QString videoPath = "path/to/your/video.mp4"; // 替换为你的视频文件路径

    // 创建视频播放器
    VideoPlayer player(videoPath);

    // 显示窗口
    player.resize(800, 600);
    player.show();

    // 自动开始播放
    player.start();

    // 设置定时器以实现定时循环播放，例如每5分钟重新播放
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&player]() {
        // 停止当前播放
        player.m_player->stop();
        // 重新开始播放
        player.m_player->play();
    });

    // 设置定时器间隔为5分钟（300000毫秒）
    timer.start(300000);

    return app.exec();
}

