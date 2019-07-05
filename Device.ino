#include "Constant.h"
#include "Utility.h"
#include "Id_Maker.h"
#include "Device.h"

void Device::begin() {
  Serial.begin (115200);
  EEPROM.begin(512);
  WiFi.persistent(false);

  //Check the build number - to ensure if this is a first build
  if (Device::readBuildCount() != "YY" && Device::readBuildCount() != "NN") {
      Serial.println("This is the first build..."); 
	    //first build
	  Device::saveBuildCount("YY");
      Device::clearBufferSize();
      Device::saveBufferSize("10");
      Device::clearSampleRate();
      Device::saveSampleRate("100");
      Device::saveWebHost("www.zygozu.com");
  } else {
      Device::saveBuildCount("NN");
  }

  //Set default device userid and password to "admin" and "admin" if no userid and password set
  if (Device::readDeviceUid() == "" && Device::readDevicePwd() == "") {
      Device::resetDeviceIdPwd();
  }

  if (Device::readWebHost() == "" || (Device::readWebHost()).indexOf('.') == -1) {
	    Device::saveWebHost("www.zygozu.com");
  }

  //Serial.println("device_uid:" + Device::readDeviceUid());
  //Serial.println("device_pwd:" + Device::readDevicePwd());

  Device::clearLogin();
  Device::clearLoginTimestamp();
}

void Device::saveBuildCount(String saveBuildCount) {
	  for (int i = 0; i < BUILD_COUNT_ADDR; ++i) {
	       EEPROM.write(i, 0);
	  }
	  for (int i = 0; i < (int)saveBuildCount.length(); ++i) {
	       EEPROM.write(i, saveBuildCount[i]);
	  }
	  EEPROM.commit();
	  //Serial.println("writing eeprom uuid");
	}

