alert("Contador de letras para o seu nome");

let nome = prompt("Qual o seu nome?");

let cont = 0;

for( let i = 0 ; i < nome.length ; i++ ){

    if( nome[i] != ' ' ){

        cont++;

    }

}

alert(nome + ": " + cont + " characters")

//window.alert("A quantidade de letras no seu nome é de: " + cont);