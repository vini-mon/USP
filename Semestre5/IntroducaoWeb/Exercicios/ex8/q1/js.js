"use strict";

var madTalk = document.getElementById('lib-button');
var story = document.getElementById('story');

var noun = document.getElementById('noun');
var adjective = document.getElementById('adjective');
var person = document.getElementById('person');

function makeMadTalk(){

    var text = person.value + " " + adjective.value + " " + noun.value;

    story.innerText = text;

}

madTalk.addEventListener('click', makeMadTalk);

