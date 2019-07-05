#ifndef _SERVER_PAGE_H
#define _SERVER_PAGE_H

String ssidRootPage(String networkHtml);
String ssidSetPage();
String webHomePage();
String loginPage();
String ssidSetErrorPage();
String needLoginPage();

extern const char header[] PROGMEM;
extern const char dropdownCss[] PROGMEM;
extern const char headJs[] PROGMEM;
extern const char headCss[] PROGMEM;
extern const char contentHead[] PROGMEM;
extern const char contentTail[] PROGMEM;
extern const char setCss[] PROGMEM;
extern const char setJs[] PROGMEM;
extern const char setHtml[] PROGMEM;
extern const char setErrHtml1[] PROGMEM;
extern const char setErrHtml2[] PROGMEM;
extern const char homePageHtml[] PROGMEM;
extern const char loginHtml[] PROGMEM;
extern const char needLoginHtml[] PROGMEM;

#endif 

