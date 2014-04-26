/**
 * @file test_app.cpp
 *
 * @breif TestApp impl.
 */
#include <cef_browser.h>
#include <cef_command_line.h>

#include "test_app.h"
#include "test_handler.h"
#include "util.h"

TestApp::TestApp() {}

void TestApp::OnContextInitialized() {
    REQUIRE_UI_THREAD();

    // Information used when creating the native window
    CefWindowInfo info;
#ifdef OS_WIN
    // On Windows we need to specify certain flags that will be passed to
    // 'CreateWindowEx'
    info.SetAsPopup(NULL, "cef_test_app");
#endif
    // SimpleHandler implements browser-level callbacks
    CefRefPtr<CefClient> handler(new TestHandler);
    // Specify CEF browser settings here
    CefBrowserSettings settings;
    std::string url;
    CefRefPtr<CefCommandLine> args = CefCommandLine::GetGlobalCommandLine();
    url = args->GetSwitchValue("url");
    if (url.empty())
        url = "http://www.google.com/";
    // Create the first browser window
    CefBrowserHost::CreateBrowserSync(info, handler.get(), url, settings, NULL);
}
