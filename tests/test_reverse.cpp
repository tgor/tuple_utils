#include "../src/reverse.hpp"
#include <tuple>
#include <string>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>


class TestReverseTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestReverseTuple);
    CPPUNIT_TEST(test1Element);
    CPPUNIT_TEST(test2Elements);
    CPPUNIT_TEST(test3Elements);
    CPPUNIT_TEST(test4Elements);
    CPPUNIT_TEST(test5Elements);
    CPPUNIT_TEST(testEmpty);
    CPPUNIT_TEST(testRvalue);
    CPPUNIT_TEST(testLvalue);
    CPPUNIT_TEST(testConst);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test1Element();
    void test2Elements();
    void test3Elements();
    void test4Elements();
    void test5Elements();
    void testEmpty();
    void testRvalue();
    void testLvalue();
    void testConst();
};

void TestReverseTuple::setUp()
{}

void TestReverseTuple::tearDown()
{}

void TestReverseTuple::test1Element()
{
    auto result = tuple_utils::reverse(std::make_tuple("test"));

    static_assert(std::is_same<decltype(result), std::tuple<const char*>>::value, "Type mismatch");
    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("test") == result);
}

void TestReverseTuple::test2Elements()
{
    auto result = tuple_utils::reverse(std::make_tuple(4, 3.3));

    static_assert(std::is_same<decltype(result), std::tuple<double, int>>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(3.3, 4) == result);
}

void TestReverseTuple::test3Elements()
{
    auto result = tuple_utils::reverse(std::make_tuple(4, 3.3, "test"));

    static_assert(std::is_same<decltype(result), std::tuple<const char*, double, int>>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple("test", 3.3, 4) == result);
}

void TestReverseTuple::test4Elements()
{
    auto result = tuple_utils::reverse(std::make_tuple(4, 3.3, 7, 5.5f));

    static_assert(std::is_same<decltype(result), std::tuple<float, int, double, int>>::value, "Type mismatch");
    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(5.5f, 7, 3.3, 4) == result);
}

void TestReverseTuple::test5Elements()
{
    auto result = tuple_utils::reverse(std::make_tuple(12L, 4, 3.3, 7, 5.5f));

    static_assert(std::is_same<decltype(result), std::tuple<float, int, double, int, long>>::value, "Type mismatch");
    CPPUNIT_ASSERT(5 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(5.5f, 7, 3.3, 4, 12L) == result);
}

void TestReverseTuple::testEmpty()
{
    auto result = tuple_utils::reverse(std::make_tuple());

    static_assert(std::is_same<decltype(result), std::tuple<>>::value, "Type mismatch");
    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple() == result);
}

void TestReverseTuple::testRvalue()
{
    auto result = tuple_utils::reverse(std::make_tuple(12L, 45.5f));

    static_assert(std::is_same<decltype(result), std::tuple<float, long>>::value, "Type mismatch");
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(45.5f, 12L) == result);
}

void TestReverseTuple::testLvalue()
{
    auto arg = std::make_tuple(12L, "test", 45.5f);
    auto result = tuple_utils::reverse(arg);

    static_assert(std::is_same<decltype(result), std::tuple<float, const char*, long>>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(45.5f, "test", 12L) == result);
}

void TestReverseTuple::testConst()
{
    const auto arg = std::make_tuple(12L, "test", 45.5f);
    auto result = tuple_utils::reverse(arg);

    static_assert(std::is_same<decltype(result), std::tuple<float, const char*, long>>::value, "Type mismatch");
    CPPUNIT_ASSERT(3 == std::tuple_size<decltype(result)>::value);
    CPPUNIT_ASSERT(std::make_tuple(45.5f, "test", 12L) == result);
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestReverseTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

