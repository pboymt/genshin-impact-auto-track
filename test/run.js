const { setTimeout } = require('timers/promises');
const addon = require('..');

const version = addon.version();
console.log(`DLL version:`);
console.log(version);

const compileVersion = addon.getCompileVersion();
console.log(`Compile version:`);
console.log(compileVersion);

const compileTime = addon.getCompileTime();
console.log(`Compile time:`);
console.log(compileTime);

if (process.argv.includes('--test')) {
    process.exit(0);
}

process.on('beforeExit', () => {
    addon.uninit();
});

function testGetUID() {
    try {
        const uid = addon.getUID();
        console.log(`UID:`);
        console.log(uid);
    } catch (e) {
        console.log(e);
    }
}

function testGetStarJson() {
    try {
        const starJson = addon.getStarJson();
        console.log(`StarJson:`);
        console.log(starJson);
    } catch (e) {
        console.log(e);
    }
}

function testGetTransformOfMap() {
    try {
        const transformOfMap = addon.getPositionOfMap();
        console.log(`TransformOfMap:`);
        console.log(transformOfMap);
    } catch (e) {
        console.log(e);
    }
}

function testDebugCapture() {
    try {
        const result = addon.debugCapture();
        console.log(`DebugCapture:`);
        console.log(result);
    } catch (e) {
        console.log(e);
    }
}

(async () => {

    const inited = addon.init();

    if (!inited) {
        console.log('Failed to init addon');
        return;
    }

    addon.setUseDx11CaptureMode();
    // addon.setHandle(0);
    await setTimeout(2000);

    while (true) {
        try {
            // console.clear();
            console.log(`----------------------------------------`);
            console.log(new Date().toLocaleString());
            testGetUID();
            testGetStarJson();
            testGetTransformOfMap();
            testDebugCapture();
        } catch (error) {
            console.log(error.message);
            // console.log(addon.getLastErrMsg());
        }
        await setTimeout(1000);
    }

})().catch((err) => {
    console.log(err);
    console.log(addon.getLastErr());
    console.log(addon.getLastErrMsg());

}).finally(() => {
    addon.uninit();
});
