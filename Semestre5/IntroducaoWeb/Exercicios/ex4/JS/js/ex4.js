const color = ["Blue ", "Green", "Red", "Orange", "Violet", "Indigo"];
const order = [2, 1, 4, 5, 6, 3]

let cont = 1;

order.forEach(x => {
   
    document.getElementById('msg').insertAdjacentHTML('beforeend', cont + "st choice is " + color[x-1] + ".<br/>");

    cont++;

});