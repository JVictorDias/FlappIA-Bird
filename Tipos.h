
#define LARG_GRAFICO            297
#define CHAO_QUANTIDADE         10

#define QTD_SPRITE_CACTUS       6
#define QTD_OBSTACULOS          6

#define QTD_NUVEM               3
#define QTD_PREDIO              3
#define QTD_ARVORE              3


typedef struct passaros
{
    double X, Y;
    double VelocidadeY;
    double Angulo;

    Sprite* sprite[QTD_SPRITES_BIRDS];
    int SpriteAtual;

    int Estado;
    int TimerFrame;
    int ResetarFitness;

    int TamanhoDNA;
    double* DNA;
    double Fitness;

    RedeNeural* Cerebro;

    double ParaquedasCooldown;

}   Passaros;

typedef struct obstaculo
{
    double X, Y;
    double Vy;
    double AmplitudeMaxima;
    double AmplitudeAtual;
    Sprite* sprite;

}   Obstaculo;

typedef struct chao
{
    double X, Y;
    Sprite* sprite;

}   Chao;

typedef struct grafico
{
    double MediaFitness[LARG_GRAFICO];
    double MelhorFitness[LARG_GRAFICO];

}   Grafico;

typedef struct enfeite
{
    double X, Y;
    Sprite* sprite;

}   Enfeite;



