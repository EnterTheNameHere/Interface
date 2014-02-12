#ifndef WINDOWMANAGER_HPP_INCLUDED_1628
#define WINDOWMANAGER_HPP_INCLUDED_1628

#include "TextureManager.hpp"
#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Image.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

namespace Interface
{
using WhoreMasterRenewal::Logger;


class WindowManager
{
public:
    WindowManager() :
        WindowManager( std::make_shared<sf::RenderWindow>() )
    {}
    
    WindowManager( std::shared_ptr<sf::RenderWindow> renderWindow )
        : m_RenderWindow( renderWindow ),
          m_TextureManager( std::make_shared<TextureManager>() ),
          m_Font( std::make_shared<sf::Font>() )
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
        
        // TODO: report error
        m_Font->loadFromFile("Resources/Fonts/DejaVuSerif.ttf");
        
        
        
        // Global widgets
        std::string mousePositionPattern = "Mouse position:\nX: {%} Y: {%}\n{%}";
        auto labelMousePosition = std::make_shared<Label>( m_Font );
        labelMousePosition->SetText( mousePositionPattern );
        labelMousePosition->SetPosition( {5,5} );
        labelMousePosition->SetFontSize( 12 );
        labelMousePosition->SetFontColor( sf::Color::Black );      
        
        std::string windowName = "Image test";
        std::shared_ptr<Window> window = std::make_shared<Window>( windowName );
        
        {
            window->m_Children.push_back( labelMousePosition );
            
            auto image1 = std::make_shared<Image>( m_TextureManager);
            image1->LoadImage( "Resources/Images/Sizes.jpeg" );
            
            auto image2 = std::make_shared<Image>(m_TextureManager);
            image2->LoadImage( "Resources/Images/200x100.png" );
            
            auto image3 = std::make_shared<Image>(m_TextureManager);
            image3->LoadImage( "Resources/Images/300x50.bmp" );
            
            auto image4 = std::make_shared<Image>(m_TextureManager);
            image4->LoadImage( "Resources/Images/15x15.gif" );
            
            window->m_Children.push_back( image1 );
            window->m_Children.push_back( image2 );
            window->m_Children.push_back( image3 );
            window->m_Children.push_back( image4 );
            
            
            
            auto multipleImage1 = std::make_shared<Image>(m_TextureManager);
            multipleImage1->LoadImage( "Resources/Images/multiple.tga" );
            multipleImage1->SetTextureRectangle( { {0,0},{200,300} } );
            multipleImage1->SetPosition( {0,300} );
            
            auto multipleImage2 = std::make_shared<Image>(m_TextureManager);
            multipleImage2->LoadImage( "Resources/Images/multiple.tga" );
            multipleImage2->SetTextureRectangle( { {253,28},{151,61} } );
            multipleImage2->SetPosition( {201,300} );
            
            auto multipleImage3 = std::make_shared<Image>(m_TextureManager);
            multipleImage3->LoadImage( "Resources/Images/multiple.tga" );
            multipleImage3->SetTextureRectangle( { {200,118},{164,182} } );
            multipleImage3->SetPosition( {353,300} );
            
            auto multipleImage4 = std::make_shared<Image>(m_TextureManager);
            multipleImage4->LoadImage( "Resources/Images/multiple.tga" );
            multipleImage4->SetTextureRectangle( { {451,0},{249,233} } );
            multipleImage4->SetPosition( {518,300} );
            
            auto multipleImage5 = std::make_shared<Image>(m_TextureManager);
            multipleImage5->LoadImage( "Resources/Images/multiple.tga" );
            multipleImage5->SetTextureRectangle( { {364,233},{336,67} } );
            multipleImage5->SetPosition( {768,300} );
            
            window->m_Children.push_back( multipleImage1 );
            window->m_Children.push_back( multipleImage2 );
            window->m_Children.push_back( multipleImage3 );
            window->m_Children.push_back( multipleImage4 );
            window->m_Children.push_back( multipleImage5 );
            
            
            auto borders = std::make_shared<Image>(m_TextureManager);
            borders->SetPosition( {800, 500} );
            borders->LoadImage( "Resources/Images/Borders.png" );
            
            window->m_Children.push_back( borders );
        }
        
