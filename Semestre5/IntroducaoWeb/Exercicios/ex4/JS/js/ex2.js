let message = document.getElementById('msg');

for( let i = 0 ; i < 16 ; i++ ){

    if( i%2 == 0 ){

        document.getElementById('msg').insertAdjacentHTML('beforeend', i + " is even<br/>");

    }else{

        document.getElementById('msg').insertAdjacentHTML('beforeend', i + " is odd<br/>");

    }

}