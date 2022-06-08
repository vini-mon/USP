DROP TABLE UNIFORME;
DROP TABLE DIRETOR;
DROP TABLE POSICAO_JOGADOR;
DROP TABLE JOGADOR;
DROP TABLE PARTIDA;
DROP TABLE JOGA;
DROP TABLE TIME;

CREATE TABLE TIME(

    NOME VARCHAR(50) NOT NULL,
    ESTADO VARCHAR(12),
    TIPO VARCHAR(12),
    SALDO_GOLS NUMBER(4),
    
    CONSTRAINT PK_TIME_TIME PRIMARY KEY(NOME),
    CONSTRAINT CK_TIPO_TIME CHECK(UPPER(TIPO) IN ('AMADOR', 'PROFISSIONAL'))
    

);

CREATE TABLE JOGA(

    TIME1 VARCHAR(20) NOT NULL,
    TIME2 VARCHAR(20) NOT NULL,
    CLASSICO CHAR(1),
    
    CONSTRAINT PK_JOGA_JOGA PRIMARY KEY (TIME1, TIME2),
    CONSTRAINT FK_TIME1_JOGA FOREIGN KEY(TIME1) REFERENCES TIME(NOME) ON DELETE CASCADE,
    CONSTRAINT FK_TIME2_JOGA FOREIGN KEY(TIME2) REFERENCES TIME(NOME) ON DELETE CASCADE,
    CONSTRAINT CK_CLASSICO_JOGA CHECK(UPPER(CLASSICO) IN ('S', 'N'))

);

CREATE TABLE PARTIDA(

    TIME1 VARCHAR(20) NOT NULL,
    TIME2 VARCHAR(20) NOT NULL,
    DATA DATE NOT NULL,
    PLACAR VARCHAR(5) DEFAULT '0X0',
    
    CONSTRAINT PK_PARTIDA_PARTIDA PRIMARY KEY(TIME1, TIME2, DATA),
    CONSTRAINT FK_TIME1_PARTIDA FOREIGN KEY(TIME1, TIME2) REFERENCES JOGA(TIME1, TIME2) ON DELETE CASCADE,
    CONSTRAINT CK_PLACAR_PARTIDA CHECK (REGEXP_LIKE(PLACAR, '[[:digit:]]{1,2}\X[[:digit:]]{1,2}', 'i'))
    

);

CREATE TABLE JOGADOR(

    CPF VARCHAR(11) NOT NULL,
    RG VARCHAR(11) NOT NULL,
    NOME VARCHAR(50) NOT NULL,
    DATA_NASC DATE,
    NATURALIDADE VARCHAR(25),
    TIME VARCHAR(20),
    
    CONSTRAINT PK_CPF_JOGADOR PRIMARY KEY(CPF),
    CONSTRAINT UN_JOGADOR UNIQUE(RG, NOME),
    
    CONSTRAINT FK_TIME_JOGADOR FOREIGN KEY(TIME) REFERENCES TIME(NOME) ON DELETE CASCADE,
    CONSTRAINT CK_CPF_JOGADOR CHECK(REGEXP_LIKE(CPF, '[0-9]{3}\.[0-9]{3}\.[0-9]{3}\.[0-9]{2}'))

);

CREATE TABLE POSICAO_JOGADOR(

    JOGADOR VARCHAR(11) NOT NULL,
    POSICAO VARCHAR(10) NOT NULL,
    
    CONSTRAINT PK_POSICAO_JOGADOR PRIMARY KEY(JOGADOR, POSICAO),
    CONSTRAINT FK_JOGADOR_POSICAO_JOGADOR FOREIGN KEY(JOGADOR) REFERENCES JOGADOR(CPF) ON DELETE CASCADE

);

CREATE TABLE DIRETOR(

    TIME VARCHAR(20) NOT NULL,
    NOME VARCHAR(50) NOT NULL,
    
    CONSTRAINT PK_DIRETOR_DIRETOR PRIMARY KEY(TIME, NOME),
    CONSTRAINT FK_TIME_DIRETOR FOREIGN KEY(NOME) REFERENCES TIME(NOME) ON DELETE CASCADE

);

CREATE TABLE UNIFORME(

    TIME VARCHAR(20) NOT NULL,
    TIPO VARCHAR(10) NOT NULL,
    COR_PRINCIPAL VARCHAR(10) NOT NULL,
    
    CONSTRAINT PK_UNIFORME PRIMARY KEY(TIME, TIPO),
    CONSTRAINT FK_TIME_UNIFORME FOREIGN KEY (TIME) REFERENCES TIME(NOME) ON DELETE CASCADE,
    CONSTRAINT CK_UNIFORME CHECK(UPPER(TIPO) IN ('TITULAR','RESERVA'))

);

