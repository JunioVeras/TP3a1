// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: codigo completo do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <iostream>

struct Retangulo
{
    int altura;
    int largura;
};

struct Piso
{
    Retangulo ret_alto;
    Retangulo ret_largo;
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
        bool mesa_cabe(Mesa mesa, Retangulo retangulo);
    public:
        Casa();
        void calcula_opt_retangulos();
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
            this->planta[i][j].ret_alto.altura = 0;
            this->planta[i][j].ret_alto.largura = 0;
            this->planta[i][j].ret_largo.altura = 0;
            this->planta[i][j].ret_largo.largura = 0;
        }
    }

    std::cin >> this->K;

    this->mesas = new Mesa[this->K];
    for(int i = 0; i < this->K; i++)
    {
        std::cin >> this->mesas[i].largura;
        std::cin >> this->mesas[i].comprimento;
    }
}

void Casa::calcula_opt_retangulos()
{
    for(int i = 0; i < this->N; i++)
    {
        for(int j = 0; j < this->M; j++)
        {
            if(this->planta[i][j].disponivel == 0)
            {
                continue;
            }

            if(i == 0 && j == 0)
            {
                this->planta[i][j].ret_alto.altura = 1;
                this->planta[i][j].ret_alto.largura = 1;
                this->planta[i][j].ret_largo.altura = 1;
                this->planta[i][j].ret_largo.largura = 1;
            }
            else if(i == 0 && j > 0)
            {
                this->planta[i][j].ret_alto.altura = 1;
                this->planta[i][j].ret_alto.largura = this->planta[i][j-1].ret_largo.largura + 1;
                this->planta[i][j].ret_largo.altura = 1;
                this->planta[i][j].ret_largo.largura = this->planta[i][j-1].ret_largo.largura + 1;
            }
            else if(i > 0 && j == 0)
            {
                this->planta[i][j].ret_alto.altura = this->planta[i-1][j].ret_alto.altura + 1;
                this->planta[i][j].ret_alto.largura = 1;
                this->planta[i][j].ret_largo.altura = this->planta[i-1][j].ret_alto.altura + 1;;
                this->planta[i][j].ret_largo.largura = 1;
            }
            else if(i > 0 && j > 0)
            {
                this->planta[i][j].ret_alto.altura = this->planta[i-1][j].ret_alto.altura + 1;
                this->planta[i][j].ret_alto.largura = (this->planta[i-1][j].ret_alto.largura < this->planta[i][j-1].ret_largo.largura + 1)?
                this->planta[i-1][j].ret_alto.largura : this->planta[i][j-1].ret_largo.largura + 1;

                this->planta[i][j].ret_largo.largura = this->planta[i][j-1].ret_largo.largura + 1;
                this->planta[i][j].ret_largo.altura = (this->planta[i][j-1].ret_largo.altura < this->planta[i-1][j].ret_alto.altura + 1)?
                this->planta[i][j-1].ret_largo.altura : this->planta[i-1][j].ret_alto.altura + 1;

                if(this->planta[i-1][j].disponivel == 0)
                {
                    this->planta[i][j].ret_alto.altura = 1;
                    this->planta[i][j].ret_alto.largura = this->planta[i][j-1].ret_largo.largura + 1;
                }
                if(this->planta[i][j-1].disponivel == 0)
                {
                    this->planta[i][j].ret_largo.largura = 1;
                    this->planta[i][j].ret_largo.altura = this->planta[i-1][j].ret_alto.altura + 1;
                }
            }
        }
    }
}

bool Casa::mesa_cabe(Mesa mesa, Retangulo retangulo)
{
    if(mesa.largura <= retangulo.largura && mesa.comprimento <= retangulo.altura)
    {
        return 1;
    }
    else if(mesa.largura <= retangulo.altura && mesa.comprimento <= retangulo.largura)
    {
        return 1;
    }
    return 0;
}

void Casa::verifica_mesas()
{
    Mesa maior_mesa;
    maior_mesa.largura = 0;
    maior_mesa.comprimento = 0;

    for(int i = 0; i < this->N; i++)
    {
        for(int j = 0; j < this->M; j++)
        {
            if(this->planta[i][j].disponivel == 0)
            {
                continue;
            }

            for(int k = 0; k < this->K; k++)
            {
                if(mesa_cabe(this->mesas[k], this->planta[i][j].ret_alto) || mesa_cabe(this->mesas[k], this->planta[i][j].ret_largo))
                {
                    if(this->mesas[k].largura * this->mesas[k].comprimento > maior_mesa.largura * maior_mesa.comprimento)
                    {
                        maior_mesa = this->mesas[k];
                    }
                } 
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
            std::cout << this->planta[i][j].disponivel << "(" << this->planta[i][j].ret_alto.largura <<
            "," << this->planta[i][j].ret_alto.altura << ")("<< this->planta[i][j].ret_largo.largura << 
            "," << this->planta[i][j].ret_largo.altura << ") ";
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
    casa.calcula_opt_retangulos();
    casa.verifica_mesas();
    // casa.imprimir();
    return 0;
}