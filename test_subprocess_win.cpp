/**
 * @file test_subprocess_win.cpp
 *
 * @breif Sub-process entry-point.
 */
#include <windows.h>

#include <cef_app.h>

#include "test_app.h"

int main(int argc, char* argv[])
{
    HINSTANCE hInstance = GetModuleHandle(0);
    CefMainArgs args(hInstance);
    CefRefPtr<CefApp> app(new TestApp);
    return CefExecuteProcess(args, app.get(), 0);
}
