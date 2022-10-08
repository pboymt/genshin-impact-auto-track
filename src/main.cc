#include <napi.h>
#include "../cvAutoTrack/cvAutoTrack.h"

using namespace Napi;

Napi::String TVersion(const CallbackInfo &info)
{
    Env env = info.Env();
    char version_buff[1024] = {0};
    bool result = verison(version_buff);
    return String::New(env, version_buff);
}

Napi::Boolean TInit(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = init();
    return Boolean::New(env, result);
}

Napi::Boolean TUninit(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = uninit();
    return Boolean::New(env, result);
}

Napi::Boolean TStartServe(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = startServe();
    return Boolean::New(env, result);
}

Napi::Boolean TStopServe(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = stopServe();
    return Boolean::New(env, result);
}

Napi::Boolean TSetUseBitbltCaptureMode(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = SetUseBitbltCaptureMode();
    return Boolean::New(env, result);
}

Napi::Boolean TSetUseDx11CaptureMode(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = SetUseDx11CaptureMode();
    return Boolean::New(env, result);
}

Napi::Boolean TSetHandle(const CallbackInfo &info)
{
    Env env = info.Env();
    long long int handle = info[0].As<Number>().Int64Value();
    bool result = SetHandle(handle);
    return Boolean::New(env, result);
}

Napi::Boolean TSetWorldCenter(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = info[0].As<Number>().DoubleValue();
    double y = info[1].As<Number>().DoubleValue();
    bool result = SetWorldCenter(x, y);
    return Boolean::New(env, result);
}

Napi::Boolean TSetWorldScale(const CallbackInfo &info)
{
    Env env = info.Env();
    double scale = info[0].As<Number>().DoubleValue();
    bool result = SetWorldScale(scale);
    return Boolean::New(env, result);
}

Napi::Object TGetTransformOfMap(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = 0;
    double y = 0;
    double a = 0;
    int mapId = 0;
    bool result = GetTransformOfMap(x, y, a, mapId);
    Object obj = Object::New(env);
    obj.Set("x", Number::New(env, x));
    obj.Set("y", Number::New(env, y));
    obj.Set("a", Number::New(env, a));
    obj.Set("mapId", Number::New(env, mapId));
    return obj;
}

Napi::Object TGetPositionOfMap(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = 0;
    double y = 0;
    int mapId = 0;
    bool result = GetPositionOfMap(x, y, mapId);
    Object obj = Object::New(env);
    obj.Set("x", Number::New(env, x));
    obj.Set("y", Number::New(env, y));
    obj.Set("mapId", Number::New(env, mapId));
    return obj;
}

Napi::Number TGetDirection(const CallbackInfo &info)
{
    Env env = info.Env();
    double a = 0;
    bool result = GetDirection(a);
    return Number::New(env, a);
}

Napi::Number TGetRotation(const CallbackInfo &info)
{
    Env env = info.Env();
    double a = 0;
    bool result = GetRotation(a);
    return Number::New(env, a);
}

Napi::Object TGetStar(const CallbackInfo &info)
{
    Env env = info.Env();
    double x = 0;
    double y = 0;
    bool isEnd = false;
    bool result = GetStar(x, y, isEnd);
    Object obj = Object::New(env);
    obj.Set("x", Number::New(env, x));
    obj.Set("y", Number::New(env, y));
    obj.Set("isEnd", Boolean::New(env, isEnd));
    return obj;
}

Napi::String TGetStarJson(const CallbackInfo &info)
{
    Env env = info.Env();
    char star_buff[2048] = {0};
    bool result = GetStarJson(star_buff);
    return String::New(env, star_buff);
}

Napi::Number TGetUID(const CallbackInfo &info)
{
    Env env = info.Env();
    int uid = 0;
    bool result = GetUID(uid);
    return Number::New(env, uid);
}

Napi::Object TGetInfoLoadPicture(const CallbackInfo &info)
{
    Env env = info.Env();
    const char *v_path = info[0].As<String>().Utf8Value().c_str();
    char *path = const_cast<char *>(v_path);
    int uid = 0;
    double x = 0;
    double y = 0;
    double a = 0;
    bool result = GetInfoLoadPicture(path, uid, x, y, a);
    Object obj = Object::New(env);
    obj.Set("path", String::New(env, path));
    obj.Set("uid", Number::New(env, uid));
    obj.Set("x", Number::New(env, x));
    obj.Set("y", Number::New(env, y));
    obj.Set("a", Number::New(env, a));
    return obj;
}

Napi::Object TGetInfoLoadVideo(const CallbackInfo &info)
{
    Env env = info.Env();
    const char *v_path = info[0].As<String>().Utf8Value().c_str();
    char *path = const_cast<char *>(v_path);
    const char *v_pathOutFile = info[1].As<String>().Utf8Value().c_str();
    char *pathOutFile = const_cast<char *>(v_pathOutFile);
    bool result = GetInfoLoadVideo(path, pathOutFile);
    Object obj = Object::New(env);
    obj.Set("path", String::New(env, path));
    obj.Set("pathOutFile", String::New(env, pathOutFile));
    return obj;
}

Napi::Boolean TDebugCapture(const CallbackInfo &info)
{
    Env env = info.Env();
    bool result = DebugCapture();
    return Boolean::New(env, result);
}

Napi::Number TGetLastErr(const CallbackInfo &info)
{
    Env env = info.Env();
    int err = GetLastErr();
    return Number::New(env, err);
}

Napi::String TGetLastErrMsg(const CallbackInfo &info)
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