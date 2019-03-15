#include "mainwidgetui.h"
#include "ui_mainwidgetui.h"

MainWidgetUI::MainWidgetUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidgetUI)
{
    ui->setupUi(this);

    desenseCalculator_setBaseInformation();
    desenseCalculator_RFBandInfoSetCheck();
    desenseCalculator_RFDesenseDataTableShow();
}

MainWidgetUI::~MainWidgetUI()
{
    delete ui;
}

void MainWidgetUI::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QVariant MainWidgetUI::iniFilesValueRead(const QString &key1, const QString &key2)
{
    QSettings iniFileRead("./RFBandInfo.ini", QSettings::IniFormat);

    return iniFileRead.value(key1 + "/" + key2);
}

void MainWidgetUI::iniFilesSetValue(const QString &key1, const QString &key2, const QVariant &value)
{
    QSettings iniFile("./RFBandInfo.ini", QSettings::IniFormat);

    iniFile.setValue(key1 + "/" + key2, value);
}

void MainWidgetUI::desenseCalculator_setBaseInformation(void)
{
    ui->CLK_ExistRisks_Value->setText(iniFilesValueRead(QStringLiteral("Base Information"),
                                                        QStringLiteral("ClkExistRisks")).toString());
    ui->CLK_Risks_Value->setText(iniFilesValueRead(QStringLiteral("Base Information"),
                                                   QStringLiteral("ClkRisks")).toString());
    ui->MIPI_CLK_Value->setText(iniFilesValueRead(QStringLiteral("Base Information"),
                                                  QStringLiteral("BitCLK")).toString());

    ui->Screen_Bits_Value->setText(tr("24 Bits"));

    connect(ui->MIPI_CLK_Value, &QLineEdit::editingFinished, this, &MainWidgetUI::desenseCalculator_setVMipiValue);
    connect(ui->RF_Calculator, &QPushButton::clicked, this, &MainWidgetUI::desenseCalculator_RFDataCalculator);

    emit desenseCalculator_setVMipiValue();
}

void MainWidgetUI::desenseCalculator_setVMipiValue(void)
{
    double vmipi_temp = ui->MIPI_CLK_Value->text().toDouble();
    QString vmipi_str = QString("%1%2").arg(QString::number(vmipi_temp/24.0,'f',3)).arg("MHz");

    ui->Vmipi_CLK_Value->setText(vmipi_str);
}

void MainWidgetUI::desenseCalculator_RFBandInfoSetCheck(void)
{
    ui->GSM850_Ck->setChecked(true);
    ui->GSM900_Ck->setChecked(true);
    ui->DCS1800_Ck->setChecked(true);
    ui->PCS1900_Ck->setChecked(true);

    ui->WCDMA_B1_Ck->setChecked(true);
    ui->WCDMA_B2_Ck->setChecked(true);
    ui->WCDMA_B3_Ck->setChecked(false);
    ui->WCDMA_B4_Ck->setChecked(false);
    ui->WCDMA_B5_Ck->setChecked(true);
    ui->WCDMA_B8_Ck->setChecked(true);

    ui->TDSCMDA_B34_Ck->setChecked(false);
    ui->TDSCMDA_B39_Ck->setChecked(false);

    ui->CDMA_BC0_Ck->setChecked(true);
    ui->CDMA_BC1_Ck->setChecked(true);
    ui->CDMA_BC10_Ck->setChecked(false);

    ui->FDD_B1_Ck->setChecked(true);
    ui->FDD_B2_Ck->setChecked(true);
    ui->FDD_B3_Ck->setChecked(true);
    ui->FDD_B4_Ck->setChecked(false);
    ui->FDD_B5_Ck->setChecked(true);
    ui->FDD_B7_Ck->setChecked(true);
    ui->FDD_B8_Ck->setChecked(true);
    ui->FDD_B12_Ck->setChecked(false);
    ui->FDD_B13_Ck->setChecked(false);
    ui->FDD_B17_Ck->setChecked(false);
    ui->FDD_B20_Ck->setChecked(false);
    ui->FDD_B25_Ck->setChecked(false);
    ui->FDD_B26_Ck->setChecked(false);
    ui->FDD_B28_Ck->setChecked(true);

    ui->TDD_B38_Ck->setChecked(false);
    ui->TDD_B39_Ck->setChecked(false);
    ui->TDD_B40_Ck->setChecked(true);
    ui->TDD_B41_Ck->setChecked(true);
    ui->TDD_B42_Ck->setChecked(false);

    ui->GPS_Ck->setChecked(true);
    ui->WIFI24G_11B_Ck->setChecked(true);
    ui->WIFI24G_11G_Ck->setChecked(true);
    ui->WIFI24G_11N_Ck->setChecked(true);
    ui->WIFI5G_11A_Ck->setChecked(false);
    ui->WIFI5G_11N_Ck->setChecked(false);
    ui->WIFI5G_11AC_Ck->setChecked(false);
}

