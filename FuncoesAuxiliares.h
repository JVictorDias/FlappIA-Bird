

double BestFitnessGeracao()
{
    double Maior = 0;
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        if(Passaro[i].Fitness > Maior)
        {
            Maior = Passaro[i].Fitness;
        }
    }
    return Maior;
}

double MediaFitnessGeracao()
{
    double Media = 0;
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Media = Media + Passaro[i].Fitness;
    }
    Media = Media/(double)POPULACAO_TAMANHO;
    return Media;
}

double BestFitnessEver()
{
    double Maior = 0;
    for(int i=0; i<GeracaoCompleta; i++)
    {
        if(BestFitnessPopulacao[i] > Maior)
        {
            Maior = BestFitnessPopulacao[i];
        }
    }
    return Maior;
}




double getRandomValue()
{
    return (rand()%20001/10.0) - 1000.0;
}


void SalvarRedeArquivo()
{
    double Maior = 0;
    int Indice = 0;
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        if(Passaro[i].Fitness > Maior)
        {
            Maior = Passaro[i].Fitness;
            Indice = i;
        }
    }

    char String[1000];
    sprintf(String, "redes\\%.2f - [%d,%d,%d,%d]",
            DistanciaRecorde,
            BIRD_BRAIN_QTD_LAYERS,
            BIRD_BRAIN_QTD_INPUT,
            BIRD_BRAIN_QTD_HIDE,
            BIRD_BRAIN_QTD_OUTPUT);

    FILE* f = fopen(String,"wb");
    fwrite(&Passaro[Indice].TamanhoDNA,  1,                              sizeof(int), f);
    fwrite(Passaro[Indice].DNA,         Passaro[Indice].TamanhoDNA, sizeof(double), f);
    fclose(f);

}

void InicializarNovaPartida();
void CarregarRede();

void VerificarTeclas()
{
    if(MODO_JOGO != 1)
    {
        if(PIG_Tecla == TECLA_BAIXO)
        {
            Periodo = Periodo/2.0;
        }
        if(PIG_Tecla == TECLA_CIMA)
        {
            Periodo = Periodo*2.0;
        }
    }

    if(PIG_Tecla == TECLA_ESC)
    {
        DesenharTela = -DesenharTela;
    }

    if(PIG_Tecla == TECLA_BARRAESPACO)
    {
        SinalPular = 1;
    }

    if(PIG_Tecla == TECLA_z)
    {
        SinalParaquedas = 1;
    }
}

int procurarUltimoObstaculo()
{
    double Menor = canoSuperior[0].X;
    int Indice = 0;

    for(int i=1; i<QTD_OBSTACULOS; i++)
    {
        if(canoSuperior[i].X > Menor)
        {
            Menor = canoSuperior[i].X;
            Indice = i;
        }
    }

    return Indice;
}


int ProcurarProximoObstaculo(double X)
{
    int Indice;
    double Menor;
    int Largura;

    Menor = 9999999;
    Indice = 0;
    for(int i=0; i<QTD_OBSTACULOS; i++)
    {
        Largura = canoSuperior[i].sprite->Largura;

        if(canoSuperior[i].X < Menor && canoSuperior[i].X + Largura > X-(SpriteBirds[0][0].Largura/2))
        {
            Menor = canoSuperior[i].X;
            Indice = i;
        }
    }

    return Indice;
}


