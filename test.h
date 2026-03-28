#ifndef w_TEST_H
#define w_TEST_H
class w_Test {
public:
    static void testList();
    static void testFile2();
    static void testString();
    static void testFile();
    static void testSort();
    static void testStats();
    static void testStats2();

private:
    static void eANDs(bool empty, int size, bool want_empty, int want_size);
};
#endif
