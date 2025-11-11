#include "dialog.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QtMath>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , waitingForOperand(true)
    , currentExpression("")
    , lastOperand(0.0)
    , lastOperator("")
    , equalsPressedBefore(false)
{
    createUI();
    
    // Connect digit buttons
    connect(btn0, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn1, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn2, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn3, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn4, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn5, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn6, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn7, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn8, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn9, &QPushButton::clicked, this, &Dialog::digitPressed);
    
    // Connect operator buttons
    connect(btnAdd, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnSubtract, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnMultiply, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnDivide, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnPower, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnMod, &QPushButton::clicked, this, &Dialog::operatorPressed);
    
    // Connect other buttons
    connect(btnEquals, &QPushButton::clicked, this, &Dialog::equalsPressed);
    connect(btnClear, &QPushButton::clicked, this, &Dialog::clearPressed);
    connect(btnDelete, &QPushButton::clicked, this, &Dialog::deletePressed);
    connect(btnDecimal, &QPushButton::clicked, this, &Dialog::decimalPressed);
    
    // Connect scientific function buttons
    connect(btnSin, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnCos, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnTan, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnLog, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnLn, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnSqrt, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnSquare, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnExp, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnFactorial, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    connect(btnAbs, &QPushButton::clicked, this, &Dialog::scientificFunctionPressed);
    
    // Connect constant buttons
    connect(btnPi, &QPushButton::clicked, this, &Dialog::constantPressed);
    connect(btnE, &QPushButton::clicked, this, &Dialog::constantPressed);
    
    // Connect parenthesis buttons
    connect(btnLeftParen, &QPushButton::clicked, this, &Dialog::parenthesisPressed);
    connect(btnRightParen, &QPushButton::clicked, this, &Dialog::parenthesisPressed);
    
    // Initialize display
    display->setText("0");
    formulaDisplay->clear();
}

Dialog::~Dialog()
{
}

void Dialog::createUI()
{
    setWindowTitle("Scientific Calculator");
    setFixedSize(600, 600);
    
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create formula display
    formulaDisplay = new QLabel(this);
    formulaDisplay->setMinimumHeight(40);
    formulaDisplay->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QFont formulaFont = formulaDisplay->font();
    formulaFont.setPointSize(14);
    formulaDisplay->setFont(formulaFont);
    mainLayout->addWidget(formulaDisplay);
    
    // Create main display
    display = new QLineEdit(this);
    display->setMinimumHeight(60);
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    display->setReadOnly(true);
    QFont displayFont = display->font();
    displayFont.setPointSize(20);
    display->setFont(displayFont);
    mainLayout->addWidget(display);
    
    // Create button grid
    QGridLayout *gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);
    
    // Create buttons
    QFont buttonFont;
    buttonFont.setPointSize(12);
    
    // Row 0 - Scientific functions
    btnSin = new QPushButton("sin", this);
    btnSin->setMinimumHeight(50);
    btnSin->setFont(buttonFont);
    gridLayout->addWidget(btnSin, 0, 0);
    
    btnCos = new QPushButton("cos", this);
    btnCos->setMinimumHeight(50);
    btnCos->setFont(buttonFont);
    gridLayout->addWidget(btnCos, 0, 1);
    
    btnTan = new QPushButton("tan", this);
    btnTan->setMinimumHeight(50);
    btnTan->setFont(buttonFont);
    gridLayout->addWidget(btnTan, 0, 2);
    
    btnLog = new QPushButton("log", this);
    btnLog->setMinimumHeight(50);
    btnLog->setFont(buttonFont);
    gridLayout->addWidget(btnLog, 0, 3);
    
    btnLn = new QPushButton("ln", this);
    btnLn->setMinimumHeight(50);
    btnLn->setFont(buttonFont);
    gridLayout->addWidget(btnLn, 0, 4);
    
    btnSqrt = new QPushButton("√", this);
    btnSqrt->setMinimumHeight(50);
    btnSqrt->setFont(buttonFont);
    gridLayout->addWidget(btnSqrt, 0, 5);
    
    // Row 1 - More scientific functions
    btnSquare = new QPushButton("x²", this);
    btnSquare->setMinimumHeight(50);
    btnSquare->setFont(buttonFont);
    gridLayout->addWidget(btnSquare, 1, 0);
    
    btnPower = new QPushButton("x^y", this);
    btnPower->setMinimumHeight(50);
    btnPower->setFont(buttonFont);
    gridLayout->addWidget(btnPower, 1, 1);
    
    btnExp = new QPushButton("e^x", this);
    btnExp->setMinimumHeight(50);
    btnExp->setFont(buttonFont);
    gridLayout->addWidget(btnExp, 1, 2);
    
    btnMod = new QPushButton("mod", this);
    btnMod->setMinimumHeight(50);
    btnMod->setFont(buttonFont);
    gridLayout->addWidget(btnMod, 1, 3);
    
    btnFactorial = new QPushButton("n!", this);
    btnFactorial->setMinimumHeight(50);
    btnFactorial->setFont(buttonFont);
    gridLayout->addWidget(btnFactorial, 1, 4);
    
    btnAbs = new QPushButton("|x|", this);
    btnAbs->setMinimumHeight(50);
    btnAbs->setFont(buttonFont);
    gridLayout->addWidget(btnAbs, 1, 5);
    
    // Row 2 - Constants and parentheses
    btnPi = new QPushButton("π", this);
    btnPi->setMinimumHeight(50);
    btnPi->setFont(buttonFont);
    gridLayout->addWidget(btnPi, 2, 0);
    
    btnE = new QPushButton("e", this);
    btnE->setMinimumHeight(50);
    btnE->setFont(buttonFont);
    gridLayout->addWidget(btnE, 2, 1);
    
    btnLeftParen = new QPushButton("(", this);
    btnLeftParen->setMinimumHeight(50);
    btnLeftParen->setFont(buttonFont);
    gridLayout->addWidget(btnLeftParen, 2, 2);
    
    btnRightParen = new QPushButton(")", this);
    btnRightParen->setMinimumHeight(50);
    btnRightParen->setFont(buttonFont);
    gridLayout->addWidget(btnRightParen, 2, 3);
    
    btnClear = new QPushButton("C", this);
    btnClear->setMinimumHeight(50);
    btnClear->setFont(buttonFont);
    gridLayout->addWidget(btnClear, 2, 4);
    
    btnDelete = new QPushButton("DEL", this);
    btnDelete->setMinimumHeight(50);
    btnDelete->setFont(buttonFont);
    gridLayout->addWidget(btnDelete, 2, 5);
    
    // Row 3
    btn7 = new QPushButton("7", this);
    btn7->setMinimumHeight(50);
    btn7->setFont(buttonFont);
    gridLayout->addWidget(btn7, 3, 0);
    
    btn8 = new QPushButton("8", this);
    btn8->setMinimumHeight(50);
    btn8->setFont(buttonFont);
    gridLayout->addWidget(btn8, 3, 1);
    
    btn9 = new QPushButton("9", this);
    btn9->setMinimumHeight(50);
    btn9->setFont(buttonFont);
    gridLayout->addWidget(btn9, 3, 2);
    
    btnDivide = new QPushButton("÷", this);
    btnDivide->setMinimumHeight(50);
    btnDivide->setFont(buttonFont);
    gridLayout->addWidget(btnDivide, 3, 3, 1, 2);
    
    btnMultiply = new QPushButton("×", this);
    btnMultiply->setMinimumHeight(50);
    btnMultiply->setFont(buttonFont);
    gridLayout->addWidget(btnMultiply, 3, 5);
    
    // Row 4
    btn4 = new QPushButton("4", this);
    btn4->setMinimumHeight(50);
    btn4->setFont(buttonFont);
    gridLayout->addWidget(btn4, 4, 0);
    
    btn5 = new QPushButton("5", this);
    btn5->setMinimumHeight(50);
    btn5->setFont(buttonFont);
    gridLayout->addWidget(btn5, 4, 1);
    
    btn6 = new QPushButton("6", this);
    btn6->setMinimumHeight(50);
    btn6->setFont(buttonFont);
    gridLayout->addWidget(btn6, 4, 2);
    
    btnSubtract = new QPushButton("-", this);
    btnSubtract->setMinimumHeight(50);
    btnSubtract->setFont(buttonFont);
    gridLayout->addWidget(btnSubtract, 4, 3, 1, 2);
    
    btnAdd = new QPushButton("+", this);
    btnAdd->setMinimumHeight(50);
    btnAdd->setFont(buttonFont);
    gridLayout->addWidget(btnAdd, 4, 5);
    
    // Row 5
    btn1 = new QPushButton("1", this);
    btn1->setMinimumHeight(50);
    btn1->setFont(buttonFont);
    gridLayout->addWidget(btn1, 5, 0);
    
    btn2 = new QPushButton("2", this);
    btn2->setMinimumHeight(50);
    btn2->setFont(buttonFont);
    gridLayout->addWidget(btn2, 5, 1);
    
    btn3 = new QPushButton("3", this);
    btn3->setMinimumHeight(50);
    btn3->setFont(buttonFont);
    gridLayout->addWidget(btn3, 5, 2);
    
    btnEquals = new QPushButton("=", this);
    btnEquals->setMinimumHeight(50);
    btnEquals->setFont(buttonFont);
    gridLayout->addWidget(btnEquals, 5, 3, 2, 3);
    
    // Row 6
    btn0 = new QPushButton("0", this);
    btn0->setMinimumHeight(50);
    btn0->setFont(buttonFont);
    gridLayout->addWidget(btn0, 6, 0, 1, 2);
    
    btnDecimal = new QPushButton(".", this);
    btnDecimal->setMinimumHeight(50);
    btnDecimal->setFont(buttonFont);
    gridLayout->addWidget(btnDecimal, 6, 2);
}

