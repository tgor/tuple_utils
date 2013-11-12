#include "../src/make_custom_tuple.hpp"
#include <tuple>
#include <string>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>


class TestMakeCustomTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMakeCustomTuple);
    CPPUNIT_TEST(testSimpleCreation);
    CPPUNIT_TEST(testCutCreation);
    CPPUNIT_TEST(testExtendedCreation);
    CPPUNIT_TEST(testVariousCreation);
    CPPUNIT_TEST(testNullCreation);
    CPPUNIT_TEST(testSingleCreation);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void testSimpleCreation();
    void testCutCreation();
    void testExtendedCreation();
    void testVariousCreation();
    void testNullCreation();
    void testSingleCreation();
    std::tuple<int, float, double, char, std::string> base {1, 2.2, 3.3, '4', "test"};
};

void TestMakeCustomTuple::setUp()
{}

void TestMakeCustomTuple::tearDown()
{}

void TestMakeCustomTuple::testSimpleCreation()
{
    auto result = tuple_utils::make_custom_tuple<0, 1, 2, 3, 4>(base);
    CPPUNIT_ASSERT(std::get<0>(result) == std::get<0>(base));
    CPPUNIT_ASSERT(std::get<1>(result) == std::get<1>(base));
    CPPUNIT_ASSERT(std::get<2>(result) == std::get<2>(base));
    CPPUNIT_ASSERT(std::get<3>(result) == std::get<3>(base));
    CPPUNIT_ASSERT(std::get<4>(result) == std::get<4>(base));
    CPPUNIT_ASSERT(std::tuple_size<decltype(result)>::value == std::tuple_size<decltype(base)>::value);
}

void TestMakeCustomTuple::testCutCreation()
{
    auto result = tuple_utils::make_custom_tuple<1, 2>(base);
    CPPUNIT_ASSERT(std::get<0>(result) == std::get<1>(base));
    CPPUNIT_ASSERT(std::get<1>(result) == std::get<2>(base));
    CPPUNIT_ASSERT(2 == std::tuple_size<decltype(result)>::value);
}

void TestMakeCustomTuple::testExtendedCreation()
{
    auto result = tuple_utils::make_custom_tuple<0, 1, 2, 3, 4, 4, 3, 2>(base);
    CPPUNIT_ASSERT(std::get<0>(result) == std::get<0>(base));
    CPPUNIT_ASSERT(std::get<1>(result) == std::get<1>(base));
    CPPUNIT_ASSERT(std::get<2>(result) == std::get<2>(base));
    CPPUNIT_ASSERT(std::get<3>(result) == std::get<3>(base));
    CPPUNIT_ASSERT(std::get<4>(result) == std::get<4>(base));
    CPPUNIT_ASSERT(std::get<5>(result) == std::get<4>(base));
    CPPUNIT_ASSERT(std::get<6>(result) == std::get<3>(base));
    CPPUNIT_ASSERT(std::get<7>(result) == std::get<2>(base));
    CPPUNIT_ASSERT(8 == std::tuple_size<decltype(result)>::value);
}

void TestMakeCustomTuple::testVariousCreation()
{
    auto result = tuple_utils::make_custom_tuple<2, 4, 1, 0>(base);
    CPPUNIT_ASSERT(std::get<0>(result) == std::get<2>(base));
    CPPUNIT_ASSERT(std::get<1>(result) == std::get<4>(base));
    CPPUNIT_ASSERT(std::get<2>(result) == std::get<1>(base));
    CPPUNIT_ASSERT(std::get<3>(result) == std::get<0>(base));
    CPPUNIT_ASSERT(4 == std::tuple_size<decltype(result)>::value);
}

void TestMakeCustomTuple::testNullCreation()
{
    auto result = tuple_utils::make_custom_tuple<>(base);
    CPPUNIT_ASSERT(0 == std::tuple_size<decltype(result)>::value);
}

void TestMakeCustomTuple::testSingleCreation()
{
    auto result = tuple_utils::make_custom_tuple<3>(base);
    CPPUNIT_ASSERT(std::get<0>(result) == std::get<3>(base));
    CPPUNIT_ASSERT(1 == std::tuple_size<decltype(result)>::value);
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestMakeCustomTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

