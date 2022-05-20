"use strict"

let hexaColor = document.getElementById('hexaColor');
let nameColor = document.getElementById('nameColor');
let squareColor = document.getElementById('squareColor');
let number = document.getElementById('number');
let button = document.getElementById('button');

button.addEventListener('click', () => setColor(number.value));

setColor("1");

function setColor(number){

    let numberRequest = number;

    console.log(numberRequest);

    let request = "https://reqres.in/api/unknown/" + numberRequest;

    console.log(request);

    fetch(request, {}).then(function(response){

        console.log(response.headers.get("Content-Type"));

        return response.json()
        
        .then(function(color){

            let dados = color;

            let hexa = color.data.color;
            let name = color.data.name;

            console.log(dados); 

            hexaColor.textContent = "Color: " + hexa;
            nameColor.textContent = name;
            squareColor.style.backgroundColor = hexa;

        });

    });

}