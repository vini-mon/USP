let urlnumber = document.getElementById('number');
let params = new URLSearchParams(document.location.search.substring(1));
let max = params.get("max");

const myJson = {max:max}

console.log(max);

let number = Math.floor(Math.random() * (2 - 0)) + 0;

urlnumber.innerText = myJson.max;

response.writeHead(200, { 'Content-Type': contentType });
response.end(content, 'utf-8');