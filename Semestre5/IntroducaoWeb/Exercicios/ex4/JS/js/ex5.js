let library = [
{

    author: 'Bill Gates',
    title: 'The Road Ahead',
    readingStatus: true

},
{

    author: 'Steve Jobs',
    title: 'Walter Isaacson',
    readingStatus: true

},
{

    author: 'Suzanne Collins',
    title:  'Mockingjay: The Final Book of The Hunger Games', 
    readingStatus: false

}];

let target = document.getElementById('msg1');

target.insertAdjacentHTML('beforeend', "<h3>Coleção</h3>");
target.insertAdjacentHTML('beforeend', "<ul>");

library.forEach(x =>{

    target.insertAdjacentHTML('beforeend', "<li><b>Título:</b> " + x.title + " | <b>Autor:</b> " + x.author + " | <b>Disponível para leitura:</b> " + x.readingStatus + ".</li>");
    
});

target.insertAdjacentHTML('beforeend', "</ul>");

library.push({

    author: 'Douglas Adams',
    title: 'O Guia do Mochileiro das Galáxias',
    readingStatus: false

});

target = document.getElementById('msg2');

target.insertAdjacentHTML('beforeend', "<h3>Indisponíveis para leitura</h3>");

target.insertAdjacentHTML('beforeend', "<ul>");

library.forEach(x =>{

    if(x.readingStatus == false){

        target.insertAdjacentHTML('beforeend', "<li><b>Título:</b> " + x.title + " | <b>Autor:</b> " + x.author + ".</li>");
    
    }

});

target.insertAdjacentHTML('beforeend', "</ul>");
