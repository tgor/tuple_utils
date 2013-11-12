#include "../src/print_tuple.hpp"
#include <tuple>
#include <string>
#include <sstream>
#include <type_traits>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>

class TestPrintTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPrintTuple);
    CPPUNIT_TEST(testEmpty);
    CPPUNIT_TEST(test1arg);
    CPPUNIT_TEST(test2arg);
    CPPUNIT_TEST(test3arg);
    CPPUNIT_TEST(test4arg);
    CPPUNIT_TEST(testChangedDelim);
    CPPUNIT_TEST(testNoDelim);
    CPPUNIT_TEST(testComplexDelim);
    CPPUNIT_TEST(testDelim2xChange);
    CPPUNIT_TEST(testChangedBraces);
    CPPUNIT_TEST(testNoBraces);
    CPPUNIT_TEST(testComplexBraces);
    CPPUNIT_TEST(testBraces2xChange);
    CPPUNIT_TEST(testToStringEmpty);
    CPPUNIT_TEST(testToString1arg);
    CPPUNIT_TEST(testToString2arg);
    CPPUNIT_TEST(testToString3arg);
    CPPUNIT_TEST(testToStringDelim);
    CPPUNIT_TEST(testToStringBraces);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void testEmpty();
    void test1arg();
    void test2arg();
    void test3arg();
    void test4arg();
    void testChangedDelim();
    void testNoDelim();
    void testComplexDelim();
    void testDelim2xChange();
    void testChangedBraces();
    void testNoBraces();
    void testComplexBraces();
    void testBraces2xChange();
    void testToStringEmpty();
    void testToString1arg();
    void testToString2arg();
    void testToString3arg();
    void testToStringDelim();
    void testToStringBraces();
};

void TestPrintTuple::setUp()
{
    tuple_utils::change_delim(", ");
    tuple_utils::change_braces("", "");
}

void TestPrintTuple::tearDown()
{}

void TestPrintTuple::testEmpty()
{
    std::ostringstream outstream;
    std::tuple<> arg1;
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str().empty());
}

void TestPrintTuple::test1arg()
{
    std::ostringstream outstream;
    std::tuple<int> arg1{12};
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "12");
}

void TestPrintTuple::test2arg()
{
    std::ostringstream outstream;
    std::tuple<float, short> arg1{0.001, 2};
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "0.001, 2");
}

void TestPrintTuple::test3arg()
{
    std::ostringstream outstream;
    std::tuple<int, int, const char*> arg1{3, 4, "test"};
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3, 4, test");
}

void TestPrintTuple::test4arg()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201, hello, world, 21.12");
}

void TestPrintTuple::testChangedDelim()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_delim("-");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201-hello-world-21.12");
}

void TestPrintTuple::testNoDelim()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_delim("");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201helloworld21.12");
}

void TestPrintTuple::testComplexDelim()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_delim("_+_");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201_+_hello_+_world_+_21.12");
}

void TestPrintTuple::testDelim2xChange()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_delim("_");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201_hello_world_21.12");

    outstream.str("");
    outstream.clear();
    tuple_utils::change_delim(";");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201;hello;world;21.12");
}

void TestPrintTuple::testChangedBraces()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_braces("(", ")");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "(3.201, hello, world, 21.12)");
}

void TestPrintTuple::testNoBraces()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_braces("", "");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "3.201, hello, world, 21.12");
}

void TestPrintTuple::testComplexBraces()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_braces("<<<", ">>>");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "<<<3.201, hello, world, 21.12>>>");
}

void TestPrintTuple::testBraces2xChange()
{
    std::ostringstream outstream;
    std::tuple<double, std::string, std::string, float> arg1{3.201, "hello", "world", 21.12};
    tuple_utils::change_braces("{", "}");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "{3.201, hello, world, 21.12}");

    outstream.str("");
    outstream.clear();
    tuple_utils::change_braces("[", "]");
    outstream << arg1;

    CPPUNIT_ASSERT(outstream.str() == "[3.201, hello, world, 21.12]");
}

void TestPrintTuple::testToStringEmpty()
{
    std::tuple<> arg;
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT(result.empty());
}

void TestPrintTuple::testToString1arg()
{
    std::tuple<std::string> arg{"mary had a little lamb"};
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT("mary had a little lamb" == result);
}

void TestPrintTuple::testToString2arg()
{
    std::tuple<int, int> arg{3, 5};
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT("3, 5" == result);
}

void TestPrintTuple::testToString3arg()
{
    std::tuple<int, const char*, int> arg{3, "test", 5};
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT("3, test, 5" == result);
}

void TestPrintTuple::testToStringDelim()
{
    std::tuple<int, const char*, int> arg{3, "test", 5};
    tuple_utils::change_delim("-");
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT("3-test-5" == result);
}

void TestPrintTuple::testToStringBraces()
{
    std::tuple<int, const char*, int> arg{3, "test", 5};
    tuple_utils::change_braces("[", "]");
    auto result = tuple_utils::to_string(arg);

    CPPUNIT_ASSERT("[3, test, 5]" == result);
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestPrintTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

