const { setTimeout } = require('timers/promises');
const addon = require('../lib/main');

(async () => {

    await setTimeout(4000);

    // addon.setUseDx11CaptureMode();

    const result = addon.debugCapture();

    console.log(result);

})();