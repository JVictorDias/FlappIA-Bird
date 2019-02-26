
void MatarPassaro(int Indice)
{
    if(Passaro[Indice].Estado != 3)
    {
        Passaro[Indice].Estado = 3;
        PassarosMortos++;
    }
}

int verificarColisao(   double X1, double Y1, double Larg1, double Alt1,
                        double X2, double Y2, double Larg2, double Alt2)
{
    if(X1 + Larg1 <= X2)
    {
        return 0;
    }
    if(X1 >= X2 + Larg2)
    {
        return 0;
    }
    if(Y1 + Alt1 <= Y2)
    {
        return 0;
    }
    if(Y1 >= Y2 + Alt2)
    {
        return 0;
    }
    return 1;
}


void getAtributosProximoCanoSuperior(double PassaroX, double* X, double* Y, double* Larg, double* Alt)
{
    int IndiceObstaculo = ProcurarProximoObstaculo(PassaroX);
    double Correcao = 4;

    *X = canoSuperior[IndiceObstaculo].X + Correcao;
    *Y = canoSuperior[IndiceObstaculo].Y;
    *Alt = SpriteCano.Altura;
    *Larg = SpriteCano.Largura - 2*Correcao;
}

void getAtributosProximoCanoInferior(double PassaroX, double* X, double* Y, double* Larg, double* Alt)
{
    int IndiceObstaculo = ProcurarProximoObstaculo(PassaroX);
    double Correcao = 4;

    *X = canoInferior[IndiceObstaculo].X + Correcao;
    *Y = canoInferior[IndiceObstaculo].Y;
    *Alt = SpriteCano.Altura;
    *Larg = SpriteCano.Largura - 2*Correcao;
}

void getAtributosPassaro(int i, double* PassaroX, double* PassaroY, double* PassaroLarg, double* PassaroAlt)
{
    double Correcao = 5;

    *PassaroX = Passaro[i].X - Passaro[i].sprite[Passaro[i].SpriteAtual]->Largura/2.0 + Correcao;
    *PassaroY = Passaro[i].Y - Passaro[i].sprite[Passaro[i].SpriteAtual]->Altura/2.0 + Correcao;
    *PassaroLarg = Passaro[i].sprite[Passaro[i].SpriteAtual]->Largura - 2*Correcao;
    *PassaroAlt  = Passaro[i].sprite[Passaro[i].SpriteAtual]->Altura - 2*Correcao;
}

void AplicarColisao()
{
    int IndiceObstaculo;
    double XObstaculo, YObstaculo, AlturaObstaculo, LarguraObstaculo;
    double PassaroX, PassaroY, PassaroLarg, PassaroAlt;
    int FatorDeCorrecaoHorizontal = 7;
    int FatorDeCorrecaoVertical = 5;

    for(int i=0; i<QuantidadePassaros; i++)
    {
        if(Passaro[i].Estado != 3)      /// MORTO
        {
            getAtributosPassaro(i, &PassaroX, &PassaroY, &PassaroLarg, &PassaroAlt);

            getAtributosProximoCanoSuperior(Passaro[i].X,
                                            &XObstaculo, &YObstaculo,
                                            &LarguraObstaculo, &AlturaObstaculo);

            if(verificarColisao(PassaroX,   PassaroY,   PassaroLarg,        PassaroAlt,
                                XObstaculo, YObstaculo, LarguraObstaculo,   AlturaObstaculo) == 1)
            {
                MatarPassaro(i);
                continue;
            }

            getAtributosProximoCanoInferior(Passaro[i].X,
                                            &XObstaculo, &YObstaculo,
                                            &LarguraObstaculo, &AlturaObstaculo);

            if(verificarColisao(PassaroX,   PassaroY,   PassaroLarg,        PassaroAlt,
                                XObstaculo, YObstaculo, LarguraObstaculo,   AlturaObstaculo) == 1)
            {
                MatarPassaro(i);
            }
        }
    }
}

