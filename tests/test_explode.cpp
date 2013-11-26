#include "../src/explode.hpp"
#include <tuple>
#include <string>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>


class TestExplodeTuple : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestExplodeTuple);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:

};

void TestExplodeTuple::setUp()
{}

void TestExplodeTuple::tearDown()
{}



CPPUNIT_TEST_SUITE_REGISTRATION( TestExplodeTuple );

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    return wasSuccessful;
}

