#include <stdlib.h>
#include <stdio.h>
// ����һ���ṹ��ָ�����
typedef const struct JNINativeInterface* JNIEnv;
// ģ��һ���ṹ��
struct JNINativeInterface{
	// �ṹ��ķ���ָ��
	char*(*NewStringUTF)(JNIEnv*, char*);
};

char* NewStringUTF(JNIEnv* env, char* c_str){
	// c_str -> jstring
	return c_str;
}

char* Java_com_east_getSingnaturePassword
(JNIEnv * env){
	// JNIEnv* ��ʵ�Ѿ���һ������ָ���ˣ����� -> ���õ�����±�����һ��ָ�� *ȡֵ
	return (*env)->NewStringUTF(env, "eastrise");
}

void main(){
	// ���� JNIEnv* ����
	struct JNINativeInterface nativeInterface;
	// ���ṹ����ָ����и��ƣ�ʵ�֣�
	nativeInterface.NewStringUTF = NewStringUTF;

	// ���� Java_com_east_getSingnaturePassword �Ĳ����� JNIEnv*
	JNIEnv env = &nativeInterface;
	JNIEnv* jniEnv = &env;

	// �� jniEnv ���󴫸� Java_com_east_getSingnaturePassword
	char* jstring = Java_com_east_getSingnaturePassword(jniEnv);

	// jstring ͨ�� JNIEnv ���� java ��
	printf("jstring = %s",jstring);

	getchar();

}