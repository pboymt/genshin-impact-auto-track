"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
const node_pre_gyp_1 = __importDefault(require("@mapbox/node-pre-gyp"));
const node_path_1 = __importDefault(require("node:path"));
const binding_path = node_pre_gyp_1.default.find(node_path_1.default.resolve(node_path_1.default.join(__dirname, '../package.json')));
const binding = require(binding_path);
module.exports = binding;
