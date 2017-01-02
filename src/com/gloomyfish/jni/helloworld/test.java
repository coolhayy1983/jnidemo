package com.gloomyfish.jni.helloworld;

import java.nio.charset.Charset;

public class test { 
	
        public static void main(String[] args) { 
                System.out.println("current JRE:" + System.getProperty("java.version")); 
                System.out.println("current defaultCharset of JVM:" + Charset.defaultCharset()); 
        } 
}