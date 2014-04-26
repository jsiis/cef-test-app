/**
 * @file test_app.h
 *
 * @breif CefApp instance class
 */
#ifndef _TEST_APP
#define _TEST_APP

#include <cef_app.h>

class TestApp: public CefApp,
               public CefBrowserProcessHandler
{
public:
    TestApp();

    // CefApp impl.
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE { return this; }

    // CefBrowserProcessHandler
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation
    IMPLEMENT_REFCOUNTING(TestApp);
};

#endif // _TEST_APP
