#include "com_east_jni08_Sample1.h"

// ���� java �� static �Ļ�ȡ uuid �ķ���
JNIEXPORT void JNICALL Java_com_east_jni08_Sample1_callStaticMethod
(JNIEnv* env,jclass jclz){
	
	// 2. ��ȡjmethodID
	jmethodID j_mid = (*env)->GetStaticMethodID(env, jclz, "getUUID", "()Ljava/lang/String;");

	// 1. ���� getUUID �ķ��� statics
	jstring j_uuid = (*env)->CallStaticObjectMethod(env,jclz,j_mid);

	// jstring -> c_str
	char* c_uuid = (*env)->GetStringUTFChars(env,j_uuid,NULL);

	// ���գ��ַ�������
	(*env)->ReleaseStringChars(env,j_uuid,c_uuid);

	printf("c_uuid = %s",c_uuid);
}


// c �� ���� java ����
JNIEXPORT jobject JNICALL Java_com_east_jni08_Sample1_createPoint
(JNIEnv* env, jclass jclz){

	// 2. ��Ҫ��ȡ Point ��class name = "ȫ����"
	// ���������ϵ� jclz  ָ���� Sample1.class
	jclass point_clz = (*env)->FindClass(env,"com/east/jni08/Point");

	// 3. ��ȡjmethodID ,���췽��д�� "<init>"
	jmethodID j_mid = (*env)->GetMethodID(env, point_clz, "<init>","(II)V");

	// 1. ��������
	jobject point = (*env)->NewObject(env,point_clz, j_mid, 11, 12);

	// ��ϰ�� y ���¸�ֵ,���� set ����
	j_mid = (*env)->GetMethodID(env,point_clz,"setY","(I)V");
	/* va_list ����
	void (JNICALL *CallVoidMethodV)
	(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
	// jvalue
	void (JNICALL *CallVoidMethodA)
	(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);
	*/

	(*env)->CallObjectMethod(env,point,j_mid,33);

	// ֱ�����¸�ֵ���൱�ڷ����˵��Ǳȷ����
	jfieldID j_fid = (*env)->GetFieldID(env,point_clz,"y","I");
	(*env)->SetIntField(env,point,j_fid,55);


	return point;
}

void main(){
	// ����������ȥ�޸�
	const int number = 100;
	// number = 200;

	int number1 = 100;
	int number2 = 200;

	// ����ָ�루const �� * ֮ǰ,��ַ���Ա����¸�ֵ������ֵ���ܸı䣩
	// int const * n_p = &number2;
	// n_p = &number1;
	// printf("n_p = %p",n_p); // ��ַ�ǿ������±���ֵ��
	// *n_p = 300; // ֵ���ܸı�

	// ָ�볣����const �� * ֮��,��ַ�����Ա����¸�ֵ������ֵ���Ըı䣩
	int* const n_p = &number2;
	// n_p = &number1; // ��ַ�ǲ��ܱ����¸�ֵ��
	*n_p = 300;
	printf("number2 = %d",number2);

	getchar();
}