#include "../src/merge_tuples.hpp"
#include <tuple>
#include <string>
#include <type_traits>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>

class TestMergeTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMergeTuple);
    CPPUNIT_TEST(test1tuple);
    CPPUNIT_TEST(test2tuples);
    CPPUNIT_TEST(test3tuples);
    CPPUNIT_TEST(test4tuples);
    CPPUNIT_TEST(testEmptyTuplesBegin);
    CPPUNIT_TEST(testEmptyTuplesMid);
    CPPUNIT_TEST(testEmptyTuplesEnd);
    CPPUNIT_TEST(testOnlyEmpty);
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
    void testEmptyTuplesBegin();
    void testEmptyTuplesMid();
    void testEmptyTuplesEnd();
    void testOnlyEmpty();
    void testTuples1Elem();
    void testTuples2Elem();
};

void TestMergeTuple::setUp()
{}

void TestMergeTuple::tearDown()
{}

void TestMergeTuple::test1tuple()
{
    std::tuple<int, long, char, double, int> arg{1, 22, 'a', 2.2, 4};
    auto result = tuple_utils::merge(arg);

    static_assert(true == std::is_same<std::tuple<int, long, char, double, int>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(result == arg);
}

void TestMergeTuple::test2tuples()
{
    std::tuple<int, int> arg1 {2, 21};
    std::tuple<int, int> arg2 {12, 1};
    auto result = tuple_utils::merge(arg1, arg2);

    static_assert(true == std::is_same<std::tuple<int, int, int, int>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(2 == std::get<0>(result));
    CPPUNIT_ASSERT(21 == std::get<1>(result));
    CPPUNIT_ASSERT(12 == std::get<2>(result));
    CPPUNIT_ASSERT(1 == std::get<3>(result));
}

void TestMergeTuple::test3tuples()
{
    std::tuple<int, int, long, std::string> arg1 {2, 2, 22, "hello"};
    std::tuple<std::string, long, std::string, int> arg2 {" ", 0, "world", 1};
    std::tuple<int, short> arg3 {0, 1};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<int, int, long, std::string, std::string, long, std::string, int, int, short>,
                  decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(10 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(2 == std::get<0>(result));
    CPPUNIT_ASSERT(2 == std::get<1>(result));
    CPPUNIT_ASSERT(22 == std::get<2>(result));
    CPPUNIT_ASSERT("hello" == std::get<3>(result));
    CPPUNIT_ASSERT(" " == std::get<4>(result));
    CPPUNIT_ASSERT(0 == std::get<5>(result));
    CPPUNIT_ASSERT("world" == std::get<6>(result));
    CPPUNIT_ASSERT(1 == std::get<7>(result));
    CPPUNIT_ASSERT(0 == std::get<8>(result));
    CPPUNIT_ASSERT(1 == std::get<9>(result));
}

void TestMergeTuple::test4tuples()
{
    std::tuple<std::string, short> arg1 {"mary", 24};
    std::tuple<std::string, short> arg2 {"lamb", 11};
    std::tuple<long, long, short> arg3 {33, 4, 6};
    std::tuple<short, std::string, int, short> arg4 {10, ";", 20, 11};
    auto result = tuple_utils::merge(arg1, arg2, arg3, arg4);

    static_assert(true == std::is_same<std::tuple<std::string, short, std::string, short, long, long, short, short, std::string, int, short>,
                  decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(11 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT("mary" == std::get<0>(result));
    CPPUNIT_ASSERT(24 == std::get<1>(result));
    CPPUNIT_ASSERT("lamb" == std::get<2>(result));
    CPPUNIT_ASSERT(11 == std::get<3>(result));
    CPPUNIT_ASSERT(33 == std::get<4>(result));
    CPPUNIT_ASSERT(4 == std::get<5>(result));
    CPPUNIT_ASSERT(6 == std::get<6>(result));
    CPPUNIT_ASSERT(10 == std::get<7>(result));
    CPPUNIT_ASSERT(";" == std::get<8>(result));
    CPPUNIT_ASSERT(20 == std::get<9>(result));
    CPPUNIT_ASSERT(11 == std::get<10>(result));
}

void TestMergeTuple::testEmptyTuplesBegin()
{
    std::tuple<> arg1 {};
    std::tuple<std::string, short> arg2 {"lamb", 11};
    std::tuple<long, long, short> arg3 {33, 4, 6};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<std::string, short, long, long, short>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT("lamb" == std::get<0>(result));
    CPPUNIT_ASSERT(11 == std::get<1>(result));
    CPPUNIT_ASSERT(33 == std::get<2>(result));
    CPPUNIT_ASSERT(4 == std::get<3>(result));
    CPPUNIT_ASSERT(6 == std::get<4>(result));
}

void TestMergeTuple::testEmptyTuplesMid()
{
    std::tuple<std::string, short> arg1 {"lamb", 11};
    std::tuple<> arg2 {};
    std::tuple<long, long, short> arg3 {33, 4, 6};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<std::string, short, long, long, short>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT("lamb" == std::get<0>(result));
    CPPUNIT_ASSERT(11 == std::get<1>(result));
    CPPUNIT_ASSERT(33 == std::get<2>(result));
    CPPUNIT_ASSERT(4 == std::get<3>(result));
    CPPUNIT_ASSERT(6 == std::get<4>(result));
}

void TestMergeTuple::testEmptyTuplesEnd()
{
    std::tuple<std::string, short> arg1 {"lamb", 11};
    std::tuple<long, long, short> arg2 {33, 4, 6};
    std::tuple<> arg3 {};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<std::string, short, long, long, short>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT("lamb" == std::get<0>(result));
    CPPUNIT_ASSERT(11 == std::get<1>(result));
    CPPUNIT_ASSERT(33 == std::get<2>(result));
    CPPUNIT_ASSERT(4 == std::get<3>(result));
    CPPUNIT_ASSERT(6 == std::get<4>(result));
}

void TestMergeTuple::testOnlyEmpty()
{
    std::tuple<> arg1 {};
    std::tuple<> arg2 {};
    std::tuple<> arg3 {};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
}

void TestMergeTuple::testTuples1Elem()
{
    std::tuple<int> arg1 {2};
    std::tuple<long> arg2 {1};
    std::tuple<int> arg3 {4};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<int, long, int>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(2 == std::get<0>(result));
    CPPUNIT_ASSERT(1 == std::get<1>(result));
    CPPUNIT_ASSERT(4 == std::get<2>(result));
}

void TestMergeTuple::testTuples2Elem()
{
    std::tuple<int, long> arg1 {2, 22};
    std::tuple<int, long> arg2 {1, 11};
    std::tuple<int, long> arg3 {4, 3};
    auto result = tuple_utils::merge(arg1, arg2, arg3);

    static_assert(true == std::is_same<std::tuple<int, long, int, long, int, long>, decltype(result)>::value, "Type mismatch");
    CPPUNIT_ASSERT(6 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(2== std::get<0>(result));
    CPPUNIT_ASSERT(22 == std::get<1>(result));
    CPPUNIT_ASSERT(1 == std::get<2>(result));
    CPPUNIT_ASSERT(11 == std::get<3>(result));
    CPPUNIT_ASSERT(4 == std::get<4>(result));
    CPPUNIT_ASSERT(3 == std::get<5>(result));
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestMergeTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