double Dialog::evaluateExpression()
{
    // Create copies of the operands and operators to work with
    QVector<double> nums = operands;
    QVector<QString> ops = operators;
    
    // First pass: handle power (highest precedence)
    int i = 0;
    while (i < ops.size()) {
        if (ops[i] == "x^y") {
            double result = qPow(nums[i], nums[i + 1]);
            // Replace the two operands with the result
            nums[i] = result;
            nums.remove(i + 1);
            ops.remove(i);
            // Don't increment i, check the same position again
        } else {
            i++;
        }
    }
    
    // Second pass: handle multiplication, division, and modulo (higher precedence)
    i = 0;
    while (i < ops.size()) {
        if (ops[i] == "×" || ops[i] == "÷" || ops[i] == "mod") {
            double result;
            if (ops[i] == "×") {
                result = nums[i] * nums[i + 1];
            } else if (ops[i] == "÷") {
                if (nums[i + 1] == 0.0) {
                    // Division by zero - will be handled by caller
                    return 0.0;
                }
                result = nums[i] / nums[i + 1];
            } else { // ops[i] == "mod"
                if (nums[i + 1] == 0.0) {
                    return 0.0;
                }
                result = fmod(nums[i], nums[i + 1]);
            }
            // Replace the two operands with the result
            nums[i] = result;
            nums.remove(i + 1);
            ops.remove(i);
            // Don't increment i, check the same position again
        } else {
            i++;
        }
    }
    
    // Third pass: handle addition and subtraction (lower precedence)
    i = 0;
    while (i < ops.size()) {
        double result;
        if (ops[i] == "+") {
            result = nums[i] + nums[i + 1];
        } else { // ops[i] == "-"
            result = nums[i] - nums[i + 1];
        }
        // Replace the two operands with the result
        nums[i] = result;
        nums.remove(i + 1);
        ops.remove(i);
        // Don't increment i, check the same position again
    }
    
    // Should have exactly one number left
    return nums.isEmpty() ? 0.0 : nums[0];
}