/*
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('PALMEIRAS', 'SP', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('VASCO', 'RJ', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('FLAMENGO', 'RJ', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('BOTAFOGO', 'RJ', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('CHAPECOENSE', 'SC', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('SANTOS', 'SP', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('UNIDOS', NULL, 'AMADOR', NULL);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('INTER', 'SP', 'AMADOR', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('CRUZEIRO', 'MG', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('ATLETICO', 'MG', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('INTERNACIONAL', 'RS', 'PROFISSIONAL', 0);


INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('VASCO', 'CHAPECOENSE', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('INTER', 'PALMEIRAS', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('PALMEIRAS', 'SANTOS', 'S');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('UNIDOS', 'INTER', NULL);
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('CRUZEIRO', 'SANTOS', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('VASCO', 'FLAMENGO', 'S');

INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'CHAPECOENSE', TO_DATE('2018/04/30 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'RIO DE JANEIRO');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL)  VALUES ('INTER', 'PALMEIRAS', TO_DATE('2018/03/02 20:00:00', 'YYYY/MM/DD HH24:MI:SS'), '1X0', 'SANTOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('PALMEIRAS', 'SANTOS', TO_DATE('2018/02/01 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '4X2', 'SANTOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('UNIDOS', 'INTER', TO_DATE('2020/12/01 16:30:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'SAO CARLOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('CRUZEIRO', 'SANTOS', TO_DATE('2018/07/01 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '0X2', 'BELO HORIZONTE');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('CRUZEIRO', 'SANTOS', TO_DATE('2018/12/07 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '3X2', NULL);
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'FLAMENGO', TO_DATE('2018/02/10 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), '2X1', 'RIO DE JANEIRO');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'FLAMENGO', TO_DATE('2020/12/03 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), NULL, NULL);


INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('400.560.298-61', '20.000.201-3', 'REINALDO', TO_DATE('1995/09/02', 'YYYY/MM/DD'), 'SAO PAULO', 'SANTOS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('400.560.298-60', '40.123.201-3', 'JOSE', TO_DATE('1997/10/12', 'YYYY/MM/DD'), NULL,'PALMEIRAS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('111.460.298-60', '40.435.201-3', 'ALFREDO', TO_DATE('1990/01/22', 'YYYY/MM/DD'), 'RIO DE JANEIRO', 'CHAPECOENSE');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('103.460.333-60', '40.234.201-3', 'EDERSON', TO_DATE('1989/10/10', 'YYYY/MM/DD'), 'CAMPINAS', 'SANTOS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('011.460.298-60', '20.435.201-3', 'NETO', TO_DATE('1991/09/02', 'YYYY/MM/DD'), 'FLORIANOPOLIS', 'CHAPECOENSE');   
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('123.340.198-45', '34.124.002-5', 'SANTIAGO', TO_DATE('1987/12/01', 'YYYY/MM/DD'), 'IBATE', 'UNIDOS');   
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('301.400.298-00', '40.100.202-7', 'ALESSANDRO', TO_DATE('1992/03/01', 'YYYY/MM/DD'), 'BELO HORIZONTE', 'SANTOS');   


INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('400.560.298-61', 'MEIA');  
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('400.560.298-60', 'GOLEIRO');   
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('111.460.298-60', 'ATACANTE');  
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('103.460.333-60', 'ZAGUEIRO');  
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('011.460.298-60', 'GOLEIRO');      
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('123.340.198-45', 'ZAGUEIRO');      
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('301.400.298-00', 'ATACANTE');      
    
INSERT INTO DIRETOR (TIME, NOME) VALUES ('PALMEIRAS', 'ROGER MACHADO');      
INSERT INTO DIRETOR (TIME, NOME) VALUES ('VASCO', 'ZE RICARDO');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('CHAPECOENSE', 'GILSON');       
INSERT INTO DIRETOR (TIME, NOME) VALUES ('INTER', 'AUGUSTO');        
INSERT INTO DIRETOR (TIME, NOME) VALUES ('SANTOS', 'JAIR');        
INSERT INTO DIRETOR (TIME, NOME) VALUES ('UNIDOS', 'CAMARGO');        
INSERT INTO DIRETOR (TIME, NOME) VALUES ('CRUZEIRO', 'MANO MENEZES');        

INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('PALMEIRAS', 'TITULAR', 'VERDE');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('PALMEIRAS', 'RESERVA', 'BRANCO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('VASCO', 'TITULAR', 'BRANCO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('CHAPECOENSE', 'RESERVA', NULL);
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('SANTOS', 'RESERVA', 'PRETO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('INTER', 'TITULAR', NULL);
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('CRUZEIRO', 'TITULAR', 'AZUL');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('UNIDOS', 'TITULAR', 'AZUL');
*/


/*
 SELECT * FROM TIME;
*/