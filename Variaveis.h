


    PIG_Cor     Cores[8] = {CINZA, AMARELO, VERDE, VERMELHO, AZUL, CIANO, LARANJA, ROXO};

    Passaros    Passaro[POPULACAO_MAX];
    int         QuantidadePassaros = 0;
    int         SinalPular = 0;
    int         SinalParaquedas = 0;

    Passaros*   MelhorPassaro;

    Chao        chao[CHAO_QUANTIDADE];
    Grafico     grafico;
    Enfeite     arvore[QTD_ARVORE], nuvem[QTD_NUVEM], predio[QTD_PREDIO];

    Obstaculo   canoSuperior[QTD_OBSTACULOS];
    Obstaculo   canoInferior[QTD_OBSTACULOS];

    int         Fonte, FontePequena, FonteVermelha, FonteAzul, FontePretaGrande, FonteAzulGrande;
    double      VELOCIDADE;
    int         TimerGeral = 0;
    double      Periodo = 0.005;
    double      DistanciaRecorde, DistanciaAtual;

    int         PassarosMortos;
    int         ObstaculoDaVez = 1;
    int         Geracao;
    int         DesenharTela = 1;

    int         POPULACAO_TAMANHO;
    int         GeracaoCompleta = 0;
    double*     DNADaVez[POPULACAO_MAX];

    double      MediaFitnessPopulacao[LARG_GRAFICO];
    double      MediaFitnessFilhos[LARG_GRAFICO];
    double      BestFitnessPopulacao[LARG_GRAFICO];

    double      CanoParaquedasCooldown;

