#include <napi.h>
#include "../cvAutoTrack/cvAutoTrack.h"

using namespace Napi;

Napi::Value TVersion(const CallbackInfo &info)
{
    Env env = info.Env();
    char version_buff[1024] = {0};
    bool result = verison(version_buff);
    return String::New(env, version_buff);
}

Napi::Value TInit(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = init();
    return Boolean::New(env, result);
}

Napi::Value TUninit(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = uninit();
    return Boolean::New(env, result);
}

Napi::Value TStartServe(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = startServe();
    if (result)
    {
        return Boolean::New(env, result);
    }
    else
    {
        Napi::Error::New(env, "Run function 'startServe' failed").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TStopServe(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = stopServe();
    if (result)
    {
        return Boolean::New(env, result);
    }
    else
    {
        Napi::Error::New(env, "Run function 'stopServe' failed").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetUseBitbltCaptureMode(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = SetUseBitbltCaptureMode();
    if (result)
    {
        return Boolean::New(env, true);
    }
    else
    {
        Napi::Error::New(env, "Run function 'SetUseBitbltCaptureMode' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetUseDx11CaptureMode(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = SetUseDx11CaptureMode();
    if (result)
    {
        return Boolean::New(env, true);
    }
    else
    {
        Napi::Error::New(env, "Run function 'SetUseDx11CaptureMode' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetHandle(const CallbackInfo &info)
{
    Env env = info.Env();
    long long int handle = info[0].As<Number>().Int64Value();
    bool result = SetHandle(handle);
    if (result)
    {
        return Boolean::New(env, true);
    }
    else
    {
        Napi::Error::New(env, "Run function 'SetHandle' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetWorldCenter(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = info[0].As<Number>().DoubleValue();
    double y = info[1].As<Number>().DoubleValue();
    bool result = SetWorldCenter(x, y);
    if (result)
    {
        return Boolean::New(env, true);
    }
    else
    {
        Napi::Error::New(env, "Run function 'SetWorldCenter' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetWorldScale(const CallbackInfo &info)
{
    Env env = info.Env();
    double scale = info[0].As<Number>().DoubleValue();
    bool result = SetWorldScale(scale);
    if (result)
    {
        return Boolean::New(env, true);
    }
    else
    {
        Napi::Error::New(env, "Run function 'SetWorldScale' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetTransformOfMap(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = -1;
    double y = -1;
    double a = -1;
    int mapId = -1;
    bool result = GetTransformOfMap(x, y, a, mapId);
    if (result)
    {
        Object obj = Object::New(env);
        obj.Set("x", Number::New(env, x));
        obj.Set("y", Number::New(env, y));
        obj.Set("a", Number::New(env, a));
        obj.Set("mapId", Number::New(env, mapId));
        return obj;
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetTransformOfMap' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetPositionOfMap(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = -1;
    double y = -1;
    int mapId = -1;
    bool result = GetPositionOfMap(x, y, mapId);
    if (result)
    {
        Object obj = Object::New(env);
        obj.Set("x", Number::New(env, x));
        obj.Set("y", Number::New(env, y));
        obj.Set("mapId", Number::New(env, mapId));
        return obj;
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetPositionOfMap' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetDirection(const CallbackInfo &info)
{
    Env env = info.Env();
    double a = -1;
    bool result = GetDirection(a);
    if (result)
    {
        return Number::New(env, a);
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetDirection' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetRotation(const CallbackInfo &info)
{
    Env env = info.Env();
    double a = -1;
    bool result = GetRotation(a);
    if (result)
    {
        return Number::New(env, a);
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetRotation' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetStar(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = -1;
    double y = -1;
    bool isEnd = false;
    bool result = GetStar(x, y, isEnd);
    if (result)
    {
        Object obj = Object::New(env);
        obj.Set("x", Number::New(env, x));
        obj.Set("y", Number::New(env, y));
        obj.Set("isEnd", Boolean::New(env, isEnd));
        return obj;
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetStar' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetStarJson(const CallbackInfo &info)
{
    Env env = info.Env();
    char star_buff[2048] = {0};
    bool result = GetStarJson(star_buff);
    if (result)
    {
        return String::New(env, star_buff);
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetStarJson' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetUID(const CallbackInfo &info)
{
    Env env = info.Env();
    int uid = -1;
    bool result = GetUID(uid);
    if (result)
    {
        return Number::New(env, uid);
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetUID' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetInfoLoadPicture(const CallbackInfo &info)
{
    Env env = info.Env();
    const char *v_path = info[0].As<String>().Utf8Value().c_str();
    char *path = const_cast<char *>(v_path);
    int uid = -1;
    int &uid_ref = uid;
    double x = -1;
    double &x_ref = x;
    double y = -1;
    double &y_ref = y;
    double a = -1;
    double &a_ref = a;
    bool result = GetInfoLoadPicture(path, uid_ref, x_ref, y_ref, a_ref);
    if (result)
    {
        Object obj = Object::New(env);
        obj.Set("path", String::New(env, path));
        obj.Set("uid", Number::New(env, uid));
        obj.Set("x", Number::New(env, x));
        obj.Set("y", Number::New(env, y));
        obj.Set("a", Number::New(env, a));
        return obj;
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetInfoLoadPicture' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetInfoLoadVideo(const CallbackInfo &info)
{
    Env env = info.Env();
    const char *v_path = info[0].As<String>().Utf8Value().c_str();
    char *path = const_cast<char *>(v_path);
    const char *v_pathOutFile = info[1].As<String>().Utf8Value().c_str();
    char *pathOutFile = const_cast<char *>(v_pathOutFile);
    bool result = GetInfoLoadVideo(path, pathOutFile);
    if (result)
    {
        Object obj = Object::New(env);
        obj.Set("path", String::New(env, path));
        obj.Set("pathOutFile", String::New(env, pathOutFile));
        return obj;
    }
    else
    {
        Napi::Error::New(env, "Run function 'GetInfoLoadVideo' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TDebugCapture(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = DebugCapture();
    if (result)
    {
        return Boolean::New(env, result);
    }
    else
    {
        Napi::Error::New(env, "Run function 'DebugCapture' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetLastErr(const CallbackInfo &info)
{
    Env env = info.Env();
    int err = GetLastErr();
    return Number::New(env, err);
}

Napi::Value TGetLastErrMsg(const CallbackInfo &info)
{
    Env env = info.Env();
    int buff_size = 2048;
    char msg_buff[2048] = {0};
    GetLastErrMsg(msg_buff, buff_size);
    return String::New(env, msg_buff);
}

Object ModuleInit(Env env, Object exports)
{
    exports.Set(String::New(env, "version"), Function::New(env, TVersion));
    exports.Set(String::New(env, "init"), Function::New(env, TInit));
    exports.Set(String::New(env, "uninit"), Function::New(env, TUninit));
    exports.Set(String::New(env, "startServe"), Function::New(env, TStartServe));
    exports.Set(String::New(env, "stopServe"), Function::New(env, TStopServe));
    exports.Set(String::New(env, "setUseBitbltCaptureMode"), Function::New(env, TSetUseBitbltCaptureMode));
    exports.Set(String::New(env, "setUseDx11CaptureMode"), Function::New(env, TSetUseDx11CaptureMode));
    exports.Set(String::New(env, "setHandle"), Function::New(env, TSetHandle));
    exports.Set(String::New(env, "setWorldCenter"), Function::New(env, TSetWorldCenter));
    exports.Set(String::New(env, "setWorldScale"), Function::New(env, TSetWorldScale));
    exports.Set(String::New(env, "getTransformOfMap"), Function::New(env, TGetTransformOfMap));
    exports.Set(String::New(env, "getPositionOfMap"), Function::New(env, TGetPositionOfMap));
    exports.Set(String::New(env, "getDirection"), Function::New(env, TGetDirection));
    exports.Set(String::New(env, "getRotation"), Function::New(env, TGetRotation));
    exports.Set(String::New(env, "getStar"), Function::New(env, TGetStar));
    exports.Set(String::New(env, "getStarJson"), Function::New(env, TGetStarJson));
    exports.Set(String::New(env, "getUID"), Function::New(env, TGetUID));
    exports.Set(String::New(env, "getInfoLoadPicture"), Function::New(env, TGetInfoLoadPicture));
    exports.Set(String::New(env, "getInfoLoadVideo"), Function::New(env, TGetInfoLoadVideo));
    exports.Set(String::New(env, "debugCapture"), Function::New(env, TDebugCapture));
    exports.Set(String::New(env, "getLastErr"), Function::New(env, TGetLastErr));
    exports.Set(String::New(env, "getLastErrMsg"), Function::New(env, TGetLastErrMsg));
    return exports;
}

NODE_API_MODULE(addon, ModuleInit)