#include <iostream>
#include <Windows.h>
#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

int main()
{
    Model m;
    View v(&m);
    Controller c(&m, &v);

    c.PlayGame();

    return 0;
}