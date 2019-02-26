

void AlocarPassaro()
{
    static int ControladorCor = 0;
    int Tamanho;

    for(int i=0; i<QTD_SPRITES_BIRDS; i++)
    {
        Passaro[QuantidadePassaros].sprite[i] = getPassaroSprite(i, ControladorCor);
    }

    Passaro[QuantidadePassaros].TimerFrame       = CriarTimer();
    Passaro[QuantidadePassaros].ResetarFitness   = 1;

    Passaro[QuantidadePassaros].Cerebro = RNA_CriarRedeNeural(  BIRD_BRAIN_QTD_LAYERS,
                                                                BIRD_BRAIN_QTD_INPUT,
                                                                BIRD_BRAIN_QTD_HIDE,
                                                                BIRD_BRAIN_QTD_OUTPUT);


    Tamanho = RNA_QuantidadePesos(Passaro[QuantidadePassaros].Cerebro);

    Passaro[QuantidadePassaros].TamanhoDNA = Tamanho;
    Passaro[QuantidadePassaros].DNA = (double*)malloc(Tamanho*sizeof(double));

    DNADaVez[QuantidadePassaros] = (double*)malloc(Tamanho*sizeof(double));

    for(int j=0; j<Tamanho; j++)
    {
        DNADaVez[QuantidadePassaros][j] = getRandomValue();
    }

    InicializarPassaro(QuantidadePassaros, DNADaVez[QuantidadePassaros], 0, 0);

    ControladorCor = (ControladorCor+1)%QTD_COR_BIRDS;
    QuantidadePassaros = QuantidadePassaros + 1;
}

void AlocarPassaros()
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        AlocarPassaro();
    }
}
