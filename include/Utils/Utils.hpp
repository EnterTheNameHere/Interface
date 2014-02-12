#ifndef UTILS_HPP_INCLUDED_2044
#define UTILS_HPP_INCLUDED_2044

#include <sstream>
#include <string>

namespace Utils
{

//std::stringstream& imp_formatString( std::stringstream& ss, const char* format );
//inline std::stringstream& imp_formatString( std::stringstream& ss, const char* format )
//{
//    ss << format;
//    
//    return ss;
//}
//
//template<class T, class... VTtypes>
//std::stringstream& imp_formatString( std::stringstream& ss, const char* format, const T& value, const VTtypes&... VTvalues );
//template<class T, class... VTtypes>
//std::stringstream& imp_formatString( std::stringstream& ss, const char* format, const T& value, const VTtypes&... VTvalues )
//{
//    for( ; *format != '\0'; format++ )
//    {
//        if( *format == '%' )
//        {
//             check for %%
//            if( *(format+1) == '%' )
//            {
//                ss << '%';
//                format++;
//                continue;
//            }
//            ss << value;
//            return imp_formatString( ss, format+1, VTvalues... );
//        }
//         You can use {%} to display parameter. It will not look for following '%'
//        else if( *format == '{' && *(format+1) == '%' && *(format+2) == '}' )
//        {
//            ss << value;
//            return imp_formatString( ss, format+3, VTvalues... );
//        }
//        
//        ss << *format;
//    }
//    
//    return ss;
//}
//
//
//
//std::string formatString( const char* format );
//inline std::string formatString( const char* format )
//{
//    std::stringstream ss;
//    return imp_formatString( ss, format ).str();
//}
//
//template<class T, class... VTtypes>
//std::string formatString( const char* format, const T& value, const VTtypes&... VTvalues );
//template<class T, class... VTtypes>
//std::string formatString( const char* format, const T& value, const VTtypes&... VTvalues )
//{
//    std::stringstream ss;
//    return imp_formatString( ss, format, value, VTvalues... ).str();
//}



template<typename _CharT>
std::basic_stringstream<_CharT>& imp_formatString( std::basic_stringstream<_CharT>& ss, const _CharT* format );
template<typename _CharT>
std::basic_stringstream<_CharT>& imp_formatString( std::basic_stringstream<_CharT>& ss, const _CharT* format )
{
    ss << format;
    
    return ss;
}

template<typename _CharT, class T, class... VTtypes>
std::basic_stringstream<_CharT>& imp_formatString( std::basic_stringstream<_CharT>& ss, const _CharT* format, const T& value, const VTtypes&... VTvalues );
template<typename _CharT, class T, class... VTtypes>
std::basic_stringstream<_CharT>& imp_formatString( std::basic_stringstream<_CharT>& ss, const _CharT* format, const T& value, const VTtypes&... VTvalues )
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



template<class _CharT>
std::basic_string<_CharT> formatString( const _CharT* format );
template<class _CharT >
std::basic_string<_CharT> formatString( const _CharT* format )
{
    std::basic_stringstream<_CharT> ss;
    return imp_formatString( ss, format ).str();
}

template<class _CharT>
std::basic_string<_CharT> formatString( const std::basic_string<_CharT>& format );
template<class _CharT>
std::basic_string<_CharT> formatString( const std::basic_string<_CharT>& format )
{
    std::basic_stringstream<_CharT> ss;
    return imp_formatString( ss, format.c_str() ).str();
}

template<class _CharT, class T, class... VTtypes>
std::basic_string<_CharT> formatString( const _CharT* format, const T& value, const VTtypes&... VTvalues );
template<class _CharT, class T, class... VTtypes>
std::basic_string<_CharT> formatString( const _CharT* format, const T& value, const VTtypes&... VTvalues )
{
    std::basic_stringstream<_CharT> ss;
    return imp_formatString( ss, format, value, VTvalues... ).str();
}

template<class _CharT, class T, class... VTypes>
std::basic_string<_CharT> formatString( const std::basic_string<_CharT>& format, const T& value, const VTypes&... VTvalues );
template<class _CharT, class T, class... VTypes>
std::basic_string<_CharT> formatString( const std::basic_string<_CharT>& format, const T& value, const VTypes&... VTvalues )
{
    std::basic_stringstream<_CharT> ss;
    return imp_formatString( ss, format.c_str(), value, VTvalues... ).str();
}

}

#endif // UTILS_HPP_INCLUDED_2044
