let urlnumber = document.getElementById('number');
let params = new URLSearchParams(document.location.search.substring(1));
let max = params.get("max");

const myJson = {max:max}

console.log(myJson);

if( myJson.max == null ){

    myJson.max = 2;

}

let number = Math.floor(Math.random() * (myJson.max - 0)) + 0;

urlnumber.innerText = number;