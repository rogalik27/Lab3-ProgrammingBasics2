#include <iostream>
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
};

int main(){
    Point point1;

    Point point2(2,5,2);

    cout << point1.getX() << " " << point1.getY() << " " << point1.getZ() << endl;
    cout << point2.getX() << " " << point2.getY() << " " << point2.getZ() << endl;

}
