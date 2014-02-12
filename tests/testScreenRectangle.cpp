#include <UTile/UnitTest.hpp>
#include <UTile/Assertions/Assert.hpp>

#include "ScreenRectangle.hpp"
#include "ScreenPosition.hpp"
#include "ScreenSize.hpp"

namespace Tests
{

using namespace UnitTest;
using Assertions::Assert;
using namespace Interface;

class TestScreenRectangle : public UnitTest::Test<TestScreenRectangle>
{
public:
    virtual void RunTest() const override
    {
        GetID();
        
        // 0, 0, 0, 0 rectangle
        ScreenRectangle rect1;
        Assert::That( rect1.Left, Is::EqualTo(0) );
        Assert::That( rect1.Top, Is::EqualTo(0) );
        Assert::That( rect1.Right, Is::EqualTo(0) );
        Assert::That( rect1.Bottom, Is::EqualTo(0) );
        Assert::That( rect1.Width, Is::EqualTo(0) );
        Assert::That( rect1.Height, Is::EqualTo(0) );
        
        // 0, 0, 800, 600 rectangle
        ScreenRectangle rect2( 60, 100, 160, 150 );
        Assert::That( rect2.Left, Is::EqualTo(60) );
        Assert::That( rect2.Top, Is::EqualTo(100) );
        Assert::That( rect2.Right, Is::EqualTo(160) );
        Assert::That( rect2.Bottom, Is::EqualTo(150) );
        Assert::That( rect2.Width, Is::EqualTo(100) );
        Assert::That( rect2.Height, Is::EqualTo(50) );
        
        // 20, 20, 140, 50 rectangle
        ScreenRectangle rect3( ScreenPosition( 20, 50 ), ScreenSize( 120, 30 ) );
        Assert::That( rect3.Left, Is::EqualTo(20) );
        Assert::That( rect3.Top, Is::EqualTo(50) );
        Assert::That( rect3.Right, Is::EqualTo(140) );
        Assert::That( rect3.Bottom, Is::EqualTo(80) );
        Assert::That( rect3.Width, Is::EqualTo(120) );
        Assert::That( rect3.Height, Is::EqualTo(30) );
        
        // 60, 80, 10, 20 rectangle
        ScreenRectangle rect4( 60, 80, 10, 20 );
        Assert::That( rect4.Left, Is::EqualTo(60) );
        Assert::That( rect4.Top, Is::EqualTo(80) );
        Assert::That( rect4.Right, Is::EqualTo(10) );
        Assert::That( rect4.Bottom, Is::EqualTo(20) );
        Assert::That( rect4.Width, Is::EqualTo(50) );
        Assert::That( rect4.Height, Is::EqualTo(60) );
    }
};

} // namespace Tests
