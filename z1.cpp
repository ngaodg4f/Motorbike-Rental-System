#include <iostream>
#include <vector>
using std::cout, std::vector;

class A {
    private:
        int a;
    
    public:
        A(){}
        A(int a) : a(a){}

        void print(){
            cout << a << '\n';
        }
};

class B {
    private:
        A a;
    
    public:
        B(){}
        B(A a) : a(a){}

        void print(){
            a.print();
        }
};

int main(){
    A a (10);
    B b (a);
    b.print();
}