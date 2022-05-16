"use strict"

window.addEventListener('DOMContentLoaded', (event) => {
    
    const text = document.getElementById('change_heading');

    text.textContent = "Chenge color";

    const block = document.querySelectorAll('div');

    const colorName = document.querySelector('span');

    const randomBlock = block[block.length-1];

    console.log(block);

    changeColor();
    changeColorName();

    for( let i = 0 ; i < block.length ; i++ ){

        console.log(block[i]);

        block[i].addEventListener('click', () => {changeColor(block[i].className)});
        block[i].addEventListener('mouseenter', function(){changeColorName(block[i].className)});
        block[i].addEventListener('mouseleave', function(){changeColorName("none")});

    }

    setInterval(function(){randomColor()}, 500);

    function changeColor(color){

        if( text.className == color ){

            text.className = "";

        }else{

            if( color == "brown" ){

                text.className = "brown";

            }else if( color == "green" ){

                text.className = "green";

            }else if( color == "blue" ){

                text.className = "blue";

            }else if( color == "yellow" ){

                text.className = "yellow";

            }else if( color == "purple" ){

                text.className = "purple";

            }

        }

    }

    function changeColorName(color){

        if( color == "none" ){

            colorName.textContent = "None!";

        }else{

            if( color == "brown" ){

                colorName.textContent = "brown";
        
            }else if( color == "green" ){

                colorName.textContent = "green";
        
            }else if( color == "blue" ){

                colorName.textContent = "blue";
        
            }else if( color == "yellow" ){

                colorName.textContent = "yellow";
        
            }else if( color == "purple" ){

                colorName.textContent = "purple";
        
            }

        }

    }

    function randomColor(){

        let newColor = Math.floor(Math.random() * 5);

        if( newColor == 0 ){

            randomBlock.className = "brown";

        }else if( newColor == 1 ){

            randomBlock.className = "green";

        }else if( newColor == 2 ){

            randomBlock.className = "blue";

        }else if( newColor == 3 ){

            randomBlock.className = "yellow";

        }else if( newColor == 4 ){

            randomBlock.className = "purple";

        }

    }

    
});