var p = document.createElement("p");
p.tagName = "paragrafo";

var img = document.createElement("img");
img.tagName = "imagem";
img.src = "img/teste.png"
img.style.maxWidth = "150px";

p.innerHTML = "sou um filho";

document.getElementById("conteudo").appendChild(p);
document.getElementById("conteudo").appendChild(img);

document.getElementById("conteudo").removeChild(p);