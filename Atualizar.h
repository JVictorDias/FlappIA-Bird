
Passaros* getMelhorPassaro()
{
    double Maior = 0;
    int Indice = 0;

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        if(Passaro[i].Estado != 3 && Passaro[i].X > Maior)
        {
            Maior = Passaro[i].X;
            Indice = i;
        }
    }
    return &Passaro[Indice];
}


void AtualizarMelhorPassaro()
{
    if(MODO_JOGO == TESTE)
    {
        MelhorPassaro = &Passaro[0];
    }

    if(MODO_JOGO == DUELO)
    {
        MelhorPassaro = &Passaro[1];
    }

    if(MODO_JOGO == EVOLUCAO)
    {
        if(MelhorPassaro->Estado == 3)
        {
            MelhorPassaro = getMelhorPassaro();
        }
    }
}

void AtualizarAnguloPassaro()
{
    double Decremento = 0.8;

    for(int i=0; i<QuantidadePassaros; i++)
    {
        if(Passaro[i].Estado != 3 && Passaro[i].Estado != 2)
        {
            if(Passaro[i].Angulo - Decremento > -75.0)
            {
                Passaro[i].Angulo = Passaro[i].Angulo - Decremento;
            }
        }
    }
}

void AtualizarFramePassaro()
{
    for(int i=0; i<QuantidadePassaros; i++)
    {
        if(Passaro[i].Estado != 3)
        {
            if(TempoDecorrido(Passaro[i].TimerFrame) >= 0.1)
            {
                Passaro[i].SpriteAtual = (Passaro[i].SpriteAtual + 1)%3;

                ReiniciarTimer(Passaro[i].TimerFrame);
            }
            if(Passaro[i].Estado == 2)
            {
                Passaro[i].SpriteAtual = 1;
            }
        }
    }
}

