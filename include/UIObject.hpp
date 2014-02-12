#ifndef UIOBJECT_HPP_INCLUDED_1625
#define UIOBJECT_HPP_INCLUDED_1625

#include "ScreenRectangle.hpp"

namespace Interface
{

class UIObject
{
public:
    virtual ~UIObject() = default;
    
    //virtual void SetPosition( const ScreenPosition& position ) = 0;
    //virtual const ScreenPosition& GetPosition() const = 0;
    //virtual void SetPosition( const ScreenSize& size ) = 0;
    //virtual const ScreenSize& GetSize() const = 0;
    
    int m_ID = 0;
    //ScreenRectangle m_Bounds = {0,0,0,0};
};

} // namespace Interface

#endif // UIOBJECT_HPP_INCLUDED_1625
