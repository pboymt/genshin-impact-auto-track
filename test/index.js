const addon = require('../lib');

const version = addon.version();
console.log(`DLL version: ${version}`);

const compileVersion = addon.getCompileVersion();
console.log(`Compile version: ${compileVersion}`);

const compileTime = addon.getCompileTime();
console.log(`Compile time: ${compileTime}`);