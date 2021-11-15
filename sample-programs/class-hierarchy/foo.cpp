class Shape {
   public:
    virtual ~Shape() = default;
    virtual double Area(double x) = 0;
};

class Square : public Shape {
   public:
    double Area(double x) override;
};

double Square::Area(double x) { return x * x; }

class Circle : public Shape {
   public:
    double Area(double x) override;
};

double Circle::Area(double x) { return 3.1415926 * x * x; }

double foo(Shape *shape, double x) {
    double answer = shape->Area(x);
    return answer;
}

double goo(Square *shape, double x) {
    double answer = shape->Area(x);
    return answer;
}
