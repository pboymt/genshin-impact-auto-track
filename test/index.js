const addon = require('../lib/main');

const version = addon.version();
console.log(`DLL version: ${JSON.stringify(version)}`);

const compileVersion = addon.getCompileVersion();
console.log(`Compile version: ${JSON.stringify(compileVersion)}`);

const compileTime = addon.getCompileTime();
console.log(`Compile time: ${JSON.stringify(compileTime)}`);

