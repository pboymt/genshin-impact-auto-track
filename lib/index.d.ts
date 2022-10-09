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
     * 注意，不论本函数返回何值，`hwnd` 只要不是 `0`，就会被设置为窗口句柄，并禁止自动获取窗口句柄。
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
     * 获取当前人物所在位置以及角度（箭头朝向）。
     *
     * ### 返回值
     *
     * 返回一个对象，包含以下属性：
     * - `x` 获取到的人物的x轴坐标位置。
     * - `y` 获取到的人物的y轴坐标位置。
     * - `a` 获取到的人物的角度（箭头朝向）。
     *
     * ### 说明
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @returns {TransformOfMap} 获取到的人物的所在地图区域。
     */
    export function getTransformOfMap(): TransformOfMap;

    /**
     * 获取所在位置的所在地图区域并重映射坐标区域。
     *
     * ### 返回值
     *
     * 返回一个对象，包含以下属性：
     * - `x` 获取到的人物的x轴坐标位置。
     * - `y` 获取到的人物的y轴坐标位置。
     * - `mapId` 获取到的人物的所在地图区域。
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
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @returns {TransformOfMap} 获取到的人物的所在地图区域。
     */
    export function getPositionOfMap(): PositionOfMap;

    /**
     * 获取当前角度（箭头朝向）。
     * 
     * @returns {number} 获取到的人物的角度（箭头朝向）。
     * 
     * ### 说明
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     */
    export function getDirection(): number;

    /**
     * 获取当前视角方位（视角朝向）。
     * 
     * ### 说明
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @returns {number} 获取到的人物的视角方位（视角朝向）。
     */
    export function getRotation(): number;

    export function getStar(): Star;
    export function getStarJson(): string;

    /**
     * 获取在屏幕右下角显示的玩家的UID。
     * 
     * ### 说明
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @returns {number} 获取到的玩家的UID。
     */
    export function getUID(): number;

    /**
     * 获取本地图片中的UID、当前人物所在位置以及角度（箭头朝向）。
     * 
     * ### 参数
     * 
     * - `path` 输入图片文件路径
     * 
     * ### 返回值
     * 
     * 返回一个对象，包含以下属性：
     * - `uid` 获取到的玩家的UID。
     * - `x` 获取到的人物的x轴坐标位置。
     * - `y` 获取到的人物的y轴坐标位置。
     * - `a` 获取到的人物的角度（箭头朝向）。
     * 
     * ### 说明
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @param path 输入图片文件路径
     */
    export function getInfoLoadPicture(path: string): Info;

    /**
     * 获取本地视频中的UID、当前人物所在位置以及角度（箭头朝向）并保存至文本中。
     * 
     * ### 参数
     * - `path` 输入视频文件路径
     * - `pathOutFile` 输出的路径数据保存文件路径
     * 
     * ### 返回值
     * 
     * 返回一个对象，包含以下属性：
     * - `path` 输入视频文件路径
     * - `pathOutFile` 输出的路径数据保存文件路径
     * 
     * ### 说明
     * 
     * 写入文本格式如下：
     * ```
     * | int Time | int uid | double x | double y | double a | 
     * ```
     * 
     * **注意**：暂未对错误进行处理，如果获取失败，可能会报错。
     * 
     * @param path 
     * @param pathOutFile 
     */
    export function getInfoLoadVideo(path: string, pathOutFile: string): InfoLoadVideo;

    export function debugCapture(): boolean;

    /**
     * 获取最后设置的错误码。
     * 
     * ### 返回值
     * 
     * 返回一个整数，表示错误码。错误码含义如下：
     * 
     * | 错误码 | 含义                                     | 可能的原因 |
     * | ------ | ---------------------------------------- | ---------- |
     * | `0`    | 执行成功/正常退出。                      |            |
     * | `1`    | 未初始化（当前处在 **未初始化** 状态）。 |            |
     * | `2`    | 未能找到原神窗口句柄。                   |            |
     * | `3`    | 窗口画面为空。                           |            |
     * | `4`    | 未能匹配到特征点。                       |            |
     * | `5`    | 原神小地图区域为空或者区域长宽小于60px。 |            |
     * | `6`    | 未能匹配到派蒙。                         |            |
     * | `7`    | 特征点数组访问越界，是个bug。            |            |
     * | `8`    | 未能在UID区域检测到有效UID。             |            |
     * | `9`    | 提取小箭头特征误差过大。                 |            |
     * | `10`   | 无效句柄或指定句柄所指向窗口不存在。     |            |
     * | `11`   | 未能取到小箭头区域。                     |            |
     * | `12`   | 窗口句柄失效。                           |            |
     * | `13`   | 窗口大小小于480px * 360px。              |            |
     * ### 说明
     *
     * 由于函数成功执行后可能不会将错误码设为 `0` ，以及一些函数不会设置错误码，因此取出的错误码不一定代表前一条函数产生/引发的错误。
     * 
     * @returns {number} 获取到的错误码。
     */
    export function getLastErr(): number;

    export function getLastErrMsg(): string;
}