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
{
    std::cin >> this->N;
    std::cin >> this->M;

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

    this->mesas = new Mesa[this->K];
    for(int i = 0; i < this->K; i++)
    {
        std::cin >> this->mesas[i].largura;
        std::cin >> this->mesas[i].comprimento;
    }

    this->retangulos = new int[this->N+1];
    for(int i = 0; i < this->N+1; i++)
    {
        this->retangulos[i] = 0;
    }
}

void Casa::calcula_alturas()
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
{
    if(this->retangulos[altura] < largura)
    {
        this->retangulos[altura] = largura;
    }
}

void Casa::calcula_retangulos()
{
    for(int i = this->N-1; i >=0; i--)
    {
        for(int j = 0; j < this->M; j++)
        {
            if(this->planta[i][j].disponivel == 0)
            {
                continue;
            }
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
            insere_retangulo(this->planta[i][j].altura, compativel_direita - compativel_esquerda + 1);
        }
    }
}

bool operator>(Mesa mesa1, Mesa mesa2)
{
    if(mesa1.comprimento * mesa1.largura > mesa2.comprimento * mesa2.largura)
    {
        return 1;
    }
    return 0;
}

void Casa::verifica_mesas()
{
    Mesa maior_mesa;
    maior_mesa.comprimento = 0;
    maior_mesa.largura = 0;
    for(int i = 0; i < this->K; i++)
    {
        if(this->mesas[i].comprimento <= this->N)
        {
            if(this->retangulos[this->mesas[i].comprimento] >= this->mesas[i].largura)
            {
                maior_mesa = (this->mesas[i] > maior_mesa) ? this->mesas[i] : maior_mesa;
            }
        }
        if(this->mesas[i].largura <= this->N)
        {
            if(this->retangulos[this->mesas[i].largura] >= this->mesas[i].comprimento)
            {
                maior_mesa = (this->mesas[i] > maior_mesa) ? this->mesas[i] : maior_mesa;
            }
        }
    }
    std::cout << maior_mesa.largura << " " << maior_mesa.comprimento;
}

void Casa::imprimir()
{
    for(int i = 0; i < this->N; i++)
    {
        for(int j = 0; j < this->M; j++)
        {
            printf("%2d ", this->planta[i][j].altura);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(int i = 0; i <= this->N; i++)
    {
        std::cout << i << " " << this->retangulos[i];
        std::cout << std::endl;
    }
}

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