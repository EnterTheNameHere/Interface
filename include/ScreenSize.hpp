#ifndef SCREENSIZE_HPP_INCLUDED_1839
#define SCREENSIZE_HPP_INCLUDED_1839

namespace Interface
{

struct ScreenSize
{
    ScreenSize( int width = 0, int height = 0 ) :
        Width( width ),
        Height( height )
    {}
    
    int Width = 0;
    int Height = 0;
};
typedef ScreenSize TextureSize;

} // namespace Interface

#endif // SCREENSIZE_HPP_INCLUDED_1839
