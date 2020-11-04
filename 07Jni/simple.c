
// ʵ�����ǵ� native ����
#include "com_east_jni07_NdkSample.h"
#include "com_east_jni07_NdkSample1.h"

// JNIEXPORT�� JNI һ���ؼ��֣������٣�������ͨ���������Ϊ�÷������Ա��ⲿ����
// jstring������ java �е� String
// JNICALL��Ҳ��һ���ؼ��֣������ٵ� jni call
// jobject�� java ��������������󣬾��Ǳ���Ŀ�� NdkSample java ����
// jclass��java ���������� class ���󣬾��Ǳ���Ŀ�е� NdkSample.class
JNIEXPORT jstring JNICALL Java_com_east_jni07_NdkSample_getSingnaturePassword
(JNIEnv * env, jclass clz){
	// C �� typedef const struct JNINativeInterface* JNIEnv; �Ѿ���һ���ṹ��ָ����
	// C++ �� typedef _JNIEnv JNIEnv; // ����һ���ṹ��
	// JNIEnv * ��ʵ�Ѿ���һ������ָ���ˣ����� -> ���õ�����±�����һ��ָ�� *ȡֵ
	return (*env)->NewStringUTF(env, "eastrise");
}

JNIEXPORT void JNICALL Java_com_east_jni07_NdkSample1_changeName
(JNIEnv * env, jobject jobj){
	// 1. ��ȡ jclass
	jclass j_clz = (*env)->GetObjectClass(env,jobj);
	// 2. ��ȡ jfieldID
	// ��ȡ jfieldId (JNIEnv *env, jclass clazz, const char *name, const char *sig)
	// name ��ȡ�ĸ����Ե������� ,sig ���Ե�ǩ��
	jfieldID j_fid = (*env)->GetFieldID(env, j_clz, "name", "Ljava/lang/String;");
	// 1. ��ȡ name ������ֵ
	jstring j_str = (*env)->GetObjectField(env,jobj,j_fid);

	// ��ӡ�ַ��� jstring -> c_str
	char* c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
	
	printf("name is %s", c_str);

	// �޸ĳ� Jack
	jstring jack_name = (*env)->NewStringUTF(env,"Jack");
	(*env)->SetObjectField(env,jobj,j_fid,jack_name);
}

// ��̬�����������Ϊ jclass ���� NdkSample1.class
JNIEXPORT void JNICALL Java_com_east_jni07_NdkSample1_changeAge
(JNIEnv * env, jclass jcls){
	
	// 2. ��ȡ jfieldID
	jfieldID j_fid = (*env)->GetStaticFieldID(env,jcls,"age","I");
	// 1. ��ȡ age ��ֵ Static ��ȡ��̬��
	jint age = (*env)->GetStaticIntField(env,jcls,j_fid);

	// jnit == int
	age += 12;
	
	(*env)->SetStaticIntField(env,jcls,j_fid,age);
}

// c ���� java ����ͨ����
JNIEXPORT void JNICALL Java_com_east_jni07_NdkSample1_callAddMethod
(JNIEnv * env, jobject jobj){

	// 3. ��ȡ jclass
	jclass jcls = (*env)->GetObjectClass(env,jobj);

	// 2. ��ȡ jmethodID
	jmethodID j_mid = (*env)->GetMethodID(env,jcls,"add","(II)I");

	// 1. ���� java ����
	jint sum = (*env)->CallObjectMethod(env,jobj,j_mid,2,3);

	printf("sum = %d",sum);
}
