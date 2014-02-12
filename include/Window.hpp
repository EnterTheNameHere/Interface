#ifndef WINDOW_HPP_INCLUDED_1609
#define WINDOW_HPP_INCLUDED_1609

#include "ScreenRectangle.hpp"
#include "Clickable.hpp"
#include "Drawable.hpp"
#include "UIObject.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

namespace Interface
{
using WhoreMasterRenewal::Logger;

class Window : public UIObject, public Drawable, public Clickable
{
public:
    Window( std::string name ) : UIObject(), Drawable(), Clickable(),
        m_Name {name}
    {
        Logger() << "Window created...\n";
    }
    
    virtual ~Window() override
    {
        Logger() << "Window destroyed...\n";
    }
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> renderTarget ) override
    {
        if( auto rt = renderTarget.lock() )
        {
            if( m_NeedToRecreateBackground )
                RecreateBackground( rt );
            rt->draw( m_Background );
            
            for( std::shared_ptr<UIObject> child : m_Children )
            {
                if( std::shared_ptr<Drawable> test = std::dynamic_pointer_cast<Drawable>( child ) )
                {
                    test->Draw( rt );
                }
            }
        }
    }
    
    virtual void SetBackgroundColor( sf::Color color )
    {
        m_BackgroundColor = color;
    }
    
    virtual const sf::Color& GetBackgroundColor() const
    {
        return m_BackgroundColor;
    }
    
    virtual void Clicked( ClickedEvent& event )
    {
        // Todo: change to more sensible code
        static std::stringstream ss;
        ss.str("");
        ss << ( event.Button == sf::Mouse::Left ? "Left " : "" );
        ss << ( event.Button == sf::Mouse::Middle ? "Middle " : "" );
        ss << ( event.Button == sf::Mouse::Right ? "Right" : "" );
        ss << ( event.Button == sf::Mouse::XButton1 ? "XButton1" : "" );
        ss << ( event.Button == sf::Mouse::XButton2 ? "XButton2" : "" );
        
        Logger() << Utils::formatString( "Window::Clicked( [{%};{%}] {%} )",
                                            event.X,
                                            event.Y,
                                            ss.str() ) << std::endl;
        
        for( auto child : m_Children )
        {
            if( std::shared_ptr<Clickable> clickedUIObject = std::dynamic_pointer_cast<Clickable>(child) )
            {
                Logger() << Utils::formatString( "Bounds: {%},{%},{%},{%}\n",
                                                  clickedUIObject->GetRectangle().Left,
                                                  clickedUIObject->GetRectangle().Top,
                                                  clickedUIObject->GetRectangle().Right,
                                                  clickedUIObject->GetRectangle().Bottom );
                // Check mouse is over the 
                if( clickedUIObject->GetRectangle().Contains( event.X, event.Y ) )
                {
                    if( clickedUIObject->OnClicked )
                    {
                        clickedUIObject->OnClicked( clickedUIObject.get(), event );
                    }
                    else
                    {
                        Logger() << "No clicked function assigned" << std::endl;
                    }
                }
            }
        }
    }
    
    // TODO: replace with image?
    sf::Sprite m_Background = {};
    sf::Texture m_BackgroundTexture = {};
    bool m_NeedToRecreateBackground = true;
    std::vector<std::shared_ptr<UIObject>> m_Children = {};
    std::string m_Name;
    
private:
    virtual void RecreateBackground( std::shared_ptr<sf::RenderTarget>& renderTarget )
    {
        sf::Image temp;
        temp.create( renderTarget->getSize().x, renderTarget->getSize().y, m_BackgroundColor );
        
        m_BackgroundTexture.loadFromImage( temp );
        m_Background.setTexture( m_BackgroundTexture );
    }
    
    sf::Color m_BackgroundColor = {0,0,0,255};
};

} // namespace Interface

#endif // WINDOW_HPP_INCLUDED_1609
