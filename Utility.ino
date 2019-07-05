#include <Arduino.h>

#include "Constant.h"
#include "Utility.h"
#include "MD5.h"

int countChar(String inStr, String letter) {
   int count = 0;
   int lsize = letter.length();
   for (int n = 0; n < inStr.length(); n=n+lsize) {
        if (inStr.substring(n, n+lsize) == letter) {
            count++;
        }
   }
   Serial.println("final count: " + String(count));
   return count;
}

//char** split(String ipt, const char* delimiter) {
//
//   char buff[ipt.length()];
//   ipt.toCharArray(buff, ipt.length());
//
//   int sizeOfArray = countChar(ipt, String(delimiter));
//   int i = 0;
//   char *p = strtok (buff, delimiter);
//   char *array[sizeOfArray];
//   while (p != NULL) {
//        array[i++] = p;
//        p = strtok (NULL, delimiter);
//   }
//
////   for (int j = 0; j < sizeOfArray; j++) {
////       Serial.println(String(array[j]) + "......kkkkkkk");
////   }
//   return array;
//}

String saveKeyValueStr(String keyValueStr, String key, String value) {
  
	String existValue = valueOfKeyValueStr(keyValueStr, key);
  if (existValue == "") {
      keyValueStr = keyValueStr + KV_DELIMITER + key + KV_DIVIDER + value;
  } else {
      String inKV = key + KV_DIVIDER + existValue;
      String toReplaceKV = key + KV_DIVIDER + value;
      if (keyValueStr.indexOf(inKV) == 0) {
          keyValueStr.replace(inKV, toReplaceKV);
      } else {
          keyValueStr.replace(inKV, KV_DELIMITER+toReplaceKV);
      }
  }
  return keyValueStr;
}


String valueOfKeyValueStr(String input, String key) {

   char *token;
   char cinput[input.length()];
   input.toCharArray(cinput, input.length());
 
   /* get the first token */
   token = strtok(cinput, KV_DELIMITER);
   
   /* walk through other tokens */
   while( token != NULL ) {
      String strToken = String(token);
      strToken.trim();
      if (strToken.indexOf(KV_DIVIDER) > 0  && strToken.indexOf(key) == 0) {      
          String value = strToken.substring(strToken.indexOf(KV_DIVIDER)+KV_DIVIDER.length());
          strToken.replace(KV_DIVIDER+value, "");
          if (strToken == key) {
              return value;
          }
      }
      token = strtok(NULL, KV_DELIMITER);
   }
   return "";
}

char* stringToChar(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

String toMD5(String input) {
    //generate the MD5 hash for our string
    unsigned char* hash=MD5::make_hash(stringToChar(input));
    //generate the digest (hex encoding) of our hash
    char *out = MD5::make_digest(hash, 16);
    free(hash);
    //print it on our serial monitor
    return String(out);
}

String toHmacMD5(String message, String key) {
   char *md5str = MD5::hmac_md5(stringToChar(message), message.length(), stringToChar(key), key.length());
   return String(md5str);
}

void serPrint(String message, int logMode) {
   int isLog = 0;
   if (DEVICE_MODE != PRODUCTION) {
       isLog = 1;
   } else if (logMode == PRODUCTION) {
       isLog = 1;
   }
   if (isLog == 1) {
       Serial.println(message);
   }
}

//useServerTime = 0 => not use
//useServerTime = 1 => use
String toBufferMeasure (float x, float y, float z, String ts, int useServerTime, String bufferStr) {
   String record = "";
   if (useServerTime == 1) {
	   record = "{\"X\":\"" + String(x) + "\"," + "\"Y\":\"" + String(y) + "\"," + "\"Z\":\"" + String(z) + + "\"," + "\"STS\":\"" + ts + "\"}";
   } else {
	   record = "{\"X\":\"" + String(x) + "\"," + "\"Y\":\"" + String(y) + "\"," + "\"Z\":\"" + String(z) + + "\"," + "\"LTS\":\"" + ts + "\"}";
   }
   if (bufferStr == "") {
       bufferStr = bufferStr + record;
   } else {
       bufferStr = bufferStr + "," + record;
   }
   return bufferStr;

}

//useServerTime = 0 => not use
//useServerTime = 1 => use
String toBufferMeasureCSV (float x, float y, float z, String ts, int useServerTime, String bufferStr) {
   String record = "";
   if (useServerTime == 1) {
	     record = "X," + String(x) + "," + "Y," + String(y) + "," + "Z," + String(z) + "," + "STS," + ts;
       //Serial.println(record); 
   } else {
	     record = "X," + String(x) + "," + "Y," + String(y) + "," + "Z," + String(z) + "," + "LTS," + ts;
   }
   if (bufferStr == "") {
       bufferStr = bufferStr + record;
   } else {
       bufferStr = bufferStr + "\n" + record;
   }
   return bufferStr;

}

String urlencode(String str) {
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++) {
        c=str.charAt(i);
        if (c == ' ') {
            encodedString+= '+';
        } else if (isalnum(c)){
            encodedString+=c;
        } else{
            code1=(c & 0xf)+'0';
            if ((c & 0xf) >9){
                code1=(c & 0xf) - 10 + 'A';
            }
            c=(c>>4)&0xf;
            code0=c+'0';
            if (c > 9){
                code0=c - 10 + 'A';
            }
            code2='\0';
            encodedString+='%';
            encodedString+=code0;
            encodedString+=code1;
            //encodedString+=code2;
        }
        yield();
    }
    return encodedString;
}

