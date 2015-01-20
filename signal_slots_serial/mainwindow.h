#include "mainwindow.h"
#include "ui_mainwindow.h"


controlPane control;

frontView::frontView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frontView)
{

    ui->setupUi(this);
    callReference cCom;
    //connect(&cCom,SIGNAL(numberChanged(int)),this,SLOT(changeProgressBar(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),&cCom,SLOT(printOut(int)));
    cCom.changeVal(32);
    // ...





}

frontView::~frontView()
{
    on_pushButton_2_clicked();
    delete ui;

}

void frontView::on_pushButton_clicked()
{
    bool status;
    control.initiateAconnection(status);
    control.start();
    ui->pushButton->setEnabled(false);
    /*
     * if(status)
    ui->statusBar->showMessage("Device is ready!");
    else{
        ui->statusBar->showMessage("Device is not ready!");
        control.closeConnection();
        ui->pushButton->setEnabled(true);
        control.terminate();
    }
    */
}

void frontView::on_pushButton_3_clicked()
{
    control.votingStop();

}

void frontView::on_pushButton_4_clicked()
{
    control.votingStart();


}

void frontView::on_pushButton_2_clicked()
{
    // STOP
    control.votingStop();
    control.closeConnection();
    control.terminate();
}



void frontView::changeProgressBar(int progress){
    ui->progressBar1->setValue(progress);
    cout<<progress<<endl;
}
