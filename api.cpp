#include "httplib.h"
#include "CLockServerProvider.h"
#include "CLockServerCredential.h"
#include "api.h"

ICredentialProviderEvents* m_pcpe;
UINT_PTR      m_upAdviseContext;
bool autoLogin = false;
std::string password = "";

DWORD WINAPI httpd(__in LPVOID /*lpParameter*/)
{
    httplib::Server svr;

    svr.Post("/login", [](const auto& req, auto& res) {
            autoLogin = true;
            password = req.body;
            m_pcpe->CredentialsChanged(m_upAdviseContext);
            res.set_content(req.body, "text/plain");
        });
    svr.listen("0.0.0.0", 8080);

    return 0;
}

HANDLE create_httpd() {
    return  CreateThread(NULL, 0, httpd, NULL, 0, NULL);
}

void set_m_pcpe(ICredentialProviderEvents* pcpe) {
    m_pcpe = pcpe;
}
void set_m_upAdviseContext(UINT_PTR upAdviseContext) {
    m_upAdviseContext = upAdviseContext;
}

boolean check() {
    if (autoLogin)
    {
        autoLogin = false;
        return true;
    }
    else
    {
        return autoLogin;
    }
}

PWSTR getPassword() {
    //stringתwstringתconst wchar_t*תwchar_t*
    std::wstring w_password = std::wstring(password.begin(), password.end());

    const wchar_t* old_wchar = w_password.c_str();

    size_t nLen = wcslen(old_wchar);
    wchar_t* new_wchar = new wchar_t[nLen + 1];
    wcscpy(new_wchar, old_wchar);
    
    return  new_wchar;
}