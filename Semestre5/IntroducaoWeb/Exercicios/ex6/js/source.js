var body = document.querySelector("body");

console.log(body)

body.style.fontFamily = "Impact,Charcoal,sans-serif";

var nome = document.getElementById("name");
var nickname = document.getElementById("nickname");
var favorites = document.getElementById("favorites");
var hometown = document.getElementById("hometown");

nome.textContent = "Homem-Aranha";
nickname.textContent = "Cabeça de Teia";
favorites.textContent = "Fotografia, ser o herói da vizinhança e salvar o mundo";
hometown.textContent = "Nova Iorque";

var img = document.createElement("img");
img.src = "img/miranha.jpg"
img.alt = "Peter Parker";
img.style.maxWidth = "300px";
img.style.borderRadius = "100%";

var ul = document.querySelector("ul");

body.insertBefore(img, ul);
