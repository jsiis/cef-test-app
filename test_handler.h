/**
 * @file test_handler.h
 *
 * @breif CefClient instance class
 */
#ifndef _TEST_HANDLER
#define _TEST_HANDLER

#include <cef_client.h>

#include <list>

class TestHandler: public CefClient,
                   public CefDisplayHandler,
                   public CefLifeSpanHandler,
                   public CefLoadHandler {
public:
    TestHandler();
    virtual ~TestHandler();

    // Provide access to the single global instance of this object
    static TestHandler* GetInstance();

    // CefClient impl.
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
        return this;
    }
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
        return this;
    }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() {
        return this;
    }

    // CefDisplayHandler impl.
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
            const CefString& title) OVERRIDE;
    // CefLifeSpanHandler impl.
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    // CefLoadHandler impl.
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            ErrorCode errorCode,
            const CefString& errorText,
            const CefString& failedUrl) OVERRIDE;
    // Request that all existing browser windows close
    void CloseAllBrowsers(bool force_close);
private:
    // List of existing browser windows. Only accessed on the CEF UI thread
    typedef std::list<CefRefPtr<CefBrowser> > CefBrowserList;
    CefBrowserList browsers_;

    // Include the default reference counting implementation
    IMPLEMENT_REFCOUNTING(TestHandler);
};

#endif // _TEST_HANDLER
