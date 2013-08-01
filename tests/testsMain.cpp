
#include <UTile/UnitTest.hpp>
#include <SFML/Graphics.hpp>
#include <Utils/Utils.hpp>

int main( int, char** )
{
    UnitTest::TestManager manager;
    manager.RunAllTests();
    
    return 0;
}


// TODO: pub ScreenPosition into its own file and include its header...
struct ScreenPosition
{
    ScreenPosition( int x, int y ) :
        X( x ),
        Y( y )
    {
    }
    
    ScreenPosition( const ScreenPosition& position )
    {
        this->X = position.X;
        this->Y = position.Y;
    }
    
    ScreenPosition& operator = ( const ScreenPosition& position )
    {
        this->X = position.X;
        this->Y = position.Y;
        
        return *this;
    }
    
    bool operator == ( const ScreenPosition& right ) const
    {
        if( (this->X == right.X) && (this->Y == right.Y) )
            return true;
        else
            return false;
    }
    
    bool operator != ( const ScreenPosition& right ) const
    {
        return (*this == right);
    }
    
    ScreenPosition& operator += ( const ScreenPosition& right )
    {
        this->X += right.X;
        this->Y += right.Y;
        return *this;
    }
    
    ScreenPosition& operator -= ( const ScreenPosition& right )
    {
        this->X -= right.X;
        this->Y -= right.Y;
        return *this;
    }
    
    ScreenPosition& operator *= ( int multiplier )
    {
        this->X *= multiplier;
        this->Y *= multiplier;
        return *this;
    }
    
    ScreenPosition& operator /= ( int divisor )
    {
        this->X /= divisor;
        this->Y /= divisor;
        return *this;
    }
    
    const ScreenPosition operator + ( const ScreenPosition& right ) const
    {
        return (ScreenPosition(*this) += right);
    }
    
    const ScreenPosition operator - ( const ScreenPosition& right ) const
    {
        return (ScreenPosition(*this) -= right);
    }
    
    ScreenPosition operator * ( int multiplier )
    {
        return ScreenPosition(*this) *= multiplier;
    }
    
    ScreenPosition operator / ( int divisor )
    {
        return ScreenPosition(*this) /= divisor;
    }
    
    ScreenPosition operator - () const
    {
        return ScreenPosition(*this) * (-1);
    }
    
    int X = 0;
    int Y = 0;
};

using namespace UnitTest;

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
