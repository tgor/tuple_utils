#include <tuple>
#include <string>
#include <limits>
#include <cmath>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include "../src/zip_tuples.hpp"
#include "../src/print_tuple.hpp"

class TestZipTuples : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestZipTuples);
    CPPUNIT_TEST(test1tuple);
    CPPUNIT_TEST(testLvalues);
    CPPUNIT_TEST(testConstLvalues);
    CPPUNIT_TEST(testRvalues);
    CPPUNIT_TEST(test2tuplesSameSize);
    CPPUNIT_TEST(test2tuplesDiffSize);
    CPPUNIT_TEST(test3tuplesSameSize);
    CPPUNIT_TEST(test3tuplesDiffSize);
    CPPUNIT_TEST(test4tuplesSameSize);
    CPPUNIT_TEST(test4tuplesDiffSize);
    CPPUNIT_TEST(test5tuplesSameSize);
    CPPUNIT_TEST(test5tuplesDiffSize);
    CPPUNIT_TEST(testDuplicatedElement);
    CPPUNIT_TEST(test2xSameElement);
    CPPUNIT_TEST(testEmptyBegin);
    CPPUNIT_TEST(testEmptyEnd);
    CPPUNIT_TEST(testEmptyMid);
    CPPUNIT_TEST(testMultipleEmpty);
    CPPUNIT_TEST(testOneEmpty);
    CPPUNIT_TEST(testNoArgs);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test1tuple();
    void testLvalues();
    void testConstLvalues();
    void testRvalues();
    void test2tuplesSameSize();
    void test2tuplesDiffSize();
    void test3tuplesSameSize();
    void test3tuplesDiffSize();
    void test4tuplesSameSize();
    void test4tuplesDiffSize();
    void test5tuplesSameSize();
    void test5tuplesDiffSize();
    void testDuplicatedElement();
    void test2xSameElement();
    void testEmptyBegin();
    void testEmptyEnd();
    void testEmptyMid();
    void testMultipleEmpty();
    void testOneEmpty();
    void testNoArgs();

};

void TestZipTuples::setUp()
{}

void TestZipTuples::tearDown()
{}

void TestZipTuples::test1tuple()
{
    auto result = tuple_utils::zip(std::make_tuple(4, 5.5, 1L, "test"));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  3,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(4) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(5.5) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(1L) == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple("test") == std::get<3>(result));
}

void TestZipTuples::testLvalues()
{
    auto arg1 = std::make_tuple("x", "y", 3);
    auto arg2 = std::make_tuple(5.5, 4L, -3);
    auto result = tuple_utils::zip(arg1, arg2);

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("x", 5.5) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple("y", 4L) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(3, -3) == std::get<2>(result));
}

void TestZipTuples::testConstLvalues()
{
    const auto arg1 = std::make_tuple("x", "y", 3);
    const auto arg2 = std::make_tuple(5.5, 4L, -3);
    auto result = tuple_utils::zip(arg1, arg2);

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("x", 5.5) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple("y", 4L) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(3, -3) == std::get<2>(result));
}

void TestZipTuples::testRvalues()
{
    auto result = tuple_utils::zip(std::make_tuple("x", "y", 3), std::make_tuple(5.5, 4L, -3));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("x", 5.5) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple("y", 4L) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(3, -3) == std::get<2>(result));
}

void TestZipTuples::test2tuplesSameSize()
{
    auto arg1 = std::make_tuple(4.4, 6.6f, 8, 10);
    auto result = tuple_utils::zip(arg1, std::make_tuple(5, 7.7, "nine", 11));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<double, int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<float, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, const char*>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  3,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(4.4, 5) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(6.6f, 7.7) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(8, "nine") == std::get<2>(result));
    CPPUNIT_ASSERT(std::make_tuple(10, 11) == std::get<3>(result));
}

void TestZipTuples::test2tuplesDiffSize()
{
    auto arg1 = std::make_tuple(4.4, 6.6f);
    auto result = tuple_utils::zip(arg1, std::make_tuple(5, 7.7, "nine", 11));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<double, int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<float, double>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(4.4, 5) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(6.6f, 7.7) == std::get<1>(result));
}

void TestZipTuples::test3tuplesSameSize()
{
    auto result = tuple_utils::zip(std::make_tuple(1), std::make_tuple(2.2), std::make_tuple("three"));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, const char*>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1, 2.2, "three") == std::get<0>(result));
}

void TestZipTuples::test3tuplesDiffSize()
{
    const auto arg1 = std::make_tuple(9, 8, 7, "not included");
    const auto arg2 = std::make_tuple(6.6, 5.5, 4.4);
    const auto arg3 = std::make_tuple(3, 2L, 1ULL, "likewise");
    auto result = tuple_utils::zip(arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, unsigned long long>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(9, 6.6, 3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(8, 5.5, 2L) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(7, 4.4, 1ULL) == std::get<2>(result));
}

void TestZipTuples::test4tuplesSameSize()
{
    const auto arg1 = std::make_tuple("hello", 8, 7);
    auto arg2 = std::make_tuple(" ", 5.5, 4.4);
    auto arg4 = std::make_tuple("!", 2L, 1ULL);
    auto result = tuple_utils::zip(arg1, arg2, std::make_tuple("world", 4.12, 0.1f), arg4);

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<const char*, const char*, const char*, const char*>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, double, long>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, double, float, unsigned long long>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("hello", " ", "world", "!") == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(8, 5.5, 4.12, 2L) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(7, 4.4, 0.1f, 1ULL) == std::get<2>(result));
}

