#include <tuple>
#include <string>
#include <limits>
#include <cmath>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include "../src/cartesian_product.hpp"
#include "../src/print_tuple.hpp"

class TestCartesianProduct : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestCartesianProduct);
    CPPUNIT_TEST(test1tuple);
    CPPUNIT_TEST(test2tuplesSameSize);
    CPPUNIT_TEST(test2tupleDiffSize);
    CPPUNIT_TEST(test3tuplesSameSize);
    CPPUNIT_TEST(test3tupleDiffSize);
    CPPUNIT_TEST(test4tuplesSameSize);
    CPPUNIT_TEST(test4tupleDiffSize);
    CPPUNIT_TEST(test5tuplesSameSize);
    CPPUNIT_TEST(test5tupleDiffSize);
    CPPUNIT_TEST(testEmptyBegin);
    CPPUNIT_TEST(testEmptyEnd);
    CPPUNIT_TEST(testEmptyMid);
    CPPUNIT_TEST(testMultipleEmpty);
    CPPUNIT_TEST(testOneEmpty);
    CPPUNIT_TEST(testDuplicatedElement);
    CPPUNIT_TEST(test2xSameElement);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test1tuple();
    void test2tuplesSameSize();
    void test2tupleDiffSize();
    void test3tuplesSameSize();
    void test3tupleDiffSize();
    void test4tuplesSameSize();
    void test4tupleDiffSize();
    void test5tuplesSameSize();
    void test5tupleDiffSize();
    void testEmptyBegin();
    void testEmptyEnd();
    void testEmptyMid();
    void testMultipleEmpty();
    void testOneEmpty();
    void testDuplicatedElement();
    void test2xSameElement();
};

void TestCartesianProduct::setUp()
{}

void TestCartesianProduct::tearDown()
{}

void TestCartesianProduct::test1tuple()
{
    auto result = tuple_utils::c_product(std::make_tuple(1, 2, 3, "four", 5.05));

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<2, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<3, decltype(result)>::type, const char*>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<4, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(1 == std::get<0>(result));
    CPPUNIT_ASSERT(2 == std::get<1>(result));
    CPPUNIT_ASSERT(3 == std::get<2>(result));
    CPPUNIT_ASSERT(std::string("four") == std::get<3>(result));
    CPPUNIT_ASSERT(std::abs(5.05 - std::get<4>(result)) < std::numeric_limits<float>::epsilon());
}

void TestCartesianProduct::test2tuplesSameSize()
{
    auto arg1 = std::make_tuple(1, "test");
    auto result = tuple_utils::c_product(arg1, std::make_tuple(3.3, 4));

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<const char*, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                3,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 3.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 4) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 3.3) == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 4) == std::get<3>(result));
}

void TestCartesianProduct::test2tupleDiffSize()
{
    auto arg1 = std::make_tuple(1, "test");
    auto result = tuple_utils::c_product(arg1, std::make_tuple(3.3, 4, '5'));

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<int, char>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                3,
                                                decltype(result)>::type,
                                                std::tuple<const char*, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                4,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                5,
                                                decltype(result)>::type,
                                                std::tuple<const char*, char>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(6 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 3.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 4) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, '5') == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 3.3) == std::get<3>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 4) == std::get<4>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", '5') == std::get<5>(result));
}

void TestCartesianProduct::test3tuplesSameSize()
{
    auto arg1 = std::make_tuple(1, "test");
    auto arg3 = std::make_tuple(4.4, 32ull);
    auto result = tuple_utils::c_product(arg1, std::make_tuple(11, 22), arg3);

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int, unsigned long long>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<int, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                3,
                                                decltype(result)>::type,
                                                std::tuple<int, int, unsigned long long>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                4,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                5,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, unsigned long long>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                6,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                7,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, unsigned long long>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(8 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 11, 4.4) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 11, 32ull) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 22, 4.4) == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 22, 32ull) == std::get<3>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 11, 4.4) == std::get<4>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 11, 32ull) == std::get<5>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 22, 4.4) == std::get<6>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 22, 32ull) == std::get<7>(result));
}

