//  ------------------------------------------------------------------------
//
//  This file is part of the Intan Technologies RHD2000 Interface
//  Version 1.3
//  Copyright (C) 2013 Intan Technologies
//
//  ------------------------------------------------------------------------
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QtGui>

#include "qtincludes.h"

#include "impedancefreqListdialog.h"

// Electrode impedance measurement frequency selection dialog.
// Allows users to select a new measurement frequency, while validating
// the the new frequency lies within an acceptable range.

ImpedanceFreqListDialog::ImpedanceFreqListDialog(QVector<double> *pDesiredImpedanceFreqVec, double lowerBandwidth, double upperBandwidth,
                                         double dspCutoffFreq, bool dspEnabled, double sampleRate, QWidget *parent) :
    QDialog(parent)
{
    pDeFVec = pDesiredImpedanceFreqVec;
    // Lower frequency limit based on sample rate: FPGA command RAM can only hold 1024 commands,
    // so this limits the period of the sinusoidal waveform generated by the impedance test DAC.
    lowerLimitSample = sampleRate / 1024.0;

    // Upper frequency limit based on sample rate: It is difficult to accurately approximate
    // a sine wave (using the on-chip impedance test DAC) in fewer than 4 steps per period.
    upperLimitSample = sampleRate / 4.0;

    // Lower frequency limit based on amplifier bandwidth:  We should stay at least 1.5X above
    // the effective lower amplifier bandwidth of the amplifier so that our impedance
    // measurements are not affected by a roll-off in gain.  (This may be overly conservative.)
    double effectiveLowerBandwidth = lowerBandwidth;
    if (dspEnabled) {
        if (dspCutoffFreq > lowerBandwidth) {
            effectiveLowerBandwidth = dspCutoffFreq;
        }
    }
    lowerLimitBandwidth = effectiveLowerBandwidth * 1.5;

    // Upper frequency limit based on amplifier bandwidth:  We should stay at least 1.5X below
    // the effective upper amplifier bandwidth of the amplifier so that our impedance
    // measurements are not affected by a roll-off in gain.  (This may be overly conservative.)
    upperLimitBandwidth = upperBandwidth / 1.5;

    impedanceFreqLineEdit = new QLineEdit(valueVecToText(pDesiredImpedanceFreqVec, 0));
    // I don't like to put lots of 'new' in the program. But this is how the qDialog should create. After add to the parent widget, the parent object can handle the delete.

    connect(impedanceFreqLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(onLineEditTextChanged()));

    QString sampleRangeText("The sampling rate of ");
    sampleRangeText.append(QString::number(sampleRate / 1000.0, 'f', 2));
    sampleRangeText.append(" kS/s retricts this range to ");
    sampleRangeText.append(QString::number(lowerLimitSample, 'f', 1));
    sampleRangeText.append(" Hz to ");
    sampleRangeText.append(QString::number(upperLimitSample, 'f', 0));
    sampleRangeText.append(" Hz.");
    sampleRangeLabel = new QLabel(sampleRangeText);

    bandwidth1RangeLabel = new QLabel(tr("For acceptable accuracy, the frequency should "
                                         "lie within the amplifier bandwidth by a factor of 1.5."));
    bandwidth1RangeLabel->setWordWrap(true);

    QString bandwidthRangeText("This restricts the measurement frequency range to ");
    bandwidthRangeText.append(QString::number(lowerLimitBandwidth, 'f', 1));
    bandwidthRangeText.append(" Hz to ");
    bandwidthRangeText.append(QString::number(upperLimitBandwidth, 'f', 0));
    bandwidthRangeText.append(" Hz.");
    bandwidth2RangeLabel = new QLabel(bandwidthRangeText);

    QHBoxLayout *impedanceFreqSelectLayout = new QHBoxLayout;
    impedanceFreqSelectLayout->addWidget(new QLabel(tr("Electrode Impedance Measurement Frequency")));
    impedanceFreqSelectLayout->addWidget(impedanceFreqLineEdit);
    impedanceFreqSelectLayout->addWidget(new QLabel(tr("Hz")));
    impedanceFreqSelectLayout->addStretch(1);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(impedanceFreqSelectLayout);
    mainLayout->addWidget(sampleRangeLabel);
    mainLayout->addWidget(bandwidth1RangeLabel);
    mainLayout->addWidget(bandwidth2RangeLabel);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Select Electrode Impedance Measurement Frequency"));

    onLineEditTextChanged();
}

// Validate new entry, and enable OK button if entry is valid.
void ImpedanceFreqListDialog::onLineEditTextChanged()
{
    QVector<double> values;
    textToValueVec(impedanceFreqLineEdit->text(), &values);
    bool inRange = true;
    foreach(auto value, values)
    {
        if (value < lowerLimitSample || value > upperLimitSample) {
            sampleRangeLabel->setStyleSheet("color: red");
            inRange = false;
            break;
        } else {
            sampleRangeLabel->setStyleSheet("");
        }

        if (value < lowerLimitBandwidth || value > upperLimitBandwidth) {
            bandwidth1RangeLabel->setStyleSheet("color: red");
            bandwidth2RangeLabel->setStyleSheet("color: red");
            inRange = false;
            break;
        } else {
            bandwidth1RangeLabel->setStyleSheet("");
            bandwidth2RangeLabel->setStyleSheet("");
        }
    }

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(inRange);
    if(inRange) {
        pDeFVec->clear();
        foreach(auto _val, values) {
            pDeFVec->append(_val);
        }
    }
}

void textToValueVec(QString text, QVector<double> *pVec)
{
    QStringList list = text.split(",",QString::SkipEmptyParts);
    if (list.length()>0)
    {
        pVec->clear();
        foreach(auto _num, list)
            pVec->append(_num.toDouble());
    }
}

QString valueVecToText(QVector<double> *pVec, int precision = -1)
{
    QString text;
    QString numFormat(" %1,");
    foreach(auto _num, *pVec)
        text.append(numFormat.arg(_num, 0, 'f', precision));
    return text;
}
