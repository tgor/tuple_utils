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

struct t_plus
{
    template <class T, class U>
    auto operator()(T&& t, U&& u) const
    -> decltype(std::forward<T>(t) + std::forward<U>(u))
    {
        return std::forward<T>(t) + std::forward<U>(u);
    }
};



class TestFoldTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFoldTuple);
    CPPUNIT_TEST(test1tuple);
    CPPUNIT_TEST(test2tuples);
    CPPUNIT_TEST(test3tuples);
    CPPUNIT_TEST(test4tuples);
    CPPUNIT_TEST(testTuples1Elem);
    CPPUNIT_TEST(testTuples2Elem);
    CPPUNIT_TEST(testLambdaCaptureValue);
    CPPUNIT_TEST(testLambdaCaptureReference);
    CPPUNIT_TEST(testLambdaCaptureBoth);
    CPPUNIT_TEST(testFunctorByValue);
    CPPUNIT_TEST(testFunctorByReference);
    CPPUNIT_TEST(testFunctorByBoth);
    CPPUNIT_TEST(testFuncPointerByValue);
    CPPUNIT_TEST(testFuncPointerByReference);
    CPPUNIT_TEST(testFuncPointerByBoth);
    CPPUNIT_TEST(testFoldRvalues);
    CPPUNIT_TEST(testFoldRLvalues);
    CPPUNIT_TEST(testFirstSmaller);
    CPPUNIT_TEST(testLastSmaller);
    CPPUNIT_TEST(testSmallerInMid);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test1tuple();
    void test2tuples();
    void test3tuples();
    void test4tuples();
    void testTuples1Elem();
    void testTuples2Elem();    
    void testLambdaCaptureValue();
    void testLambdaCaptureReference();
    void testLambdaCaptureBoth();
    void testFunctorByValue();
    void testFunctorByReference();
    void testFunctorByBoth();
    void testFuncPointerByValue();
    void testFuncPointerByReference();
    void testFuncPointerByBoth();
    void testFoldRvalues();
    void testFoldRLvalues();
    void testFirstSmaller();
    void testLastSmaller();
    void testSmallerInMid();
};

void TestFoldTuple::setUp()
{}

void TestFoldTuple::tearDown()
{}

void TestFoldTuple::test1tuple()
{
    std::tuple<int, long, char, double, int> arg{1, 4, 6, 4, 4};
    auto result = tuple_utils::fold([](int val){ return val+1;}, arg);

    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(2 == std::get<0>(result));
    CPPUNIT_ASSERT(5 == std::get<1>(result));
    CPPUNIT_ASSERT(7 == std::get<2>(result));
    CPPUNIT_ASSERT(5 == std::get<3>(result));
    CPPUNIT_ASSERT(5 == std::get<4>(result));
}

void TestFoldTuple::test2tuples()
{
    std::tuple<int, int> arg1 {2, 2};
    std::tuple<long, short> arg2 {12, 1};
    auto result = tuple_utils::fold(t_plus(), arg1, arg2);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, long>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(14 == std::get<0>(result));
    CPPUNIT_ASSERT(3 == std::get<1>(result));
}

