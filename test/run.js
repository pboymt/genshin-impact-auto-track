const { setTimeout } = require('timers/promises');
const addon = require('../lib');

const version = addon.version();
console.log(`DLL version: ${version}`);

const compileVersion = addon.getCompileVersion();
console.log(`Compile version: ${compileVersion}`);

const compileTime = addon.getCompileTime();
console.log(`Compile time: ${compileTime}`);

if (process.argv.includes('--test')) {
    process.exit(0);
}

process.on('beforeExit', () => {
    addon.uninit();
});

(async () => {

    const inited = addon.init();

    if (!inited) {
        console.log('Failed to init addon');
        return;
    }

    // addon.setUseDx11CaptureMode();
    addon.setHandle(0);
    await setTimeout(3000);

    while (true) {
        try {
            console.clear();
            const uid = addon.getUID();
            const star = addon.getStarJson();
            const pos = addon.getTransformOfMap();
            console.log(`UID: ${uid}`);
            console.log(`Star: ${star}`);
            console.log(pos);
        } catch (error) {
            console.log(error);
            console.log(addon.getLastErrMsg());
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