void MainWidgetUI::desenseCalculator_RFBandInfoCheck(void)
{
    rfbandinfoptr->gsmbandnum = 0;
    rfbandinfoptr->utmsbandnum = 0;
    rfbandinfoptr->tdscdmabandnum = 0;
    rfbandinfoptr->ltebandnum = 0;
    rfbandinfoptr->wifigpsbandnum = 0;

    if(ui->GSM850_Ck->isChecked())  {rfbandinfoptr->gsmbandstatus[rfbandinfoptr->gsmbandnum] = ui->GSM850_Ck->text(); rfbandinfoptr->gsmbandnum++;}
    if(ui->GSM900_Ck->isChecked())  {rfbandinfoptr->gsmbandstatus[rfbandinfoptr->gsmbandnum] = ui->GSM900_Ck->text(); rfbandinfoptr->gsmbandnum++;}
    if(ui->DCS1800_Ck->isChecked()) {rfbandinfoptr->gsmbandstatus[rfbandinfoptr->gsmbandnum] = ui->DCS1800_Ck->text();rfbandinfoptr->gsmbandnum++;}
    if(ui->PCS1900_Ck->isChecked()) {rfbandinfoptr->gsmbandstatus[rfbandinfoptr->gsmbandnum] = ui->PCS1900_Ck->text();rfbandinfoptr->gsmbandnum++;}

    if(ui->WCDMA_B1_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B1_Ck->text();rfbandinfoptr->utmsbandnum++;}
    if(ui->WCDMA_B2_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B2_Ck->text();rfbandinfoptr->utmsbandnum++;}
    if(ui->WCDMA_B3_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B3_Ck->text();rfbandinfoptr->utmsbandnum++;}
    if(ui->WCDMA_B4_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B4_Ck->text();rfbandinfoptr->utmsbandnum++;}
    if(ui->WCDMA_B5_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B5_Ck->text();rfbandinfoptr->utmsbandnum++;}
    if(ui->WCDMA_B8_Ck->isChecked()) {rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = ui->WCDMA_B8_Ck->text();rfbandinfoptr->utmsbandnum++;}

    if(ui->TDSCMDA_B34_Ck->isChecked()) {rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = ui->TDSCMDA_B34_Ck->text();rfbandinfoptr->tdscdmabandnum++;}
    if(ui->TDSCMDA_B39_Ck->isChecked()) {rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = ui->TDSCMDA_B39_Ck->text();rfbandinfoptr->tdscdmabandnum++;}
    if(ui->CDMA_BC0_Ck->isChecked())    {rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = ui->CDMA_BC0_Ck->text();   rfbandinfoptr->tdscdmabandnum++;}
    if(ui->CDMA_BC1_Ck->isChecked())    {rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = ui->CDMA_BC1_Ck->text();   rfbandinfoptr->tdscdmabandnum++;}
    if(ui->CDMA_BC10_Ck->isChecked())   {rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = ui->CDMA_BC10_Ck->text();  rfbandinfoptr->tdscdmabandnum++;}

    if(ui->FDD_B1_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B1_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B2_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B2_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B3_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B3_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B4_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B4_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B5_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B5_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B7_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B7_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B8_Ck->isChecked())  {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B8_Ck->text(); rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B12_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B12_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B13_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B13_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B17_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B17_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B20_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B20_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B25_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B25_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B26_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B26_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->FDD_B28_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->FDD_B28_Ck->text();rfbandinfoptr->ltebandnum++;}

    if(ui->TDD_B39_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->TDD_B38_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->TDD_B39_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->TDD_B39_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->TDD_B40_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->TDD_B40_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->TDD_B41_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->TDD_B41_Ck->text();rfbandinfoptr->ltebandnum++;}
    if(ui->TDD_B42_Ck->isChecked()) {rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = ui->TDD_B42_Ck->text();rfbandinfoptr->ltebandnum++;}

    if(ui->GPS_Ck->isChecked())         {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->GPS_Ck->text();        rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI24G_11B_Ck->isChecked()) {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI24G_11B_Ck->text();rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI24G_11G_Ck->isChecked()) {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI24G_11G_Ck->text();rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI24G_11N_Ck->isChecked()) {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI24G_11N_Ck->text();rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI5G_11A_Ck->isChecked())  {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI5G_11A_Ck->text(); rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI5G_11N_Ck->isChecked())  {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI5G_11N_Ck->text(); rfbandinfoptr->wifigpsbandnum++;}
    if(ui->WIFI5G_11AC_Ck->isChecked()) {rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = ui->WIFI5G_11AC_Ck->text();rfbandinfoptr->wifigpsbandnum++;}

    rfbandinfoptr->gsmbandstatus[rfbandinfoptr->gsmbandnum] = tr(" ");
    rfbandinfoptr->utmsbandstatus[rfbandinfoptr->utmsbandnum] = tr(" ");
    rfbandinfoptr->tdscdmabandstatus[rfbandinfoptr->tdscdmabandnum] = tr(" ");
    rfbandinfoptr->ltebandstatus[rfbandinfoptr->ltebandnum] = tr(" ");
    rfbandinfoptr->wifigpsbandstatus[rfbandinfoptr->wifigpsbandnum] = tr(" ");
}

