#ifndef SCREENRECTANGLE_HPP_INCLUDED_1822
#define SCREENRECTANGLE_HPP_INCLUDED_1822

#include "ScreenPosition.hpp"
#include "ScreenSize.hpp"

namespace Interface
{

class ScreenRectangle
{
public:
    ScreenRectangle( int left = 0, int top = 0, int width = 0, int height = 0 ) :
        Left(left),
        Top(top),
        Width(width),
        Height(height),
        Bottom(Top+Width),
        Right(Left+Height)
    {
    }
    
    ScreenRectangle( ScreenPosition position, ScreenSize size ) :
        ScreenRectangle( position.X, position.Y, size.Width, size.Height )
    {
    }
    
    const ScreenPosition GetPosition() const
    {
        return {Left,Top};
    }
    
    void SetPosition( const ScreenPosition& position )
    {
        Left = position.X;
        Top = position.Y;
        Right = Left + Width;
        Bottom = Top + Height;
    }
    
    const ScreenSize GetSize() const
    {
        return {Width,Height};
    }
    
    void SetSize( const ScreenSize& size )
    {
        Width = size.Width;
        Height = size.Height;
        Right = Left + Width;
        Bottom = Top + Height;
    }
    
    bool Contains( const ScreenPosition& pos ) const
    {
        if( ( pos.X <= Right && pos.X >= Left )
           && ( pos.Y <= Bottom && pos.Y >= Top ) )
           return true;
        return false;
    }
    
    bool Contains( int x, int y ) const
    {
        return this->Contains( {x,y} );
    }
    
    int Left = 0;
    int Top = 0;
    int Width = 0;
    int Height = 0;
    int Right = 0;
    int Bottom = 0;
};
typedef ScreenRectangle TextureRectangle;

}

#endif // SCREENRECTANGLE_HPP_INCLUDED_1822
