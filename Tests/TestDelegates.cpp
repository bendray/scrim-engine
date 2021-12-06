#include <gtest/gtest.h>

#include <Delegate.hpp>

void val_int(int t)
{
        t += 1;
        return;
}
void ref_int(int& t)
{
        t += 1;
        return;
}
void pt_int(int* t)
{
        *t += 1;
        return;
}

TEST(CDelegateTest1, TestByValue)
{

    using SomeIntByValEvent = Scrim::Event<int>;

    SomeIntByValEvent evt;

    evt += &val_int;

    int num = 3;
    evt.Invoke(num);

    EXPECT_EQ(num, 3);

    evt.Invoke(6+8);
}

TEST(CDelegateTest2, TestByRef)
{

    using SomeIntByRefEvent = Scrim::Event<int&>;

    SomeIntByRefEvent evt;

    evt += &ref_int;

    int num = 3;
    evt.Invoke(num);
    EXPECT_EQ(num, 4);

    int& rf = num;
    evt.Invoke(rf);
    EXPECT_EQ(num, 5);
}

TEST(CDelegateTest3, TestByPt)
{

    using SomeIntByPtEvent = Scrim::Event<int*>;

    SomeIntByPtEvent evt;

    evt += &pt_int;

    int num = 3;
    evt.Invoke(&num);
    EXPECT_EQ(num, 4);

    int* pt = &num;
    evt.Invoke(pt);
    EXPECT_EQ(num, 5);
}
