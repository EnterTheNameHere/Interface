#ifndef DRAWABLE_HPP_INCLUDED_1618
#define DRAWABLE_HPP_INCLUDED_1618

namespace Interface
{

class Drawable
{
public:
    Drawable()
    {
        m_Border.setFillColor( sf::Color::Transparent );
        m_Border.setOutlineThickness( 2 );
        m_Border.setOutlineColor( sf::Color(0,0,255,150) );
        m_Border.getOutlineColor();
    }
    
    virtual ~Drawable()
    {}
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> renderTarget ) = 0;
    
    virtual void SetPosition( const ScreenPosition& position = {0,0} )
    {
        m_Bounds.SetPosition( position );
        
        m_Border.setPosition( static_cast<float>(position.X), static_cast<float>(position.Y) );
    }
    
    virtual const ScreenPosition GetPosition() const
    {
        return m_Bounds.GetPosition();
    }
    
    virtual void SetSize( const ScreenSize& size = {0,0} )
    {
        m_Bounds.SetSize( size );
        
        m_Border.setSize( {static_cast<float>(size.Width), static_cast<float>(size.Height)} );
    }
    
    virtual const ScreenSize GetSize() const
    {
        return m_Bounds.GetSize();
    }
    
    virtual void SetRectangle( const ScreenRectangle& rect = { {0,0}, {0,0} } )
    {
        m_Bounds = rect;
        
        m_Border.setPosition( static_cast<float>(rect.Left), static_cast<float>(rect.Top) );
        m_Border.setSize( {static_cast<float>(rect.Width), static_cast<float>(rect.Height)} );
    }
    
    virtual const ScreenRectangle GetRectangle() const
    {
        return m_Bounds;
    }
    
    virtual void SetVisible( bool visible = false )
    {
        m_Visible = visible;
    }
    
    virtual bool IsVisible() const
    {
        return m_Visible;
    }
    
    sf::RectangleShape m_Border = {};
    
private:
    ScreenRectangle m_Bounds = { {0,0}, {0,0} };
    bool m_Visible = true;
};

} // namespace Interface

#endif // DRAWABLE_HPP_INCLUDED_1618
