"use strict"

const number = document.getElementById('number');
const button = document.getElementById('happy');
const response = document.getElementById('response');

button.addEventListener('click', happiness);

async function happiness(){

    const getJoeHappiness = async (callback, error) => {

        await new Promise (resolve => setTimeout(() => {

            const happiness = Math.random();

            const happy = number.value;

            if (happiness > happy) {

                callback({happiness: happiness});

            } else {

                error({ mesage: "Joe is sad!"});

            }
            
        }, 2000));

    }

    getJoeHappiness( (result) => {

        console.log("happiness", result);

        response.innerHTML = "Yes! By " + Math.floor(result.happiness*100) + "%"; 

    }, (error) => {

        console.log("F", error.mesage);

        response.innerHTML = "<span class=\"red\">No!!! " + error.mesage + "</span>"; 

    });

}


