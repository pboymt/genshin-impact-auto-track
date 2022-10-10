const { setTimeout } = require('timers/promises');
const addon = require('..');

console.log(addon.version());

process.on('beforeExit', () => {
    addon.uninit();
});

(async () => {

    const inited = addon.init();

    if (!inited) {
        console.log('Failed to init addon');
        return;
    }

    addon.setUseDx11CaptureMode();

    await setTimeout(3000);

    while (true) {
        const star = addon.getDirection();
        console.log(star);
    }

})().catch((err) => {
    console.error(err);
    console.log(addon.getLastErr());
    console.log(addon.getLastErrMsg());

    addon.debugCapture();

}).finally(() => {
    addon.uninit();
});
