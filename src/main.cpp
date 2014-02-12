
#include "Utils/Logger.hpp"
#include "WindowManager.hpp"

using Utils::Logger;
using Interface::WindowManager;

int main( int /*argc*/, char** /*arga*/ )
{
    Logger() << "Entered main()\n";
    
    try
    {
        WindowManager wm;
        wm.Run();
    }
    catch( std::exception& ex )
    {
        Logger() << "Exception caught:\n" << ex.what() << "\n";
    }
    catch( ... )
    {
        Logger() << "Unknown exception caught...\n";
    }
    
    Logger() << "Finished main()\n";
    return 0;
}
