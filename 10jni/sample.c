#include "com_east_jni10_Sample.h"
#include <stdlib.h>

// 4. ����һ�� compare �ķ���
int compare(const int* number1, const int* number2){
	return *number1 - *number2;
}

// ��������
JNIEXPORT void JNICALL Java_com_east_jni10_Sample_sort
(JNIEnv* env, jclass jclz, jintArray jarray){
	
	// 2. ��ȡ jintArray ���׵�ַ
	jint* intArray = (*env)->GetIntArrayElements(env,jarray,NULL);

	// 3. ��ȡ����ĳ���
	int length = (*env)->GetArrayLength(env,jarray);

	// 1. �� jarray ��������
	// void qsort(void * _Base, size_t _NumOfElements, size_t _SizeOfElements, int(*_PtFuncCompare)(const void *, const void *))
	// ��һ��������void* ������׵�ַ
	// �ڶ�������������ĳ���
	// ����������������Ԫ���������͵Ĵ�С
	// ���ĸ������������һ���ȽϷ���ָ�루Comparable��
	qsort(intArray,length,sizeof(int),compare);

	// ͬ����������ݸ� java ���� intArray ������ jarray�� ���Լ����Ϊ copy
	// JNI_OK == 0:����Ҫͬ�����ݸ� jarray�� ��Ҫ�ͷ� intArray
	// JNI_COMMIT == 1����ͬ�����ݸ� jarray, ���ǲ����ͷ� intArray
	// JNI_ABORT == 2������ͬ�����ݸ� jarray, ���ǻ��ͷ� intArray

	(*env)->ReleaseIntArrayElements(env, jarray, intArray, JNI_OK);

}

// �ֲ�����
JNIEXPORT void JNICALL Java_com_east_jni10_Sample_localRef
(JNIEnv * env, jclass jclz){
	// �� native �㹹���� Java ���󣬲�����Ӧ����ô����Ӧ�ý��л���ɾ����
	// native �㿪�ٵ��ڴ���˭�������ܿ��ٶ��

	// �ַ�����ȡ��String ����
	jclass str_clz = (*env)->FindClass(env,"java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, str_clz, "<init>", "()V");
	jobject j_str = (*env)->NewObject(env,str_clz,jmid);

	// ���� 100 �д���

	// jobject ��Ҫ��ʹ���ˣ�Ҫ���� javaGC ��Դ��
	(*env)->DeleteLocalRef(env,j_str);

	// ɾ���˾Ͳ�����ʹ���ˣ�C �� C++ ����Ҫ�Լ��ͷ��ڴ棨��̬���ٵĲ���Ҫ����̬���ٵ���Ҫ��
}

// ȫ������

jstring globalStr;

JNIEXPORT void JNICALL Java_com_east_jni10_Sample_saveGlobalRef
(JNIEnv * env, jclass j_clz, jstring value){
	// ����ȫ�����ã�����������Ҫ�õ�
	globalStr = (*env)->NewGlobalRef(env,value);

	// NewWeakGlobalRef ��java �е������ú����޷���֤����Ϊ��
}

JNIEXPORT jstring JNICALL Java_com_east_jni10_Sample_getGlobalRef
(JNIEnv * env, jclass j_clz){
	return globalStr;
}


JNIEXPORT void JNICALL Java_com_east_jni10_Sample_deleteGlobalRef
(JNIEnv * env, jclass j_clz){
	(*env)->DeleteGlobalRef(env,globalStr);
}

// �ֲ���̬����
JNIEXPORT void JNICALL Java_com_east_jni10_Sample_staticLocalCache
(JNIEnv * env, jclass j_clz, jstring value){
	// name ���ԣ���ֵ����
	static jfieldID jfid = NULL; // �ֲ���̬���棬���ᷴ����ȥ��ȡ jfieldID
	
	if (jfid){
		printf("fieldID is not null\n");
	}
	else{
		jfid = (*env)->GetStaticFieldID(env, j_clz, "name", "Ljava/lang/String;");// ���û�о�̬���� ��������ᱻ��ε��ã���ȥ�����Ļ�ȡ jfieldID
	}

	(*env)->SetStaticObjectField(env,j_clz,jfid,value);
}


// ȫ�־�̬����
static jfieldID f_name_id = NULL;
static jfieldID f_name1_id = NULL;
static jfieldID f_name2_id = NULL;


//JNIEXPORT void JNICALL Java_com_east_jni10_Sample_staticLocalCache
//(JNIEnv * env, jclass j_clz, jstring value){
//	// ��Ϊ�Ǿ�̬���棬��������������������ã�Ҳ���ᷴ����ȥ��ȡ jfieldID
//	(*env)->SetStaticObjectField(env,j_clz,f_name_id,value);
//}


JNIEXPORT void JNICALL Java_com_east_jni10_Sample_initStaticCache
(JNIEnv *env, jclass j_clz){
	// ��ʼ��ȫ�־�̬����
	f_name_id = (*env)->GetStaticFieldID(env, j_clz, "name", "Ljava/lang/String;");
	f_name1_id = (*env)->GetStaticFieldID(env, j_clz, "name1", "Ljava/lang/String;");
	f_name2_id = (*env)->GetStaticFieldID(env, j_clz, "name2", "Ljava/lang/String;");
}

// �쳣����
JNIEXPORT void JNICALL Java_com_east_jni10_Sample_exception
(JNIEnv *env, jclass j_clz){

	// ����������� ��name3 ��ֵ
	jfieldID jfid = (*env)->GetStaticFieldID(env, j_clz, "name3", "Ljava/lang/String;");

	// ���ַ�ʽ���
	// 1. ���ȴ�ʩ�� ���� name3 �� name
	// 1.1 ��û���쳣
	jthrowable throwable = (*env)->ExceptionOccurred(env);
	/*if (throwable){
		// ���ȴ�ʩ���Ȱ��쳣���
		printf("native have a exception");
		// ����쳣
		(*env)->ExceptionClear(env);
		// ���»�ȡ name ����
		jfid = (*env)->GetStaticFieldID(env, j_clz, "name", "Ljava/lang/String;");
	}*/

	// 2. ��� java ����һ���쳣
	if (throwable){
		// ����쳣
		(*env)->ExceptionClear(env);
		// �� java ���� һ�� Throwable �쳣

		// ��һ�ַ�ʽ��ֱ�Ӱ��쳣�׸� java ��
		(*env)->Throw(env, throwable);

		// �ڶ��ַ�ʽ���쳣
		// (*env)->ThrowNew(env, no_such_clz, "NoSuchFieldException name3");

		return; //  ���� return ������Ļ������������������У��϶�����crash
	}

	jstring name = (*env)->NewStringUTF(env, "Eastrise");
	(*env)->SetStaticObjectField(env, j_clz, jfid, name);

}