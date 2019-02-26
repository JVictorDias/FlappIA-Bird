



double DistanciaHorizonalProximoObstaculo(double X)
{
    int indice = ProcurarProximoObstaculo(X);

    return (canoSuperior[indice].X + (SpriteCano.Largura/2.0)) - X;
}

double DistanciaVerticalProximoObstaculo(double X, double Y)
{
    int indice = ProcurarProximoObstaculo(X);

    return (((canoInferior[indice].Y + SpriteCano.Altura) + canoSuperior[indice].Y)/2.0) - Y;
}

double VelocidadeProximoObstaculo(double X)
{
    int indice = ProcurarProximoObstaculo(X);

    return canoSuperior[indice].Vy;
}

double AlturaProximoObstaculo(double X)
{
    int indice = ProcurarProximoObstaculo(X);

    return ((canoInferior[indice].Y + SpriteCano.Altura) + canoSuperior[indice].Y)/2.0;
}

double AberturaProximoObstaculo(double X)
{
    int indice = ProcurarProximoObstaculo(X);

    return canoSuperior[indice].Y - (canoInferior[indice].Y + SpriteCano.Altura);
}
