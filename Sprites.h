
#define OBSTACULOS_SPRITE_QUANTIDADE    8
#define QTD_COR_BIRDS                   6
#define QTD_SPRITES_BIRDS               3

typedef struct sprite
{
    int Largura, Altura;
    int Objeto;

}   Sprite;

    Sprite SpriteCano;
    Sprite SpriteChao;
    Sprite SpriteBirds[6][3];
    Sprite SpriteNuvem, SpriteArvore, SpritePredio;
    Sprite SpriteParaquedas;

    int SpriteNeuronDesativado;
    int SpriteNeuronAtivado;
    int SpriteLuz;
    int SpriteSeta;


void InicializarSpriteCano()
{
    SpriteCano.Objeto = CriarSprite("imagens\\cano.bmp");
    SpriteCano.Largura = 86;
    SpriteCano.Altura = 836;
}

void InicializarSpritesBird()
{
    int Largura[3] = {54,55,58};
    int Altura[3] = {46,46,46};

    char String[1000];

    for(int i=0; i<QTD_COR_BIRDS; i++)
    {
        for(int j=0; j<QTD_SPRITES_BIRDS; j++)
        {
            sprintf(String,"imagens\\flap%d%d.png", j+1, i);

            SpriteBirds[i][j].Objeto = CriarSprite(String);
            SpriteBirds[i][j].Largura = Largura[j];
            SpriteBirds[i][j].Altura = Altura[j];
        }
    }
}

void InicializarSpritesNeuronios()
{
    SpriteNeuronDesativado = CriarSprite("imagens//neuronio7.png");
    DefinirColoracao(SpriteNeuronDesativado, PRETO);

    SpriteNeuronAtivado = CriarSprite("imagens//neuronio7.png");
    DefinirColoracao(SpriteNeuronAtivado, BRANCO);

    SpriteLuz = CriarSprite("imagens//luz.png");

    SpriteSeta = CriarSprite("imagens\\seta2.png");
    DefinirColoracao(SpriteSeta, PRETO);
}

void InicializarSpriteChao()
{
    SpriteChao.Objeto = CriarSprite("imagens\\chao.png");
    SpriteChao.Largura = 209;
    SpriteChao.Altura = 75;
}

void InicializarSpriteNuvem()
{
    SpriteNuvem.Objeto = CriarSprite("imagens\\nuvens.png");
    SpriteNuvem.Largura = 959;
    SpriteNuvem.Altura = 114;
}

void InicializarSpritePredio()
{
    SpritePredio.Objeto = CriarSprite("imagens\\predios.png");
    SpritePredio.Largura = 959;
    SpritePredio.Altura = 54;
}

void InicializarSpriteArvore()
{
    SpriteArvore.Objeto = CriarSprite("imagens\\arvores.png");
    SpriteArvore.Largura = 959;
    SpriteArvore.Altura = 52;
}

void InicializarSpriteParaquedas()
{
    SpriteParaquedas.Objeto = CriarSprite("imagens\\paraquedas.png");
    SpriteParaquedas.Largura = 50;
    SpriteParaquedas.Altura = 50;
}

void InicializarSprites()
{
    InicializarSpriteNuvem();
    InicializarSpritePredio();
    InicializarSpriteArvore();

    InicializarSpriteChao();

    InicializarSpriteCano();
    InicializarSpritesBird();
    InicializarSpritesNeuronios();

    InicializarSpriteParaquedas();

}


Sprite* getPassaroSprite(int Indice, int Cor)
{
    return &SpriteBirds[Cor][Indice];
}



