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

	return compress (nativesrc, nativedest, (int) level);

	(*env)->ReleaseStringUTFChars(env, src, nativesrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativedest);
}

JNIEXPORT jboolean JNICALL Java_driverJNI_decompress
(JNIEnv * env, jobject clazz, jstring src, jstring dest, jint level)
{
	char *nativesrc = (*env)->GetStringUTFChars(env, src, 0);
	char *nativedest = (*env)->GetStringUTFChars(env, dest, 0);

	return decompress (nativesrc, nativedest, (int) level);

	(*env)->ReleaseStringUTFChars(env, src, nativesrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativedest);
}

#ifdef __cplusplus
}
#endif