void Dialog::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString digit = button->text();
    
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->clear();
        formulaDisplay->clear();
        currentExpression.clear();
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    }
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    if (display->text() == "0" && digit != "0") {
        display->setText(digit);
    } else if (display->text() != "0") {
        display->setText(display->text() + digit);
    }
    
    // Update the expression display
    currentExpression += digit;
    formulaDisplay->setText(currentExpression);
}

void Dialog::operatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString clickedOperator = button->text();
    double operand = display->text().toDouble();
    
    // If equals was just pressed, start from the result
    if (equalsPressedBefore) {
        equalsPressedBefore = false;
        operands.clear();
        operators.clear();
        currentExpression = QString::number(operand);
        operands.append(operand);
    }
    
    if (waitingForOperand) {
        // If we're waiting for operand (operator pressed immediately after another operator),
        // just replace the last operator
        if (!operators.isEmpty()) {
            operators[operators.size() - 1] = clickedOperator;
            // Update the expression display
            if (!currentExpression.isEmpty() && currentExpression.endsWith(" ")) {
                currentExpression.chop(2); // Remove last operator and space
            }
            currentExpression += clickedOperator + " ";
            formulaDisplay->setText(currentExpression);
        } else {
            // First number followed by operator
            operands.append(operand);
            operators.append(clickedOperator);
            if (currentExpression.isEmpty()) {
                currentExpression = QString::number(operand);
            }
            currentExpression += " " + clickedOperator + " ";
            formulaDisplay->setText(currentExpression);
        }
    } else {
        // Save the current operand and operator
        operands.append(operand);
        operators.append(clickedOperator);
        
        // Add operator to expression
        if (!currentExpression.isEmpty() && !currentExpression.endsWith(" ")) {
            currentExpression += " " + clickedOperator + " ";
        } else if (!currentExpression.isEmpty()) {
            currentExpression += clickedOperator + " ";
        } else {
            currentExpression = QString::number(operand) + " " + clickedOperator + " ";
        }
        formulaDisplay->setText(currentExpression);
    }
    
    waitingForOperand = true;
}

