#ifndef LABEL_HPP_INCLUDED_1620
#define LABEL_HPP_INCLUDED_1620

namespace Interface
{
using Utils::Logger;

class Label : public UIObject, public Drawable
{
public:    
    Label( std::shared_ptr<sf::Font> font ) : Label( "", font )
    {
    }
    
    Label( sf::String text,
           std::shared_ptr<sf::Font> font,
           unsigned int fontSize = 12,
           unsigned int fontStyle = sf::Text::Regular ) : UIObject(),
                                                          Drawable(),
        m_Text( text, *font, fontSize ),
        m_Font( font )
    {
        m_Text.setStyle( fontStyle );
        CalculateSize();
    }
    
    virtual ~Label()
    {
    }
    
    virtual void Draw( std::weak_ptr<sf::RenderTarget> rt ) override
    {
        if( auto renderTarget = rt.lock() )
        {
            renderTarget->draw( m_Text );
            renderTarget->draw( m_Border );
        }
    }
    
    virtual void SetText( const sf::String& text )
    {
        m_Text.setString( text );
        CalculateSize();
    }
    
    virtual const sf::String& GetText() const
    {
        return m_Text.getString();
    }
    
    virtual void SetFontSize( unsigned int size )
    {
        m_Text.setCharacterSize( size );
        CalculateSize();
    }
    
    virtual unsigned int GetFontSize() const
    {
        return m_Text.getCharacterSize();
    }
    
    virtual void SetFontStyle( unsigned int fontStyle )
    {
        m_Text.setStyle( fontStyle );
        CalculateSize();
    }
    
    virtual unsigned int GetFontStyle() const
    {
        return m_Text.getStyle();
    }
    
    virtual void SetFontColor( const sf::Color& color )
    {
        m_Text.setColor( color );
    }
    
    virtual const sf::Color& GetFontColor() const
    {
        return m_Text.getColor();
    }
    
    virtual void SetPosition( const ScreenPosition& position ) override
    {
        m_Text.setPosition( static_cast<float>(position.X), static_cast<float>(position.Y) );
        CalculateSize();
    }
    /*
    virtual const ScreenPosition& GetPosition() const override
    {
        return Drawable::GetPosition();
    }
    */
    void updateGeometry() const
    {
        sf::VertexArray m_vertices;
        sf::FloatRect m_bounds;
        const sf::Font* m_font = m_Font.get();
        sf::String m_string = m_Text.getString();
        sf::Uint32 m_style = m_Text.getStyle();
        unsigned int m_characterSize = m_Text.getCharacterSize();
        sf::Color m_color = m_Text.getColor();
        
        // Clear the previous geometry
        m_vertices.clear();
        m_bounds = sf::FloatRect();

        // No font: nothing to draw
        if (!m_font)
            return;

        // No text: nothing to draw
        if (m_string.isEmpty())
            return;

        // Compute values related to the text style
        bool  bold               = (m_style & sf::Text::Bold) != 0;
        bool  underlined         = (m_style & sf::Text::Underlined) != 0;
        float italic             = (m_style & sf::Text::Italic) ? 0.208f : 0.f; // 12 degrees
        float underlineOffset    = m_characterSize * 0.1f;
        float underlineThickness = m_characterSize * (bold ? 0.1f : 0.07f);
        
        std::stringstream ss;
        ss << (bold ? "BOLD " : "") <<
            ( (m_style&sf::Text::Italic) ? "ITALIC " : "") <<
            (underlined ? "UNDERLINED " : "");
        if( ss.str() != "" )
            ss << '\n';
        
        ss << Utils::formatString(
            "italic: {%} underlineOffset: {%} underlineThickness: {%}\n",
            italic,
            underlineOffset,
            underlineThickness );
        
        // Precompute the variables needed by the algorithm
        float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
        float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
        float x      = 0.f;
        float y      = static_cast<float>(m_characterSize);
        
        ss << Utils::formatString(
            "hspace: {%} vspace: {%} x: {%} y: {%}\n",
            hspace,
            vspace,
            x,
            y );
        
        // Create one quad for each character
        float minY = static_cast<float>(m_characterSize);
        sf::Uint32 prevChar = 0;
        for (std::size_t i = 0; i < m_string.getSize(); ++i)
        {
            sf::Uint32 curChar = m_string[i];

            // Apply the kerning offset
            x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
            prevChar = curChar;

            // If we're using the underlined style and there's a new line, draw a line
            if (underlined && (curChar == L'\n'))
            {
                float top = y + underlineOffset;
                float bottom = top + underlineThickness;
                
                ss << Utils::formatString(
                    "underlined&newline... top: {%} bottom: {%}\n",
                    top,
                    bottom );
                
                m_vertices.append(sf::Vertex(sf::Vector2f(0, top),    m_color, sf::Vector2f(1, 1)));
                m_vertices.append(sf::Vertex(sf::Vector2f(x, top),    m_color, sf::Vector2f(1, 1)));
                m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
                m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
            }

            // Handle special characters
            switch (curChar)
            {
                case L' ' :
                    x += hspace;
                    continue;

                case L'\t' :
                    x += hspace * 4;
                    continue;

                case L'\n' :
                    if (x > m_bounds.width)
                        m_bounds.width = x;
                    y += vspace;
                    x = 0;
                    continue;

                case L'\v' :
                    y += vspace * 4;
                    continue;
                
                default:
                    break;
            }

            // Extract the current glyph's description
            const sf::Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

            int left   = glyph.bounds.left;
            int top    = glyph.bounds.top;
            int right  = glyph.bounds.left + glyph.bounds.width;
            int bottom = glyph.bounds.top  + glyph.bounds.height;

            float u1 = static_cast<float>(glyph.textureRect.left);
            float v1 = static_cast<float>(glyph.textureRect.top);
            float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
            float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

            // Add a quad for the current character
            m_vertices.append(sf::Vertex(sf::Vector2f(x + left  - italic * top,    y + top),    m_color, sf::Vector2f(u1, v1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x + right - italic * top,    y + top),    m_color, sf::Vector2f(u2, v1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x + right - italic * bottom, y + bottom), m_color, sf::Vector2f(u2, v2)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x + left  - italic * bottom, y + bottom), m_color, sf::Vector2f(u1, v2)));

            // Advance to the next character
            x += glyph.advance;

            // Update the minimum Y coordinate
            if (y + top < minY)
                minY = y + top;
        }

