#include "httplib.h"
#include "httpServer.h"
#include "CSampleProvider.h"
#include "CSampleCredential.h"
ICredentialProviderEvents* m_pcpe;
UINT_PTR      m_upAdviseContext;
bool autoLogin = false;

DWORD WINAPI httpd(__in LPVOID /*lpParameter*/)
{
    httplib::Server svr;

    svr.Get("/hi", [](const auto&, auto& res) {
        res.set_content("Hello World!", "text/plain");
        m_pcpe->CredentialsChanged(m_upAdviseContext);
        autoLogin = true;
        });

    svr.listen("0.0.0.0", 8080);

    return 0;
}

HANDLE create_httpd() {
    return  CreateThread(NULL, 0, httpd, NULL, 0, NULL);
}

void set1(ICredentialProviderEvents* pcpe) {
    m_pcpe = pcpe;
}
void set2(UINT_PTR upAdviseContext) {
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