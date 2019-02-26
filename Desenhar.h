

PIG_Cor calcularCor(double Intensidade, PIG_Cor CorBase)
{
    CorBase.r = CorBase.r*Intensidade;
    CorBase.g = CorBase.g*Intensidade;
    CorBase.b = CorBase.b*Intensidade;

    return CorBase;
}


void DesenharRedeNeural(int X, int Y, int Largura, int Altura)
{
    double NeuroEntradaX[BIRD_BRAIN_QTD_INPUT];
    double NeuroEntradaY[BIRD_BRAIN_QTD_INPUT];
    double NeuroEscondidoX[BIRD_BRAIN_QTD_LAYERS][BIRD_BRAIN_QTD_HIDE];
    double NeuroEscondidoY[BIRD_BRAIN_QTD_LAYERS][BIRD_BRAIN_QTD_HIDE];
    double NeuroSaidaX[BIRD_BRAIN_QTD_OUTPUT];
    double NeuroSaidaY[BIRD_BRAIN_QTD_OUTPUT];

    double Entrada[BIRD_BRAIN_QTD_INPUT];
    double XOrigem = X + 325;
    double YOrigem = Y + Altura;
    double LarguraPintura = Largura;
    double AlturaPintura = Altura;
    double TamanhoNeuronio = 20;
    char String[1000];
    int Sprite;
    int qtdEscondidas       = MelhorPassaro->Cerebro->QuantidadeEscondidas;
    int qtdNeuroEntrada     = MelhorPassaro->Cerebro->CamadaEntrada.QuantidadeNeuronios;
    int qtdNeuroEscondidas  = MelhorPassaro->Cerebro->CamadaEscondida[0].QuantidadeNeuronios;
    int qtdNeuroSaida       = MelhorPassaro->Cerebro->CamadaSaida.QuantidadeNeuronios;

    for(int i=0; i<BIRD_BRAIN_QTD_INPUT; i++)
    {
        Entrada[i] = MelhorPassaro->Cerebro->CamadaEntrada.Neuronios[i].Saida;
    }

    double EscalaAltura = ((double)AlturaPintura)/(double)(qtdNeuroEscondidas-1);
    double EscalaLargura = ((double)LarguraPintura-475)/(double)(qtdEscondidas+1);

    if(PIG_meuTeclado[TECLA_BARRAESPACO])
    {
        sprintf(String,"[Obstáculo] Distancia Horizontal: %.2f", Entrada[0]);
        EscreverEsquerda(String, X + 15, YOrigem - 0*EscalaAltura -5, Fonte);

        sprintf(String,"[Obstáculo] Distancia Vertical: %.2f", Entrada[1]);
        EscreverEsquerda(String, X + 15, YOrigem - 1*EscalaAltura -5, Fonte);

        sprintf(String,"[Obstáculo] Velocidade: %.2f", Entrada[2]);
        EscreverEsquerda(String, X + 15, YOrigem - 2*EscalaAltura -5, Fonte);

        sprintf(String,"[Obstáculo] Abertura: %.2f", Entrada[3]);
        EscreverEsquerda(String, X + 15, YOrigem - 3*EscalaAltura -5, Fonte);
    }

    double temp = YOrigem - (EscalaAltura*(qtdNeuroEscondidas-2))/2.0 + (EscalaAltura*(qtdNeuroSaida-1))/2.0;

    sprintf(String,"Pular");
    EscreverEsquerda(String, X + Largura - 135, temp - 0*EscalaAltura -5, Fonte);

    sprintf(String,"Paraquedas");
    EscreverEsquerda(String, X + Largura - 135, temp - 1*EscalaAltura -5, FontePequena);

    /// Desenhar Conexoes

    for(int i=0; i<qtdNeuroEntrada-1; i++)
    {
        NeuroEntradaX[i] = XOrigem;
        NeuroEntradaY[i] = YOrigem - i*EscalaAltura;
    }

    for(int i=0; i<qtdEscondidas; i++)
    {
        int qtdCamadaAnterior;
        Camada* CamadaAnterior;
        double *XAnterior, *YAnterior;

        if(i == 0)
        {
            qtdCamadaAnterior = qtdNeuroEntrada;
            CamadaAnterior = &MelhorPassaro->Cerebro->CamadaEntrada;
            XAnterior = NeuroEntradaX;
            YAnterior = NeuroEntradaY;
        }
        else
        {
            qtdCamadaAnterior = qtdNeuroEscondidas;
            CamadaAnterior = &MelhorPassaro->Cerebro->CamadaEscondida[i-1];
            XAnterior = NeuroEscondidoX[i-1];
            YAnterior = NeuroEscondidoY[i-1];
        }

        for(int j=0; j<qtdNeuroEscondidas-1; j++)
        {
            NeuroEscondidoX[i][j] = XOrigem + (i+1)*EscalaLargura;
            NeuroEscondidoY[i][j] = YOrigem - j*EscalaAltura;

            for(int k=0; k<qtdCamadaAnterior-1; k++)
            {
                double Peso = MelhorPassaro->Cerebro->CamadaEscondida[i].Neuronios[j].Peso[k];
                double Saida = CamadaAnterior->Neuronios[k].Saida;
                if(Peso*Saida > 0)
                {
                    DesenharLinhaSimples(XAnterior[k],
                                         YAnterior[k],
                                         NeuroEscondidoX[i][j],
                                         NeuroEscondidoY[i][j], VERMELHO);

                }
                else
                {
                    DesenharLinhaSimples(XAnterior[k],
                                         YAnterior[k],
                                         NeuroEscondidoX[i][j],
                                         NeuroEscondidoY[i][j], CINZA_CLARO);
                }
            }
        }
    }

    for(int i=0; i<qtdNeuroSaida; i++)
    {
        int UltimaCamada = MelhorPassaro->Cerebro->QuantidadeEscondidas-1;
        double temp = YOrigem - (EscalaAltura*(qtdNeuroEscondidas-2))/2.0 + (EscalaAltura*(qtdNeuroSaida-1))/2.0;

        NeuroSaidaX[i] = XOrigem + (qtdEscondidas+1)*EscalaLargura;
        NeuroSaidaY[i] = temp - i*EscalaAltura;

        for(int k=0; k<qtdNeuroEscondidas-1; k++)
        {
            double Peso = MelhorPassaro->Cerebro->CamadaSaida.Neuronios[i].Peso[k];
            double Saida = MelhorPassaro->Cerebro->CamadaEscondida[UltimaCamada].Neuronios[k].Saida;

            if(Peso*Saida > 0)
            {
                DesenharLinhaSimples(NeuroEscondidoX[UltimaCamada][k],
                                     NeuroEscondidoY[UltimaCamada][k],
                                     NeuroSaidaX[i],
                                     NeuroSaidaY[i], VERMELHO);


            }
            else
            {
                DesenharLinhaSimples(NeuroEscondidoX[UltimaCamada][k],
                                     NeuroEscondidoY[UltimaCamada][k],
                                     NeuroSaidaX[i],
                                     NeuroSaidaY[i], CINZA_CLARO);
            }
        }
    }

    /// Desenhar Neuronios

    for(int i=0; i<qtdNeuroEntrada-1; i++)
    {
        PIG_Cor cor;
        double Opacidade;

        switch(i)
        {
            case 0:
            {
                Opacidade = fabs(Entrada[0])/800.0;
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
            case 1:
            {
                Opacidade = Entrada[1]/73.0;
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
            case 2:
            {
                Opacidade = Entrada[2]/90.0;
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
            case 3:
            {
                Opacidade = Entrada[3]/47.0;
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
            case 4:
            {
                Opacidade = Entrada[4]/8.0;
                if(Entrada[4] > 8)
                {
                    Opacidade = 1;
                }
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
            case 5:
            {
                Opacidade = Entrada[5]/120.0;
                cor = calcularCor(Opacidade, BRANCO);
            }   break;
        }

        DefinirColoracao(SpriteNeuronAtivado, cor);
        DefinirOpacidade(SpriteLuz, Opacidade*255);

        DesenharSprite(SpriteLuz,
                       NeuroEntradaX[i],
                       NeuroEntradaY[i],
                       3.5*TamanhoNeuronio,
                       3.5*TamanhoNeuronio, 0, 0);

        DesenharSprite(SpriteNeuronAtivado,
                       NeuroEntradaX[i],
                       NeuroEntradaY[i],
                       TamanhoNeuronio,
                       TamanhoNeuronio, 0, 0);

        DefinirOpacidade(SpriteLuz, 255);
        DefinirColoracao(SpriteNeuronAtivado, BRANCO);

        DesenharSprite(SpriteSeta,
                       NeuroEntradaX[i] - 56,
                       NeuroEntradaY[i],
                       64,
                       12, 0, 0);
    }

    for(int i=0; i<qtdEscondidas; i++)
    {
        for(int j=0; j<qtdNeuroEscondidas-1; j++)
        {
            Sprite = SpriteNeuronDesativado;
            double SaidaNeuronio = MelhorPassaro->Cerebro->CamadaEscondida[i].Neuronios[j].Saida;
            if(SaidaNeuronio > 0)
            {
                Sprite = SpriteNeuronAtivado;
                DesenharSprite( SpriteLuz,
                                NeuroEscondidoX[i][j],
                                NeuroEscondidoY[i][j],
                                3.5*TamanhoNeuronio,
                                3.5*TamanhoNeuronio, 0, 0);
            }
            DesenharSprite(Sprite,
                           NeuroEscondidoX[i][j],
                           NeuroEscondidoY[i][j],
                           TamanhoNeuronio,
                           TamanhoNeuronio, 0, 0);
        }
    }

    for(int i=0; i<qtdNeuroSaida; i++)
    {
        Sprite = SpriteNeuronDesativado;
        double SaidaNeuronio = MelhorPassaro->Cerebro->CamadaSaida.Neuronios[i].Saida;
        if(SaidaNeuronio > 0.5)
        {
            Sprite = SpriteNeuronAtivado;
            DesenharSprite(SpriteLuz,
                       NeuroSaidaX[i],
                       NeuroSaidaY[i],
                       3.5*TamanhoNeuronio,
                       3.5*TamanhoNeuronio, 0, 0);
        }
        DesenharSprite(Sprite,
                       NeuroSaidaX[i],
                       NeuroSaidaY[i],
                       TamanhoNeuronio,
                       TamanhoNeuronio, 0, 0);
    }
}

void DesenharGrafico(int X, int Y, double Largura, int Altura)
{
    SDL_Point PontosBest[LARG_GRAFICO];
    SDL_Point PontosMedia[LARG_GRAFICO];
    SDL_Point PontosMediaFilhos[LARG_GRAFICO];

    double scala;
    double scalaHorizontal;

    if(BestFitnessGeracao() > BestFitnessEver())
    {
        scala = BestFitnessGeracao()/(double)Altura;
    }
    else
    {
        scala = BestFitnessEver()/(double)Altura;
    }

    if(GeracaoCompleta == 0)
    {
        scalaHorizontal = 0;
    }
    else
    {
        scalaHorizontal = (double)Largura/(double)(GeracaoCompleta);
    }

    for(int i=1; i<11; i++)
    {
        DesenharLinhaSimples(X,
                             Y+i*(Altura/10),
                             X+Largura,
                             Y+i*(Altura/10),
                             CINZA_CLARO);

        DesenharLinhaSimples(X+i*(Largura/10),
                             Y,
                             X+i*(Largura/10),
                             Y+Altura,
                             CINZA_CLARO);
    }

    DesenharLinhaSimples(X, Y, X+Largura, Y,        PRETO);
    DesenharLinhaSimples(X, Y, X,         Y+Altura, PRETO);

    for(int i=0; i<GeracaoCompleta+1; i++)
    {
        int PontoX = X+1+(i*scalaHorizontal);
        double YMedia, YBest;

        if(i == GeracaoCompleta)
        {
            YMedia = Y+1+(int)(MediaFitnessGeracao()/scala);
            YBest = Y+1+(int)(BestFitnessGeracao()/scala);
        }
        else
        {
            YMedia = Y+1+(int)(MediaFitnessPopulacao[i]/scala);
            YBest = Y+1+(int)(BestFitnessPopulacao[i]/scala);
        }

        DesenharPonto(PontoX, YMedia, VERMELHO, 3);
        PontosMedia[i].x = PontoX;
        PontosMedia[i].y = ALT_TELA - YMedia;

        DesenharPonto(PontoX, YBest,  AZUL, 3);
        PontosBest[i].x = PontoX;
        PontosBest[i].y = ALT_TELA - YBest;
    }

    DesenharLinhas(PontosBest, GeracaoCompleta+1, AZUL);
    DesenharLinhas(PontosMedia, GeracaoCompleta+1, VERMELHO);
}

void DesenharObstaculos()
{
    for(int i=0; i<QTD_OBSTACULOS; i++)
    {
        if(canoSuperior[i].Y - (canoInferior[i].Y + SpriteCano.Altura) <= 75)
        {
            DefinirColoracao(SpriteCano.Objeto, VERMELHO);
        }

        DesenharSprite(canoSuperior[i].sprite->Objeto,
                       canoSuperior[i].X,
                       canoSuperior[i].Y,
                       canoSuperior[i].sprite->Largura,
                       canoSuperior[i].sprite->Altura,
                       0, 1);

        DesenharSprite(canoInferior[i].sprite->Objeto,
                       canoInferior[i].X,
                       canoInferior[i].Y,
                       canoInferior[i].sprite->Largura,
                       canoInferior[i].sprite->Altura,
                       180, 1);

        if(canoSuperior[i].Y - (canoInferior[i].Y + SpriteCano.Altura) <= 75)
        {
            DefinirColoracao(SpriteCano.Objeto, BRANCO);
        }
    }
}

void DesenharChao()
{
    for(int i=0; i<CHAO_QUANTIDADE; i++)
    {
        DesenharSprite(chao[i].sprite->Objeto,
                       chao[i].X,
                       chao[i].Y,
                       chao[i].sprite->Largura,
                       chao[i].sprite->Altura,
                       0, 1);
    }
}

void DesenharFundo()
{
    PIG_Cor cor = ((PIG_Cor){110,200,205,255});
    DesenharRetangulo(0, 0, ALT_TELA, LARG_TELA, cor);
}

void DesenharPassaros()
{
    int Frame, Largura, Altura, Sprite;
    double Angulo;

    for(int i=0; i<QuantidadePassaros; i++)
    {
        if(Passaro[i].Estado == 2)
        {
            DesenharSprite(SpriteParaquedas.Objeto,
                           Passaro[i].X,
                           Passaro[i].Y + SpriteBirds[0][0].Altura/2,
                           SpriteParaquedas.Largura,
                           SpriteParaquedas.Altura,
                           0, 0);
        }

        Sprite  = Passaro[i].SpriteAtual;

        Frame   = Passaro[i].sprite[Sprite]->Objeto;
        Largura = Passaro[i].sprite[Sprite]->Largura;
        Altura  = Passaro[i].sprite[Sprite]->Altura;
        Angulo  = Passaro[i].Angulo;

        DesenharSprite( Frame,
                        Passaro[i].X,
                        Passaro[i].Y,
                        Largura,
                        Altura,
                        Angulo-20, 0);

    }
}

void DesenharNuvens()
{
    for(int i=0; i<QTD_NUVEM; i++)
    {
        DesenharSprite(nuvem[i].sprite->Objeto,
                       nuvem[i].X,
                       nuvem[i].Y,
                       nuvem[i].sprite->Largura,
                       nuvem[i].sprite->Altura,
                       0, 1);
    }
}

void DesenharPredios()
{
    for(int i=0; i<QTD_PREDIO; i++)
    {
        DesenharSprite(predio[i].sprite->Objeto,
                       predio[i].X,
                       predio[i].Y,
                       predio[i].sprite->Largura,
                       predio[i].sprite->Altura,
                       0, 1);
    }
}

void DesenharArvores()
{
    for(int i=0; i<QTD_ARVORE; i++)
    {
        DesenharSprite(arvore[i].sprite->Objeto,
                       arvore[i].X,
                       arvore[i].Y,
                       arvore[i].sprite->Largura,
                       arvore[i].sprite->Altura,
                       0, 1);
    }
}

void DesenharInterface()
{
    PIG_Cor cor = ((PIG_Cor){110,200,205,255});
    double X = LARG_TELA-300;

    DesenharRetangulo(X, 0, ALT_TELA, 300, cor);
    DesenharLinhaSimples(X,0,X,ALT_TELA,PRETO);
    DesenharGrafico(X, 0, LARG_GRAFICO, 300);
    DesenharRedeNeural(X-220, 360, 600, 100);
}

void Desenhar()
{
    int BASE = 730;
    double X = LARG_TELA-290;

    if(DesenharTela == 1)
    {
        IniciarDesenho();

        DesenharFundo();

        DesenharNuvens();
        DesenharPredios();
        DesenharArvores();

        DesenharPassaros();
        DesenharObstaculos();
        DesenharChao();

        DesenharInterface();

        char String[1000];

        sprintf(String,"Geração: %d", Geracao);
        EscreverEsquerda(String, X, BASE, FontePretaGrande);

        sprintf(String,"Clock: %f segundo", Periodo);
        EscreverEsquerda(String, X, BASE-30, FontePretaGrande);

        sprintf(String,"Distancia Recorde:");
        EscreverEsquerda(String, X, BASE-60, FontePretaGrande);

        sprintf(String,"%.0f pixels", DistanciaRecorde);
        EscreverEsquerda(String, X+165, BASE-60, FonteAzulGrande);

        sprintf(String,"Distancia Atual:");
        EscreverEsquerda(String, X, BASE-90, FontePretaGrande);

        sprintf(String,"%.0f pixels", DistanciaAtual);
        EscreverEsquerda(String, X+165, BASE-90, FontePretaGrande);

        EncerrarDesenho();
    }
}
