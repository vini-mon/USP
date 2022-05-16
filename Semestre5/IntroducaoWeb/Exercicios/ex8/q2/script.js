"use strict"

const text = document.getElementById('change_heading');

const block = document.querySelectorAll('div');

const colorName = document.querySelector('selected');

console.log(block);

changeColor();
changeColorName();

for( let i = 0 ; i < block.length ; i++ ){

    console.log(block[i]);

    block[i].addEventListener('click', function(){changeColor(block[i].className)});
    block[i].addEventListener('mouseenter', function(){changeColorName(block[i].className)});
    block[i].addEventListener('mouseleave', function(){changeColorName(block[i].className)});

}


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

        }

    }

    

}

function changeColorName(color){

    console.log(color);

}