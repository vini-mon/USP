import Item from './Item';
import ReactPropTypes from 'prop-types';

function List(){

    return(

        <>

            <h1>Minha lista</h1>

            <ul>

                <Item marca="Ferrari" lancamento={1995} />
                <Item marca="Adidas" lancamento={2003} />
                <Item />

            </ul>
        
        </>

    );

}

Item.propTypes = {

    marca: ReactPropTypes.string.isRequired,
    lancamento: ReactPropTypes.number.isRequired 

}

Item.defaultProps = {

    marca: "undefined",
    lancamento: 0

}

export default List;