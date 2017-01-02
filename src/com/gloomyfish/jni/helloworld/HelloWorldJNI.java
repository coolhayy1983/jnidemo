package com.gloomyfish.jni.helloworld;
import java.io.UnsupportedEncodingException;

import com.gloomyfish.jni.helloworld.GbktoUtf8;


public class HelloWorldJNI {

	public native void helloJNI(String name);
	public native String helloJNI1(String name1);
	
	public static void main(String[] args) throws UnsupportedEncodingException {
	
		System.out.println(System.getProperty("file.encoding"));
		String str = "返回string";
		//String str = "返回string";//utf-8 
		//System.out.println(str);
		System.loadLibrary("hellojni");
		HelloWorldJNI jnidemo = new HelloWorldJNI();		
		jnidemo.helloJNI("返回void");
		//jnidemo.helloJNI("返回void");//utf-8
		
		/*
		 * 1、会打印c++里面的打印语句
		 * 2、打印返回来的语句
		 * */
		
		System.out.println("the String(返回) return by C is "+jnidemo.helloJNI1(str));  
		
		/*调用gbktoutf8感觉不是应用在此处
		GbktoUtf8 gbktou = new GbktoUtf8();
		System.out.println(gbktou.convertString(jnidemo.helloJNI1(str)));  
        */
		
		/*页面为utf编码，utf转gbk，会是乱码*,utf 转 unicode 再转gbk，unicode都要作为中转/
		
		/*
		String str1 = "你好hello"; 
		String utf8 = new String(str1.getBytes("UTF-8"));  
		System.out.println("utf8:" + utf8);  
		String unicode = new String(utf8.getBytes(),"UTF-8");   
		System.out.println("unicode:" + unicode);  
		String gbk = new String(unicode.getBytes("GBK"));  
		System.out.println("gbk:" + gbk); 
		*/

		
	}

}