void MainWidgetUI::desenseCalculator_RFDesenseDataTableShow(void)
{
    desenseCalculator_RFBandInfoCheck();

/*************************ITEM*****************************/
    {
        desenseCalculator_setTableItemRowCount(ui->SUMDataTable,0);
        desenseCalculator_RFTableInfo(ui->SUMDataTable,0);
    }

    desenseCalculator_RFDesenseDataTableCreate(ui->GSMTable, rfbandinfoptr->gsmbandnum);
    desenseCalculator_RFDesenseDataTableCreate(ui->UTMSTable, rfbandinfoptr->utmsbandnum);
    desenseCalculator_RFDesenseDataTableCreate(ui->TDS_CDMATable, rfbandinfoptr->tdscdmabandnum);
    desenseCalculator_RFDesenseDataTableCreate(ui->LTETable, rfbandinfoptr->ltebandnum);
    desenseCalculator_RFDesenseDataTableCreate(ui->WIFIGPSTable, rfbandinfoptr->wifigpsbandnum);
}

void MainWidgetUI::desenseCalculator_RFDesenseDataTableCreate(QTableWidget *rfTablePtr, int rfbandnum)
{
    desenseCalculator_setTableItemRowCount(rfTablePtr,rfbandnum);
    desenseCalculator_RFTableInfo(rfTablePtr,rfbandnum);
    desenseCalculator_setRFBandFreq(rfTablePtr,rfbandnum);
    desenseCalculator_setRFBandFreqDelta(rfTablePtr);
    desenseCalculator_setRFDataSum(rfTablePtr,rfbandnum);
}

