#ifndef w_TEST_H
#define w_TEST_H
class w_Test {
public:
    static void testList();
    static void testString();

private:
    static void eANDs(bool empty, int size, bool want_empty, int want_size);
};
#endif
