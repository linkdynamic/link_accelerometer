#include "Server_Page.h"
#include "AP_Html.h"
#include "STA_Html.h"
#include "STA_Login_Html.h"
#include "STA_Need_Login_Html.h"

String pageContent;

String ssidRootPage(String networkHtml) {
    pageContent = FPSTR(header);
    pageContent += FPSTR(dropdownCss); 
    pageContent += FPSTR(headJs);
    pageContent += FPSTR(headCss);
    pageContent += FPSTR(contentHead);
    pageContent += networkHtml;
    pageContent += FPSTR(contentTail);
    return pageContent;
}

String ssidSetPage() {
    pageContent = FPSTR(header);
    pageContent += FPSTR(setCss);
    pageContent += FPSTR(setJs); 
    pageContent += FPSTR(setHtml);
    return pageContent;
}

String ssidSetErrorPage(String ip) {
    pageContent = FPSTR(header);
    pageContent += FPSTR(setCss); 
    pageContent += FPSTR(setErrHtml1);
    pageContent += "http://" + ip + "/";
    pageContent += FPSTR(setErrHtml2);
    return pageContent;
}

String webHomePage() {
    pageContent = FPSTR(homePageHtml);
    return pageContent;
}

String loginPage() {
    pageContent = FPSTR(loginHtml);
    return pageContent;
}

String needLoginPage(){
    pageContent = FPSTR(needLoginHtml);
    return pageContent;
}


