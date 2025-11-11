#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void digitPressed();
    void operatorPressed();
    void equalsPressed();
    void clearPressed();
    void deletePressed();
    void decimalPressed();

private:
    void createUI();
    
    QLabel *formulaDisplay;
    QLineEdit *display;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnAdd;
    QPushButton *btnSubtract;
    QPushButton *btnMultiply;
    QPushButton *btnDivide;
    QPushButton *btnEquals;
    QPushButton *btnClear;
    QPushButton *btnDelete;
    QPushButton *btnDecimal;
    
    double firstNum;
    bool waitingForOperand;
    QString pendingOperator;
    QString currentExpression;
    
    // For repeating equals operation
    double lastOperand;
    QString lastOperator;
    bool equalsPressedBefore;
};
#endif // DIALOG_H
