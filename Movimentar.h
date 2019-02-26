

void MovimentarEnfeites()
{
    for(int i=0; i<QTD_NUVEM; i++)
    {
        nuvem[i].X = nuvem[i].X + VELOCIDADE/45.0;

        if(nuvem[i].X <= -nuvem[i].sprite->Largura)
        {
            nuvem[i].X = nuvem[i].X + nuvem[i].sprite->Largura*QTD_NUVEM;
        }
    }

    for(int i=0; i<QTD_PREDIO; i++)
    {
        predio[i].X = predio[i].X + VELOCIDADE/15.0;

        if(predio[i].X <= -predio[i].sprite->Largura)
        {
            predio[i].X = predio[i].X + predio[i].sprite->Largura*QTD_PREDIO;
        }
    }

    for(int i=0; i<QTD_ARVORE; i++)
    {
        arvore[i].X = arvore[i].X + VELOCIDADE/5.0;

        if(arvore[i].X <= -arvore[i].sprite->Largura)
        {
            arvore[i].X = arvore[i].X + arvore[i].sprite->Largura*QTD_ARVORE;
        }
    }
}

void MovimentarChao()
{
    for(int i=0; i<CHAO_QUANTIDADE; i++)
    {
        chao[i].X = chao[i].X + VELOCIDADE;

        if(chao[i].X <= -chao[i].sprite->Largura)
        {
            chao[i].X = chao[i].X + chao[i].sprite->Largura*(CHAO_QUANTIDADE);
        }
    }
}



void MovimentarObstaculos()
{
    int Largura;

    CanoParaquedasCooldown = CanoParaquedasCooldown + fabs(VELOCIDADE);
    for(int i=0; i<QTD_OBSTACULOS; i++)
    {
        canoSuperior[i].X = canoSuperior[i].X + VELOCIDADE;
        canoInferior[i].X = canoInferior[i].X + VELOCIDADE;

        Largura = SpriteCano.Largura;

        if(canoSuperior[i].X + Largura < 0)
        {
            getNovoObstaculo(i,0);
        }

        canoSuperior[i].Y = canoSuperior[i].Y + canoSuperior[i].Vy;
        canoSuperior[i].AmplitudeAtual = canoSuperior[i].AmplitudeAtual + fabs(canoSuperior[i].Vy);
        if(canoSuperior[i].AmplitudeAtual > canoSuperior[i].AmplitudeMaxima)
        {
            canoSuperior[i].AmplitudeAtual = 0;
            canoSuperior[i].Vy = -canoSuperior[i].Vy;
        }

        canoInferior[i].Y = canoInferior[i].Y + canoInferior[i].Vy;
        canoInferior[i].AmplitudeAtual = canoInferior[i].AmplitudeAtual + fabs(canoInferior[i].Vy);
        if(canoInferior[i].AmplitudeAtual > canoInferior[i].AmplitudeMaxima)
        {
            canoInferior[i].AmplitudeAtual = 0;
            canoInferior[i].Vy = -canoInferior[i].Vy;
        }
    }
}

void MovimentarPassaros()
{
    for(int i=0; i<QuantidadePassaros; i++)
    {
        if(Passaro[i].Estado == 3)  /// MUERTO
        {
            Passaro[i].X = Passaro[i].X + VELOCIDADE;

            if(Passaro[i].Y <= 80)
            {
                Passaro[i].VelocidadeY = 0;
                Passaro[i].Y = 80;
            }
            else
            {
                Passaro[i].Y = Passaro[i].Y + Passaro[i].VelocidadeY;
            }
        }
        else
        {
            Passaro[i].ParaquedasCooldown = Passaro[i].ParaquedasCooldown + fabs(VELOCIDADE);

            if(Passaro[i].Estado == 2)
            {
                Passaro[i].Fitness = Passaro[i].Fitness + 1.0;
            }
            if(Passaro[i].Estado == 1)
            {
                Passaro[i].Fitness = Passaro[i].Fitness + 2.0;
            }


            Passaro[i].Y = Passaro[i].Y + Passaro[i].VelocidadeY;

            if(Passaro[i].Y < 75 || Passaro[i].Y > 800)
            {
                MatarPassaro(i);
            }
        }
    }
}