void TestCartesianProduct::test3tupleDiffSize()
{
    auto arg1 = std::make_tuple(1, "test");
    auto arg2 = std::make_tuple(11);
    auto result = tuple_utils::c_product(arg1, arg2, std::make_tuple(4.4, 0.1f, 5u));

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int, float>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<int, int, unsigned>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                3,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                4,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, float>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                5,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, unsigned>
                                            >::value, "Type mismatch");
    CPPUNIT_ASSERT(6 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 11, 4.4) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 11, 0.1f) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 11, 5u) == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 11, 4.4) == std::get<3>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 11, 0.1f) == std::get<4>(result));
    CPPUNIT_ASSERT(std::make_tuple("test", 11, 5u) == std::get<5>(result));
}

void TestCartesianProduct::test4tuplesSameSize()
{
    auto arg1 = std::make_tuple(1, 2);
    auto arg2 = std::make_tuple(3, 4);
    auto arg3 = std::make_tuple(5, 6);
    auto arg4 = std::make_tuple(7, 8);
    auto result = tuple_utils::c_product(arg1, arg2, arg3, arg4);
    auto expected = std::string{"((1, 3, 5, 7), (1, 3, 5, 8), (1, 3, 6, 7), (1, 3, 6, 8), (1, 4, 5, 7), \
(1, 4, 5, 8), (1, 4, 6, 7), (1, 4, 6, 8), (2, 3, 5, 7), (2, 3, 5, 8), (2, 3, 6, 7), (2, 3, 6, 8), \
(2, 4, 5, 7), (2, 4, 5, 8), (2, 4, 6, 7), (2, 4, 6, 8))"};

    CPPUNIT_ASSERT(16 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(tuple_utils::to_string(result) == expected);
}

void TestCartesianProduct::test4tupleDiffSize()
{
    auto arg2 = std::make_tuple(1, "test");
    auto arg3 = std::make_tuple(11, 3.3, 4);
    auto result = tuple_utils::c_product(std::make_tuple(4.4, 0.1f, 5u), arg2, arg3, std::make_tuple(4, 5));
    auto expected = std::string{"((4.4, 1, 11, 4), (4.4, 1, 11, 5), (4.4, 1, 3.3, 4), (4.4, 1, 3.3, 5), \
(4.4, 1, 4, 4), (4.4, 1, 4, 5), (4.4, test, 11, 4), (4.4, test, 11, 5), (4.4, test, 3.3, 4), \
(4.4, test, 3.3, 5), (4.4, test, 4, 4), (4.4, test, 4, 5), (0.1, 1, 11, 4), (0.1, 1, 11, 5), \
(0.1, 1, 3.3, 4), (0.1, 1, 3.3, 5), (0.1, 1, 4, 4), (0.1, 1, 4, 5), (0.1, test, 11, 4), \
(0.1, test, 11, 5), (0.1, test, 3.3, 4), (0.1, test, 3.3, 5), (0.1, test, 4, 4), (0.1, test, 4, 5), \
(5, 1, 11, 4), (5, 1, 11, 5), (5, 1, 3.3, 4), (5, 1, 3.3, 5), (5, 1, 4, 4), (5, 1, 4, 5), \
(5, test, 11, 4), (5, test, 11, 5), (5, test, 3.3, 4), (5, test, 3.3, 5), (5, test, 4, 4), \
(5, test, 4, 5))"};

    CPPUNIT_ASSERT(36 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(tuple_utils::to_string(result) == expected);
}

void TestCartesianProduct::test5tuplesSameSize()
{
    auto arg1 = std::make_tuple("test");
    auto arg2 = std::make_tuple(34);
    auto arg3 = std::make_tuple(5.5);
    auto arg4 = std::make_tuple(7.6);
    auto result = tuple_utils::c_product(arg1, arg2, arg3, arg4, std::make_tuple(-5));

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<const char*, int, double, double, int>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("test", 34, 5.5, 7.6, -5) == std::get<0>(result));
}

void TestCartesianProduct::test5tupleDiffSize()
{
    auto arg1 = std::make_tuple(12);
    auto arg2 = std::make_tuple(34);
    auto arg3 = std::make_tuple(56);
    auto arg4 = std::make_tuple(78);
    auto result = tuple_utils::c_product(arg1, arg2, arg3, arg4, std::make_tuple(101L, 102.2));

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, int, int, int, long>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int, int, int, double>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(12, 34, 56, 78, 101L) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(12, 34, 56, 78, 102.2) == std::get<1>(result));
}

