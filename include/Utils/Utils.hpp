#ifndef UTILS_HPP_INCLUDED_2044
#define UTILS_HPP_INCLUDED_2044

#include <sstream>
#include <string>

namespace Utils
{

std::stringstream& imp_formatString( std::stringstream& ss, const char* format );
std::stringstream& imp_formatString( std::stringstream& ss, const char* format )
{
    ss << format;
    
    return ss;
}

template<class T, class... VTtypes>
std::stringstream& imp_formatString( std::stringstream& ss, const char* format, const T& value, const VTtypes&... VTvalues );
template<class T, class... VTtypes>
std::stringstream& imp_formatString( std::stringstream& ss, const char* format, const T& value, const VTtypes&... VTvalues )
{
    for( ; *format != '\0'; format++ )
    {
        if( *format == '%' )
        {
            // check for %%
            if( *(format+1) == '%' )
            {
                ss << '%';
                format++;
                continue;
            }
            ss << value;
            return imp_formatString( ss, format+1, VTvalues... );
        }
        // You can use {%} to display parameter. It will not look for following '%'
        else if( *format == '{' && *(format+1) == '%' && *(format+2) == '}' )
        {
            ss << value;
            return imp_formatString( ss, format+3, VTvalues... );
        }
        
        ss << *format;
    }
    
    return ss;
}



std::string formatString( const char* format );
std::string formatString( const char* format )
{
    std::stringstream ss;
    return imp_formatString( ss, format ).str();
}

template<class T, class... VTtypes>
std::string formatString( const char* format, const T& value, const VTtypes&... VTvalues );
template<class T, class... VTtypes>
std::string formatString( const char* format, const T& value, const VTtypes&... VTvalues )
{
    std::stringstream ss;
    return imp_formatString( ss, format, value, VTvalues... ).str();
}


}

#endif // UTILS_HPP_INCLUDED_2044