QString MainWidgetUI::desenseCalculator_RFBandInfo(QTableWidget *rfTablePtr, int curruntband)
{
    if(rfTablePtr->objectName() == QStringLiteral("GSMTable"))
        return rfbandinfoptr->gsmbandstatus[curruntband];
    else if(rfTablePtr->objectName() == QStringLiteral("UTMSTable"))
        return rfbandinfoptr->utmsbandstatus[curruntband];
    else if(rfTablePtr->objectName() == QStringLiteral("TDS_CDMATable"))
        return rfbandinfoptr->tdscdmabandstatus[curruntband];
    else if(rfTablePtr->objectName() == QStringLiteral("LTETable"))
        return rfbandinfoptr->ltebandstatus[curruntband];
    else if(rfTablePtr->objectName() == QStringLiteral("WIFIGPSTable"))
        return rfbandinfoptr->wifigpsbandstatus[curruntband];
    else
        return "";
}

void MainWidgetUI::desenseCalculator_setTableItemRowCount(QTableWidget *rfTablePtr, int rfbandnum)
{
    int totalnum = 0, totalNumTemp = 0;

    for(int i = 0; i< rfbandnum; i++)
    {
        totalNumTemp = iniFilesValueRead(desenseCalculator_RFBandInfo(rfTablePtr, i), QStringLiteral("NUM")).toInt();
        if(totalNumTemp)
            totalnum += totalNumTemp;
        else
            totalnum = 0;
    }

    rfTablePtr->clearContents();
    rfTablePtr->setRowCount(0);
    rfTablePtr->setColumnCount(0);

    rfTablePtr->setRowCount(totalnum + 1);
    rfTablePtr->setColumnCount(4);
}

void MainWidgetUI::desenseCalculator_RFTableInfo(QTableWidget *tabletemp,int rownum)
{
    int num = 0, numtemp = 0, numBackup = 0;

    tabletemp->verticalHeader()->setVisible(false);
    tabletemp->horizontalHeader()->setVisible(false);
    tabletemp->setColumnWidth(0,88);
    tabletemp->setColumnWidth(1,92);
    tabletemp->setColumnWidth(2,75);
    tabletemp->setColumnWidth(3,155);
    tabletemp->setItem(0,0,new QTableWidgetItem(QStringLiteral("测试频段")));
    tabletemp->setItem(0,1,new QTableWidgetItem(QStringLiteral("测试频点(MHz)")));
    tabletemp->setItem(0,2,new QTableWidgetItem(QStringLiteral("Delta(MHz)")));
    tabletemp->setItem(0,3,new QTableWidgetItem(QStringLiteral("备注")));

    for(int i = 0; i < 4; i++)
        tabletemp->item(0,i)->setTextAlignment(Qt::AlignCenter);

    for(int i = 0; i< rownum; i++)
    {
        numtemp = iniFilesValueRead(desenseCalculator_RFBandInfo(tabletemp, i), QStringLiteral("NUM")).toInt();
        if(numtemp)
            num = numtemp;

        if(num > 1)
            tabletemp->setSpan(numBackup+1, 0, num, 1);

        if(num != 0)
        {
            tabletemp->setItem(numBackup+1,0,new QTableWidgetItem(desenseCalculator_RFBandInfo(tabletemp, i)));
            tabletemp->item(numBackup+1,0)->setTextAlignment(Qt::AlignCenter);
        }
        numBackup += num;
    }
}

void MainWidgetUI::desenseCalculator_setRFBandFreq(QTableWidget *rfTablePtr, int rfbandnum)
{
    int num = 0, numtemp = 0,numBackup = 0;
    QString rfbandtemp;
    QString bandinfodata;

    for(int i = 0; i< rfbandnum; i++)
    {
        numtemp = iniFilesValueRead(desenseCalculator_RFBandInfo(rfTablePtr, i), QStringLiteral("NUM")).toInt();
        if(numtemp)
            num = numtemp;

        for(int j = 1; j <= num; j++)
        {
            rfbandtemp = QString("%1%2").arg("/FREQ").arg(QString::number(j));
            bandinfodata = iniFilesValueRead(desenseCalculator_RFBandInfo(rfTablePtr, i), rfbandtemp).toString();
            rfTablePtr->setItem(numBackup+j,1,new QTableWidgetItem(bandinfodata));
            rfTablePtr->item(numBackup+j,1)->setTextAlignment(Qt::AlignCenter);
        }
        numBackup += num;
    }
}

