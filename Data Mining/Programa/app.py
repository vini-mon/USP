import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import xgboost as xgb

# Função para carregar os dados
def load_data(file):
    return pd.read_csv(file)

st.title("Análise de Consumo e Produção de Energia com Predições")
st.write("Carregue um dataset para visualizar padrões de consumo e produção com base nas predições do modelo.")

# Upload de dados
uploaded_file = st.file_uploader("Carregue um arquivo CSV", type=["csv"])
if uploaded_file:
    # Carregar os dados
    data = load_data(uploaded_file)
    st.write("Dados carregados (visualizando as primeiras linhas):")
    st.dataframe(data.head())

    # Carregar o modelo treinado
    model = xgb.XGBRegressor()
    model.load_model("xgboost_model.json")  # Certifique-se de que o modelo esteja no mesmo diretório

    # Verificar se a coluna 'hour' existe para análise
    if 'hour' not in data.columns:
        st.error("O dataset precisa conter uma coluna chamada 'hour' para análise de padrões por hora do dia.")
    else:
        # Selecionar colunas para a predição (assumindo que 'hour' é uma característica e outras colunas podem ser incluídas conforme necessário)
        features = data.drop(columns=['Previsões'], errors='ignore')

        # Realizar predições
        predictions = model.predict(features)

        # Adicionar as predições ao DataFrame
        data['preds'] = predictions

        # Exibir resultados
        st.write("Resultados das predições:")
        st.dataframe(data)



        # Supondo que 'data' seja o DataFrame com as predições e dados relevantes
        # Converter colunas de data para datetime
        data['day'] = data['day_of_month']
        data['datetime'] = pd.to_datetime(data[['year', 'month', 'day']])

        # Definir o índice como datetime
        data.set_index('datetime', inplace=True)

        # Plot do consumo e produção de energia
        plt.figure(figsize=(14, 7))
        sns.lineplot(data=data, x=data.index, y='preds', hue='is_consumption', marker='o')
        plt.title('Consumo e Produção de Energia ao Longo do Tempo')
        plt.xlabel('Data')
        plt.ylabel('Energia (kWh)')
        plt.legend(title='Tipo', labels=['Produção', 'Consumo'])
        st.pyplot(plt)

        # Calcular e plotar a diferença (Produção - Consumo)
        data['produced_energy'] = data.apply(lambda row: row['preds'] if row['is_consumption'] == 0 else 0, axis=1)
        data['consumed_energy'] = data.apply(lambda row: row['preds'] if row['is_consumption'] == 1 else 0, axis=1)
        data['excess_energy'] = data['produced_energy'] - data['consumed_energy']

        plt.figure(figsize=(14, 7))
        sns.lineplot(data=data, x=data.index, y='excess_energy', color='purple', marker='o')
        plt.title('Excesso de Produção de Energia ao Longo do Tempo')
        plt.xlabel('Data')
        plt.ylabel('Excesso de Energia (kWh)')
        st.pyplot(plt)

        # Análise de consumo e produção por região (county)
        plt.figure(figsize=(14, 7))
        sns.lineplot(data=data, x=data.index, y='preds', hue='county', marker='o')
        plt.title('Consumo e Produção de Energia por Região')
        plt.xlabel('Data')
        plt.ylabel('Energia (kWh)')
        plt.legend(title='Região', bbox_to_anchor=(1.05, 1), loc='upper left')
        st.pyplot(plt)

        # Análise por tipo de negócio (is_business)
        plt.figure(figsize=(14, 7))
        sns.lineplot(data=data, x=data.index, y='preds', hue='is_business', marker='o')
        plt.title('Consumo e Produção de Energia por Tipo de Negócio')
        plt.xlabel('Data')
        plt.ylabel('Energia (kWh)')
        plt.legend(title='Tipo de Negócio')
        st.pyplot(plt)

        # Análise por tipo de produto (product_type)
        plt.figure(figsize=(14, 7))
        sns.lineplot(data=data, x=data.index, y='preds', hue='product_type', marker='o')
        plt.title('Consumo e Produção de Energia por Tipo de Produto')
        plt.xlabel('Data')
        plt.ylabel('Energia (kWh)')
        plt.legend(title='Tipo de Produto', bbox_to_anchor=(1.05, 1), loc='upper left')
        st.pyplot(plt)


        # Botão para salvar o DataFrame com predições
        if st.button("Salvar Resultados em CSV"):
            data.to_csv("resultado_com_predicoes.csv", index=False)
            st.write("Arquivo salvo como 'resultado_com_predicoes.csv'")
