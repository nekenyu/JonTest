#include "SomeNamespace/SomeNamespace.h"

#include <iostream>
using namespace std;

int main()
{
   std::cout << "SomeNamespace::getAnswer()=" << SomeNamespace::getAnswer() << std::endl; // 42
}