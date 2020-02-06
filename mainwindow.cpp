#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

const int MAX_HEIGHT = 90;
const int MAX_WIDTH = 90;

int w_a[MAX_WIDTH][MAX_HEIGHT];
int w_b[MAX_WIDTH][MAX_HEIGHT];
const QString COLORS[5] = {"white","black","#ff4000","#80ff00","#0040ff"};

int RULE_SURVIVE[3]={3,4,5};
int RULE_BIRTH[1]={2};
int RULE_GENS=4;

int sizeSurvive = (sizeof(RULE_SURVIVE)/sizeof(*RULE_SURVIVE));
int sizeBirth = (sizeof(RULE_BIRTH)/sizeof(*RULE_BIRTH));

QVector<QLabel*> v;

void setColor(QLabel *label, int state){
    label->setStyleSheet("QLabel { background-color : "+COLORS[state]+";}");
}

bool ruleContains(int n, int rule[]) {
    int size = (sizeof(rule)/sizeof(*rule));
    for(int i=0; i < size; i++) {
        if ( rule[i] == n )
            return true;
    }
    return false;
}

int calNeighbors(int x,int y){
    int totalSum = 0;
        int xLeft = x-1;
        int xRight = x+1;
        int yTop = y-1;
        int yBottom = y+1;

        if (xLeft >=0 && yTop >=0 && w_a[xLeft][yTop] == 1) totalSum++;
        if (yTop >= 0 && w_a[x][yTop] ==1 ) totalSum++;
        if (xRight < MAX_WIDTH && yTop >= 0 && w_a[xRight][yTop] ==1 ) totalSum++;
        if (xLeft >=0 && w_a[xLeft][y] ==1 ) totalSum++;
        if (xRight < MAX_WIDTH && w_a[xRight][y] ==1 ) totalSum++;
        if (xLeft >=0 && yBottom < MAX_HEIGHT && w_a[xLeft][yBottom] ==1 ) totalSum++;
        if (yBottom < MAX_HEIGHT && w_a[x][yBottom] ==1 ) totalSum++;
        if (xRight < MAX_WIDTH && yBottom < MAX_HEIGHT && w_a[xRight][yBottom] ==1 ) totalSum++;

        return totalSum;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    for (int i = 0;i<MAX_WIDTH;++i)
        for (int j = 0; j<MAX_HEIGHT;++j){
         QLabel *label = new QLabel();

         label->setFixedSize(5,5);
         quint32 value = QRandomGenerator::global()->generate();
         if (value %2 == 0){
             w_a[i][j] = 0;
         } else {
             w_a[i][j] = 1;
            }

         label->setMargin(0);
         label->setIndent(0);
         v.push_back(label);
         ui->gridLayout->addWidget(label, i, j);

    }
    ui->gridLayout->setHorizontalSpacing(0);
    ui->gridLayout->setVerticalSpacing(0);

//    QTimer *timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this, SLOT(render()));
//    timer->start(50);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::render(){
    for (int i = 0;i<MAX_WIDTH;++i){
        for (int j = 0; j<MAX_HEIGHT;++j){
            QLabel *label = v[MAX_HEIGHT*i+j];
            setColor(label, w_a[i][j]);
            w_b[i][j]=w_a[i][j];
        }
    }

    for (int i = 0;i<MAX_WIDTH;++i){
        for (int j = 0; j<MAX_HEIGHT;++j){
            int currentState = w_b[i][j];
            if ( currentState == 0) {
                        int neighborsOn = calNeighbors(i,j);
                        if ( ruleContains(neighborsOn, RULE_BIRTH))
                            w_a[i][j] = 1;
                    }
                    else if ( currentState > 0 && (currentState < (RULE_GENS - 1) || RULE_GENS == 2) ) {

                        int neighborsOn = (sizeSurvive == 0) ? 0 : calNeighbors(i,j);
                        bool shouldSurvive = ruleContains(neighborsOn, RULE_SURVIVE);
                        if (currentState == 1 && shouldSurvive)
                        {
                            w_a[i][j] = currentState;
                        }
                        else if (!shouldSurvive) {
                                w_a[i][j] = (currentState + 1) % RULE_GENS;
                        }

                        if ( currentState > 1)
                            w_a[i][j] = currentState + 1;
                    }
                    else if (currentState >= (RULE_GENS - 1)) {
                        w_a[i][j] = 0;
                    }
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->render();
}
