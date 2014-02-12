#ifndef BUTTON_HPP_INCLUDED_1620
#define BUTTON_HPP_INCLUDED_1620

#include "Image.hpp"
#include "Label.hpp"

namespace Interface
{
using Utils::Logger;

class Button : public UIObject, public Clickable
{
public:
    Button( std::shared_ptr<TextureManager> manager, std::shared_ptr<sf::Font> font ) : UIObject(), Clickable(),
        m_Background( Image(manager) ),
        m_Text( font )
    {
        RecalculateBounds();
    }
    
    virtual ~Button()
    {
    }
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> rt ) override
    {
        m_Background.Draw( rt );
        m_Text.Draw( rt );
    }
    
    virtual void OnClicked( ClickedEvent& /*event*/ )
    {
        Logger() << Utils::formatString( "Button: \"{%}\" clicked.\n", m_Text.GetText().toAnsiString() );
    }
    
    virtual void LoadImage( const std::string& path )
    {
        m_Background.LoadImage( path );
        
        RecalculateBounds();
    }
    
    virtual void SetText( const sf::String& text )
    {
        m_Text.SetText( text );
        
        RecalculateBounds();
    }
    
    virtual const sf::String& GetText() const
    {
        return m_Text.GetText();
    }
    
    virtual void SetPosition( const ScreenPosition& position ) override
    {
        m_Background.SetPosition( position );
        // TODO: allow user to set the padding
        ScreenPosition textPos = position;
        
        
        m_Text.SetPosition( textPos );
        
        RecalculateBounds();
    }
    
    virtual void RecalculateBounds()
    {
        Logger() << "RecalculateBounds\n";
        Drawable::SetPosition( m_Background.GetPosition() );
        ScreenSize size = { std::max( m_Background.GetSize().Width, m_Text.GetSize().Width ),
                            std::max( m_Background.GetSize().Height, m_Text.GetSize().Height ) };
        Drawable::SetSize( size );
    }
    
    Image m_Background;
    Label m_Text;
};

} // namespace Interface

#endif // BUTTON_HPP_INCLUDED_1620
