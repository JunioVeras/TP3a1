// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: codigo completo do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <iostream>

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

void Casa::calcula_retangulos()
{
    for(int i = this->N-1; i >=0; i--)
    {
        for(int j = 0; j < this->M; j++)
        {
            
        }
    }
}

void Casa::verifica_mesas()
{

    // std::cout << maior_mesa.largura << " " << maior_mesa.comprimento;
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
}

int main()
// Descricao: main
// Entrada: void
// Saida:
{
    Casa casa;
    casa.calcula_alturas();
    casa.verifica_mesas();
    casa.imprimir();
    return 0;
}