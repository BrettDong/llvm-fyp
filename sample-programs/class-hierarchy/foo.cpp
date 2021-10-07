class Shape
{
    public:
        virtual ~Shape() = default;
        virtual double Area(double x) = 0;
};

class Square : public Shape
{
    public:
        double Area(double x) override;
};

double Square::Area(double x)
{
    return x * x;
}

double foo(double x)
{
    Shape *shape;
    double answer = shape->Area(x);
    return answer;
}

double goo(double x)
{
    Square *shape;
    double answer = shape->Area(x);
    return answer;
}
