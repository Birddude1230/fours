# fours
A fours problem brute forcer, in C.
[Usage](##Usage)

##The fours problem
###In general
[The fours problem, also known as four fours,](https://en.wikipedia.org/wiki/Four_fours) is a mathematical puzzle that requires identifying equations for various numbers that are composed only of the digit 4 four times, and some set of mathematical operators. There are many variants of the puzzle, including many that use somewhat unusual operators (such as allowing adding a decimal point to a 4 to create .4). The numbers the equations should equal are ususally 1 to n.
###In this program
This program currently considers only the four "basic" operators: addition, subtraction, multiplication, and division. This severly restricts the possible values. The primary focus is not to solve for specific values, but rather to compute overall coverage and statistics of the simplified problem.

##Install
Compile the source `four.c` using your C complier of choice (I reccomend gcc). The resulting binary can be moved as desired.

##Usage
Run the compiled program from the command line to output a list of possible formulas, followed by a list of values and formulas that equal that value. Values with zero formulas are omitted. The special value `-999999` is used only for formulas that contain divison by zero.
