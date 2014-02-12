#include "UTile/UnitTest.hpp"
#include "Utils/Utils.hpp"

#include <string>

using namespace UnitTest;

class TestFormatString : public Test<TestFormatString>
{
    void RunTest() const
    {
        GetID();
        
        std::string expected = "";
        std::string formatted = Utils::formatString( "" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "Only format";
        formatted = Utils::formatString( "Only format" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "One parameter here...";
        formatted = Utils::formatString( "One % here...", "parameter" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "2 parameters";
        formatted = Utils::formatString( "% %", 2, "parameters" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "42 is *";
        formatted = Utils::formatString( "% % %", 42, "is", '*' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%%%";
        formatted = Utils::formatString( "%%%%%%", '\t', '\n', '\r', '\n', '\n', '\r' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "\t\n\r\n\n\r";
        formatted = Utils::formatString( "{%}{%}{%}{%}{%}{%}", '\t', '\n', '\r', '\n', '\n', '\r' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12 34 %";
        formatted = Utils::formatString( "{%}% %{%} %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12 % 34";
        formatted = Utils::formatString( "%{%} %% {%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "% 12 %";
        formatted = Utils::formatString( "%% {%}% %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%1";
        formatted = Utils::formatString( "%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%";
        formatted = Utils::formatString( "{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "123";
        formatted = Utils::formatString( "%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%1";
        formatted = Utils::formatString( "%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%%";
        formatted = Utils::formatString( "%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%2";
        formatted = Utils::formatString( "{%}%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12%";
        formatted = Utils::formatString( "%{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%12";
        formatted = Utils::formatString( "%%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%12";
        formatted = Utils::formatString( "%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12%";
        formatted = Utils::formatString( "{%}{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1234";
        formatted = Utils::formatString( "{%}%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%2";
        formatted = Utils::formatString( "{%}%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1234";
        formatted = Utils::formatString( "%{%}%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%%1";
        formatted = Utils::formatString( "%%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%%";
        formatted = Utils::formatString( "{%}%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%23";
        formatted = Utils::formatString( "{%}%%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12345";
        formatted = Utils::formatString( "%{%}%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "%1%";
        formatted = Utils::formatString( "%%{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1%23";
        formatted = Utils::formatString( "{%}%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        
        
        // Wrong formats
        expected = "{%%1";
        formatted = Utils::formatString( "{%%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "12 %} %";
        formatted = Utils::formatString( "{%}% %%} %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "1{2 % 3}4";
        formatted = Utils::formatString( "%{% %% %}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = "% 1}2 %";
        formatted = Utils::formatString( "%% %}% %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        
        
        // basic strings
        std::string format = "";
        expected = "";
        formatted = Utils::formatString( format );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = "Only format";
        expected = "Only format";
        formatted = Utils::formatString( format );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = "One % here...";
        expected = "One parameter here...";
        formatted = Utils::formatString( format, "parameter" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = "% %";
        expected = "2 parameters";
        formatted = Utils::formatString( format, 2, "parameters" );
        Assert::That( expected, Is::EqualTo( formatted ) );
    }
};
/*
class TestFormatWString : public Test<TestFormatWString>
{
    void RunTest() const
    {
        GetID();
        
        std::wstring expected = L"";
        std::wstring formatted = Utils::formatString( L"" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"Only format";
        formatted = Utils::formatString( L"Only format" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"One parameter here...";
        formatted = Utils::formatString( L"One % here...", L"parameter" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"2 parameters";
        formatted = Utils::formatString( L"% %", 2, L"parameters" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"42 is *";
        formatted = Utils::formatString( L"% % %", 42, L"is", L'*' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%%%";
        formatted = Utils::formatString( L"%%%%%%", L'\t', L'\n', L'\r', L'\n', L'\n', L'\r' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"\t\n\r\n\n\r";
        formatted = Utils::formatString( L"{%}{%}{%}{%}{%}{%}", L'\t', L'\n', L'\r', L'\n', L'\n', L'\r' );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12 34 %";
        formatted = Utils::formatString( L"{%}% %{%} %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12 % 34";
        formatted = Utils::formatString( L"%{%} %% {%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"% 12 %";
        formatted = Utils::formatString( L"%% {%}% %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%1";
        formatted = Utils::formatString( L"%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%";
        formatted = Utils::formatString( L"{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"123";
        formatted = Utils::formatString( L"%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%1";
        formatted = Utils::formatString( L"%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%%";
        formatted = Utils::formatString( L"%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%2";
        formatted = Utils::formatString( L"{%}%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12%";
        formatted = Utils::formatString( L"%{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%12";
        formatted = Utils::formatString( L"%%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%12";
        formatted = Utils::formatString( L"%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12%";
        formatted = Utils::formatString( L"{%}{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1234";
        formatted = Utils::formatString( L"{%}%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%2";
        formatted = Utils::formatString( L"{%}%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1234";
        formatted = Utils::formatString( L"%{%}%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%%1";
        formatted = Utils::formatString( L"%%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%%";
        formatted = Utils::formatString( L"{%}%%%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%23";
        formatted = Utils::formatString( L"{%}%%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12345";
        formatted = Utils::formatString( L"%{%}%{%}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"%1%";
        formatted = Utils::formatString( L"%%{%}%%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1%23";
        formatted = Utils::formatString( L"{%}%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        
        
        // Wrong formats
        expected = L"{%%1";
        formatted = Utils::formatString( L"{%%%%{%}", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"12 %} %";
        formatted = Utils::formatString( L"{%}% %%} %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"1{2 % 3}4";
        formatted = Utils::formatString( L"%{% %% %}%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        expected = L"% 1}2 %";
        formatted = Utils::formatString( L"%% %}% %%", 1, 2, 3, 4, 5, 6 );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        
        
        // basic strings
        std::wstring format = L"";
        expected = L"";
        formatted = Utils::formatString( format );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = L"Only format";
        expected = L"Only format";
        formatted = Utils::formatString( format );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = L"One % here...";
        expected = L"One parameter here...";
        formatted = Utils::formatString( format, L"parameter" );
        Assert::That( expected, Is::EqualTo( formatted ) );
        
        format = L"% %";
        expected = L"2 parameters";
        formatted = Utils::formatString( format, 2, L"parameters" );
        Assert::That( expected, Is::EqualTo( formatted ) );
    }
};
*/
