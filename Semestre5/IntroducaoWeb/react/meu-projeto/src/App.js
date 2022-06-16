// npm install react-router-dom


import './App.css';
import HelloWorld from './components/HelloWorld';
import SayMyName from './components/SayMyName';
import Pessoa from './components/Pessoa';
import List from './components/List';
import Evento from './components/Evento';
import Forms from './components/Forms';

function App() {

  const name = "Vini";

  return (

    <div className="App">

      <Evento />

      <hr/>

      <Forms />





      <HelloWorld />

      <SayMyName nome="Jamal"/>
      <SayMyName nome="Pedrin"/>
      <SayMyName nome={name}/>

      <hr/>

      <Pessoa nome="Jamal" idade="22" profissao="Desenvolvedor"/>

      <hr/>

      <List />

    </div>

  );
}

export default App;
