#ifndef CHANGEFONTSDIALOG_H
#define CHANGEFONTSDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeFontsDialog;
}

class ChangeFontsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeFontsDialog(int lfontSize, int rFontSize, QWidget *parent = 0);


private:

};

#endif // CHANGEFONTSDIALOG_H
