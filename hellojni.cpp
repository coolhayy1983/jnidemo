// hellojni.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "com_gloomyfish_jni_helloworld_HelloWorldJNI.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

/*
相应的编码转换
本地程序是UNICODE编码的话，你需要先转换到ANSI，再从ANSI转换到UNICODE。
int main()
{
setlocale(LC_ALL, "");

const wchar_t* s1 = L"UNICODE转换成UTF-8";
cout << WC2UT(s1).c_str() << endl;

const char* s2 = "ANSI转换成UNICODE";
wcout << MB2WC(s2).c_str() << endl;

const wchar_t* s3 = L"UNICODE转换成ANSI";
cout << WC2MB(s3).c_str() << endl;

return 0;
}

*/

std::string WC2UT(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);

	return std::string(&utf8[0]);
}

std::wstring UT2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);

	return std::wstring(&unicode[0]);
}

std::wstring MB2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);

	return std::wstring(&unicode[0]);
}

std::string WC2MB(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, NULL, NULL);

	return std::string(&utf8[0]);
}

char* jstringToWindows(JNIEnv *env, jstring jstr)
{
	int length = env->GetStringLength(jstr);
	const jchar* jcstr = env->GetStringChars(jstr, 0);
	char* rtn = (char*)malloc(length * 2 + 1);
	int size = 0;
	size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jcstr, length, rtn, (length * 2 + 1), NULL, NULL);
	if (size <= 0)
		return NULL;
	env->ReleaseStringChars(jstr, jcstr);
	rtn[size] = 0;
	return rtn;
}

jstring WindowsTojstring(JNIEnv *env, const char* str)
{
	jstring rtn = 0;
	int slen = strlen(str);
	unsigned short* buffer = 0;
	if (slen == 0)
		rtn = env->NewStringUTF(str);
	else
	{
		int length = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, NULL, 0);
		buffer = (unsigned short*)malloc(length * 2 + 1);
		if (MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, (LPWSTR)buffer, length) > 0)
			rtn = env->NewString((jchar*)buffer, length);
	}
	if (buffer)
		free(buffer);
	return rtn;
}


JNIEXPORT void JNICALL Java_com_gloomyfish_jni_helloworld_HelloWorldJNI_helloJNI
(JNIEnv *env, jobject obj, jstring param1){

	const char* content = env->GetStringUTFChars(param1, 0);

	/*
	  两边的页面都是utf-8编码，传进来的content那么不会乱码，但是这边的“中文”就会乱码。
	*/
	const wchar_t* s1 = L"UNICODE转换成UTF-8(void方法)";
	cout << WC2UT(s1).c_str() << content<<endl;

	/*
	底下这几种方式都会乱码
	const char* s2 = "ANSI转换成UNICODE";
	wcout << MB2WC(s2).c_str() << endl;
	const wchar_t* s3 = L"UNICODE转换成ANSI";
	cout << WC2MB(s3).c_str() << endl;
	cout << "无返回The string in C code" << endl;
	*/

	env->ReleaseStringUTFChars(param1, content);
	return;

}


/*
两边的页面编码都是GBK的时候，
这时，如果加上jstringToWindows以及WindowsTojstring，不会出现乱码
*/

JNIEXPORT jstring JNICALL Java_com_gloomyfish_jni_helloworld_HelloWorldJNI_helloJNI1
(JNIEnv *env, jobject obj, jstring param2){

	const char *str;
	jstring tostring;
	const char* content = env->GetStringUTFChars(param2, 0);

	str = jstringToWindows(env, param2);
	tostring = WindowsTojstring(env, str);


	const wchar_t* s2 = L"UNICODE转换成UTF-8(string方法)";
	cout << WC2UT(s2).c_str() << content << endl;

	/*printf会乱码
	printf("返回字符串The string in C %s \n", str);
	*/
	env->ReleaseStringUTFChars(param2, content);
	return tostring;

}






