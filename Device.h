#ifndef _DEVICE_H
#define _DEVICE_H

#include "Address.h"
#include <EEPROM.h>

class Device {
  
public:
  static byte state;
  static void begin();
  static String readBuildCount();
  static String readUUID();
  static String readSSID();
  static String readPwd();
  static String readApiKey();
  static String readWebUid();
  static String readWebPwd();
  static String readPinNumber();
  static String readDeviceUid();
  static String readDevicePwd();
  static String readDeviceMeasureKeyValue();
  static String readLogin();
  static String readLoginTimestamp();
  static String readSdOnly();
  static String readBufferSize();
  static String readSampleRate();
  static String readEncryptSecret();
  static String readWebHost();

  static void saveBuildCount(String saveBuildCount);
  static void saveUUID(String saveUuid);
  static void saveSSID(String saveSsid);
  static void savePwd(String savePwd);
  static void saveApiKey(String saveApiKey);
  static void saveWebUid(String saveWebUid);
  static void saveWebPwd(String saveWebPwd);
  static void savePinNumber(String savePinNumber);
  static void saveDeviceUid(String saveDeviceUid);
  static void saveDevicePwd(String saveDevicePwd);
  static void saveDeviceMeasureKeyValue(String saveDeviceMeasureKeyValue);
  static void saveLogin(String saveLogin);
  static void saveLoginTimestamp(String saveLoginTimestamp);
  static void saveSdOnly(String saveSdOnly);
  static void saveBufferSize(String saveBufferSize);  
  static void saveSampleRate(String saveSampleRate); 
  static void saveEncryptSecret(String saveEncryptSecret);
  static void saveWebHost(String saveWebHost);

  //static void clearBuildCount();
  static void clearUUID();
  static void clearSsid();
  static void clearPwd();
  static void clearApiKey();
  static void clearWebUid();
  static void clearWebPwd();
  static void clearPinNumber();
  static void clearDeviceUid();
  static void clearDevicePwd();
  static void clearDeviceMeasureKeyValue();
  static void clearLogin();
  static void clearLoginTimestamp();
  static void clearSdOnly();
  static void clearBufferSize();
  static void clearSampleRate();
  static void clearEncryptSecret();
  static void clearWebHost();
  static void clearAll();

  static void resetDeviceIdPwd();
  static void reboot();
  static String uuid(String prefix, String postfix);

  static bool isLogin(int enterTimestamp);
  static bool isAuth(String enterUid, String enterPwd, String ts);
  static bool logout();
  static float measureValue(String key);
  static void saveMeasureValue(String key, String value);
  static boolean isValidNumbers(String str);
  
};

#endif 

