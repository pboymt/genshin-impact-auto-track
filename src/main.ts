import binary from '@mapbox/node-pre-gyp';
import path from 'node:path';

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

    export function version(): Result<string>;
    export function init(): Result;
    export function uninit(): Result;
    export function startServe(): Result;
    export function stopServe(): Result;
    export function setUseBitbltCaptureMode(): Result;
    export function setUseDx11CaptureMode(): Result;
    export function setHandle(handle: number): Result;
    export function setWorldCenter(x: number, y: number): Result;
    export function setWorldScale(scale: number): Result;
    export function getTransformOfMap(): Result<TransformOfMap>;
    export function getPositionOfMap(): Result<PositionOfMap>;
    export function getDirection(): Result<number>;
    export function getRotation(): Result<number>;
    export function getStar(): Result<Star>;
    export function getStarJson(): Result<string>;
    export function getUID(): Result<number>;
    export function getInfoLoadPicture(): Result;
    export function getInfoLoadVideo(): Result;
    export function debugCapture(path?: string): Result<string>;
    export function getLastErr(): number;
    export function getLastErrMsg(): string;
    export function getLastErrJson(): string;
    export function getCompileVersion(): Result<string>;
    export function getCompileTime(): Result<string>;
}

const binding_path = binary.find(path.resolve(path.join(__dirname, '../package.json')));
const binding: typeof GenshinImpactAutoTrack = require(binding_path);

export = binding;