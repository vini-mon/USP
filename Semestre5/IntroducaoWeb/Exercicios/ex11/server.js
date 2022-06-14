const http = require('http');
const fs = require('fs');
const path = require('path');
const { parse } = require('path');

http.createServer( (request, response) => {
;
    console.log('url ', request.url.pathname);
    //console.log('request ', request);

    let filePath = '.' + request.url;

    //console.log('request ',request);

    console.log(filePath);

    if (filePath == './') {

        console.log("brabo");
        filePath = './index.html';

    }else if(filePath == './random'){

        let url = new URLSearchParams(document.location.search.substring(1));

        console.log(url);

        filePath = './random/random.js';

    }else{

        console.log("error 404");

    }

    const extname = String(path.extname(filePath)).toLowerCase();

    const mimeTypes = {

        '.html': 'text/html',
        '.js': 'text/javascript',
        '.css': 'text/css',
        '.json': 'application/json',
        '.png': 'image/png',
        '.jpg': 'image/jpg',
        '.gif': 'image/gif',
        '.svg': 'image/svg+xml',
        '.wav': 'audio/wav',
        '.mp4': 'video/mp4',
        '.woff': 'application/font-woff',
        '.ttf': 'application/font-ttf',
        '.eot': 'application/vnd.ms-fontobject',
        '.otf': 'application/font-otf',
        '.wasm': 'application/wasm'

    };

    const contentType = mimeTypes[extname] || 'application/octet-stream';

    fs.readFile(filePath, (error, content) => {

        return new Promise( ()=> {

            if (error) {

                if(error.code == 'ENOENT') {

                    fs.readFile('./404.html', (error, content) => {

                        response.writeHead(404, { 'Content-Type': 'text/html' });
                        response.end(content, 'utf-8');

                    });

                }else {

                    response.writeHead(500);
                    response.end('Sorry, check with the site admin for error: '+error.code+' ..\n');

                }


            }else {

                response.writeHead(200, { 'Content-Type': contentType });
                response.end(content, 'utf-8');

            }

        });

    });

}).listen(8125);

console.log('Server running at http://127.0.0.1:8125/');