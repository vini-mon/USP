document.getElementById("set").addEventListener("click", function(){

    document.getElementById("title").setAttribute("class", "blue")

})

document.getElementById("remove").addEventListener("click", function(){

    document.getElementById("title").removeAttribute("class")

})

document.getElementById("get").addEventListener("click", function(){

    var value = document.getElementById("title").getAttribute("class")
    document.getElementById("class").innerHTML = value

})