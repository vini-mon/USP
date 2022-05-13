console.log(

    document.documentElement.firstChild,
    document.documentElement.lastChild

)

var lista = document.body.childNodes

console.log(

    lista

)

console.log(

    lista[7].childNodes

)

console.log(

    lista[7].childNodes[1].childNodes[0].nodeValue

)

/* 
alert(lista[3].nodeName);
alert(lista[3].nodeType);
alert(lista.length); */