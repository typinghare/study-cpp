
#include <iostream>
class Foo {
 public:
    int a = 0;
};

class Bar {
 public:
    Foo foo;

    void setFoo(const Foo& foo) { this->foo = foo; }
};

int main() {
    Foo foo;
    Bar bar;
    bar.setFoo(foo);

    foo.a = 10;

    std::cout << bar.foo.a << std::endl;

    return 0;
}
