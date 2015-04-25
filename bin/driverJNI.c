#include <driverJNI.h>
#include <driver.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jboolean JNICALL Java_driverJNI_compress
  (JNIEnv * env, jobject clazz, jstring src, jstring dest, jint level)
{
	const char *nativesrc = (*env)->GetStringUTFChars(env, src, 0);
	const char *nativedest = (*env)->GetStringUTFChars(env, dest, 0);

	return (jblooean) compress (nativesrc, nativedest, (int) level);

	(*env)->ReleaseStringUTFChars(env, src, nativsrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativdest);
}

JNIEXPORT jboolean JNICALL Java_driverJNI_decompress
(JNIEnv * env, jobject clazz, jstring src, jstring dest, jint level)
{
	const char *nativesrc = (*env)->GetStringUTFChars(env, src, 0);
	const char *nativedest = (*env)->GetStringUTFChars(env, dest, 0);

	return (jblooean) decompress (nativesrc, nativedest, (int) level);

	(*env)->ReleaseStringUTFChars(env, src, nativsrc);
	(*env)->ReleaseStringUTFChars(env, dest, nativdest);
}

#ifdef __cplusplus
}
#endif
#endif
