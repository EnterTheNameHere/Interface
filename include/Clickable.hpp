#ifndef CLICKABLE_HPP_INCLUDED_1622
#define CLICKABLE_HPP_INCLUDED_1622

#include "Events.hpp"
#include "Drawable.hpp"

#include <functional>

namespace Interface
{

class Clickable : public Drawable
{
public:
    typedef std::function<void(Clickable*,ClickedEvent&)> ClickedEventHandler;
    
    Clickable() : Drawable()
    {}
    virtual ~Clickable() = default;
    
    ClickedEventHandler OnClicked = nullptr;
};

} // namespace Interface

#endif // CLICKABLE_HPP_INCLUDED_1622