void TestFoldTuple::test3tuples()
{
    std::tuple<int, int, long, std::string, float> arg1 {2, 2, 22, "hello", 1.1};
    std::tuple<int, short, long, std::string, double> arg2 {12, 14, 13, " ", 2.2};
    std::tuple<long long, int, long, const char *, float> arg3 {0, 1, 3, "world", 0.1};
    auto result = tuple_utils::fold(t_plus(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, long long>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<2, decltype(result)>::type, long>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<3, decltype(result)>::type, std::string>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<4, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(14 == std::get<0>(result));
    CPPUNIT_ASSERT(17 == std::get<1>(result));
    CPPUNIT_ASSERT(38 == std::get<2>(result));
    CPPUNIT_ASSERT("hello world" == std::get<3>(result));
    CPPUNIT_ASSERT(std::abs(3.4 - std::get<4>(result)) < std::numeric_limits<float>::epsilon());
}

void TestFoldTuple::test4tuples()
{
    std::tuple<int, std::string, char> arg1 {11, "mary had", 24};
    std::tuple<int, std::string, short> arg2 {22, "", 11};
    std::tuple<double, const std::string, short> arg3 {33.3, " a little lamb", 6};
    std::tuple<int, std::string, short> arg4 {0, ";", 0};
    auto result = tuple_utils::fold(t_plus(), arg1, arg2, arg3, arg4);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, std::string>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<2, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::abs(66.3 - std::get<0>(result)) < std::numeric_limits<float>::epsilon());
    CPPUNIT_ASSERT("mary had a little lamb;" == std::get<1>(result));
    CPPUNIT_ASSERT(41 == std::get<2>(result));
}

void TestFoldTuple::testTuples1Elem()
{
    std::tuple<int> arg1 {2};
    std::tuple<unsigned> arg2 {1};
    std::tuple<unsigned> arg3 {4};
    auto result = tuple_utils::fold(t_plus(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, unsigned>::value, "Type mismatch");
    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(7 == std::get<0>(result));
}

void TestFoldTuple::testTuples2Elem()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(t_plus(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(7 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(3.6 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

void TestFoldTuple::testLambdaCaptureValue()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold([](double x, double y){ return x * y;}, arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

void TestFoldTuple::testLambdaCaptureReference()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<double, double> arg3 {4.0, 0.3};
    auto result = tuple_utils::fold([](const double& x, double& y){ return x * y;}, arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

void TestFoldTuple::testLambdaCaptureBoth()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<double, double> arg3 {4.0, 0.3};
    auto result = tuple_utils::fold([](double x, const double& y){ return x * y;}, arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

struct FunctorByValue
{
    template <typename X, typename Y>
    auto operator()(X x, Y y) -> decltype(x*y)
    {
        return x*y;
    }
};

void TestFoldTuple::testFunctorByValue()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(FunctorByValue(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

struct FunctorByReference
{
    template <typename X, typename Y>
    auto operator()(const X& x, Y& y) -> decltype(x*y)
    {
        return x*y;
    }
};

void TestFoldTuple::testFunctorByReference()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(FunctorByReference(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

struct FunctorByBoth
{
    template <typename X, typename Y>
    auto operator()(X x, const Y& y) -> decltype(x*y)
    {
        return x*y;
    }
};

void TestFoldTuple::testFunctorByBoth()
{
    std::tuple<short, double> arg1 {2, 2.2};
    std::tuple<int, float> arg2 {1, 1.1};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(FunctorByBoth(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(8 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(0.726 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
}

auto funcValue(long x, long y) -> decltype(2*x - y)
{
    return 2*x - y;
}

void TestFoldTuple::testFuncPointerByValue()
{
    std::tuple<int, short> arg1 {2, 2};
    std::tuple<long, long> arg2 {12, 1};
    auto result = tuple_utils::fold(funcValue, arg1, arg2);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, long>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, long>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(-8 == std::get<0>(result));
    CPPUNIT_ASSERT(3 == std::get<1>(result));
}

auto funcReference(long& x, long& y) -> decltype(2*x - y)
{
    return 2*x - y;
}

void TestFoldTuple::testFuncPointerByReference()
{
    std::tuple<long, long> arg1 {2, 2};
    std::tuple<long, long> arg2 {12, 1};
    auto result = tuple_utils::fold(funcReference, arg1, arg2);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, long>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, long>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(-8 == std::get<0>(result));
    CPPUNIT_ASSERT(3 == std::get<1>(result));
}

auto funcBoth(short x, const short& y) -> decltype(2*x - y)
{
    return 2*x - y;
}

void TestFoldTuple::testFuncPointerByBoth()
{
    std::tuple<int, short> arg1 {2, 2};
    std::tuple<short, short> arg2 {12, 1};
    auto result = tuple_utils::fold(funcBoth, arg1, arg2);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(-8 == std::get<0>(result));
    CPPUNIT_ASSERT(3 == std::get<1>(result));
}

void TestFoldTuple::testFoldRvalues()
{
    auto result = tuple_utils::fold(t_plus(), std::make_tuple(2, 4.4, 5), std::make_tuple(3, 5, 6));

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<2, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(5 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(9.4 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
    CPPUNIT_ASSERT(11 == std::get<2>(result));
}

void TestFoldTuple::testFoldRLvalues()
{
    auto arg1 = std::make_tuple(2, 4.4, 5);
    auto result = tuple_utils::fold(t_plus(), arg1, std::make_tuple(3, 5, 6));

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, double>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<2, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(5 == std::get<0>(result));
    CPPUNIT_ASSERT(std::abs(9.4 - std::get<1>(result)) < std::numeric_limits<float>::epsilon());
    CPPUNIT_ASSERT(11 == std::get<2>(result));
}

void TestFoldTuple::testFirstSmaller()
{
    auto arg1 = std::make_tuple(2);
    auto result = tuple_utils::fold(t_plus(), arg1, std::make_tuple(3, 5, 6), std::make_tuple(1, 5.5, 1.1));

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(6 == std::get<0>(result));
}

void TestFoldTuple::testLastSmaller()
{
    std::tuple<int, int, long, std::string, float> arg1 {2, 2, 22, "hello", 1.1};
    std::tuple<int, short, long, std::string, double> arg2 {12, 14, 13, " ", 2.2};
    auto arg3 = std::make_tuple(0, 1);
    auto result = tuple_utils::fold(t_plus(), arg1, arg2, arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    static_assert(std::is_same<std::tuple_element<1, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(14 == std::get<0>(result));
    CPPUNIT_ASSERT(17 == std::get<1>(result));
}

void TestFoldTuple::testSmallerInMid()
{
    std::tuple<short, double, int> arg1 {2, 2.2, 4};
    std::tuple<int, double> arg3 {4, 0.3};
    auto result = tuple_utils::fold(t_plus(), arg1, std::make_tuple(4), arg3);

    static_assert(std::is_same<std::tuple_element<0, decltype(result)>::type, int>::value, "Type mismatch");
    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(10 == std::get<0>(result));
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

