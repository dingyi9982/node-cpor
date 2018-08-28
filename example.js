'use strict';

var fs = require('fs');

module.exports = require('bindings')('cpor.node');

let CporVerify = module.exports.CporVerify;

// setTimeout(() => {
//     CporChallenge('/Users/dingyi/10m.data', '/tmp/abcdefg.key', 
//               '/tmp/abcdefg.t', '/tmp/abcdefg.tag', 80, 4096);
// }, 10000);

let key_data = fs.readFileSync('/tmp/abcdefg.key', 'latin1');
let t_data = fs.readFileSync('/tmp/abcdefg.t', 'latin1');
let tag_data = fs.readFileSync('/tmp/abcdefg.tag', 'latin1');

let success = CporVerify('/Users/dingyi/10兆.data', key_data, t_data, tag_data, 80, 4096);
if(success == 1) {
    console.log('Verified!');
} else if(success == 0) {
    console.log('Cheating!');
} else {
    console.log('Error!');
}
