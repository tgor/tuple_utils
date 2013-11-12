#include "../src/fold_tuples.hpp"
#include <tuple>
#include <string>
#include <limits>
#include <cmath>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>


class TestFoldTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFoldTuple);
    CPPUNIT_TEST(test1tuple);
    CPPUNIT_TEST(test2tuples);
    CPPUNIT_TEST(test3tuples);
    CPPUNIT_TEST(test4tuples);
    CPPUNIT_TEST(testEmptyTuples);
    CPPUNIT_TEST(testTuples1Elem);
    CPPUNIT_TEST(testTuples2Elem);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test1tuple();
    void test2tuples();
    void test3tuples();
    void test4tuples();
    void testEmptyTuples();
    void testTuples1Elem();
    void testTuples2Elem();
};

void TestFoldTuple::setUp()
{}

void TestFoldTuple::tearDown()
{}

void TestFoldTuple::test1tuple()
{
    std::tuple<int, long, char, double, int> arg{1, 22, 'a', 2.2, 4};
    auto result = tuple_utils::fold(arg);

    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(result == arg);
}

void TestFoldTuple::test2tuples()
{
    std::tuple<int, int> arg1 {2, 2};
    std::tuple<int, int> arg2 {12, 1};
    auto result = tuple_utils::fold(arg1, arg2);

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(14 == std::get<0>(result));
    CPPUNIT_ASSERT(3 == std::get<1>(result));
}

void TestFoldTuple::test3tuples()
{
    std::tuple<int, int, long, std::string, float> arg1 {2, 2, 22, "hello", 1.1};
    std::tuple<int, int, long, std::string, float> arg2 {12, 14, 13, " ", 2.2};
    std::tuple<int, int, long, std::string, float> arg3 {0, 1, 3, "world", 0.1};
    auto result = tuple_utils::fold(arg1, arg2, arg3);

    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(14 == std::get<0>(result));
    CPPUNIT_ASSERT(17 == std::get<1>(result));
    CPPUNIT_ASSERT(38 == std::get<2>(result));
    CPPUNIT_ASSERT("hello world" == std::get<3>(result));
    CPPUNIT_ASSERT(std::abs(3.4 - std::get<4>(result)) < std::numeric_limits<float>::epsilon());
}

void TestFoldTuple::test4tuples()
{
    std::tuple<int, std::string, short> arg1 {11, "mary had", 24};
    std::tuple<int, std::string, short> arg2 {22, "", 11};
    std::tuple<int, std::string, short> arg3 {33, " a little lamb", 6};
    std::tuple<int, std::string, short> arg4 {0, ";", 0};
    auto result = tuple_utils::fold(arg1, arg2, arg3, arg4);

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(66 == std::get<0>(result));
    CPPUNIT_ASSERT("mary had a little lamb;" == std::get<1>(result));
    CPPUNIT_ASSERT(41 == std::get<2>(result));
}

void TestFoldTuple::testEmptyTuples()
{
    std::tuple<> arg1 {};
    std::tuple<> arg2 {};
    std::tuple<> arg3 {};
    auto result = tuple_utils::fold(arg1, arg2, arg3);

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
}

void TestFoldTuple::testTuples1Elem()
{
    std::tuple<int> arg1 {2};
    std::tuple<int> arg2 {1};
    std::tuple<int> arg3 {4};
    auto result = tuple_utils::fold(arg1, arg2, arg3);

    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(7 == std::get<0>(result));
}

void TestFoldTuple::testTuples2Elem()
{
    std::tuple<int, double> arg1 {2, 2.2};
    std::tuple<int, double> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(arg1, arg2, arg3);

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(7 == std::get<0>(result));
    CPPUNIT_ASSERT(3.6 == std::get<1>(result));
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestFoldTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

