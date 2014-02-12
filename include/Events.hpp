#ifndef EVENTS_HPP_INCLUDED_1623
#define EVENTS_HPP_INCLUDED_1623

namespace Interface
{

struct ClickedEvent
{
public:
    ClickedEvent( int x, int y, sf::Mouse::Button button ) :
        X(x), Y(y), Button(button)
    {}
    
    int X;
    int Y;
    sf::Mouse::Button Button;
};

} // namespace Interface

#endif // EVENTS_HPP_INCLUDED_1623
