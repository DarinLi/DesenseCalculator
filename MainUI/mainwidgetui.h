#ifndef MAINWIDGETUI_H
#define MAINWIDGETUI_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include <QTranslator>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QDir>

#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>

#define gsmbandnummax     10
#define utmsbandnummax    10
#define tdscdmabandnummax 10
#define ltebandnummax     30
#define wifigpsbandnummax 10

namespace Ui {
class MainWidgetUI;
}

class MainWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetUI(QWidget *parent = nullptr);
    ~MainWidgetUI();

public:
    QVariant iniFilesValueRead(const QString &key1, const QString &key2);
    void iniFilesSetValue(const QString &key1, const QString &key2, const QVariant &value);
    void desenseCalculator_setBaseInformation(void);

    void desenseCalculator_RFBandInfoSetCheck(void);//设置默认的干扰频段
    void desenseCalculator_RFBandInfoCheck(void);//获取当前需要计算干扰的频段

    void desenseCalculator_RFDesenseDataTableShow(void);
    void desenseCalculator_RFDesenseDataTableCreate(QTableWidget *rfTablePtr, int rfbandnum);

    QString desenseCalculator_RFBandInfo(QTableWidget *rfTablePtr, int curruntband);

    void desenseCalculator_setTableItemRowCount(QTableWidget *rfTablePtr, int rfbandnum);
    void desenseCalculator_RFTableInfo(QTableWidget *tabletemp,int rownum);
    void desenseCalculator_setRFBandFreq(QTableWidget *rfTablePtr, int rfbandnum);
    void desenseCalculator_setRFBandFreqDelta(QTableWidget *rfTablePtr);
    void desenseCalculator_setRFDataSum(QTableWidget *rfTablePtr, int rfbandnum);

private slots:
    void desenseCalculator_setVMipiValue(void);
    void desenseCalculator_RFDataCalculator(void);

private:
    double absdouble(double x);

private:
    struct RFBandINFO{
        int gsmbandnum = 0;
        QString gsmbandstatus[gsmbandnummax];//GSM850 GSM900 DCS1800 PCS1900
        int utmsbandnum = 0;
        QString utmsbandstatus[utmsbandnummax];//WCDMA-B1 WCDMA-B2 WCDMA-B3 WCDMA-B4 WCDMA-B5 WCDMA-B8
        int tdscdmabandnum = 0;
        QString tdscdmabandstatus[tdscdmabandnummax];//TDSCDMA-B34 TDSCDMA-B39 CDMA-BC0 CDMA-BC1 CDMA-BC10
        int ltebandnum = 0;
        QString ltebandstatus[ltebandnummax];//B1 B2 B3 B4 B5 B7 B8 B12 B13 B17 B20 B25 B26 B28 B38 B39 B40 B41 B42
        int wifigpsbandnum = 0;
        QString wifigpsbandstatus[wifigpsbandnummax];//GPS WIFI2.4G-11B WIFI2.4G-11G WIFI2.4G-11N WIFI5G-11A WIFI5G-11N WIFI5G-11AC
    };

private:
    struct RFBandINFO rfbandinfo;
    struct RFBandINFO *rfbandinfoptr = &rfbandinfo;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWidgetUI *ui;
};

#endif // MAINWIDGETUI_H
