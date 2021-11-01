typedef int (*fptr_t)(int, int);

struct structA {
    fptr_t fptr;
};

struct structB {
    fptr_t fptr;
    struct structA a;
};

struct structC {
    fptr_t fptr;
    struct structA a;
    struct structB b;
};

int funcA(int a, int b) {
    return a + b;
}

int funcB(int a, int b) {
    return a * b;
}

int funcC(int a, int b) {
    return a - b;
}

int funcD(int a, int b) {
    return a * b + a;
}

int funcE(int a, int b) {
    return a * b - a;
}

int funcF(int a, int b) {
    return a * b + b;
}

int funcG(int a, int b) {
    return a * b - b;
}

//int funcX(fptr_t p, int a, int b) {
//    return p(a, b);
//}
//
//int funcY() {
//    fptr_t p = &funcA;
//    return funcX(p, 2, 3);
//}

int funcZ() {
    struct structA a = {.fptr = &funcA};
    struct structB b = {.fptr = &funcB, .a = {.fptr = &funcD}};
    struct structC c = {.fptr = &funcC, .a = {.fptr = &funcE}, .b = {.fptr = &funcF, .a = {.fptr = &funcG}}};
    return (*b.a.fptr)(2, 3);
}