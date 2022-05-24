"use strict"

const number = document.getElementById('number');
const button = document.getElementById('happy');
const response = document.getElementById('response');

button.addEventListener('click', getHappiness);

function getHappiness(){

    function getJoeHappiness(){

        return new Promise( (resolve, reject) => {
            
            setTimeout(() => {

                const happiness = Math.random();
                const happy = number.value;

                if (happiness > happy) {

                    resolve({
                        
                        happiness: happiness
                    
                    });

                } else {

                    reject({
                        
                        mesage: "Joe is sad!"
                    
                    });

                }
                
            }, 2000);
            
        });

    }

    getJoeHappiness().then(

        (result) => {

            console.log("happiness", result.happiness);

            response.innerHTML = "Yes! By " + Math.floor(result.happiness*100) + "%"; 

        }).catch((error) => {

            console.log("error", error.mesage);
            
            response.innerHTML = "<span class=\"red\">No!!! " + error.mesage + "</span>"; 

        });

}