#include "driverJNI.h"
#include "driver.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jboolean JNICALL Java_driverJNI_compress
  (JNIEnv * env, jobject clazz, jstring src, jstring dest, jint level)
{
	char *nativesrc = (*env)->GetStringUTFChars(env, src, 0);
	char *nativedest = (*env)->GetStringUTFChars(env, dest, 0);
	jboolean status;

	status = (jboolean)compress (nativesrc, nativedest, (int)level);

	(*env)->ReleaseStringUTFChars(env, src, nativesrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativedest);
	return status;
}

JNIEXPORT jboolean JNICALL Java_driverJNI_decompress
(JNIEnv * env, jobject clazz, jstring src, jstring dest, jint level)
{
	char *nativesrc = (*env)->GetStringUTFChars(env, src, 0);
	char *nativedest = (*env)->GetStringUTFChars(env, dest, 0);
	jboolean status;

	status = (jboolean)decompress (nativesrc, nativedest, (int)level);

	(*env)->ReleaseStringUTFChars(env, src, nativesrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativedest);
	return status;
}

#ifdef __cplusplus
}
#endif
