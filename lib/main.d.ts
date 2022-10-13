declare namespace GenshinImpactAutoTrack {
    interface Result<T = unknown> {
        code: number;
        msg: string;
        data: T;
    }
    interface TransformOfMap {
        x: number;
        y: number;
        a: number;
        mapId: number;
    }
    interface PositionOfMap {
        x: number;
        y: number;
        mapId: number;
    }
    interface Star {
        x: number;
        y: number;
        isEnd: boolean;
    }
    function version(): Result<string>;
    function init(): Result;
    function uninit(): Result;
    function startServe(): Result;
    function stopServe(): Result;
    function setUseBitbltCaptureMode(): Result;
    function setUseDx11CaptureMode(): Result;
    function setHandle(handle: number): Result;
    function setWorldCenter(x: number, y: number): Result;
    function setWorldScale(scale: number): Result;
    function getTransformOfMap(): Result<TransformOfMap>;
    function getPositionOfMap(): Result<PositionOfMap>;
    function getDirection(): Result<number>;
    function getRotation(): Result<number>;
    function getStar(): Result<Star>;
    function getStarJson(): Result<string>;
    function getUID(): Result<number>;
    function getInfoLoadPicture(): Result;
    function getInfoLoadVideo(): Result;
    function debugCapture(path?: string): Result<string>;
    function getLastErr(): number;
    function getLastErrMsg(): string;
    function getLastErrJson(): string;
    function getCompileVersion(): Result<string>;
    function getCompileTime(): Result<string>;
}
declare const binding: typeof GenshinImpactAutoTrack;
export = binding;
//# sourceMappingURL=main.d.ts.map