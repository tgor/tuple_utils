#include "../src/aux/sequence.hpp"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>

#include <sstream>
#include <type_traits>

class TestSequence : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSequence);
    CPPUNIT_TEST(testMax);
    CPPUNIT_TEST(testMaxStep);
    CPPUNIT_TEST(testMaxStepMin);
    CPPUNIT_TEST(testMinEqMax);
    CPPUNIT_TEST(testXStepNeqMax);
    CPPUNIT_TEST(testFirstStepGtMax);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();   
protected:
    void testMax();
    void testMaxStep();
    void testMaxStepMin();
    void testMinEqMax();
    void testXStepNeqMax();
    void testFirstStepGtMax();
};

void TestSequence::setUp()
{}

void TestSequence::tearDown()
{}

void TestSequence::testMax()
{
    tuple_utils::make_sequence<10>::type result;
    std::ostringstream stream;
    result.print(stream);

    CPPUNIT_ASSERT(stream.str() == "0 1 2 3 4 5 6 7 8 9");
}

void TestSequence::testMaxStep()
{
    tuple_utils::make_sequence<10, 2>::type result;
    std::ostringstream stream;
    result.print(stream);

    CPPUNIT_ASSERT(stream.str() == "2 3 4 5 6 7 8 9");
}

void TestSequence::testMaxStepMin()
{
    tuple_utils::make_sequence<20, 2, 6>::type result;
    std::ostringstream stream;
    result.print(stream);

    CPPUNIT_ASSERT(stream.str() == "2 8 14");
}

void TestSequence::testMinEqMax()
{
    tuple_utils::make_sequence<9, 9>::type result;

    static_assert(true == std::is_same<decltype(result), tuple_utils::sequence<>>::value, "not the same");
}

void TestSequence::testXStepNeqMax()
{
    tuple_utils::make_sequence<30, 20, 7>::type result;
    std::ostringstream stream;
    result.print(stream);

    CPPUNIT_ASSERT(stream.str() == "20 27");
}

void TestSequence::testFirstStepGtMax()
{
    tuple_utils::make_sequence<10, 5, 7>::type result;
    std::ostringstream stream;
    result.print(stream);

    CPPUNIT_ASSERT(stream.str() == "5");
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestSequence );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

