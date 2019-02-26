



void InicializarChao()
{
    for(int i=0; i<CHAO_QUANTIDADE; i++)
    {
        chao[i].sprite = &SpriteChao;
        chao[i].X = i*209.0;
        chao[i].Y = 0.0;
    }
}


void InicializarNuvem()
{
    for(int i=0; i<QTD_NUVEM; i++)
    {
        nuvem[i].sprite = &SpriteNuvem;
        nuvem[i].X = i*nuvem[i].sprite->Largura;
        nuvem[i].Y = 100;
    }
}

void InicializarPredio()
{
    for(int i=0; i<QTD_PREDIO; i++)
    {
        predio[i].sprite = &SpritePredio;
        predio[i].X = i*predio[i].sprite->Largura;
        predio[i].Y = 110;
    }
}

void InicializarArvore()
{
    for(int i=0; i<QTD_ARVORE; i++)
    {
        arvore[i].sprite = &SpriteArvore;
        arvore[i].X = i*arvore[i].sprite->Largura;
        arvore[i].Y = 74;
    }
}

double getY(int LimInf, int LimSup, int Abertura, int Amplitude)
{
    int GAP = LimSup-LimInf-(2*Amplitude)-(Abertura);
    double Valor = rand()%GAP;
    return Valor + LimInf + Amplitude + (Abertura/2);
}

void getNovoObstaculo(int Indice, int PrimeiroObstaculo)
{
    double X;
    double Abertura = 175.0;
    double Amplitude = 150.0;
    double Y = getY(SpriteChao.Altura, ALT_TELA, Abertura, Amplitude);
    double Vy = (rand()%100)/100.0;

    if(PrimeiroObstaculo == 1)
    {
        X = 1100;
    }
    else
    {
        int Indice = procurarUltimoObstaculo();
        X = canoSuperior[Indice].X + 275;
    }

    double Direcao;

    if(rand()%2 == 0)
    {
        Direcao = 1;
    }
    else
    {
        Direcao = -1;
    }

    if(CanoParaquedasCooldown >= 4500.0)
    {
        CanoParaquedasCooldown = 0;

        Abertura = 75;
        Vy = 0;
        Amplitude = 0;
    }

    canoSuperior[Indice].sprite = &SpriteCano;
    canoSuperior[Indice].X = X;
    canoSuperior[Indice].Y = (Y+Abertura/2.0);
    canoSuperior[Indice].Vy = Direcao*Vy;
    canoSuperior[Indice].AmplitudeMaxima = Amplitude;
    canoSuperior[Indice].AmplitudeAtual = 0;

    canoInferior[Indice].sprite = &SpriteCano;
    canoInferior[Indice].X = X-1;
    canoInferior[Indice].Y = (Y-Abertura/2.0) - SpriteCano.Altura;
    canoInferior[Indice].Vy = Direcao*Vy;
    canoInferior[Indice].AmplitudeMaxima = Amplitude;
    canoInferior[Indice].AmplitudeAtual = 0;

}

void InicializarObstaculos()
{
    for(int i=0; i<QTD_OBSTACULOS; i++)
    {
        canoSuperior[i].X = 0;
        canoInferior[i].X = 0;
    }
    CanoParaquedasCooldown = 0;

    getNovoObstaculo(0, 1);
    for(int i=1; i<QTD_OBSTACULOS; i++)
    {
        getNovoObstaculo(i, 0);
    }
}




void InicializarPassaro(int Indice, double* DNA, double X, double Y)
{
    Passaro[Indice].Estado = 0;
    Passaro[Indice].Angulo = 0;
    Passaro[Indice].X = X;
    Passaro[Indice].Y = Y;
    Passaro[Indice].VelocidadeY = 0;
    Passaro[Indice].SpriteAtual = 0;
    Passaro[Indice].ParaquedasCooldown = 0;

    if(Passaro[Indice].ResetarFitness == 1)
    {
        Passaro[Indice].Fitness = 0;
    }
    else
    {
        Passaro[Indice].Estado = 3;
        PassarosMortos++;
    }

    for(int i=0; i<Passaro[Indice].TamanhoDNA; i++)
    {
        Passaro[Indice].DNA[i] = DNA[i];
    }

    RNA_CopiarVetorParaCamadas(Passaro[Indice].Cerebro, Passaro[Indice].DNA);
}

void InicializarGrafico()
{
    for(int i=0; i<LARG_GRAFICO; i++)
    {
        grafico.MediaFitness[i] = 0;
        grafico.MelhorFitness[i] = 0;
    }
}

