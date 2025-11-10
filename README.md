# Qt_homework

## Calculator Application

A simple calculator application built with Qt that provides basic arithmetic operations.

### Features

- **Basic Operations**: Addition (+), Subtraction (-), Multiplication (×), Division (÷)
- **Digit Input**: Numbers 0-9
- **Decimal Support**: Floating point calculations
- **Clear Function**: Reset calculator to initial state
- **Delete Function**: Remove last entered digit
- **Error Handling**: Division by zero protection

### UI Layout

The calculator has a clean and intuitive interface:
- Display area at the top showing input/results
- 4x5 grid of buttons below
- Large, easy-to-read buttons with 16pt font
- Display uses 20pt font, right-aligned

### Building the Project

```bash
qmake Qt_homework.pro
make
./Qt_homework
```

### Usage

1. Click digit buttons (0-9) to enter numbers
2. Click operator buttons (+, -, ×, ÷) to select operation
3. Enter second number
4. Click = to see the result
5. Click C to clear and start over
6. Click DEL to delete the last digit
7. Click . to add a decimal point