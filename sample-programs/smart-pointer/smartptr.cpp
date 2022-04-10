#include <memory>

class Base {
   public:
    virtual int action() { return 1; }
};

class DerivedA : public Base {
   public:
    int action() override { return 2; }
};

int main() {
    std::unique_ptr<Base> ptr;
    ptr = std::make_unique<DerivedA>();
    ptr->action();
    return 0;
}
