#include "iostream"
#include "Renderer.h"
using namespace std;

int main(int argc, char* argv[])
{
    Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow();
    return 0;
}