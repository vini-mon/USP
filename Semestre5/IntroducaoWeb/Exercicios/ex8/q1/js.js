"use strict";

let madTalk = document.getElementById('lib-button');
let story = document.getElementById('story');

let noun = document.getElementById('noun');
let adjective = document.getElementById('adjective');
let person = document.getElementById('person');

function makeMadTalk(){

    let text = person.value + " like " + adjective.value + " " + noun.value;

    story.innerText = text;

}

madTalk.addEventListener('click', makeMadTalk);