void Dialog::equalsPressed()
{
    double operand = display->text().toDouble();
    
    // If equals was already pressed, repeat the last operation
    if (equalsPressedBefore && !lastOperator.isEmpty()) {
        // Simple single operation repeat (like Windows Calculator)
        double currentValue = display->text().toDouble();
        double result;
        
        if (lastOperator == "+") {
            result = currentValue + lastOperand;
        } else if (lastOperator == "-") {
            result = currentValue - lastOperand;
        } else if (lastOperator == "×") {
            result = currentValue * lastOperand;
        } else if (lastOperator == "÷") {
            if (lastOperand != 0.0) {
                result = currentValue / lastOperand;
            } else {
                display->setText("Error");
                formulaDisplay->setText("Error: Division by zero");
                operands.clear();
                operators.clear();
                waitingForOperand = true;
                currentExpression.clear();
                equalsPressedBefore = false;
                return;
            }
        } else if (lastOperator == "x^y") {
            result = qPow(currentValue, lastOperand);
        } else if (lastOperator == "mod") {
            if (lastOperand != 0.0) {
                result = fmod(currentValue, lastOperand);
            } else {
                display->setText("Error");
                formulaDisplay->setText("Error: Division by zero");
                operands.clear();
                operators.clear();
                waitingForOperand = true;
                currentExpression.clear();
                equalsPressedBefore = false;
                return;
            }
        } else {
            return;
        }
        
        // Update displays
        currentExpression = QString::number(currentValue) + " " + lastOperator + " " + QString::number(lastOperand);
        formulaDisplay->setText(currentExpression);
        display->setText(QString::number(result));
        
    } else if (!operators.isEmpty()) {
        // First time pressing equals - evaluate the full expression
        
        // Add the last operand to complete the expression
        if (!waitingForOperand) {
            operands.append(operand);
            
            // Complete the expression display
            if (!currentExpression.endsWith(" ")) {
                // Expression already complete
            } else {
                currentExpression += QString::number(operand);
            }
        } else if (!operands.isEmpty()) {
            // Operator was pressed but no new operand entered, use the last operand
            operands.append(operands.last());
            currentExpression += QString::number(operands.last());
        }
        
        // Check for division by zero before evaluation
        for (int i = 0; i < operators.size(); i++) {
            if ((operators[i] == "÷" || operators[i] == "mod") && i + 1 < operands.size() && operands[i + 1] == 0.0) {
                display->setText("Error");
                formulaDisplay->setText("Error: Division by zero");
                operands.clear();
                operators.clear();
                waitingForOperand = true;
                currentExpression.clear();
                equalsPressedBefore = false;
                return;
            }
        }
        
        // Evaluate the expression with proper order of operations
        double result = evaluateExpression();
        
        // Save the last operator and operand for repeating
        // For repeating, we use the last operation
        if (!operators.isEmpty() && operands.size() >= 2) {
            lastOperator = operators.last();
            lastOperand = operands.last();
        }
        
        // Show the complete expression in the formula display
        formulaDisplay->setText(currentExpression);
        // Show the result in the main display
        display->setText(QString::number(result));
        
        // Clear the expression data
        operands.clear();
        operators.clear();
        equalsPressedBefore = true;
    }
    
    waitingForOperand = true;
}

