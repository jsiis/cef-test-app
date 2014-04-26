/**
 * @file test_win.cpp
 *
 * @breif Application entry-point
 */
#include <windows.h>

#include <cef_app.h>

#include "test_app.h"

int main(int argc, char** argv)
{
    HINSTANCE hInstance = GetModuleHandle(0);
    // Provide CEF with command-line arguments
    CefMainArgs args(hInstance);
    // TestApp implements application-level callbacks. It will create the first
    // browser instance in the `OnContextInitialized` callback after CEF has
    // initialized
    CefRefPtr<CefApp> app(new TestApp);
    // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
    // that share can the same executable. 
    // Create sub-process
    //int exit_code = CefExecuteProcess(args, app.get(), NULL);
    //if (exit_code >= 0) {  // sub-process
    //    // sub-process has completed, so return here
    //    return exit_code;
    //}
    // However, separate sub-process executable is used here, so
    // 'browser_subprocess_path' must be set in CefSettings
    CefSettings settings;
    CefString(&settings.browser_subprocess_path).FromASCII("test_subprocess.exe");
    settings.no_sandbox = true;
    // Initialize CEF
    CefInitialize(args, settings, app.get(), NULL);
    // Run the CEF message loop. This will block until `CefQuiMessageLoop` is
    // invoked.
    CefRunMessageLoop();
    // Shutdown CEF
    CefShutdown();

    return 0;
}
