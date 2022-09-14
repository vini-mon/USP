const http = require('http');
const fs = require('fs');
const path = require('path');
const { parse } = require('path');

function readFile(filePath){

    //return fs.promises.readFile(filePath);
    return new Promise( (resolve, rejected) => { 

        fs.readFile(filePath, (error, content) => {

            if (error) {

                rejected(error);

            }else {

                resolve(content);

            }

        });

    });

}


    http.createServer( async (request, response) => {


        let filePath = '.' + request.url;

        console.log(filePath);

        let split = filePath.split('?');
        let max = 1;

        filePath = split[0];

        if (filePath == './') {

            filePath = './index.html';

        }else if(filePath == './example'){

            filePath = './example/newFile.html';	
            console.log("file max:",filePath);

        }else if(filePath == './random'){

            filePath = './random/random.html';	
            console.log("file max:",filePath);

        }else{

            console.log("erro 404:", filePath);

        }

        const extname = String(path.extname(filePath)).toLowerCase();

        console.log("extname:", extname);

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

        try{

            content = await readFile(filePath);

            response.writeHead(200, { 'Content-Type': contentType });
            response.end(content, 'utf-8');
        
        }catch(error){

            if(true || error.code == 'ENOENT') {

                try{ 

                    content = await readFile('./404.html');

                    response.writeHead(404, { 'Content-Type': 'text/html' });
                    response.end(content, 'utf-8');

                }catch(error){

                    console.log("error:", error);

                    response.writeHead(500);
                    response.end('Sorry, check with the site admin for error: '+error.code+' ..\n');

                }

            }

        }

    }).listen(8125);


console.log('Server running at http://127.0.0.1:8125/');