如： 在cocos-c++中由启动场景进入到游戏主场景中时候，要调用广告SDK。

static JavaVM *g_JavaVM = NULL;
static jobject gs_object = NULL;
static bool g_bAttatedT = false;

static JNIEnv *GetEnv()
{
	int status;
    JNIEnv *envnow = NULL;
    status = g_JavaVM->GetEnv((void **)&envnow, JNI_VERSION_1_4);
    if(status < 0)
    {
        status = g_JavaVM->AttachCurrentThread(&envnow, NULL);
        if(status < 0)
        {
            return NULL;
        }
        g_bAttatedT = true;
    }
    return envnow;
}


static void DetachCurrent()
{
    if(g_bAttatedT)
    {
        g_JavaVM->DetachCurrentThread();
    }
}

//  在MainScene::onEnterTransitionDidFinish() 方法中调用
void enterMainSceneDidFinish()
{
	JNIEnv *env = GetEnv();

	if (env == NULL)
	{
		return;
	}
	if (gs_object == NULL)
		return;


	jclass classObject = env->GetObjectClass(gs_object);
	jclass class_father = env->FindClass("org/cocos2dx/cpp")
	jmethodID methodID = env->GetMethodID(classObject, "show", "()V");

	if (methodID)
		env->CallVoidMethod(gs_object, methodID);
	// 记得最后要删除引用
	//env->DeleteGlobalRef(gs_object);
    //DetachCurrent();
}

// 在jni 初始化的时候调用
	env->GetJavaVM(&g_JavaVM);
	gs_object=env->NewGlobalRef(obj);//创建一个全局变量


