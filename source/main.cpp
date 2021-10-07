#include <iostream>
#include <vector>
#include <string>
#include "terminalcolour.cpp"
#include "mandelbrot.cpp"
using namespace std;

int main()
{
    cout << Modifier(ForegroundCode::RED,BackgroundCode::GREEN);
    cout << Complex();
    cout << Modifier() << endl;
}