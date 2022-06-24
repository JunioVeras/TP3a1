// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: codigo completo do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <iostream>
#include <stack>

struct Piso
{
    int altura;
    int disponivel;
};

struct Mesa
{
    int comprimento;
    int largura;
};

class Casa
{
    private:
        int N, M, K;
        Piso **planta;
        Mesa *mesas;
        int *retangulos;
        void insere_retangulo(int altura, int largura);

    public:
        Casa();
        void calcula_alturas();
        void calcula_retangulos();
        void verifica_mesas();
        void imprimir();

};

Casa::Casa()
// Descricao: construtor da classe casa
// Entrada: entrada de dados pela linha de comandos
// Saida: as variaveis da classe sao inicializadas
{
    std::cin >> this->N;
    std::cin >> this->M;

    // criacao da matriz planta que ira conter as caracteristicas da planta da casa, cada celula corresponde a um "piso" da casa
    this->planta = new Piso*[this->N];
    for(int i = 0; i < this->N; i++)
    {
        this->planta[i] = new Piso[this->M];
    }

    for(int i = 0; i < this->N; i++)
    {
        for(int j = 0; j < this->M; j++)
        {
            char piso_atual;
            std::cin >> piso_atual;
            if(piso_atual == '#')
            {
                this->planta[i][j].disponivel = 0;
            }
            else
            {
                this->planta[i][j].disponivel = 1;
            }
            this->planta[i][j].altura = 0;
        }
    }

    std::cin >> this->K;

    // criacao do vetor de mesas que ira receber todas as dimensoes de mesas do problema
    this->mesas = new Mesa[this->K];
    for(int i = 0; i < this->K; i++)
    {
        std::cin >> this->mesas[i].comprimento;
        std::cin >> this->mesas[i].largura;
    }

    // criacao do vetor de retangulos que ira conter as dimensoes dos maiores retangulos da casa indexados pela altura do mesmo
    this->retangulos = new int[this->N+1];
    for(int i = 0; i < this->N+1; i++)
    {
        this->retangulos[i] = 0;
    }
}

void Casa::calcula_alturas()
// Descricao: realiza o calculo das possiveis alturas para os retangulos da casa, cada piso disponivel tem como altura 1 + a quantidade de elementos acima dele ate uma parede
// Entrada: void
// Saida: a matriz planta tem todas as alturas inicializadas
{
    for(int j = 0; j < this->M; j++)
    {
        int altura = 0;
        for(int i = 0; i < this->N; i++)
        {
            if(this->planta[i][j].disponivel == 0)
            {
                altura = 0;
            }
            else
            {
                altura++;
                this->planta[i][j].altura = altura;
            }
        }
    }
}

void Casa::insere_retangulo(int altura, int largura)
// Descricao: realiza a insercao dos maiores retangulos no vetor de retangulos, indexados pela altura
// Entrada: altura e largura de um retangulo
// Saida: se a largura do retangulo for maior que a do ja armazenado para aquela altura ele eh inserido
{
    if(this->retangulos[altura] < largura)
    {
        this->retangulos[altura] = largura;
    }
}

void Casa::calcula_retangulos()
// Descricao: varre a planta encontrando todos os retangulos de maior largura para cada altura
// Entrada: void
// Saida: o vetor de retangulos eh populado com a maior largura para cada altura
{
    for(int i = this->N-1; i >=0; i--)
    {
        for(int j = 0; j < this->M; j++)
        {
            if(this->planta[i][j].disponivel == 0)
            {
                continue;
            }

            // eh feita uma busca para esquerda e para direita do piso atual procurando quais outros pisos tem alturas compativeis para formacao de um retangulo com sua altura
            int compativel_esquerda = 0;
            int compativel_direita = this->M - 1;
            for(int k = j - 1; k >= 0; k--)
            {
                if(this->planta[i][k].altura < this->planta[i][j].altura)
                {
                    compativel_esquerda = k + 1;
                    break;
                }
            }
            for(int k = j + 1; k < this->M; k++)
            {
                if(this->planta[i][k].altura < this->planta[i][j].altura)
                {
                    compativel_direita = k - 1;
                    break;
                }
            }

            // eh feita uma insercao do retangulo formado com a altura do piso e a largura determinada pelo intervalo compativel com aquele piso
            insere_retangulo(this->planta[i][j].altura, compativel_direita - compativel_esquerda + 1);
        }
    }
}

bool operator>(Mesa mesa1, Mesa mesa2)
// Descricao: operador "maior que" para mesas
// Entrada: mesa1 e mesa2
// Saida: true se a mesa1 tem area maior que a mesa2 e false se nao
{
    if(mesa1.comprimento * mesa1.largura > mesa2.comprimento * mesa2.largura)
    {
        return 1;
    }
    return 0;
}

bool operator==(Mesa mesa1, Mesa mesa2)
// Descricao: operador "igual" para mesas
// Entrada: mesa1 e mesa2
// Saida: true se a mesa1 tem area igual a mesa2 e false se nao
{
    if(mesa1.comprimento * mesa1.largura == mesa2.comprimento * mesa2.largura)
    {
        return 1;
    }
    return 0;
}

void Casa::verifica_mesas()
// Descricao: verifica qual a maior mesa que cabe na casa
// Entrada: void
// Saida: impressao na tela das dimensoes da maior mesa
{
    Mesa maior_mesa;
    maior_mesa.comprimento = 0;
    maior_mesa.largura = 0;
    for(int i = 0; i < this->K; i++)
    {
        // verifica se o comprimento da mesa tem tamanho menor ou igual a altura maxima para fazer o enderecamento no vetor de retangulos
        if(this->mesas[i].comprimento <= this->N)
        {
            // verifica se a outra dimensao eh menor ou igual ao valor armazenado no vetor de retangulos 
            if(this->retangulos[this->mesas[i].comprimento] >= this->mesas[i].largura)
            {
                if(maior_mesa == this->mesas[i])
                {
                    maior_mesa = (this->mesas[i].largura > maior_mesa.largura) ? this->mesas[i] : maior_mesa;
                }
                maior_mesa = (this->mesas[i] > maior_mesa) ? this->mesas[i] : maior_mesa;
            }
        }
        // verifica se a largura da mesa tem tamanho menor ou igual a altura maxima para fazer o enderecamento no vetor de retangulos
        if(this->mesas[i].largura <= this->N)
        {
            // verifica se a outra dimensao eh menor ou igual ao valor armazenado no vetor de retangulos 
            if(this->retangulos[this->mesas[i].largura] >= this->mesas[i].comprimento)
            {
                if(maior_mesa == this->mesas[i])
                {
                    maior_mesa = (this->mesas[i].largura > maior_mesa.largura) ? this->mesas[i] : maior_mesa;
                }
                maior_mesa = (this->mesas[i] > maior_mesa) ? this->mesas[i] : maior_mesa;
            }
        }
    }
    std::cout << maior_mesa.comprimento << " " << maior_mesa.largura;
}

// void Casa::imprimir()
// {
//     for(int i = 0; i < this->N; i++)
//     {
//         for(int j = 0; j < this->M; j++)
//         {
//             printf("%2d ", this->planta[i][j].altura);
//         }
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;
//     for(int i = 0; i <= this->N; i++)
//     {
//         std::cout << i << " " << this->retangulos[i];
//         std::cout << std::endl;
//     }
// }

int main()
// Descricao: main
// Entrada: void
// Saida:
{
    Casa casa;
    casa.calcula_alturas();
    casa.calcula_retangulos();
    // casa.imprimir();
    casa.verifica_mesas();
    return 0;
}