void Device::saveUUID(String saveUuid) {
  for (int i = BUILD_COUNT_ADDR; i < UUID_ADDR; ++i) {
       EEPROM.write(i, 0); 
  }
  for (int i = 0; i < (int)saveUuid.length(); ++i) {
       EEPROM.write(BUILD_COUNT_ADDR+i, saveUuid[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom uuid"); 
}

void Device::saveSSID(String saveSsid) {
  for (int i = UUID_ADDR; i < SSID_ADDR; ++i) { 
       EEPROM.write(i, 0); 
  }
  for (int i = 0; i < (int)saveSsid.length(); ++i) {
       EEPROM.write(UUID_ADDR+i, saveSsid[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom ssid"); 
}

void Device::savePwd(String savePwd) {
  for (int i = SSID_ADDR; i < PWD_ADDR; ++i) { 
       EEPROM.write(i, 0); 
  }
  for (int i = 0; i < (int)savePwd.length(); ++i) {
       EEPROM.write(SSID_ADDR+i, savePwd[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom pass"); 
}

void Device::saveApiKey(String saveApiKey) {
  for (int i = PWD_ADDR; i < API_KEY_ADDR; ++i) { 
       EEPROM.write(i, 0); 
  }
  for (int i = 0; i < (int)saveApiKey.length(); ++i) {
       EEPROM.write(PWD_ADDR+i, saveApiKey[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom api key"); 
}

void Device::saveWebUid(String saveWebUid) {
  for (int i = API_KEY_ADDR; i < WEB_UID_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveWebUid.length(); ++i) {
       EEPROM.write(API_KEY_ADDR+i, saveWebUid[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom web user id");
}

void Device::saveWebPwd(String saveWebPwd) {
  for (int i = WEB_UID_ADDR; i < WEB_PWD_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveWebPwd.length(); ++i) {
       EEPROM.write(WEB_UID_ADDR+i, saveWebPwd[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom web password");
}

void Device::savePinNumber(String savePinNumber) {
  for (int i = WEB_PWD_ADDR; i < PIN_NUMBER_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)savePinNumber.length(); ++i) {
       EEPROM.write(WEB_PWD_ADDR+i, savePinNumber[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device pin number");
}

void Device::saveDeviceUid(String saveDeviceUid) {
  for (int i = PIN_NUMBER_ADDR; i < DEVICE_UID_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveDeviceUid.length(); ++i) {
       EEPROM.write(PIN_NUMBER_ADDR+i, saveDeviceUid[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device user id");
}

void Device::saveDevicePwd(String saveDevicePwd) {
  for (int i = DEVICE_UID_ADDR; i < DEVICE_PWD_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveDevicePwd.length(); ++i) {
       EEPROM.write(DEVICE_UID_ADDR+i, saveDevicePwd[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device password");
}


void Device::saveDeviceMeasureKeyValue(String saveDeviceMeasureKeyValue) {
  for (int i = DEVICE_PWD_ADDR; i < DEVICE_MEASURE_KV_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveDeviceMeasureKeyValue.length(); ++i) {
       EEPROM.write(DEVICE_PWD_ADDR+i, saveDeviceMeasureKeyValue[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device measure JSON");
}


void Device::saveLogin(String saveLogin) {
  for (int i = DEVICE_MEASURE_KV_ADDR; i < LOGIN_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveLogin.length(); ++i) {
       EEPROM.write(DEVICE_MEASURE_KV_ADDR+i, saveLogin[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login");
}

void Device::saveLoginTimestamp(String saveLoginTimestamp) {
  for (int i = LOGIN_ADDR; i < LOGIN_TIMESTAMP_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveLoginTimestamp.length(); ++i) {
       EEPROM.write(LOGIN_ADDR+i, saveLoginTimestamp[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

void Device::saveSdOnly(String saveSdOnly) {
  for (int i = LOGIN_TIMESTAMP_ADDR; i < SD_ONLY_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveSdOnly.length(); ++i) {
       EEPROM.write(LOGIN_TIMESTAMP_ADDR+i, saveSdOnly[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

void Device::saveBufferSize(String saveBufferSize) {
  for (int i = SD_ONLY_ADDR; i < BUFFER_SIZE_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveBufferSize.length(); ++i) {
       EEPROM.write(SD_ONLY_ADDR+i, saveBufferSize[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

void Device::saveSampleRate(String saveSampleRate) {
  for (int i = BUFFER_SIZE_ADDR; i < SAMPLE_RATE_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveSampleRate.length(); ++i) {
       EEPROM.write(BUFFER_SIZE_ADDR+i, saveSampleRate[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

void Device::saveEncryptSecret(String saveEncryptSecret) {
  for (int i = SAMPLE_RATE_ADDR; i < ENCRYPT_SECRET_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveEncryptSecret.length(); ++i) {
       EEPROM.write(SAMPLE_RATE_ADDR+i, saveEncryptSecret[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

void Device::saveWebHost(String saveWebHost) {
  for (int i = ENCRYPT_SECRET_ADDR; i < WEB_HOST_ADDR; ++i) {
       EEPROM.write(i, 0);
  }
  for (int i = 0; i < (int)saveWebHost.length(); ++i) {
       EEPROM.write(ENCRYPT_SECRET_ADDR+i, saveWebHost[i]);
  }
  EEPROM.commit();
  //Serial.println("writing eeprom device login timestamp");
}

String Device::readBuildCount() {
  String buildCount = "";
  for (int i = 0; i < BUILD_COUNT_ADDR; ++i) {
	   if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
          buildCount += char(EEPROM.read(i));
	   }
  }
  //Serial.println("Reading EEPROM Build Count: " + char(EEPROM.read(i)));
  return buildCount;
}

String Device::readUUID() {
  String uuid = "";
  for (int i = BUILD_COUNT_ADDR; i < UUID_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
           uuid += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM UUID: " + uuid);
  return uuid;
}

String Device::readSSID() {
  //Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = UUID_ADDR; i < SSID_ADDR; ++i) {
      esid += char(EEPROM.read(i));
  }
  //Serial.print("SSID: " + esid);
  return esid;
}

String Device::readPwd() {
  //Serial.println("Reading EEPROM password");
  String epass;
  for (int i = SSID_ADDR; i < PWD_ADDR; ++i) {
       epass += char(EEPROM.read(i));
  }
  //Serial.println("PASS: "+ epass);
  return epass;  
}

String Device::readApiKey() {
  String apiKey = "";
  for (int i = PWD_ADDR; i < API_KEY_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
           apiKey += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Api Key: " + apiKey);
  return apiKey;
}

String Device::readWebUid() {
  String webUid = "";
  for (int i = API_KEY_ADDR; i < WEB_UID_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   webUid += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Web User ID: " + webUid);
  return webUid;
}

String Device::readWebPwd() {
  String webPwd = "";
  for (int i = WEB_UID_ADDR; i < WEB_PWD_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   webPwd += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Web Password: " + webPwd);
  return webPwd;
}

String Device::readPinNumber() {
  String devicePin = "";
  for (int i = WEB_PWD_ADDR; i < PIN_NUMBER_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   devicePin += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince Pin Number: " + devicePin);
  return devicePin;
}

String Device::readDeviceUid() {
  String deviceUid = "";
  for (int i = PIN_NUMBER_ADDR; i < DEVICE_UID_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   deviceUid += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince User Id: " + deviceUid);
  return deviceUid;
}

String Device::readDevicePwd() {
  String devicePwd = "";
  for (int i = DEVICE_UID_ADDR; i < DEVICE_PWD_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   devicePwd += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince Password: " + devicePwd);
  return devicePwd;
}

String Device::readDeviceMeasureKeyValue() {
  String deviceMeasure = "";
  for (int i = DEVICE_PWD_ADDR; i < DEVICE_MEASURE_KV_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
         deviceMeasure += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince Measure Json: " + deviceMeasure);
  return deviceMeasure;
}

String Device::readLogin() {
  String deviceLogin = "";
  for (int i = DEVICE_MEASURE_KV_ADDR; i < LOGIN_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   deviceLogin += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince Login: " + deviceLogin);
  return deviceLogin;
}

String Device::readLoginTimestamp() {
  String deviceLoginTimestamp = "";
  for (int i = LOGIN_ADDR; i < LOGIN_TIMESTAMP_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
         deviceLoginTimestamp += char(EEPROM.read(i));
       }
  }
  //Serial.println("Reading EEPROM Devince Login Timestamp: " + deviceLoginTimestamp);
  return deviceLoginTimestamp;
}

String Device::readSdOnly() {
  String deviceSdOnly = "";
  for (int i = LOGIN_TIMESTAMP_ADDR; i < SD_ONLY_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
         deviceSdOnly += char(EEPROM.read(i));
       }
  }
  return deviceSdOnly;
}

String Device::readBufferSize() {
  String deviceBufferSize = "";
  for (int i = SD_ONLY_ADDR; i < BUFFER_SIZE_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
         deviceBufferSize += char(EEPROM.read(i));
       }
  }
  return deviceBufferSize;
}

String Device::readSampleRate() {
  String deviceSampleRate = "";
  for (int i = BUFFER_SIZE_ADDR; i < SAMPLE_RATE_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
         deviceSampleRate += char(EEPROM.read(i));
       }
  }
  return deviceSampleRate;
}

String Device::readEncryptSecret() {
  String deviceEncryptSecret = "";
  for (int i = SAMPLE_RATE_ADDR; i < ENCRYPT_SECRET_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   deviceEncryptSecret += char(EEPROM.read(i));
       }
  }
  return deviceEncryptSecret;
}

String Device::readWebHost() {
  String deviceWebHost = "";
  for (int i = ENCRYPT_SECRET_ADDR; i < WEB_HOST_ADDR; ++i) {
       if ((char(EEPROM.read(i)) != NULL) && (char(EEPROM.read(i)) != '\0')) {
    	   deviceWebHost += char(EEPROM.read(i));
       }
  }
  return deviceWebHost;
}




void Device::clearUUID () {
   for (int i = BUILD_COUNT_ADDR; i < UUID_ADDR; ++i) {
        EEPROM.write(i, 0); 
   }
   EEPROM.commit();
}

void Device::clearSsid () {
   for (int i = UUID_ADDR; i < SSID_ADDR; ++i) {
        EEPROM.write(i, 0); 
   }
   EEPROM.commit();
}

void Device::clearPwd () {
   for (int i = SSID_ADDR; i < PWD_ADDR; ++i) {
        EEPROM.write(i, 0); 
   }
   EEPROM.commit();
}

void Device::clearApiKey () {
   for (int i = PWD_ADDR; i < API_KEY_ADDR; ++i) {
        EEPROM.write(i, 0); 
   }
   EEPROM.commit();
}

void Device::clearWebUid () {
   for (int i = API_KEY_ADDR; i < WEB_UID_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearWebPwd () {
   for (int i = WEB_UID_ADDR; i < WEB_PWD_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearPinNumber () {
   for (int i = WEB_PWD_ADDR; i < PIN_NUMBER_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearDeviceUid () {
   for (int i = PIN_NUMBER_ADDR; i < DEVICE_UID_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearDevicePwd () {
   for (int i = DEVICE_UID_ADDR; i < DEVICE_PWD_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearDeviceMeasureKeyValue () {
   for (int i = DEVICE_PWD_ADDR; i < DEVICE_MEASURE_KV_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearLogin() {
   for (int i = DEVICE_MEASURE_KV_ADDR; i < LOGIN_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearLoginTimestamp() {
   for (int i = LOGIN_ADDR; i < LOGIN_TIMESTAMP_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearSdOnly() {
   for (int i = LOGIN_TIMESTAMP_ADDR; i < SD_ONLY_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearBufferSize() {
   for (int i = SD_ONLY_ADDR; i < BUFFER_SIZE_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearSampleRate() {
   for (int i = BUFFER_SIZE_ADDR; i < SAMPLE_RATE_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearEncryptSecret() {
   for (int i = SAMPLE_RATE_ADDR; i < ENCRYPT_SECRET_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

void Device::clearWebHost() {
   for (int i = ENCRYPT_SECRET_ADDR; i < WEB_HOST_ADDR; ++i) {
        EEPROM.write(i, 0);
   }
   EEPROM.commit();
}

bool Device::isLogin(int enterTimestamp) {
   String saveTs = Device::readLoginTimestamp();
   String isLogined = Device::readLogin();
   if (isLogined == "t") {
       //calculate login saved time, session time 5 mins
       if ((enterTimestamp - saveTs.toInt()) < 300) {
            return true;
       } else {
          //clear login related variable
          Device::clearLogin();
          Device::clearLoginTimestamp();
          return false;
       }   
   } else {
     return false;
   }
   return false;
}

bool Device::isAuth(String enterUid, String enterPwd, String ts) {
    if (enterUid == Device::readDeviceUid() && enterPwd == Device::readDevicePwd()) {
        Device::saveLogin("t");
        Device::saveLoginTimestamp(ts);
        return true;
    } else {
        return false;
    }
    return false;
}

bool Device::logout() {
    Device::clearLogin();
    Device::clearLoginTimestamp();
    return true;
}

void Device::clearAll() {
   //Device::clearUUID();
   Device::clearSsid();
   Device::clearPwd();
   Device::clearApiKey();
   Device::clearWebUid();
   Device::clearWebPwd();
   Device::clearPinNumber();
   Device::clearDeviceUid();
   Device::clearDevicePwd();
   Device::clearDeviceMeasureKeyValue();
   Device::clearLogin();
   Device::clearLoginTimestamp();
   Device::clearSdOnly();
   Device::clearBufferSize();
   Device::saveBufferSize("10");
   Device::clearSampleRate();
   Device::saveSampleRate("100");
   Device::clearEncryptSecret();
   Device::clearWebHost();
   Device::saveWebHost("www.zygozu.com");
}

void Device::resetDeviceIdPwd() {
    Device::saveDeviceUid("admin");
    Device::saveDevicePwd("admin");
}

void Device::reboot() {
   ESP.restart();
}

String Device::uuid(String prefix, String postfix) {
  byte uuidNumber[10];
  String uuidStr = "";
  String readUuid = Device::readUUID();
  if (Device::readUUID() != "") {
      if (Device::readUUID().substring(8,9) != "-") {
          Device::clearUUID(); 
      }
  }
  //Generate a new UUID if no UUID saved
  String buildCount = Device::readBuildCount();
  if (Device::readUUID() == "" || buildCount == "YY") {
      Id_Maker.uuid(uuidNumber);
      uuidStr = Id_Maker.uuidToString(uuidNumber);
      uuidStr = prefix + uuidStr + postfix;
      Device::saveUUID(uuidStr);
  } else {
      uuidStr = Device::readUUID();
  }
  return uuidStr;
}

float Device::measureValue(String key) {
   String MeasureKV = Device::readDeviceMeasureKeyValue();
   String value = valueOfKeyValueStr(MeasureKV, key);
   
   return value.toFloat();
}



void Device::saveMeasureValue(String key, String value) {
   String MeasureKV = Device::readDeviceMeasureKeyValue();
   if (MeasureKV == "") {
       String kvStr = key + KV_DIVIDER + value;
       Device::saveDeviceMeasureKeyValue(kvStr);
   } else {
       String newMeasureKV = saveKeyValueStr(MeasureKV, key, value);
       Device::saveDeviceMeasureKeyValue(newMeasureKV);
   }
}

boolean Device::isValidNumbers(String str) {
   for (byte i=0;i<str.length();i++) {
	   if (isDigit(str.charAt(i))) return true;
   }
   return false;
}







