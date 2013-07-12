#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Logger.hpp"

namespace WhoreMasterRenewal
{

struct ScreenPosition
{
    ScreenPosition( int x, int y ) :
        X( x ),
        Y( y )
    {}
    
    int X = 0;
    int Y = 0;
};

struct ScreenSize
{
    ScreenSize( int width, int height ) :
        Width( width ),
        Height( height )
    {}
    
    int Width = 0;
    int Height = 0;
};

struct ScreenRectangle
{
    ScreenRectangle( ScreenPosition position, ScreenSize size ) :
        Position( position ),
        Size( size )
    {}
    
    ScreenPosition Position = {0,0};
    ScreenSize Size = {0,0};
};

class Drawable
{
public:
    virtual ~Drawable()
    {}
    
    virtual void Draw() = 0;
    
    void SetPosition( ScreenPosition position = {0,0} );
    ScreenPosition GetPosition();
    void SetSize( ScreenSize size = {0,0} );
    ScreenSize GetSize();
    void SetRectangle( ScreenRectangle = { {0,0}, {0,0} } );
    ScreenRectangle GetRectangle();
    bool IsVisible();
    void SetVisible( bool visible = false );
    
private:
    ScreenRectangle m_Rectangle = { {0,0}, {0,0} };
    bool m_Visible = true;
};

class InterfaceObject
{
public:
    int m_ID;
};

class InterfaceButton : Drawable
{
    
};

class InterfaceCheckBox : Drawable
{
    
};

class InterfaceEditBox : Drawable
{
};

class InterfaceImageItem : Drawable
{
};

class InterfaceWindow : Drawable
{
};

class InterfaceListBox : Drawable
{
};

class InterfaceScrollBar : Drawable
{
};

class InterfaceSlider : Drawable
{
};

class InterfaceTextItem : Drawable
{
};



class WindowManager
{
public:
    WindowManager() :
        WindowManager( std::make_shared<sf::RenderWindow>() )
    {}
    
    WindowManager( std::shared_ptr<sf::RenderWindow> renderWindow )
        : m_RenderWindow( renderWindow )
    {
        Logger() << "WindowManager: created...\n";
    }
    
    ~WindowManager()
    {
        if( m_RenderWindow )
            m_RenderWindow = nullptr;
    }
    
    void Initialise()
    {
        Logger() << "WindowManager: Initialise...\n";
        
        sf::VideoMode mode = sf::VideoMode::getDesktopMode();
        // TODO: read window title from config
        m_RenderWindow->create( mode, "WindowTitle" );
    }
    
    void Run()
    {
        if( !m_RenderWindow->isOpen() )
            this->Initialise();
        
        while( m_RenderWindow->isOpen() )
        {
            
            m_RenderWindow->clear();
            m_RenderWindow->display();
            
            sf::Event event;
            while( m_RenderWindow->pollEvent( event ) )
            {
                
                switch( event.type )
                {
                case sf::Event::Closed:
                    // TODO: Closing event
                    m_RenderWindow->close();
                    break;
                    
                case sf::Event::GainedFocus:
                    // TODO: GotFocus event
                    break;
                
                case sf::Event::LostFocus:
                    // TODO: LostFocus event
                    break;
                    
                case sf::Event::JoystickButtonPressed:
                case sf::Event::JoystickButtonReleased:
                case sf::Event::JoystickConnected:
                case sf::Event::JoystickDisconnected:
                case sf::Event::JoystickMoved:
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                case sf::Event::MouseEntered:
                case sf::Event::MouseLeft:
                case sf::Event::MouseMoved:
                case sf::Event::MouseWheelMoved:
                case sf::Event::Resized:
                case sf::Event::TextEntered:
                    break;
                    
                default: // We ignore the rest of events
                    break;
                }
                2013-07-12-21.55
                2013-07-12-21.55.32
            }
            
        }
        
        this->Shutdown();
    }
    
    void Shutdown()
    {
        Logger() << "WindowManager: Shutdown...\n";
    }
    
private:
    std::shared_ptr<sf::RenderWindow> m_RenderWindow = nullptr;
};


} // namespace WhoreMasterRenewal


using WhoreMasterRenewal::WindowManager;
using WhoreMasterRenewal::Logger;

int main( int /*argc*/, char** /*arga*/ )
{
    Logger() << "Entered main()\n";
    
    try
    {
        WindowManager wm;
        wm.Run();
    }
    catch( std::exception& ex )
    {
        Logger() << "Exception caught:\n" << ex.what() << "\n";
    }
    catch( ... )
    {
        Logger() << "Unknown exception caught...\n";
    }
    
    Logger() << "Finished main()\n";
    return 0;
}
