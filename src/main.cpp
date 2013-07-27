#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Utils/Utils.hpp"
#include "Logger.hpp"

namespace WhoreMasterRenewal
{

struct ScreenPosition
{
    ScreenPosition( int x, int y ) :
        X( x ),
        Y( y )
    {}
    
    ScreenPosition( const sf::Vector2f& pos ) :
        X( static_cast<int>( pos.x ) ),
        Y( static_cast<int>( pos.y ) )
    {}
    
    int X = 0;
    int Y = 0;
};
typedef ScreenPosition TexturePosition;

struct ScreenSize
{
    ScreenSize( int width, int height ) :
        Width( width ),
        Height( height )
    {}
    
    int Width = 0;
    int Height = 0;
};
typedef ScreenSize TextureSize;

struct ScreenRectangle
{
    ScreenRectangle( ScreenPosition position, ScreenSize size ) :
        Position( position ),
        Size( size )
    {}
    
    ScreenPosition Position = {0,0};
    ScreenSize Size = {0,0};
};
typedef ScreenRectangle TextureRectangle;

class Drawable
{
public:
    virtual ~Drawable()
    {}
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> renderTarget ) = 0;
    
    void SetPosition( const ScreenPosition& position = {0,0} )
    {
        m_Rectangle.Position = position;
    }
    
    const ScreenPosition& GetPosition() const
    {
        return ScreenPosition( m_Rectangle.Position );
    }
    
    void SetSize( const ScreenSize& size = {0,0} )
    {
        m_Rectangle.Size = size;
    }
    
    const ScreenSize& GetSize() const
    {
        return m_Rectangle.Size;
    }
    
    void SetRectangle( const ScreenRectangle& rect = { {0,0}, {0,0} } )
    {
        m_Rectangle = rect;
    }
    
    const ScreenRectangle& GetRectangle() const
    {
        return m_Rectangle;
    }
    
    void SetVisible( bool visible = false )
    {
        m_Visible = visible;
    }
    
    bool IsVisible() const
    {
        return m_Visible;
    }
    
private:
    ScreenRectangle m_Rectangle = { {0,0}, {0,0} };
    bool m_Visible = true;
};

class Object
{
public:
    int m_ID;
};

class Button : Drawable
{
    
};

class CheckBox : Drawable
{
    
};

class EditBox : Drawable
{
};

class TextureManager
{
public:
    TextureManager()
    {
    }
    
    ~TextureManager()
    {
    }
    
    TextureManager( const TextureManager& ) = delete;
    TextureManager& operator = ( const TextureManager& ) = delete;
    
    std::shared_ptr<sf::Image> LoadImage( std::string path )
    {
        // Check if image is loaded first
        if( m_Images.find( path ) != m_Images.end() )
        {
            return m_Images[path];
        }
        
        // Create new image entry, result is std::pair<iter,bool>
        auto result = m_Images.emplace( path, std::make_shared<sf::Image>() );
        if( !result.second ) // false if emplace failed
        {
            Logger() << Utils::formatString(
                            "TextureManager Error: cannot save {%} image to repository.\n", path );
        }
        auto image = (*result.first).second;
        
        if( !image->loadFromFile( path ) )
        {
            // TODO: Generate image not found here
            Logger() << Utils::formatString( "Loading of image \"{%}\" failed.\n", path );
        }
        else
        {
            Logger() << Utils::formatString( "TextureManager: \"{%}\" loaded.", path ) << "\n";
        }
        
        return image;
    }
    
    std::shared_ptr<sf::Texture> GetTexture( std::string path )
    {
        if( m_Textures.find( path ) != m_Textures.end() )
        {
            return m_Textures[path];
        }
        
        // Create new texture entry, result is std::pair<iter,bool>
        auto result = m_Textures.emplace( path, std::make_shared<sf::Texture>() );
        if( !result.second ) // false if emplace failed
        {
            Logger() << Utils::formatString(
                            "TextureManager Error: cannot save {%} texture to repository.\n", path );
        }
        auto texture = (*result.first).second; // iterator - std::pair<string, shared_ptr<Texture>>
        
        texture->loadFromImage( *(LoadImage(path)) );
        
        return texture;
    }
    
