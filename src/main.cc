#include "main.h"

Napi::Object CreateResult(Napi::Env env, bool success, Napi::Value value)
{
    Napi::Object object = Napi::Object::New(env);
    if (success)
    {
        object.Set("code", 0);
        object.Set("msg", "success");
        if (!value.IsUndefined() && !value.IsNull())
        {
            object.Set("data", value);
        }
    }
    else
    {
        int error_code = GetLastErr();
        char last_error[1024] = {0};
        GetLastErrMsg(last_error, 1024);
        char last_error_json[1024] = {0};
        GetLastErrJson(last_error_json, 1024);
        if (error_code == 0)
        {
            object.Set("code", -1);
            object.Set("msg", "unknown error");
            object.Set("data", value);
        }
        else
        {
            object.Set("code", error_code);
            object.Set("msg", last_error);
            object.Set("data", last_error_json);
        }
    }
    return object;
}

Napi::Object ATVersion(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char version[1024] = {0};
    bool result = verison(version);
    return CreateResult(env, result, Napi::String::New(env, version));
}

Napi::Object ATInit(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = init();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATUninit(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = uninit();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATStartServe(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = startServe();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATStopServe(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = stopServe();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATSetUseBitbltCaptureMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = SetUseBitbltCaptureMode();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATSetUseDx11CaptureMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = SetUseDx11CaptureMode();
    return CreateResult(env, result, env.Null());
}

Napi::Object ATSetHandle(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Number handle;
    if (info.Length() < 1)
    {
        handle = Napi::Number::New(env, 0);
    }
    else
    {
        handle = info[0].As<Napi::Number>();
    }
    bool result = SetHandle(handle.Int64Value());
    return CreateResult(env, result, env.Null());
}

Napi::Object ATSetWorldCenter(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Number x;
    Napi::Number y;
    if (info.Length() < 2)
    {
        x = Napi::Number::New(env, 0);
        y = Napi::Number::New(env, 0);
    }
    else
    {
        x = info[0].As<Napi::Number>();
        y = info[1].As<Napi::Number>();
    }
    bool result = SetWorldCenter(x.DoubleValue(), y.DoubleValue());
    return CreateResult(env, result, env.Null());
}

Napi::Object ATSetWorldScale(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Number scale;
    if (info.Length() < 1)
    {
        scale = Napi::Number::New(env, 1.0);
    }
    else
    {
        scale = info[0].As<Napi::Number>();
    }
    bool result = SetWorldScale(scale.DoubleValue());
    return CreateResult(env, result, env.Null());
}

Napi::Object ATGetTransformOfMap(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    double a = -1;
    int map_id = -1;
    bool result = GetTransformOfMap(x, y, a, map_id);
    Napi::Object object = Napi::Object::New(env);
    object.Set("x", x);
    object.Set("y", y);
    object.Set("a", a);
    object.Set("map_id", map_id);
    return CreateResult(env, result, object);
}

Napi::Object ATGetPositionOfMap(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    int map_id = -1;
    bool result = GetPositionOfMap(x, y, map_id);
    Napi::Object object = Napi::Object::New(env);
    object.Set("x", x);
    object.Set("y", y);
    object.Set("map_id", map_id);
    return CreateResult(env, result, object);
}

Napi::Object ATGetDirection(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a = -1;
    bool result = GetDirection(a);
    return CreateResult(env, result, Napi::Number::New(env, a));
}

Napi::Object ATGetRotation(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a = -1;
    bool result = GetRotation(a);
    return CreateResult(env, result, Napi::Number::New(env, a));
}

Napi::Object ATGetStar(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    bool is_end = false;
    bool result = GetStar(x, y, is_end);
    Napi::Object object = Napi::Object::New(env);
    object.Set("x", x);
    object.Set("y", y);
    object.Set("isEnd", is_end);
    return CreateResult(env, result, object);
}

Napi::Object ATGetStarJson(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char json[1024] = {0};
    bool result = GetStarJson(json);
    return CreateResult(env, result, Napi::String::New(env, json));
}

Napi::Object ATGetUID(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int uid = -1;
    bool result = GetUID(uid);
    return CreateResult(env, result, Napi::Number::New(env, uid));
}

Napi::Object ATGetInfoLoadPicture(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    /// Not implemented
    return CreateResult(env, false, Napi::String::New(env, "\u65b9\u6cd5\u672a\u5b9e\u73b0"));
}

Napi::Object ATGetInfoLoadVideo(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    /// Not implemented
    return CreateResult(env, false, Napi::String::New(env, "\u65b9\u6cd5\u672a\u5b9e\u73b0"));
}

Napi::Object ATDebugCapture(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1)
    {
        bool result = DebugCapture();
        return CreateResult(env, result, Napi::String::New(env, "Capture.png"));
    }
    else
    {
        Napi::String arg_path = info[0].As<Napi::String>();
        const char *path_buff = arg_path.Utf8Value().c_str();
        int path_buff_size = strlen(path_buff);
        bool result = DebugCapturePath(path_buff, path_buff_size);
        return CreateResult(env, result, arg_path);
    }
}

Napi::Number ATGetLastErr(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, GetLastErr());
}

Napi::String ATGetLastErrMsg(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char msg[1024] = {0};
    GetLastErrMsg(msg, 1024);
    return Napi::String::New(env, msg);
}

Napi::String ATGetLastErrJson(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char json[2048] = {0};
    GetLastErrJson(json, 2048);
    return Napi::String::New(env, json);
}

Napi::Object ATGetCompileVersion(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char version[128] = {0};
    GetCompileVersion(version, 128);
    return CreateResult(env, true, Napi::String::New(env, version));
}

Napi::Object ATGetCompileTime(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char time[128] = {0};
    GetCompileTime(time, 128);
    return CreateResult(env, true, Napi::String::New(env, time));
}

Napi::Object ModuleInit(Napi::Env env, Napi::Object exports)
{
    exports.Set("version", Napi::Function::New(env, ATVersion));
    exports.Set("init", Napi::Function::New(env, ATInit));
    exports.Set("uninit", Napi::Function::New(env, ATUninit));
    exports.Set("startServe", Napi::Function::New(env, ATStartServe));
    exports.Set("stopServe", Napi::Function::New(env, ATStopServe));
    exports.Set("setUseBitbltCaptureMode", Napi::Function::New(env, ATSetUseBitbltCaptureMode));
    exports.Set("setUseDx11CaptureMode", Napi::Function::New(env, ATSetUseDx11CaptureMode));
    exports.Set("setHandle", Napi::Function::New(env, ATSetHandle));
    exports.Set("setWorldCenter", Napi::Function::New(env, ATSetWorldCenter));
    exports.Set("setWorldScale", Napi::Function::New(env, ATSetWorldScale));
    exports.Set("getTransformOfMap", Napi::Function::New(env, ATGetTransformOfMap));
    exports.Set("getPositionOfMap", Napi::Function::New(env, ATGetPositionOfMap));
    exports.Set("getDirection", Napi::Function::New(env, ATGetDirection));
    exports.Set("getRotation", Napi::Function::New(env, ATGetRotation));
    exports.Set("getStar", Napi::Function::New(env, ATGetStar));
    exports.Set("getStarJson", Napi::Function::New(env, ATGetStarJson));
    exports.Set("getUID", Napi::Function::New(env, ATGetUID));
    exports.Set("getInfoLoadPicture", Napi::Function::New(env, ATGetInfoLoadPicture));
    exports.Set("getInfoLoadVideo", Napi::Function::New(env, ATGetInfoLoadVideo));
    exports.Set("debugCapture", Napi::Function::New(env, ATDebugCapture));
    // exports.Set("debugCapturePath", Napi::Function::New(env, ATDebugCapturePath));
    exports.Set("getLastErr", Napi::Function::New(env, ATGetLastErr));
    exports.Set("getLastErrMsg", Napi::Function::New(env, ATGetLastErrMsg));
    exports.Set("getLastErrJson", Napi::Function::New(env, ATGetLastErrJson));
    exports.Set("getCompileVersion", Napi::Function::New(env, ATGetCompileVersion));
    exports.Set("getCompileTime", Napi::Function::New(env, ATGetCompileTime));
    return exports;
}

NODE_API_MODULE(addon, ModuleInit)