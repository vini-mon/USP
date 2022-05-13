var lista = document.getElementsByTagName("ul")

console.log(lista)

var itens = lista[0].children

console.log(itens)

var novoItem = document.createElement("li")
novoItem.textContent = "Suco de Laranja do Jailson Mendes"

lista[0].insertBefore(novoItem, itens[2])


var itens2 = lista[1].children
var novoItem2 = document.createElement("li")

novoItem2.textContent = "Maionese"

lista[1].replaceChild(novoItem2, itens2[1])
