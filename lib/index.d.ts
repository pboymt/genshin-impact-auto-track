declare module 'genshin-impact-auto-track' {

    export interface TransformOfMap {
        x: number;
        y: number;
        a: number;
        mapId: number;
    }
    export interface PositionOfMap {
        x: number;
        y: number;
        mapId: number;
    }
    export interface Star {
        x: number;
        y: number;
        isEnd: boolean;
    }
    export interface Info {
        path: string;
        uid: number;
        x: number;
        y: number;
        a: number;
    }
    export interface InfoLoadVideo {
        path: string;
        pathOutFile: string;
    }

    /**
     * 获取 GenshinImpact AutoTrack DLL 版本号，由于上游版本号输出有问题，因此不一定准确。
     * 
     * @returns {string} 版本号。
     */
    export function version(): string;

    /**
     * 初始化运行环境。
     *
     * ### 返回值
     *
     * - `true` 表示初始化完毕。当前处在 **已初始化** 状态。
     * - `false` 表示初始化失败。当前处在 **未初始化** 状态。
     *
     * ### 说明
     *
     * 部分函数需要初始化后才能调用，具体见 [函数手册](#函数手册) 其它函数。
     *
     * 经过简单测试，初始化的过程大概会持续1-10秒，内存占用峰值约为 1 GB，之后稳定在 270 MB 左右。
     *
     * 已经处在 **已初始化** 状态则不会进行任何操作。
     * 
     * @returns {boolean} 是否初始化成功。
     */
    export function init(): boolean;

    /**
     * 卸载初始化时所占用的内存。
     *
     * ### 返回值
     *
     * - `true` 表示卸载成功，所有需要初始化后才能调用的函数此时不能再被调用。当前处在 **未初始化** 状态。
     * - `false` 表示卸载失败。当前处在 **已初始化** 状态。
     *
     * ### 说明
     *
     * 已经处在 **未初始化** 状态则不会进行任何操作。
     * 
     * @returns {boolean} 是否卸载成功。
     */
    export function uninit(): boolean;

    /**
     * 设置原神客户端的窗口句柄。
     *
     * ### 参数
     *
     * - `handle` 原神客户端的窗口句柄。如果提供非零值，则程序不再自动获取窗口句柄，如果提供 `0`，则自动获取。
     *
     * ### 返回值
     *
     * - `true` 表示提供的值是窗口句柄。
     * - `false` 表示提供的值并不是窗口句柄。
     *
     * ### 说明
     *
     * 某些原神数据的获取是基于原神客户端的，因此需要一个客户端的窗口句柄。默认情况下此句柄由程序自动获取，但有可能会因为编码问题或其它未知的原因而获取不到，此时就需要手动指定客户端的窗口句柄。
     *
     * 注意，不论本函数返回何值，`handle` 只要不是 `0`，就会被设置为窗口句柄，并禁止自动获取窗口句柄。
     * 
     * @param {number} hwnd 原神客户端的窗口句柄。
     */
    export function setHandle(hwnd: number): boolean;

    /**
     * 设置映射目标地图坐标系的原点中心所在天理坐标模型中的坐标。
     *
     * ### 参数
     *
     * - `x` 原点在天理坐标模型的横坐标。
     * - `y` 原点在天理坐标模型的纵坐标。
     *
     * ### 返回值
     *
     * - `true` 表示设置成功。
     * - `false` 表示程序出现预料之外的异常（理论上永不出现）。
     *
     * ### 说明
     *
     * 要从天理坐标模型映射至目标地图模型时，将目标地图模型的原点在天理坐标模型的对应坐标传入函数，输出即被转换为该坐标为中心。
     * 
     * @param {number} x 原点在天理坐标模型的横坐标。
     * @param {number} y 原点在天理坐标模型的纵坐标。
     * 
     * @returns {boolean} 是否设置成功。
     */
    export function setWorldCenter(x: number, y: number): boolean;

    /**
     * 设置映射目标地图坐标系缩放系数与所在天理坐标模型缩放系数的的比值。
     *
     * ### 参数
     *
     * - `scale` 放大scale倍即为天理坐标模型缩放系数。
     *
     * ### 返回值
     *
     * - `true` 表示设置成功。
     * - `false` 表示程序出现预料之外的异常（理论上永不出现）。
     *
     * ### 说明
     *
     * 映射目标地图坐标系缩放系数与所在天理坐标模型缩放系数的的比值。
     * 
     * @param {number} scale 放大scale倍即为天理坐标模型缩放系数。
     * 
     * @returns {boolean} 是否设置成功。
     */
    export function setWorldScale(scale: number): boolean;

    /**
     * 获取所在位置的所在地图区域并重映射坐标区域。
     *
     * ### 参数
     *
     * - `x` 获取到的人物的x轴坐标位置。
     * - `y` 获取到的人物的y轴坐标位置。
     * - `mapId` 获取到的人物的所在地图区域。
     *
     * ### 返回值
     *
     * - `true` 表示坐标位置获取成功。
     * - `false` 表示坐标位置获取失败，此时三个参数均不会被改变。
     *
     * ### 说明
     *
     * 地图区域的值的解释
     *
     * | 地图编号 | 含义                     |
     * | -------- | ------------------------ |
     * | `0`      | 提瓦特大陆。             |
     * | `1`      | 渊下宫                   |
     * | `2`      | 地下层岩                 |
     *
     * 无论成功与否都会设置 `LastErr` 值。调用 [`GetLastErr()`](#GetLastErr) 可以获取错误码。
     *
     * 调用本函数前，如果没有初始化过，或最后一次初始化返回失败，则需要调用 [`init()`](#init) 函数进行初始化。
     * 
     * @returns {TransformOfMap} 获取到的人物的所在地图区域。
     */
    export function getTransformOfMap(): TransformOfMap;

    export function getPositionOfMap(): PositionOfMap;
    export function getDirection(): number;
    export function getRotation(): number;
    export function getStar(): Star;
    export function getStarJson(): string;
    export function getUID(): number;
    export function getInfoLoadPicture(path: string): Info;
    export function getInfoLoadVideo(path: string, pathOutFile: string): InfoLoadVideo;
    export function debugCapture(): boolean;
    export function getLastErr(): number;
    export function getLastErrMsg(): string;
}