        // If we're using the underlined style, add the last line
        if (underlined)
        {
            float top = y + underlineOffset;
            float bottom = top + underlineThickness;

            m_vertices.append(sf::Vertex(sf::Vector2f(0, top),    m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, top),    m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
        }

        // Update the bounding rectangle
        m_bounds.left = 0;
        m_bounds.top = minY;
        if (x > m_bounds.width)
            m_bounds.width = x;
        m_bounds.height = y - minY;
        
        ss << Utils::formatString(
            "bounds: {%}, {%}, {%}, {%}\n",
            m_bounds.top,
            m_bounds.left,
            m_bounds.width,
            m_bounds.height );
        ss << '\n';
        
        //Logger() << ss.str();
    }
    
    /*sf::Vector2f*/ void CalculateSize()
    {
        sf::String text = m_Text.getString();
        
        int height = 0;
        int totalHeight = 0;
        int width = 0;
        int totalWidth = 0;
        int spacing = m_Font->getLineSpacing( GetFontSize() );
        int totalSpacing = 0;
        
        for( auto ch : text )
        {
            if( ch == '\n' )
            {
                //std::cout << "newline found\n";
                totalHeight += height;
                height = 0;
                if( totalWidth < width )
                    totalWidth = width;
                width = 0;
                totalSpacing += spacing;
            }
            
            //std::cout << "char: " << ch << " height: " << m_Font->getGlyph( ch, GetFontSize(), m_Text.getStyle() & sf::Text::Bold ).bounds.height << "\n";
            if( height < m_Font->getGlyph( ch, GetFontSize(), m_Text.getStyle() & sf::Text::Bold ).bounds.height )
                height = m_Font->getGlyph( ch, GetFontSize(), m_Text.getStyle() & sf::Text::Bold ).bounds.height;
            width += m_Font->getGlyph( ch, GetFontSize(), m_Text.getStyle() & sf::Text::Bold ).advance;
        }
        totalHeight += height;
        if( totalWidth < width )
            totalWidth = width;
        totalSpacing += spacing;
        
        sf::FloatRect bounds = m_Text.getGlobalBounds();
        
        /*Logger() << Utils::formatString( "\"{%}\"\n", std::string(text) )*/ /*<<
            Utils::formatString("width: {%} bounds: {%}\nheight: {%} bounds: {%} spacing: {%}\n",
                totalWidth,
                bounds.width,
                totalHeight,
                bounds.height,
                totalSpacing )*/;
        updateGeometry();
        
        
        
        
        
        sf::Vector2f size( { static_cast<float>(totalWidth), static_cast<float>( std::max(totalSpacing,totalHeight) ) } );
        m_Border.setSize( size );
        m_Border.setPosition( bounds.left, bounds.top );
        m_Border.setOrigin( m_Text.getOrigin() );
        
        m_NeedRecalculation = false;
        
        Drawable::SetSize( {totalWidth, std::max( totalSpacing, totalHeight )} );
        
        //return { static_cast<float>(totalWidth), static_cast<float>( std::max(totalSpacing,totalHeight) ) };
    }
    
    sf::Text m_Text = {};
    std::shared_ptr<sf::Font> m_Font;
    bool m_NeedRecalculation = {true};
};

} // namespace Interface

#endif // LABEL_HPP_INCLUDED_1620
