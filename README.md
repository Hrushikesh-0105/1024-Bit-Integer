﻿# 1024-Bit-Integer Calculator

## Author
Hrushikesh Musaloj

## Overview
This C++ program implements a calculator for integers up to **309 digits**. The calculator can perform addition, subtraction, and multiplication.

## Files Required
Before executing the program, create the following files in the same directory as the executable:
- **num1.txt**: Contains the first number.
- **num2.txt**: Contains the second number.
- **result.txt**: The program will write the calculation result here.

## Instructions
1. Enter integers (positive or negative) of up to **309 digits** in the `num1.txt` and `num2.txt` files.
2. Compile and run the program.
3. The result of the operation will be stored in `result.txt`.

## Program Behavior
- Supports large integers up to **309 digits**.
- Handles **addition**, **subtraction**, and **multiplication**.
- **Overflow Detection**: If a result exceeds **309 digits**, the program prints `OVERFLOWED` and stores it in the `result.txt` file.

## Edge Cases Handled
- Leading zeros are automatically removed in the final result.
- Proper handling of negative numbers.
- Displays an error message if the required files are missing.

## Sample Usage
### Input
- `num1.txt`: 999999999999999999999999999999999999
- `num2.txt`: 1

### Output
- `result.txt`: 1000000000000000000000000000000000000

### Overflow Example
If the result exceeds **309 digits**, the program will print:
```
OVERFLOWED
```
and `result.txt` will contain:
```
OVERFLOWED
```

## Compilation Instructions
```bash
g++ -o big_int_calculator big_int_calculator.cpp
./big_int_calculator
```

## Notes
- **Maximum digits**: 309
- **Minimum requirements**: C++ compiler supporting C++11 or later.
- **Ensure the required files are created** before running the program.

Enjoy using the **Big Int Calculator**! 😊
