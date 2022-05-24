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

    fetch(request, {}).then( async (response) => {

        console.log(response.headers.get("Content-Type"));

        try{

            const color = await response.json();

            let dados = color;
            let hexa = color.data.color;
            let name_1 = color.data.name;

            console.log(dados);
    
            hexaColor.textContent = "Color: " + hexa;
            nameColor.textContent = name_1;
            squareColor.style.backgroundColor = hexa;
    
            console.log(number.value);

        }catch(error){

            console.log("(404) Error: Page not found!");

            hexaColor.textContent = "Error: 404";
            nameColor.textContent = "Page not found!";
            squareColor.style.backgroundColor = "#FFFFFF";

        }


    });

}