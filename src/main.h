#include <napi.h>
#include "../cvAutoTrack/cvAutoTrack.h"

Napi::Object CreateResult(Napi::Env env, bool success, Napi::Value value);

Napi::Object ATVersion(const Napi::CallbackInfo& info);

Napi::Object ATInit(const Napi::CallbackInfo& info);

Napi::Object ATUninit(const Napi::CallbackInfo& info);

Napi::Object ATStartServe(const Napi::CallbackInfo& info);

Napi::Object ATStopServe(const Napi::CallbackInfo& info);

Napi::Object ATSetUseBitbltCaptureMode(const Napi::CallbackInfo& info);

Napi::Object ATSetUseDx11CaptureMode(const Napi::CallbackInfo& info);

Napi::Object ATSetHandle(const Napi::CallbackInfo& info);

Napi::Object ATSetWorldCenter(const Napi::CallbackInfo& info);

Napi::Object ATSetWorldScale(const Napi::CallbackInfo& info);

Napi::Object ATGetTransformOfMap(const Napi::CallbackInfo& info);

Napi::Object ATGetPositionOfMap(const Napi::CallbackInfo& info);

Napi::Object ATGetDirection(const Napi::CallbackInfo& info);

Napi::Object ATGetRotation(const Napi::CallbackInfo& info);

Napi::Object ATGetStar(const Napi::CallbackInfo& info);

Napi::Object ATGetStarJson(const Napi::CallbackInfo& info);

Napi::Object ATGetUID(const Napi::CallbackInfo& info);

Napi::Object ATGetInfoLoadPicture(const Napi::CallbackInfo& info);

Napi::Object ATGetInfoLoadVideo(const Napi::CallbackInfo& info);

Napi::Object ATDebugCapture(const Napi::CallbackInfo& info);

// Napi::Object ATDebugCapturePath(const Napi::CallbackInfo& info);

Napi::Number ATGetLastErr(const Napi::CallbackInfo& info);

Napi::String ATGetLastErrMsg(const Napi::CallbackInfo& info);

Napi::String ATGetLastErrJson(const Napi::CallbackInfo& info);

Napi::Object ATGetCompileVersion(const Napi::CallbackInfo& info);

Napi::Object ATGetCompileTime(const Napi::CallbackInfo& info);
