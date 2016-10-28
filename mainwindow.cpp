
#include <QTimer>
#include <QThreadPool>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "psvr.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->DebugLabel->setText("test");

	psvr.Open();

	psvr_thread = new PSVRThread(this);
	connect(psvr_thread, SIGNAL(PSVRAcceleration(short, short, short)), this, SLOT(PSVRAcceleration(short, short, short)));
	psvr_thread->start();

	video_player = new VideoPlayer(512, 512);
	video_player->PlayVideo("test.mp4");
}

MainWindow::~MainWindow()
{
	delete video_player;
	psvr.Close();
	delete ui;
}

void MainWindow::PSVRAcceleration(short x, short y, short z)
{
	ui->DebugLabel->setText(QString::asprintf("%f %f %f", psvr.GetRotationX(), psvr.GetRotationY(), psvr.GetRotationZ()));
}
