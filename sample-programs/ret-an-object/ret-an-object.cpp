class Shape {
   public:
    virtual ~Shape() = default;
    virtual double Area(double x) { return 0.0; }
};

class Rectangle : public Shape {
   public:
    virtual ~Rectangle() = default;
    virtual double Area(double x) override;
};

double Rectangle::Area(double x) { return x * x; }

class Square : public Rectangle {
   public:
    double Area(double x) override;
};

double Square::Area(double x) { return x * x; }

class Circle : public Shape {
   public:
    double Area(double x) override;
};

double Circle::Area(double x) { return 3.1415926 * x * x; }

Shape *factory() { return new Rectangle(); }

int main() {
    Shape *shape = factory();
    return static_cast<int>(shape->Area(1.0));
}
