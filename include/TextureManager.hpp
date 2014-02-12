#ifndef TEXTUREMANAGER_HPP_INCLUDED_1615
#define TEXTUREMANAGER_HPP_INCLUDED_1615

#include "Logger.hpp"
#include "Utils/Utils.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <map>

namespace Interface
{
using Utils::Logger;

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

} // namespace Interface

#endif // TEXTUREMANAGER_HPP_INCLUDED_1615
