
#include "ScreenPosition.hpp"

#include <UTile/UnitTest.hpp>
#include <Utils/Utils.hpp>

using namespace UnitTest;
using namespace Interface;

class TestScreenPosition : public Test<TestScreenPosition>
{
public:
    virtual void RunTest() const override
    {
        GetID();
        
        ScreenPosition pos1 {5,5};
        ScreenPosition pos2(5,5);
        ScreenPosition pos3 = {5,5};
        
        Assert::That( pos1, Is::EqualTo( pos2 ) );
        Assert::That( pos1, Is::EqualTo( pos3 ) );
        
        ScreenPosition pos4( pos2 );
        Assert::That( pos4, Is::EqualTo( pos2 ) );
        
        ScreenPosition pos5( {-50,50} );
        Assert::That( pos5, Is::EqualTo( ScreenPosition(-50, 50) ) );
        
        ScreenPosition pos6( ScreenPosition(10,-10) );
        Assert::That( pos6, Is::EqualTo( ScreenPosition(10,-10) ) );
        
        pos2 = pos3 = pos6;
        Assert::That( pos2, Is::EqualTo( ScreenPosition(10,-10) ) );
        
        pos6 = pos5 = pos4 = pos3;
        Assert::That( pos6, Is::EqualTo( pos3 ) );
        Assert::That( pos5, Is::EqualTo( pos3 ) );
        Assert::That( pos4, Is::EqualTo( pos3 ) );
        
        
        pos3 = {55,55};
        pos3 += pos2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(65,45) ) );
        
        pos3 += ScreenPosition( -10, -10 );
        Assert::That( pos3, Is::EqualTo( ScreenPosition(55,35) ) );
        
        pos3 -= pos2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(45,45) ) );
        
        pos3 -= ScreenPosition( -10, -10 );
        Assert::That( pos3, Is::EqualTo( ScreenPosition(55,55) ) );
        
        
        
        pos3 = pos1 + pos2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(15,-5) ) );
        
        pos3 = pos1 + ScreenPosition( -10, -10 );
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-5,-5) ) );
        
        pos3 = ScreenPosition( 50, 50 ) + pos1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(55,55) ) );
        
        
        
        pos3 = pos1 - pos2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-5,15) ) );
        
        pos3 = pos1 - ScreenPosition( 10, 10 );
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-5,-5) ) );
        
        pos3 = ScreenPosition( -50, -50 ) - pos1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-55,-55) ) );
        
        pos3 = pos3 - ScreenPosition( -5, -15 );
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-50,-40) ) );
        
        
        
        Assert::That( -pos3, Is::EqualTo( ScreenPosition(50,40) ) );
        Assert::That( -pos2, Is::EqualTo( ScreenPosition(-10,10) ) );
        
        pos3 = -pos2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-10,10) ) );
        
        pos3 = pos2 - (-pos2);
        Assert::That( pos3, Is::EqualTo( ScreenPosition(20,-20) ) );
        
        pos3 = -pos2 - (-pos2);
        Assert::That( pos3, Is::EqualTo( ScreenPosition(0,0) ) );
        
        
        pos3 = {0,20};
        pos3 *= 1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(0,20) ) );
        
        pos3 *= 2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(0,40) ) );
        
        pos3 /= 1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(0,40) ) );
        
        pos3 /= 2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(0,20) ) );
        
        
        
        pos3 = {10,-10};
        Assert::That( pos3 * 1, Is::EqualTo( ScreenPosition(10,-10) ) );
        Assert::That( pos3 * -1, Is::EqualTo( ScreenPosition(-10,10) ) );
        Assert::That( pos3 * 10, Is::EqualTo( ScreenPosition(100,-100) ) );
        Assert::That( pos3 * -10, Is::EqualTo( ScreenPosition(-100,100) ) );
        
        Assert::That( pos3 / 1, Is::EqualTo( ScreenPosition(10,-10) ) );
        Assert::That( pos3 / -1, Is::EqualTo( ScreenPosition(-10,10) ) );
        Assert::That( pos3 / 10, Is::EqualTo( ScreenPosition(1,-1) ) );
        Assert::That( pos3 / -10, Is::EqualTo( ScreenPosition(-1,1) ) );
        
        
        
        pos3 = pos2 * 1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(10,-10) ) );
        pos3 = pos2 * -1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-10,10) ) );
        pos3 = pos2 * 2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(20,-20) ) );
        pos3 = pos2 * -2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-20,20) ) );
        
        pos3 = pos2 / 1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(10,-10) ) );
        pos3 = pos2 / -1;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-10,10) ) );
        pos3 = pos2 / 2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(5,-5) ) );
        pos3 = pos2 / -2;
        Assert::That( pos3, Is::EqualTo( ScreenPosition(-5,5) ) );
        
    }
};
