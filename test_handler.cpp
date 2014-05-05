/**
 * @file test_handler.cpp
 *
 * @breif TestHandler Impl.
 */
#include <sstream>
#include <string>

#include <cef_app.h>
#include <cef_runnable.h>

#include "test_handler.h"
#include "util.h"

namespace {

TestHandler* gInstance = NULL;

}

TestHandler::TestHandler() {
    ASSERT(!gInstance);
    gInstance = this;
}

TestHandler::~TestHandler() {
    gInstance = NULL;
}

// [static]
TestHandler* TestHandler::GetInstance() {
    return gInstance;
}

void TestHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    REQUIRE_UI_THREAD();
    // Add to the list of existing browsers
    browsers_.push_back(browser);
}

void TestHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    REQUIRE_UI_THREAD();
    // Remove from the list of existing browsers
    CefBrowserList::iterator it = browsers_.begin();
    for (; it != browsers_.end(); ++it) {
        if ((*it)->IsSame(browser)) {
            browsers_.erase(it);
            break;
        }
    }

    if (browsers_.empty()) {
        // All browser windows have closed. Quit the application
        CefQuitMessageLoop();
    }
}

void TestHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        ErrorCode errorCode,
        const CefString& errorText,
        const CefString& failedUrl) {
    REQUIRE_UI_THREAD();
    // Don't display error for downloaded files.
    if (errorCode == ERR_ABORTED) return;

    // Display a load error message
    std::ostringstream oss;
    oss << "<html><body bgcolor=\"white\">"
        << "<h2>Failed to load URL " << std::string(failedUrl) << " with error "
        << std::string(errorText) << " (" << errorCode
        << ").</h2></body></html>";
    frame->LoadString(oss.str(), failedUrl);
}

void TestHandler::CloseAllBrowsers(bool force_close) {
    if (!CefCurrentlyOn(TID_UI)) {
        // Must execute on ui thread
        CefPostTask(TID_UI,
                NewCefRunnableMethod(this, &TestHandler::CloseAllBrowsers,
                    force_close));
        return;
    }
    if (browsers_.empty()) return;

    CefBrowserList::iterator it = browsers_.begin();
    for (; it != browsers_.end(); ++it) {
        (*it)->GetHost()->CloseBrowser(force_close);
    }
}