    std::map<std::string, std::shared_ptr<sf::Image>> m_Images = {};
    std::map<std::string, std::shared_ptr<sf::Texture>> m_Textures = {};
};

class Image : public Drawable
{
public:
    Image( const std::shared_ptr<TextureManager>& manager ) :
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
        }
    }
    
    void LoadImage( std::string path )
    {
        m_Texture = m_TextureManager->GetTexture( path );
        m_Sprite.setTexture( *m_Texture );
        
        Drawable::SetPosition( m_Sprite.getPosition() );
    }
    
    void SetTextureRectangle( TextureRectangle rect )
    {
        
    }
    
    std::shared_ptr<TextureManager> m_TextureManager;
    std::shared_ptr<sf::Texture> m_Texture = nullptr;
    sf::Sprite m_Sprite = {};
};

class Label : Drawable
{
};

class ListBox : Drawable
{
};

class ScrollBar : Drawable
{
};

class Slider : Drawable
{
};

class TextItem : Drawable
{
};

class Window : Drawable
{
public:
    Window()
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
            for( auto child : m_Children )
            {
                child->Draw( rt );
            }
        }
    }
    
    std::vector<std::shared_ptr<Drawable>> m_Children = {};
};



class WindowManager
{
public:
    WindowManager() :
        WindowManager( std::make_shared<sf::RenderWindow>() )
    {}
    
    WindowManager( std::shared_ptr<sf::RenderWindow> renderWindow )
        : m_RenderWindow( renderWindow ),
          m_TextureManager( std::make_shared<TextureManager>() )
    {
        Logger() << "WindowManager: created...\n";
    }
    
    ~WindowManager()
    {
        if( m_RenderWindow )
            m_RenderWindow = nullptr;
        
        Logger() << "WindowManager: finished...\n";
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
        m_RenderWindow->setFramerateLimit( 60 );
        
        std::shared_ptr<Window> window = std::make_shared<Window>();
        
        
        auto image1 = std::make_shared<Image>( m_TextureManager);
        image1->LoadImage( "Resources/Images/Sizes.jpeg" );
        
        auto image2 = std::make_shared<Image>(m_TextureManager);
        image2->LoadImage( "Resources/Images/200x100.png" );
        
        auto image3 = std::make_shared<Image>(m_TextureManager);
        image3->LoadImage( "Resources/Images/300x50.bmp" );
        
        auto image4 = std::make_shared<Image>(m_TextureManager);
        image4->LoadImage( "Resources/Images/15x15.gif" );
        
        auto image5 = std::make_shared<Image>(m_TextureManager);
        image5->LoadImage( "Resources/Images/multiple.tga" );
        
        auto image6 = std::make_shared<Image>(m_TextureManager);
        image6->LoadImage( "Resources/Images/Button.png" );
        image6->m_Sprite.setColor( {255,0,255} );
        
        window->m_Children.emplace_back( image1 );
        window->m_Children.emplace_back( image2 );
        window->m_Children.emplace_back( image3 );
        window->m_Children.emplace_back( image4 );
        window->m_Children.emplace_back( image5 );
        window->m_Children.emplace_back( image6 );
        
        while( m_RenderWindow->isOpen() )
        {
            
            m_RenderWindow->clear();
            
            window->Draw( m_RenderWindow );
            
            m_RenderWindow->display();
            
            sf::Event event;
            while( m_RenderWindow->pollEvent( event ) )
            {
                
                switch( event.type )
                {
                case sf::Event::Resized:
                    {
                        sf::View visibleArea( sf::FloatRect( 0.0, 0.0, event.size.width, event.size.height ) );
                        m_RenderWindow->setView( visibleArea );
                    }
                    break;
                    
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
                case sf::Event::TextEntered:
                    break;
                    
                default: // We ignore the rest of events
                    break;
                }
            }
            
        }
        
        this->Shutdown();
    }
    
    void Shutdown()
    {
        Logger() << "WindowManager: Shutdown...\n";
    }
    
private:
    std::shared_ptr<sf::RenderWindow> m_RenderWindow;
    std::shared_ptr<TextureManager> m_TextureManager;
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
