Acessando o postgres pelo wsl:

    Abrir wsl
    Minha senha local: admin
    psql -h localhost -U postgres -d postgres
    \l

Carregando os dados no wsl:

    psql -h localhost -U postgres -d postgres -a -f "/mnt/d/USP/censo22/Censo.sql"

Acessando os bancos de dados:

    IP_SERVER é 172.21.218.12 mas pode mudar
    %sql postgresql://postgres:admin@[IP_SERVER]/fapcov2103
    
