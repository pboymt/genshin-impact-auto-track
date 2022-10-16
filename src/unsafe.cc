#include "unsafe.h"

// using namespace Napi;

Napi::Error HandleError(Napi::Env env, const char *func_name)
{
    int error_code = GetLastErr();
    char msg_buff[1024];
    GetLastErrJson(msg_buff, 1024);
    // Combine the error code and message into a single string
    // std::string error_msg = std::string("Error in '") + std::string(func_name) + std::string("' : \n") + std::string(msg_buff);
    // Convert from  to UTF-8
    return Napi::Error::New(env, msg_buff);
}

Napi::Value TVersion(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char version_buff[1024] = {0};
    bool result = verison(version_buff);
    return Napi::String::New(env, version_buff);
}

Napi::Value TInit(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = init();
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "init");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'init' failed").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
}

Napi::Value TUninit(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = uninit();
    return Napi::Boolean::New(env, result);
}

Napi::Value TStartServe(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = startServe();
    if (result)
    {
        return Napi::Boolean::New(env, result);
    }
    else
    {
        auto error = HandleError(env, "startServe");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'startServe' failed").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TStopServe(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = stopServe();
    if (result)
    {
        return Napi::Boolean::New(env, result);
    }
    else
    {
        auto error = HandleError(env, "stopServe");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'stopServe' failed").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetUseBitbltCaptureMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = SetUseBitbltCaptureMode();
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "setUseBitbltCaptureMode");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'SetUseBitbltCaptureMode' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetUseDx11CaptureMode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = SetUseDx11CaptureMode();
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "setUseDx11CaptureMode");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'SetUseDx11CaptureMode' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetHandle(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    long long int handle = info[0].As<Napi::Number>().Int64Value();
    bool result = SetHandle(handle);
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "setHandle");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'SetHandle' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetWorldCenter(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = info[0].As<Napi::Number>().DoubleValue();
    double y = info[1].As<Napi::Number>().DoubleValue();
    bool result = SetWorldCenter(x, y);
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "setWorldCenter");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'SetWorldCenter' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TSetWorldScale(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double scale = info[0].As<Napi::Number>().DoubleValue();
    bool result = SetWorldScale(scale);
    if (result)
    {
        return Napi::Boolean::New(env, true);
    }
    else
    {
        auto error = HandleError(env, "setWorldScale");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'SetWorldScale' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetTransformOfMap(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    double a = -1;
    int mapId = -1;
    bool result = GetTransformOfMap(x, y, a, mapId);
    // if (result)
    // {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("x", Napi::Number::New(env, x));
    obj.Set("y", Napi::Number::New(env, y));
    obj.Set("a", Napi::Number::New(env, a));
    obj.Set("mapId", Napi::Number::New(env, mapId));
    return obj;
    // }
    // else
    // {
    //     auto error = HandleError(env, "getTransformOfMap");
    //     error.ThrowAsJavaScriptException();
    //     //  Napi::Error::New(env, "Run function 'GetTransformOfMap' failed.").ThrowAsJavaScriptException();
    //     return env.Undefined();
    // }
}

Napi::Value TGetPositionOfMap(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    int mapId = -1;
    bool result = GetPositionOfMap(x, y, mapId);
    if (result)
    {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("x", Napi::Number::New(env, x));
        obj.Set("y", Napi::Number::New(env, y));
        obj.Set("mapId", Napi::Number::New(env, mapId));
        return obj;
    }
    else
    {
        auto error = HandleError(env, "getPositionOfMap");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetPositionOfMap' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetDirection(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a = -1;
    bool result = GetDirection(a);
    if (result)
    {
        return Napi::Number::New(env, a);
    }
    else
    {
        auto error = HandleError(env, "getDirection");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetDirection' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetRotation(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a = -1;
    bool result = GetRotation(a);
    if (result)
    {
        return Napi::Number::New(env, a);
    }
    else
    {
        auto error = HandleError(env, "getRotation");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetRotation' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetStar(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double x = -1;
    double y = -1;
    bool isEnd = false;
    bool result = GetStar(x, y, isEnd);
    if (result)
    {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("x", Napi::Number::New(env, x));
        obj.Set("y", Napi::Number::New(env, y));
        obj.Set("isEnd", Napi::Boolean::New(env, isEnd));
        return obj;
    }
    else
    {
        auto error = HandleError(env, "getStar");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetStar' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetStarJson(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    char star_buff[2048] = {0};
    bool result = GetStarJson(star_buff);
    if (result)
    {
        return Napi::String::New(env, star_buff);
    }
    else
    {
        auto error = HandleError(env, "getStarJson");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetStarJson' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetUID(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int uid = -1;
    bool result = GetUID(uid);
    if (result)
    {
        return Napi::Number::New(env, uid);
    }
    else
    {
        auto error = HandleError(env, "getUID");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetUID' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetInfoLoadPicture(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    const char *v_path = info[0].As<Napi::String>().Utf8Value().c_str();
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
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("path", Napi::String::New(env, path));
        obj.Set("uid", Napi::Number::New(env, uid));
        obj.Set("x", Napi::Number::New(env, x));
        obj.Set("y", Napi::Number::New(env, y));
        obj.Set("a", Napi::Number::New(env, a));
        return obj;
    }
    else
    {
        auto error = HandleError(env, "getInfoLoadPicture");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetInfoLoadPicture' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetInfoLoadVideo(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    const char *v_path = info[0].As<Napi::String>().Utf8Value().c_str();
    char *path = const_cast<char *>(v_path);
    const char *v_pathOutFile = info[1].As<Napi::String>().Utf8Value().c_str();
    char *pathOutFile = const_cast<char *>(v_pathOutFile);
    bool result = GetInfoLoadVideo(path, pathOutFile);
    if (result)
    {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("path", Napi::String::New(env, path));
        obj.Set("pathOutFile", Napi::String::New(env, pathOutFile));
        return obj;
    }
    else
    {
        auto error = HandleError(env, "getInfoLoadVideo");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'GetInfoLoadVideo' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TDebugCapture(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    bool result = DebugCapture();
    if (result)
    {
        return Napi::Boolean::New(env, result);
    }
    else
    {
        auto error = HandleError(env, "debugCapture");
        error.ThrowAsJavaScriptException();
        //  Napi::Error::New(env, "Run function 'DebugCapture' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetLastErr(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int err = GetLastErr();
    return Napi::Number::New(env, err);
}

Napi::Value TGetLastErrMsg(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int buff_size = 2048;
    char msg_buff[2048] = {0};
    GetLastErrMsg(msg_buff, buff_size);
    return Napi::String::New(env, msg_buff);
}

Napi::Value TGetCompileVersion(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int buff_size = 2048;
    char msg_buff[2048] = {0};
    bool result = GetCompileVersion(msg_buff, buff_size);
    if (result)
    {
        return Napi::String::New(env, msg_buff);
    }
    else
    {
        auto error = HandleError(env, "getCompileVersion");
        error.ThrowAsJavaScriptException();
        ////  Napi::Error::New(env, "Run function 'GetCompileVersion' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

Napi::Value TGetCompileTime(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int buff_size = 1024;
    char msg_buff[1024] = {0};
    bool result = GetCompileTime(msg_buff, buff_size);
    if (result)
    {
        return Napi::String::New(env, msg_buff);
    }
    else
    {
        auto error = HandleError(env, "getCompileTime");
        error.ThrowAsJavaScriptException();
        ////  Napi::Error::New(env, "Run function 'GetCompileTime' failed.").ThrowAsJavaScriptException();
        return env.Undefined();
    }
}

// Napi::Object ModuleInit(Env env, Napi::Object exports)
Napi::Object ModuleUnsafeInit(Napi::Env env)
{
    Napi::Object exports;
    exports.Set(Napi::String::New(env, "version"), Napi::Function::New(env, TVersion));
    exports.Set(Napi::String::New(env, "init"), Napi::Function::New(env, TInit));
    exports.Set(Napi::String::New(env, "uninit"), Napi::Function::New(env, TUninit));
    exports.Set(Napi::String::New(env, "startServe"), Napi::Function::New(env, TStartServe));
    exports.Set(Napi::String::New(env, "stopServe"), Napi::Function::New(env, TStopServe));
    exports.Set(Napi::String::New(env, "setUseBitbltCaptureMode"), Napi::Function::New(env, TSetUseBitbltCaptureMode));
    exports.Set(Napi::String::New(env, "setUseDx11CaptureMode"), Napi::Function::New(env, TSetUseDx11CaptureMode));
    exports.Set(Napi::String::New(env, "setHandle"), Napi::Function::New(env, TSetHandle));
    exports.Set(Napi::String::New(env, "setWorldCenter"), Napi::Function::New(env, TSetWorldCenter));
    exports.Set(Napi::String::New(env, "setWorldScale"), Napi::Function::New(env, TSetWorldScale));
    exports.Set(Napi::String::New(env, "getTransformOfMap"), Napi::Function::New(env, TGetTransformOfMap));
    exports.Set(Napi::String::New(env, "getPositionOfMap"), Napi::Function::New(env, TGetPositionOfMap));
    exports.Set(Napi::String::New(env, "getDirection"), Napi::Function::New(env, TGetDirection));
    exports.Set(Napi::String::New(env, "getRotation"), Napi::Function::New(env, TGetRotation));
    exports.Set(Napi::String::New(env, "getStar"), Napi::Function::New(env, TGetStar));
    exports.Set(Napi::String::New(env, "getStarJson"), Napi::Function::New(env, TGetStarJson));
    exports.Set(Napi::String::New(env, "getUID"), Napi::Function::New(env, TGetUID));
    exports.Set(Napi::String::New(env, "getInfoLoadPicture"), Napi::Function::New(env, TGetInfoLoadPicture));
    exports.Set(Napi::String::New(env, "getInfoLoadVideo"), Napi::Function::New(env, TGetInfoLoadVideo));
    exports.Set(Napi::String::New(env, "debugCapture"), Napi::Function::New(env, TDebugCapture));
    exports.Set(Napi::String::New(env, "getLastErr"), Napi::Function::New(env, TGetLastErr));
    exports.Set(Napi::String::New(env, "getLastErrMsg"), Napi::Function::New(env, TGetLastErrMsg));
    exports.Set(Napi::String::New(env, "getCompileVersion"), Napi::Function::New(env, TGetCompileVersion));
    exports.Set(Napi::String::New(env, "getCompileTime"), Napi::Function::New(env, TGetCompileTime));
    return exports;
}

// NODE_API_MODULE(addon, ModuleInit)