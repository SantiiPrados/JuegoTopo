#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qpaintbox.h>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QInputDialog>
#include <QProgressBar>
#include <QtWidgets>
#include <QDebug>

#define MAXTIMEOUTSIDE 2000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief onQTimer1
     *
     * Recibe la señal timeout de QTimer
     */
    void onQTimer1();

    void onQSerialPort1Rx();

    void on_pushButton_3_clicked();

    void sendData();

    void decodeData();

    void encodeData(uint8_t id);

    void on_encodeData_clicked();

    void on_checkBox_3_toggled(bool checked);

    void leds_botons_Print();

    void inGame();

    void randLedGen(uint8_t indice);

private:
    Ui::MainWindow *ui;

    QSerialPort *QSerialPort1;

    QTimer *QTimer1;
    QPaintBox *QPaintBox1;

    QString strRx, strRxProcess;

    uint8_t bufRX[48], index, nbytes, cks, header, timeoutRx;
    uint8_t payLoad[4], ID, length;

    int counter;

    typedef union {
        int32_t i32;
        int8_t i8[4];
        uint32_t ui32;
        uint16_t ui16[2];
        uint8_t ui8[4];
    }_udat;
    _udat myWord;

    typedef enum{
        ACK=0x0D,
        ALIVE=0xF0,
        FIRMWARE=0xF1,
        CHANGE_BOTONES=0xFA,
        GET_LEDS=0xFB,
        SET_LEDS=0xFC,
        GET_BOTONES=0xFD,
        OTHERS
    }_eID;

    typedef enum{
        BUTTON_DOWN,    //0
        BUTTON_UP,      //1
        BUTTON_FALLING, //2
        BUTTON_RISING   //3
    }_eButtonState;

    typedef struct _sSendBotones{
        uint16_t numButton;
        uint8_t flanco;
        uint32_t timerRead;
        uint32_t timePress=0;
    }_sSendBotones;
    _sSendBotones botones;

    uint16_t ledSelect=0;

    typedef enum{
        WAITING,
        IN_GAME,
        LOSE,
    }_eGAMESTATES;

    typedef struct _sGame{
        uint8_t state=0;
        uint16_t time=0;
        int32_t puntaje;
    }_sGame;
    _sGame game;

    typedef struct{
        uint8_t numLed;
        uint8_t state[4];
        uint8_t isOut[4];
        uint16_t timeWait[4];
        uint16_t timeOut[4];
    }_sled;
    _sled led;
    uint8_t mask[4] = {0x01, 0x01, 0x04, 0x08};
};
#endif // MAINWINDOW_H