void Dialog::clearPressed()
{
    display->setText("0");
    formulaDisplay->clear();
    operands.clear();
    operators.clear();
    waitingForOperand = true;
    currentExpression.clear();
    lastOperand = 0.0;
    lastOperator.clear();
    equalsPressedBefore = false;
}

void Dialog::deletePressed()
{
    QString text = display->text();
    if (text.length() > 1) {
        text.chop(1);
        display->setText(text);
        // Update the expression by removing the last character
        if (!currentExpression.isEmpty()) {
            currentExpression.chop(1);
            formulaDisplay->setText(currentExpression);
        }
    } else {
        display->setText("0");
        waitingForOperand = true;
    }
}

void Dialog::decimalPressed()
{
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->setText("0.");
        formulaDisplay->clear();
        currentExpression = "0.";
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    } else if (waitingForOperand) {
        display->setText("0.");
        waitingForOperand = false;
        currentExpression += "0.";
    } else if (!display->text().contains(".")) {
        display->setText(display->text() + ".");
        currentExpression += ".";
    }
    formulaDisplay->setText(currentExpression);
}

void Dialog::scientificFunctionPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString function = button->text();
    double value = display->text().toDouble();
    double result = 0.0;
    bool error = false;
    
    if (function == "sin") {
        result = qSin(qDegreesToRadians(value));
    } else if (function == "cos") {
        result = qCos(qDegreesToRadians(value));
    } else if (function == "tan") {
        result = qTan(qDegreesToRadians(value));
    } else if (function == "log") {
        if (value > 0) {
            result = qLn(value) / qLn(10.0);  // log10
        } else {
            error = true;
        }
    } else if (function == "ln") {
        if (value > 0) {
            result = qLn(value);
        } else {
            error = true;
        }
    } else if (function == "√") {
        if (value >= 0) {
            result = qSqrt(value);
        } else {
            error = true;
        }
    } else if (function == "x²") {
        result = value * value;
    } else if (function == "e^x") {
        result = qExp(value);
    } else if (function == "n!") {
        if (value >= 0 && value == qFloor(value) && value <= 170) {
            result = 1.0;
            for (int i = 2; i <= static_cast<int>(value); ++i) {
                result *= i;
            }
        } else {
            error = true;
        }
    } else if (function == "|x|") {
        result = qAbs(value);
    }
    
    if (error) {
        display->setText("Error");
        formulaDisplay->setText("Error: Invalid input");
        operands.clear();
        operators.clear();
        waitingForOperand = true;
        currentExpression.clear();
        equalsPressedBefore = false;
    } else {
        display->setText(QString::number(result));
        formulaDisplay->setText(function + "(" + QString::number(value) + ")");
        operands.clear();
        operators.clear();
        currentExpression.clear();
        equalsPressedBefore = true;
        waitingForOperand = true;
    }
}

void Dialog::constantPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString constant = button->text();
    double value;
    
    if (constant == "π") {
        value = M_PI;
    } else if (constant == "e") {
        value = M_E;
    } else {
        return;
    }
    
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->clear();
        formulaDisplay->clear();
        currentExpression.clear();
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    }
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    display->setText(QString::number(value));
    currentExpression += constant;
    formulaDisplay->setText(currentExpression);
}

void Dialog::parenthesisPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString paren = button->text();
    
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->clear();
        formulaDisplay->clear();
        currentExpression.clear();
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    }
    
    currentExpression += paren;
    formulaDisplay->setText(currentExpression);
    
    if (paren == "(") {
        waitingForOperand = true;
    }
}