        m_Windows.insert( {windowName,window} );
        
        windowName = "Button test";
        window = std::make_shared<Window>( windowName );
        window->SetBackgroundColor( sf::Color::White );
        window->m_Children.push_back( labelMousePosition );
        
        {
            auto button1 = std::make_shared<Button>(m_TextureManager, m_Font);
            button1->LoadImage( "Resources/Images/Button.png" );
            button1->SetText( "Button" );
            button1->m_Text.SetFontColor( sf::Color::Blue );
            button1->SetPosition( {200,50} );
            
            window->m_Children.push_back( std::dynamic_pointer_cast<UIObject>(button1) );
        }
        
        m_Windows.insert( {windowName,window} );
        
        windowName = "Label size test";
        window = std::make_shared<Window>( windowName );
        window->SetBackgroundColor( sf::Color::White );
        window->m_Children.push_back( labelMousePosition );
        
        {
            int screenX = 150, currentScreenX = 20, startScreenX = 20;
            int currentScreenY = 0, startScreenY = 50;
            int fontSize = 12;
            sf::Color color = sf::Color::Black;
            
            auto getScreenX = [&currentScreenX,screenX,startScreenX,&fontSize,&currentScreenY,this]()
            {
                static auto currentFontSize = 0;
                if( currentFontSize != fontSize )
                {
                    currentFontSize = fontSize;
                    currentScreenX = startScreenX;
                }
                
                auto returnValue = currentScreenX;
                
                if( fontSize < 25 )
                    currentScreenX += screenX;
                else if( fontSize < 72 )
                    currentScreenX += screenX*2;
                else
                    currentScreenX += screenX*4;
                
                
                if( currentScreenX > 1100 )
                {
                    currentScreenY += (m_Font->getLineSpacing( fontSize )+10);
                    currentScreenX = startScreenX;
                }
                
                
                return returnValue;
            };
            
            auto getScreenY = [&currentScreenY,startScreenY,&fontSize]()
            {
                static auto currentFontSize = 0;
                
                if( currentFontSize == 0 )
                    currentScreenY = startScreenY;
                
                if( currentFontSize != fontSize )
                {
                    currentFontSize = fontSize;
                }
                
                return currentScreenY;
            };
            
            std::wstring examplePattern = L"{%}|Mlý(x⁹₉ₜ)˛";
            
            auto label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 14;
            color = sf::Color::Red;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 16;
            color = sf::Color::Green;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 20;
            color = sf::Color::Cyan;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 25;
            color = sf::Color( 100, 100, 10, 255 );
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 30;
            color = sf::Color( 200, 200, 100 );;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 40;
            color = sf::Color( 150, 250, 200 );;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            
            
            fontSize = 72;
            color = sf::Color( 200, 100, 200 );;
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
            
            label = std::make_shared<Label>( Utils::formatString( examplePattern, fontSize ), m_Font, fontSize, sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined );
            label->SetPosition( {getScreenX(),getScreenY()} );
            label->SetFontColor( color );
            window->m_Children.push_back( label );
        }
        
        m_Windows.insert( {windowName,window} );
        
        windowName = "Main menu";
        window = std::make_shared<Window>( windowName );
        window->SetBackgroundColor( sf::Color::White );
        window->m_Children.push_back( labelMousePosition );
        
        {
            int screenX = 30, screenY = 30, buttonHeight = 15;
            int currentY = screenY;
            for( std::pair<std::string, std::shared_ptr<Window> > entry : m_Windows )
            {
                std::shared_ptr<Button> button = std::make_shared<Button>( m_TextureManager, m_Font );
                button->SetText( sf::String(entry.first) );
                button->m_Text.SetFontColor( sf::Color::Black );
                button->SetPosition( {screenX, currentY+=(buttonHeight+10)} );
                
                window->m_Children.push_back( std::dynamic_pointer_cast<UIObject>(button) );
            }
        }
        
        m_Windows.insert( {windowName,window} );
        
        ShowWindow( "Main menu" );
        
        bool mouseLeftButtonPressed = false;
        bool mouseRightButtonPressed = false;
        bool mouseMiddleButtonPressed = false;
        
