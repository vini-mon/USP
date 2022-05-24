"use strict"

const number = document.getElementById('number');
const button = document.getElementById('happy');
const response = document.getElementById('response');

button.addEventListener('click', happiness);

function happiness(){

    const getJoeHappiness = (callback, error) => {

        setTimeout(() => {

            const happiness = Math.random();

            const happy = number.value;

            if (happiness > happy) {

                callback(happiness);
                
            } else {

                error("Joe is sad!");

            }

        }, 200);
    }

    getJoeHappiness( (result) => {

        console.log(result);

        response.innerHTML = "Yes! By " + Math.floor(result*100) + "%";

    }, (error) => {

        console.log( error );
        
        response.innerHTML = "<span class=\"red\">No!!! " + error + "</span>";

    });

}


