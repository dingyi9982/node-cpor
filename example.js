'use strict';

var fs = require('fs');
const http = require('http');
const BufferHelper = require('bufferhelper');
const iconvlite = require('iconv-lite');
const Cpor = require('bindings')('cpor.node');
// module.exports = require('bindings')('cpor.node');
// let CporVerify = module.exports.CporVerify;

// setTimeout(() => {
//     CporChallenge('/Users/dingyi/10m.data', '/tmp/abcdefg.key', 
//               '/tmp/abcdefg.t', '/tmp/abcdefg.tag', 80, 4096);
// }, 10000);

// let key_data = fs.readFileSync('/tmp/abcdefg.key', 'latin1');
// let t_data = fs.readFileSync('/tmp/abcdefg.t', 'latin1');
// let tag_data = fs.readFileSync('/tmp/abcdefg.tag', 'latin1');

// let key_data = fs.readFileSync('C:/Users/dingyi/AppData/Local/Temp/abcdefg.key', 'latin1');
// let t_data = fs.readFileSync('C:/Users/dingyi/AppData/Local/Temp/abcdefg.t', 'latin1');
// let tag_data = fs.readFileSync('C:/Users/dingyi/AppData/Local/Temp/abcdefg.tag', 'latin1');

const CporVerify = Cpor.CporVerify;
const app = http.createServer();

const paramsDataBufferHelper = new BufferHelper();
const keyDataBufferHelper = new BufferHelper();
const tDataBufferHelper = new BufferHelper();
const tagDataBufferHelper = new BufferHelper();

app.on('request', (req, res) => {

    if (req.url === '/audit/cpor_params' && req.method === 'PUT') {
        req.on('data', (chunk) => {
            paramsDataBufferHelper.concat(chunk);
        });

        req.on('end', () => {
            res.writeHead(200);
            res.end();
        });
    }
    else if (req.url === '/audit/key' && req.method === 'PUT') {
        req.on('data', (chunk) => {
            keyDataBufferHelper.concat(chunk);
        });

        req.on('end', () => {
            res.writeHead(200);
            res.end();
        });
    } else if (req.url === '/audit/t' && req.method === 'PUT') {
        req.on('data', function (chunk) {
            tDataBufferHelper.concat(chunk);
        });

        req.on('end', () => {
            res.writeHead(200);
            res.end();
        });
    } else if (req.url === '/audit/tag' && req.method === 'PUT') {
        req.on('data', function (chunk) {
            tagDataBufferHelper.concat(chunk);
        });

        req.on('end', () => {
            res.writeHead(200);
            res.end();

            // app.close(() => {
            //     console.log("server close");
            // });

            var paramsData = iconvlite.decode(paramsDataBufferHelper.toBuffer(), 'ISO-8859-1');
            var keyData = iconvlite.decode(keyDataBufferHelper.toBuffer(), 'ISO-8859-1');
            var tData = iconvlite.decode(tDataBufferHelper.toBuffer(), 'ISO-8859-1');
            var tagData = iconvlite.decode(tagDataBufferHelper.toBuffer(), 'ISO-8859-1');

            let success = CporVerify('/Users/dingyi/10兆.data', keyData, tData, tagData);
            // let success = CporVerify('Y:/10兆.data', key_data, t_data, tag_data);
            if(success == 1) {
                console.log('Verified!');
            } else if(success == 0) {
                console.log('Cheating!');
            } else {
                console.log('Error!');
            }
        });
    } else {
        res.end();
    }
});

app.listen(9999, function () {
    console.log('Server open');
});
