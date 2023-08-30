#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int menu();
void intervaloMedia();
void intervaloProporcao();
void amostraMedia();
void amostraProporcao();
float grauConfianca(float grauConf);

void main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            intervaloMedia();
            break;
        case 2:
            intervaloProporcao();
            break;
        case 3:
            amostraMedia();
            break;
        case 4:
            amostraProporcao();
            break;
        default:
            if (opcao != 0)
            {
                printf("Opção inválida.");
            }
            break;
        }
    } while (opcao != 0);
    
}

int menu()
{
    int opcao;

    printf("\n\n-------------- MENU --------------");
    printf("\n[1] Intervalo de confiança da média");
    printf("\n[2] Intervalo de confiança da proporção");
    printf("\n[3] Tamanho da amostra da média");
    printf("\n[4] Tamanho da amostra da proporção");
    printf("\n[0] Sair");
    printf("\n----------------------------------\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void intervaloMedia()
{
    float grauConf, valCrit, desvPad, tamAm, Em, media;

    printf("Digite o grau de confiança: ");
    scanf("%f", &grauConf);
    valCrit = grauConfianca(grauConf);
    printf("Digite o desvio padrão: ");
    scanf("%f", &desvPad);
    printf("Digite o tamanho da amostra: ");
    scanf("%f", &tamAm);
    printf("Digite a média: ");
    scanf("%f", &media);
    
    Em = valCrit*desvPad/sqrt(tamAm);
    printf("\nEm = %.2f", Em);
    printf("\nIC = %.2f < u < %.2f", media-Em, media+Em);
}

void intervaloProporcao()
{
    float grauConf, valCrit, prop, tamAm, Ep, sucesso;
    char op;

    printf("Digite o grau de confiança: ");
    scanf("%f", &grauConf);
    valCrit = grauConfianca(grauConf);
    printf("Digite o tamanho da amostra: ");
    scanf("%f", &tamAm);
    printf("Você já possui a porcentagem da proporção? [S/N]\n");
    scanf(" %c", &op);
    if (op == 'S' || op == 's')
    {
        printf("Digite a porcentagem da proporção: ");
        scanf("%f", &prop);
        prop = prop/100;
    }
    else
    {
        printf("Digite o sucesso: ");
        scanf("%f", &sucesso);
        prop = sucesso/tamAm;
        printf("Proporção = %.2f\n", prop);
    }

    Ep = valCrit*sqrt(prop*(1-prop)/tamAm);
    printf("\nEp = %.2f", Ep);
    printf("\nIC = %.2f < n < %.2f", prop-Ep, prop+Ep);

}

void amostraMedia()
{
    float grauConf, valCrit, desvPad, tamAm, Em;

    printf("Digite o grau de confiança: ");
    scanf("%f", &grauConf);
    valCrit = grauConfianca(grauConf);
    printf("Digite o desvio padrão: ");
    scanf("%f", &desvPad);
    printf("Digite o erro da média: ");
    scanf("%f", &Em);

    tamAm = pow((valCrit*desvPad/Em), 2);
    printf("\nO tamanho da amostra é: %.0f (%.2f)", ceil(tamAm), tamAm);
}

void amostraProporcao()
{
    float grauConf, valCrit, prop, tamAm, Ep;
    char op;

    printf("Digite o grau de confiança: ");
    scanf("%f", &grauConf);
    valCrit = grauConfianca(grauConf);
    printf("Digite o erro da proporção: ");
    scanf("%f", &Ep);
    printf("Você já possui a porcentagem da proporção? [S/N]\n");
    scanf(" %c", &op);
    if (op == 'S' || op == 's')
    {
        printf("Digite a porcentagem da proporção: ");
        scanf("%f", &prop);
        prop = prop/100;
    }
    else
    {
        prop = 0.5;
    }

    tamAm = pow(valCrit, 2)*prop*(1-prop)/pow(Ep, 2);
    printf("\nO tamanho da amostra é: %.0f (%.2f)", ceil(tamAm), tamAm);
}

float grauConfianca(float grauConf)
{
    float valCrit;

    if (grauConf == 95)
    {
        valCrit = 1.96;
    }
    else if (grauConf == 99)
    {
        valCrit = 2.575;
    }
    else
    {
        valCrit = 1.645;
    }

    return valCrit;
}