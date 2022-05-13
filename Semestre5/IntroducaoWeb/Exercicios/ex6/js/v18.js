var lista = document.getElementsByTagName("ul")

console.log(lista)

var itens = lista[0].children

console.log(itens)

var novoItem = document.createElement("li")
novoItem.innerHTML = "Suco de Laranja do Jailson Mendes"

lista[0].insertBefore(novoItem, itens[2])