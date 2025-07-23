#include <iostream>
#include <cmath>
using namespace std;
class Point {
    private:
        double x = 0;
        double y = 0;
        double z = 0;

    public:
        Point(){}

        Point(double x, double y, double z){
            setCoord(x, y, z);
        }

        void setCoord(double x,double y,double z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        double getX(){
            return this->x;
        }

        double getY(){
            return this->y;
        }

        double getZ(){
            return this->z;
        }

        friend double operator-(const Point& a, const Point& b);
};

double operator-(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

int main() {
    Point point1;
    Point point2(2,5,2);

    cout << point1.getX() << " " << point1.getY() << " " << point1.getZ() << endl;
    cout << point2.getX() << " " << point2.getY() << " " << point2.getZ() << endl;

    double distance1 = point1 - point2;
    cout << "Distance (неявний operator-): " << distance1 << endl;

    point1.setCoord(1, 1, 1);

    double distance2 = operator-(point1, point2);
    cout << "Distance (explicit(явний) operator-): " << distance2 << endl;

    return 0;
}

