"use strict";

var p = document.getElementsByTagName("p");

var control = 0;

function br(){
    
    var text = p[0].innerHTML;

    var newText = "";

    var spaces;

    for( var i = 0 ; i < text.length ; i++ ){

        if( text[i] === " " ){

            spaces++;

        }else if( text[i] == '.' ){

            var split = text.trim().slice(control, i+1);

            control = i+2;

            console.log(split);

            split += "<br/>";

            newText += split;

        }

    }

    p[0].innerHTML = newText;

}

function color(){

    var text = p[0].innerText;

    var newSpan = "";
    var contLetter = 0;

    var control = 0;

    for( var i = 0 ; i < text.length ; i++ ){

        if( text[i] == " " || text[i] == "." || text[i] == "\'" || text[i] == "(" || text[i] == ")" || text[i] == '\"' || text[i] == ","  || text[i] == ":"  || text[i] == ";" || text[i] == "!" || text[i] == "-" ){


            if( contLetter == 0 ){

                newSpan += text.trim().slice(control, i+1);

                i++;

            }else if( contLetter == 4 || contLetter == 5 ){

                newSpan += "<span class=\"blue\">" + text.trim().slice(control, i) + "</span>";

            }else if( contLetter == 6 ){

                newSpan += "<span class=\"purple\">" + text.trim().slice(control, i) + "</span>";

            }else if( contLetter > 8 ){

                newSpan += "<span class=\"pink\">" + text.trim().slice(control, i) + "</span>";

            }else{

                newSpan += text.trim().slice(control, i);

            }

            contLetter = 0;
            control = i;

        }else{

            contLetter++;

        }

    }

    newSpan += text.slice(text.length-1);

    p[0].innerHTML = newSpan;

}

function countWords(){

    var h1 = document.getElementById("h1");

    var text = p[0].innerText;

    var spaces = 0;

    for( var i = 0 ; i < text.length ; i++ ){

        if( text[i] == " " || text[i] == "-" ){

            spaces++;

        }

    }

    spaces++;

    var words = document.createElement('div');

    words.innerHTML = "Words: " + spaces;

    h1.insertAdjacentElement("afterend", words);

}

function home(){

    var home = document.createElement('footer');

    home.innerHTML = "<a href=\"index.html\">Home</a>";

    p[0].insertAdjacentElement("afterend", home);

}

countWords();
color();
br();
home();