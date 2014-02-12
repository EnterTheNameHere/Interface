#ifndef SCREENPOSITION_HPP_INCLUDED_1555
#define SCREENPOSITION_HPP_INCLUDED_1555

namespace Interface
{

class ScreenPosition
{
public:
    ScreenPosition( int x, int y ) :
        X( x ),
        Y( y ),
        Left( X ),
        Top( Y )
    {
    }
    
    ScreenPosition( const ScreenPosition& position )
    {
        this->X = position.X;
        this->Y = position.Y;
        this->Left = this->X;
        this->Top = this->Y;
    }
    
    ScreenPosition& operator = ( const ScreenPosition& position )
    {
        this->X = position.X;
        this->Y = position.Y;
        this->Left = this->X;
        this->Top = this->Y;
        
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
        this->Left = this->X;
        this->Top = this->Y;
        return *this;
    }
    
    ScreenPosition& operator -= ( const ScreenPosition& right )
    {
        this->X -= right.X;
        this->Y -= right.Y;
        this->Left = this->X;
        this->Top = this->Y;
        return *this;
    }
    
    ScreenPosition& operator *= ( int multiplier )
    {
        this->X *= multiplier;
        this->Y *= multiplier;
        this->Left = this->X;
        this->Top = this->Y;
        return *this;
    }
    
    ScreenPosition& operator /= ( int divisor )
    {
        this->X /= divisor;
        this->Y /= divisor;
        this->Left = this->X;
        this->Top = this->Y;
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
    int Left = 0;
    int Top = 0;
};
typedef ScreenPosition TexturePosition;

} // namespace Interface

#endif // SCREENPOSITION_HPP_INCLUDED_1555
