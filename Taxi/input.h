#ifndef INPUT_H
#define INPUT_H

#include <QDialog>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = 0);
    ~Input();

    int getSrc();

    int getDst();

private:
    Ui::Input *ui;
};

#endif // INPUT_H
