function Evento(){

    function meuEvento(){

        console.log("Opa, fui ativado");

    }

    return(

        <div>

            <h1>Clique em mim</h1>
            <button onClick={meuEvento}>olhe o console</button>

        </div>

    );

}

export default Evento;