        while( m_RenderWindow->isOpen() )
        {
            
            m_RenderWindow->clear();
            
            if( m_CurrentWindow )
                m_CurrentWindow->Draw( m_RenderWindow );
            else
            {
                static sf::Text noWindow( "Error:\nWindow not found or not set...", *m_Font.get() );
                m_RenderWindow->draw( noWindow );
            }
            
            m_RenderWindow->display();
            
            auto getPressedButtonsInString = [&mouseLeftButtonPressed,
                                              &mouseMiddleButtonPressed,
                                              &mouseRightButtonPressed]()
            {
                static std::stringstream ss;
                ss.str("");
                ss << ( mouseLeftButtonPressed ? "LEFT " : "" ) <<
                      ( mouseMiddleButtonPressed ? "MIDDLE " : "" ) <<
                      ( mouseRightButtonPressed ? "RIGHT" : "" );
                
                //std::cout << std::boolalpha << mouseLeftButtonPressed << "\n";
                
                return ss.str();
            };
            
            sf::Event event;
            while( m_RenderWindow->pollEvent( event ) )
            {
                switch( event.type )
                {
                case sf::Event::Resized:
                    {
                        sf::View visibleArea( sf::FloatRect( 0.0,
                                                             0.0,
                                                             event.size.width,
                                                             event.size.height ) );
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
                    
                case sf::Event::MouseButtonPressed:
                    //Logger() << "Button pressed\n";
                    if( event.mouseButton.button == sf::Mouse::Left )
                        mouseLeftButtonPressed = true;
                    if( event.mouseButton.button == sf::Mouse::Right )
                        mouseRightButtonPressed = true;
                    if( event.mouseButton.button == sf::Mouse::Middle )
                        mouseMiddleButtonPressed = true;
                    
                    labelMousePosition->SetText( Utils::formatString( mousePositionPattern,
                                                                      event.mouseButton.x,
                                                                      event.mouseButton.y,
                                                                      getPressedButtonsInString() ));
                    break;
                    
                case sf::Event::MouseButtonReleased:
                    //Logger() << "Button released\n";
                    if( event.mouseButton.button == sf::Mouse::Left )
                        mouseLeftButtonPressed = false;
                    if( event.mouseButton.button == sf::Mouse::Right )
                        mouseRightButtonPressed = false;
                    if( event.mouseButton.button == sf::Mouse::Middle )
                        mouseMiddleButtonPressed = false;
                    
                    labelMousePosition->SetText( Utils::formatString( mousePositionPattern,
                                                                      event.mouseButton.x,
                                                                      event.mouseButton.y,
                                                                      getPressedButtonsInString() ));
                    // TODO: measure time between two clicks
                    if( m_CurrentWindow )
                    {
                        ClickedEvent ev( event.mouseButton.x, event.mouseButton.y, event.mouseButton.button );
                        m_CurrentWindow->Clicked( ev );
                    }
                    break;
                    
                case sf::Event::MouseMoved:
                    labelMousePosition->SetText( Utils::formatString( mousePositionPattern,
                                                                      event.mouseMove.x,
                                                                      event.mouseMove.y,
                                                                      getPressedButtonsInString() ));
                    break;
                    
                case sf::Event::MouseWheelMoved:
                case sf::Event::MouseEntered:
                case sf::Event::MouseLeft:
                case sf::Event::JoystickButtonPressed:
                case sf::Event::JoystickButtonReleased:
                case sf::Event::JoystickConnected:
                case sf::Event::JoystickDisconnected:
                case sf::Event::JoystickMoved:
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
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
    
    void ShowWindow( const std::string& name )
    {
        Logger() << Utils::formatString( "WindowManager: Request to show Window named \"{%}\".\n",
                                         name );
        
        if( !m_Windows.count( name ) )
            m_CurrentWindow.reset();
        else
            m_CurrentWindow = m_Windows.at( name );
    }
    
private:
    std::shared_ptr<sf::RenderWindow> m_RenderWindow;
    std::shared_ptr<TextureManager> m_TextureManager;
    std::shared_ptr<sf::Font> m_Font;
    std::map<std::string, std::shared_ptr<Window> > m_Windows = {};
    std::shared_ptr<Window> m_CurrentWindow = nullptr;
};

} // namespace Interface

#endif // WINDOWMANAGER_HPP_INCLUDED_1628
