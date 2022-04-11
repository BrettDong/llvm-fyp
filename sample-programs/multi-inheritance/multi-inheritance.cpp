class A {
   public:
    virtual int f() { return 1; }
};

class B {
   public:
    virtual int g() { return 2; }
    virtual int h() { return 3; }
};

class C : public A, public B {
   public:
    int f() override { return 4; }
    int g() override { return 5; }
    int h() override { return 6; }
};

class D {
   public:
    virtual int x() { return 0; }
};

class E : public C, public D {
   public:
    int h() { return 0; }
    int x() { return 7; }
};

int main() {
    C *c = new E();
    return c->h();
}
