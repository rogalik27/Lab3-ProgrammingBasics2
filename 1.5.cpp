#include <iostream>
using namespace std;

class Number {
private:
    int value;
    static int totalSum;

public:
    Number(int val) : value(val) {
        totalSum += val;
    }

    int getValue() const {
        return value;
    }

    static int getTotalSum() {
        return totalSum;
    }
};

int Number::totalSum = 0;

int main() {
    Number n1(5);
    Number n2(10);
    Number n3(15);

    cout << "Значення n1: " << n1.getValue() << endl;
    cout << "Значення n2: " << n2.getValue() << endl;
    cout << "Значення n3: " << n3.getValue() << endl;

    cout << "Сума всіх значень: " << Number::getTotalSum() << endl;

    return 0;
}