void TestCartesianProduct::testEmptyBegin()
{
    auto arg1 = std::make_tuple();
    auto arg3 = std::make_tuple(4.4, 32ull);
    auto result = tuple_utils::c_product(arg1, std::make_tuple(11, 22), arg3);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestCartesianProduct::testEmptyEnd()
{
    auto arg1 = std::make_tuple(4, 6.1f, 55, 53ull, 45l);
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::c_product(arg1, std::make_tuple(11, 22), arg3);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestCartesianProduct::testEmptyMid()
{
    auto arg1 = std::make_tuple(4, 6.1f, 55, 53ull, 45l);
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::c_product(arg1, std::make_tuple(11, 22), arg3, std::make_tuple(4, 5.3));

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestCartesianProduct::testMultipleEmpty()
{
    auto arg1 = std::make_tuple();
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::c_product(arg1, std::make_tuple(11, 22), arg3, std::make_tuple());

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestCartesianProduct::testOneEmpty()
{
    auto arg1 = std::make_tuple();
    auto result = tuple_utils::c_product(arg1);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestCartesianProduct::testDuplicatedElement()
{
    auto arg1 = std::make_tuple(1);
    auto result = tuple_utils::c_product(arg1, std::make_tuple(3.3, 4, "test"), arg1);

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<int, double, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<int, int, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<int, const char*, int>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 3.3, 1) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, 4, 1) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1, "test", 1) == std::get<2>(result));
}

void TestCartesianProduct::test2xSameElement()
{
    auto arg1 = std::make_tuple(1.3, 2, 3.5f);
    auto result = tuple_utils::c_product(arg1, arg1);

    static_assert(std::is_same<std::tuple_element<
                                                0,
                                                decltype(result)>::type,
                                                std::tuple<double, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                1,
                                                decltype(result)>::type,
                                                std::tuple<double, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                2,
                                                decltype(result)>::type,
                                                std::tuple<double, float>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                3,
                                                decltype(result)>::type,
                                                std::tuple<int, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                4,
                                                decltype(result)>::type,
                                                std::tuple<int, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                5,
                                                decltype(result)>::type,
                                                std::tuple<int, float>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                6,
                                                decltype(result)>::type,
                                                std::tuple<float, double>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                7,
                                                decltype(result)>::type,
                                                std::tuple<float, int>
                                            >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                8,
                                                decltype(result)>::type,
                                                std::tuple<float, float>
                                            >::value, "Type mismatch");

    CPPUNIT_ASSERT(9 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1.3, 1.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(1.3, 2) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1.3, 3.5f) == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple(2, 1.3) == std::get<3>(result));
    CPPUNIT_ASSERT(std::make_tuple(2, 2) == std::get<4>(result));
    CPPUNIT_ASSERT(std::make_tuple(2, 3.5f) == std::get<5>(result));
    CPPUNIT_ASSERT(std::make_tuple(3.5f, 1.3) == std::get<6>(result));
    CPPUNIT_ASSERT(std::make_tuple(3.5f, 2) == std::get<7>(result));
    CPPUNIT_ASSERT(std::make_tuple(3.5f, 3.5f) == std::get<8>(result));
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestCartesianProduct );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

