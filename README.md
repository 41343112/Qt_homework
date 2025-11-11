# Qt_homework

## Calculator Application

A simple calculator application built with Qt that provides basic arithmetic operations. The UI is created **entirely programmatically** without using Qt Designer (.ui files).

![Calculator Screenshot](screenshot.png)
*Windows Calculator-style interface with repeating equals functionality*

### Features

- **Basic Operations**: Addition (+), Subtraction (-), Multiplication (×), Division (÷)
- **Digit Input**: Numbers 0-9
- **Decimal Support**: Floating point calculations
- **Clear Function**: Reset calculator to initial state
- **Delete Function**: Remove last entered digit
- **Error Handling**: Division by zero protection
- **Repeating Equals**: Windows Calculator behavior - pressing = repeatedly continues applying the last operation
- **Programmatic UI**: All widgets and layouts created in C++ code, no UI designer files

### UI Layout

The calculator has a clean and intuitive interface:
- Display area at the top showing input/results
- 4x5 grid of buttons below
- Large, easy-to-read buttons with 16pt font
- Display uses 20pt font, right-aligned

### Building the Project

```bash
qmake6 Qt_homework.pro
# or use qmake if Qt6 is the default version
make
./Qt_homework
```

### Usage

1. Click digit buttons (0-9) to enter numbers
2. Click operator buttons (+, -, ×, ÷) to select operation
3. Enter second number
4. Click = to see the result
5. **Click = again to repeat the last operation** (Windows Calculator behavior)
   - Example: 5 + 3 = = = gives you 8, 11, 14
6. Click C to clear and start over
7. Click DEL to delete the last digit
8. Click . to add a decimal point

### Windows Calculator Behavior

This calculator implements the Windows Calculator behavior where pressing the equals button (=) repeatedly will continue to apply the last operation:

- **Example 1**: `5 + 3 = = =` → Results: 8, 11, 14
- **Example 2**: `10 - 2 = = =` → Results: 8, 6, 4
- **Example 3**: `4 × 3 = = =` → Results: 12, 36, 108
- **Example 4**: `100 ÷ 2 = = =` → Results: 50, 25, 12.5