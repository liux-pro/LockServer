#pragma once


DWORD WINAPI httpd(__in LPVOID /*lpParameter*/);
HANDLE create_httpd();
void set_m_pcpe(ICredentialProviderEvents* pcpe);
void set_m_upAdviseContext(UINT_PTR upAdviseContext);
boolean check();
PWSTR getPassword();

