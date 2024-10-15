#include <iostream>
#include "stacks.h"

using namespace std;

int main(){
    Stack stack;

    stack.push(30);
    stack.push(50);
    stack.push(70);

    cout << "El elemento top: " << stack.top() << endl;
    stack.pop();
    cout << "El elemento después del pop: " << stack.top();

    return 0;
}