void TestZipTuples::test4tuplesDiffSize()
{
    auto arg2 = std::make_tuple(1, "test");
    auto arg3 = std::make_tuple(11, 3.3, 4);
    auto result = tuple_utils::zip(std::make_tuple(4.4, 0.1f, 5u), arg2, arg3, std::make_tuple(4, 5));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<double, int, int, int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<float, const char*, double, int>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(4.4, 1, 11, 4) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(0.1f, "test", 3.3, 5) == std::get<1>(result));
}

void TestZipTuples::test5tuplesSameSize()
{
    std::tuple<int, std::string, char> arg1 {11, "mary had", 24};
    std::tuple<int, std::string, short> arg2 {22, "", 11};
    std::tuple<double, const std::string, short> arg3 {33.3, " a little lamb", 6};
    std::tuple<int, int, short> arg4 {0, 0, 0};
    auto result = tuple_utils::zip(arg1, arg2, arg3, arg4, std::make_tuple(0.3, 0.4f, 0.55));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int, double, int, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<std::string, std::string, std::string, int, float>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<char, short, short, short, double>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(11, 22, 33.3, 0, 0.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple("mary had", "", " a little lamb", 0, 0.4f) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(24, 11, 6, 0, 0.55) == std::get<2>(result));
}

void TestZipTuples::test5tuplesDiffSize()
{
    auto arg1 = std::make_tuple(11, std::string{"mary had"}, 24, 1, 1, 1, 1, 1);
    auto arg2 = std::make_tuple(22, std::string{""}, 11);
    auto arg3 = std::make_tuple(33.3, std::string{" a little lamb"}, 6, 2, 2, 2, 2);
    auto arg4 = std::make_tuple(0, 0, 0, 3, 3, 3, 3);
    auto result = tuple_utils::zip(arg1, arg2, arg3, arg4, std::make_tuple(0.3, 0.4f, 0.55));

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int, double, int, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<std::string, std::string, std::string, int, float>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int, int, int, double>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(11, 22, 33.3, 0, 0.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple("mary had", "", " a little lamb", 0, 0.4f) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(24, 11, 6, 0, 0.55) == std::get<2>(result));
}

void TestZipTuples::testDuplicatedElement()
{
    auto arg1 = std::make_tuple(1, 2, 3);
    auto result = tuple_utils::zip(arg1, std::make_tuple(3.3, 4, "test"), arg1);

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
    CPPUNIT_ASSERT(std::make_tuple(2, 4, 2) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(3, "test", 3) == std::get<2>(result));
}

void TestZipTuples::test2xSameElement()
{
    auto arg1 = std::make_tuple(1.3, 2, 3.5f);
    auto result = tuple_utils::zip(arg1, arg1);

    static_assert(std::is_same<std::tuple_element<
                                                  0,
                                                  decltype(result)>::type,
                                                  std::tuple<double, double>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  1,
                                                  decltype(result)>::type,
                                                  std::tuple<int, int>
                                              >::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<
                                                  2,
                                                  decltype(result)>::type,
                                                  std::tuple<float, float>
                                              >::value, "Type mismatch");

    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(1.3, 1.3) == std::get<0>(result));
    CPPUNIT_ASSERT(std::make_tuple(2, 2) == std::get<1>(result));
    CPPUNIT_ASSERT(std::make_tuple(3.5f, 3.5f) == std::get<2>(result));
}

void TestZipTuples::testEmptyBegin()
{
    auto arg1 = std::make_tuple();
    auto arg3 = std::make_tuple(4.4, 32ull);
    auto result = tuple_utils::zip(arg1, std::make_tuple(11, 22), arg3);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestZipTuples::testEmptyEnd()
{
    auto arg1 = std::make_tuple(4, 6.1f, 55, 53ull, 45l);
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::zip(arg1, std::make_tuple(11, 22), arg3);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestZipTuples::testEmptyMid()
{
    auto arg1 = std::make_tuple(4, 6.1f, 55, 53ull, 45l);
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::zip(arg1, std::make_tuple(11, 22), arg3, std::make_tuple(4, 5.3));

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestZipTuples::testMultipleEmpty()
{
    auto arg1 = std::make_tuple();
    auto arg3 = std::make_tuple();
    auto result = tuple_utils::zip(arg1, std::make_tuple(11, 22), arg3, std::make_tuple());

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestZipTuples::testOneEmpty()
{
    auto arg1 = std::make_tuple();
    auto result = tuple_utils::zip(arg1);

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

void TestZipTuples::testNoArgs()
{
    auto result = tuple_utils::zip();

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");

    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::tuple<>() == result);
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestZipTuples );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

