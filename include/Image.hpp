#ifndef IMAGE_HPP_INCLUDED_1619
#define IMAGE_HPP_INCLUDED_1619

#include "ScreenRectangle.hpp"

namespace Interface
{

class Image : public UIObject, public Drawable
{
public:
    Image( std::shared_ptr<TextureManager> manager ) : UIObject(), Drawable(),
        m_TextureManager( manager )
    {
    }
    
    virtual ~Image() override
    {
    }
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> renderTarget ) override
    {
        if( !m_Texture )
            return;
        
        if( auto rt = renderTarget.lock() )
        {
            rt->draw( m_Sprite );
            rt->draw( m_Border );
        }
    }
    
    void LoadImage( std::string path )
    {
        m_Texture = m_TextureManager->GetTexture( path );
        m_Sprite.setTexture( *m_Texture );
        
        sf::Vector2f position = m_Sprite.getPosition();
        sf::IntRect rect = m_Sprite.getTextureRect();
        
        Drawable::SetPosition( {static_cast<int>(position.x), static_cast<int>(position.y)} );
        Drawable::SetSize( {rect.width, rect.height} );
    }
    
    void SetTextureRectangle( TextureRectangle rect )
    {
        m_Sprite.setTextureRect(  { rect.Left,
                                    rect.Top,
                                    rect.Width,
                                    rect.Height } );
        
        SetSize( rect.GetSize() );
    }
    
    void SetPosition( const ScreenPosition& position ) override
    {
        Drawable::SetPosition( position );
        m_Sprite.setPosition( { static_cast<float>(position.X), static_cast<float>(position.Y) } );
    }
    
    std::shared_ptr<TextureManager> m_TextureManager;
    std::shared_ptr<sf::Texture> m_Texture = nullptr;
    sf::Sprite m_Sprite = {};
};

} // namespace Interface

#endif // IMAGE_HPP_INCLUDED_1619
