/**
 * @file test_handler_win.cpp
 *
 * @breif Windows-specific codes for TestHandler
 */
#include <string>
#include <windows.h>

#include <cef_browser.h>

#include "test_handler.h"
#include "util.h"

void TestHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
        const CefString& title) {
    REQUIRE_UI_THREAD();

    CefWindowHandle hWnd = browser->GetHost()->GetWindowHandle();
    SetWindowText(hWnd, std::wstring(title).c_str());
}
