import { useState } from "react";

function Forms(){

    function cadastrar(e){

        e.preventDefault();

        console.log(nome);

        console.log("Cadastrando...");

    }

    const [nome, setName] = useState('Jamal');

    return(

        <div>

            <form onSubmit={cadastrar}>

                <label htmlFor="nome">Nome:</label>
                <input id="name" onChange={(e)=>setName(e.target.value)} value={nome} type="text" placeholder="Nome"/> <br/>

                <label htmlFor="senha">Senha:</label>
                <input id="senha" type="password" placeholder="Senha"/> <br/>

                <input type="submit" value="Cadastrar"/>

            </form>

        </div>

    );

}

export default Forms;