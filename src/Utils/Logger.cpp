
#include "Utils/Logger.hpp"

#include <iostream>
#include <string>
#include <sstream>

namespace Utils
{

namespace
{
    bool local_WrittingToFileForFirstTime = true;
}

Logger::Logger()
    : Logger( "LogOutput.txt" )
{}

// TODO: Add option to append and not to owerwrite log file.
// TODO: Add option to set filename globally - now it would have
//         to be set with every Logger("customfilename.txt") << call.
Logger::Logger( const std::string& filename )
{
    if( local_WrittingToFileForFirstTime )
    {
        m_LogFileStream.open( filename, std::ios_base::out );
        local_WrittingToFileForFirstTime = false;
    }
    else
    {
        m_LogFileStream.open(  filename, std::ios_base::out | std::ios_base::app );
    }
}
Logger::~Logger()
{
    if( m_LogFileStream.is_open() )
    {
        m_LogFileStream.close();
    }
}

Logger& Logger::operator << ( char value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( unsigned char value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( bool value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( short int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( unsigned short int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}
        
Logger& Logger::operator << ( unsigned int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( long int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( unsigned long int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( long long int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( unsigned long long int value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( float value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( double value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( long double value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}


template<typename T>
Logger& Logger::operator << ( const T& value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( const std::string& value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( const char* value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

Logger& Logger::operator << ( const unsigned char* value )
{
    std::cout << value;
    if( m_LogFileStream.is_open() )
        m_LogFileStream << value;
    
    return *this;
}

// TODO: We should probably replace "magic" code with simple inheritance
Logger& Logger::operator << ( std::ostream& (*func)( std::ostream& ) )
{
    std::stringstream out;
    func(out);
    *this << out.str();
    
    return *this;
}

Logger& Logger::operator << ( std::ios& (*func)( std::ios& ) )
{
    std::stringstream out;
    func(out);
    *this << out.str();
    
    return *this;
}

Logger& Logger::operator << ( std::ios_base& (*func)( std::ios_base& ) )
{
    std::stringstream out;
    func(out);
    *this << out.str();
    
    return *this;
}

} // namespace Utils
