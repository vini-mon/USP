let arr1 = [3, 'a', 'a', 'a', 2, 3, 'a', 3, 'a', 2, 4, 9];

let cont = [];

let x;

arr1.forEach(y => {

    if( y == 'a' ){

        x = 99;

    }else{

        x = parseInt(y);
        
    }

    if( isNaN(cont[x]) ){

        cont[x] = 1;

    }else{

        cont[x]++;

    }

});

let maior = 0;
let referencia = 0;

for( let c in cont ){

    if( cont[c] > maior ){

        maior = cont[c];
        referencia = c;

    }

}

if(referencia == 99){

    referencia = 'a';

}

document.getElementById('msg').insertAdjacentHTML('beforeend', referencia + " ( " + maior + " times )<br/>");