double MainWidgetUI::absdouble(double x)
{
    if(x > 0)
        return x;
    else
        return -x;
}

void MainWidgetUI::desenseCalculator_setRFBandFreqDelta(QTableWidget *rfTablePtr)
{
    int tablerownum = rfTablePtr->rowCount() - 1;
    double vfreqmipi = (ui->MIPI_CLK_Value->text().toDouble())/24.0;//G3
    double freqdelta = 0,freqtemp1 = 0,freqtemp2 = 0,freqtemp3 = 0;

    for(int i = 1; i <= tablerownum; i++)
    {
        freqtemp1 = rfTablePtr->item(i,1)->text().toDouble();//B9
        freqtemp2 = freqtemp1/vfreqmipi;//B9/G3=B9*C3/B2
        freqtemp3 = int(freqtemp2);
        if((freqtemp2-freqtemp3)*vfreqmipi > vfreqmipi/2.0)
            freqdelta = (freqtemp2-freqtemp3-1)*vfreqmipi;
        else
            freqdelta = (freqtemp2-freqtemp3)*vfreqmipi;

        rfTablePtr->setItem(i,2,new QTableWidgetItem(QString::number(freqdelta)));
        rfTablePtr->item(i,2)->setTextAlignment(Qt::AlignCenter);
        if(absdouble(freqdelta) <= ui->CLK_ExistRisks_Value->text().toDouble())
            rfTablePtr->item(i,2)->setTextColor(QColor(255, 76, 108));
        else if(absdouble(freqdelta) < (ui->CLK_Risks_Value->text().toDouble()+ui->CLK_ExistRisks_Value->text().toDouble()))
            rfTablePtr->item(i,2)->setTextColor(QColor(222, 125, 44));
    }
}

void MainWidgetUI::desenseCalculator_setRFDataSum(QTableWidget *rfTablePtr, int rfbandnum)
{
    double freqdelta = 0;
    int num = 0, numtemp = 0,numBackup = 0;

    for(int i = 0; i< rfbandnum; i++)
    {
        numtemp = iniFilesValueRead(desenseCalculator_RFBandInfo(rfTablePtr, i), QStringLiteral("NUM")).toInt();
        if(numtemp)
            num = numtemp;

        for(int j = 1; j <= num; j++)
        {
            freqdelta = rfTablePtr->item(numBackup+j,2)->text().toDouble();
            if(absdouble(freqdelta) < (ui->CLK_Risks_Value->text().toDouble()+ui->CLK_ExistRisks_Value->text().toDouble()))
            {
                ui->SUMDataTable->setRowCount(ui->SUMDataTable->rowCount()+1);
                ui->SUMDataTable->setItem(ui->SUMDataTable->rowCount()-1,0,new QTableWidgetItem(rfTablePtr->item(numBackup+1,0)->text()));
                ui->SUMDataTable->setItem(ui->SUMDataTable->rowCount()-1,1,new QTableWidgetItem(rfTablePtr->item(numBackup+j,1)->text()));
                ui->SUMDataTable->setItem(ui->SUMDataTable->rowCount()-1,2,new QTableWidgetItem(rfTablePtr->item(numBackup+j,2)->text()));
                ui->SUMDataTable->item(ui->SUMDataTable->rowCount()-1,2)->setTextColor(rfTablePtr->item(numBackup+j,2)->textColor());
                ui->SUMDataTable->item(ui->SUMDataTable->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
                ui->SUMDataTable->item(ui->SUMDataTable->rowCount()-1,1)->setTextAlignment(Qt::AlignCenter);
                ui->SUMDataTable->item(ui->SUMDataTable->rowCount()-1,2)->setTextAlignment(Qt::AlignCenter);
            }
        }
        numBackup += num;
    }
}

void MainWidgetUI::desenseCalculator_RFDataCalculator(void)
{
    desenseCalculator_RFDesenseDataTableShow();
}
