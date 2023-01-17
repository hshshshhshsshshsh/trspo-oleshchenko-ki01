#include <iostream>
#include <thread>
using namespace std;


void Type1()
{
    cout << "Hello World from Thread Part1" << endl;
}

void Type3()
{
    cout << "Hello World from Thread Part3" << endl;
}


void LoveApples(int N)
{
    for (int i = 2; i <= N; i++)
    {
        cout << "I love " << i << " apples" << endl;
    }
}

int main()
{
    thread Part1(Type1);
    thread Part2(LoveApples, 4);
    thread Part3(Type3);
    
    Part1.join();
    Part2.join();
    Part3.join();

    cout << "Execution of Part1, Part2 and Part3 is completed" << endl;
    return 0;
}
