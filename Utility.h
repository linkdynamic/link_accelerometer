#ifndef _UTILITY_H
#define _UTILITY_H


//KeyValueString
static const char* KV_DELIMITER  =  ";";
static String KV_DIVIDER         =  "&";

int countChar(String inStr, char letter);
String valueOfKeyValueStr(String input, String key);
char* stringToChar(String command);
String toMD5(String input);
String toHmacMD5(String message, String key);
void serPrint(String message, int logMode);
String toBufferMeasure (float x, float y, float z, String ts, int useServerTime, String bufferStr);
String toBufferMeasureCSV (float x, float y, float z, String ts, int useServerTime, String bufferStr);
String urlencode(String str);

#endif 
