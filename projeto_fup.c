#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char nome_cliente[52];
	char cpf_cliente[13];
	int numero_conta;
    int senha_cliente;
    double saldo;
} CONTA;

typedef struct
{
    int numero_conta;
    double movimento;

} MOVIMENTACAO;

void clear_screen()
{
    system("clear");
}

CONTA le_CONTA()
{
    CONTA a;
    printf("\tNOME DO TITULAR:\n");
    setbuf(stdin, NULL);
    fgets(a.nome_cliente, sizeof(a.nome_cliente), stdin);
    a.nome_cliente[strlen(a.nome_cliente) - 1] = '\0';
    printf("\tCPF DO CLIENTE:\n");
    setbuf(stdin, NULL);
    fgets(a.cpf_cliente, sizeof(a.cpf_cliente), stdin);
    a.cpf_cliente[strlen(a.cpf_cliente) - 1] = '\0';
    setbuf(stdin, NULL);
    printf("\tNUMERO DA CONTA:\n");
    scanf("%d", &a.numero_conta);
    setbuf(stdin, NULL);
    printf("\tSENHA (MAXIMO DE 8 DIGITOS):\n");
    scanf("%d", &a.senha_cliente);
    setbuf(stdin, NULL);
    //system("PAUSE");
    return a;
    clear_screen();
}

MOVIMENTACAO le_movimentacao()
{
    MOVIMENTACAO m;
    scanf("%d", &m.numero_conta);
    scanf("%lf", &m.movimento);

    return m;
}

void menu()
{
    printf("\n*-*-*-*-*-*MENU-*-*-*-*-*-*\n");
    printf("\n\t1 - SACAR\n");
    printf("\n\t2 - DEPOSITAR\n");
    printf("\n\t3 - TRANSFERIR\n");
    printf("\n\t4 - SALDO\n");
    printf("\n\t5 - EXTRATO\n");
    printf("\n\t6 - CRIAR CONTA\n");
    printf("\n\t7 - REMOVER CONTA\n");
    printf("\n\t8 - MOSTRAR CONTAS\n");
    printf("\n\t0 - FINALIZAR\n");
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

CONTA* inserir_CONTA(CONTA *vetor_contas, int *quantidade_contas, CONTA nova)
{
    vetor_contas= (CONTA*) realloc(vetor_contas, (*quantidade_contas + 1) * sizeof(CONTA));
	if (vetor_contas == 0)
    {
        printf("Erro: nao foi possivel alocar memoria.");
        return 0;
    }
    vetor_contas[*quantidade_contas] = nova;
    (*quantidade_contas)++;
    return vetor_contas;
}

CONTA* remove_CONTA(CONTA *vetor_contas, int *quantidade_contas, int numero_conta)
{
    int i;
    for (i = 0; i < *quantidade_contas; i++){
        if (vetor_contas[i].numero_conta == numero_conta){
            vetor_contas[i] = vetor_contas[*quantidade_contas - 1]; // copia o ultimo p/ posicao a ser removida
            vetor_contas = (CONTA*) realloc(vetor_contas, (*quantidade_contas - 1) * sizeof(CONTA));
        if (vetor_contas != 0)
           (*quantidade_contas)--;
        	break;
        }
	}
    return vetor_contas;
}

MOVIMENTACAO* insere_Movimentacao(MOVIMENTACAO *vetor_movi, int *qtd_movi, MOVIMENTACAO nova_movi){
    vetor_movi = (MOVIMENTACAO*) realloc(vetor_movi, (*qtd_movi + 1) * sizeof(MOVIMENTACAO));
    if(vetor_movi == 0){
        printf("Erro: Não foi possivel alocar memoria.");
        return 0;
    }

    vetor_movi[*qtd_movi] = nova_movi;
    (*qtd_movi)++;
    return vetor_movi;

}

CONTA* remove_Movimentacao(MOVIMENTACAO *vetor_movi, int *qtd_movi, int numero_conta){
    int i;
    for(i = 0; i < *qtd_movi; i++){
        if(vetor_movi[i].numero_conta == numero_conta){
            vetor_movi[i] = vetor_movi[*qtd_movi - 1];
            vetor_movi = (MOVIMENTACAO*) realloc(vetor_movi, (*qtd_movi - 1) * sizeof(MOVIMENTACAO));
            if(vetor_movi != 0){
                (*qtd_movi)--;
                break;
            }
        }
        return vetor_movi;
    }
}

void new_operation(char *operacao)
{
    int new_operation;
    printf("DESEJA REALIZAR UMA NOVA OPERA��O ? \n(1 - sim | 2 - n�o)\n");
    scanf("%i", &new_operation);

    if(new_operation == 1)
    {
		clear_screen();
        menu();
    }
    else if(new_operation == 2)
    {
        *operacao = '0';
        clear_screen();
        printf("\tOBRIGADO, VOLTE SEMPRE!\n");
    }
    else
    {
        printf("OPERA��O INVALIDA!\n");
    }
}

int checar_senha(CONTA *vetor_contas, int *quantidade_contas, int *num_conta, int *senha)
{
    int achou = 1;
    for (int i = 0; i < *quantidade_contas; i++){
        if(*senha == vetor_contas[i].senha_cliente){
            achou = 1;
        }else{
            achou = 0;
        }
    }
    if (achou){
        return 1;
    }else{
        return 0;
    }
}

int main()
{
    char operacao;
    int quantidade_contas = 0, i, num_conta, senha;
    CONTA *vetor_contas = 0;
    CONTA a;

    menu();

    while(operacao != '0')
    {
        scanf("\n%c", &operacao);

        switch(operacao)
        {
            case '1':
            	//sacar();
                printf("\tSAQUE\n");
                printf("\n\tDIGITE O NUMERO DA CONTA: ");
                scanf("%d", &num_conta);
                printf("\n\tDIGITE A SENHA DE SEGURANCA: \n");
                scanf("%d", &senha);
                fflush(stdin);
                //funcao checar senha
                if (checar_senha(vetor_contas, &quantidade_contas, &num_conta, &senha)){
                    clear_screen();
                    printf("\tDigite o valor do saque:\n");
                    printf("SAQUE EFETUADO!");
                    new_operation(&operacao);
                }else{
                    fflush(stdin);
                    printf("ERRO: SENHA INCORRETA\n");
                    new_operation(&operacao);
                }
                break;
            case '2':
                //depositar();
                printf("DEPOSITO\n");
                new_operation(&operacao);
                break;
            case '3':
                //transferir();
                printf("TRANSFERENCIA\n");
                new_operation(&operacao);
                break;
            case '4':
                //saldo();
        		printf("SALDO\n");
                new_operation(&operacao);
            	break;
            case '5':
                //extrato
                printf("EXTRATO\n");
                new_operation(&operacao);
                break;
            case '6':
                clear_screen();
                setbuf(stdin, NULL);
                a = le_CONTA();
                vetor_contas = inserir_CONTA(vetor_contas, &quantidade_contas, a);
                new_operation(&operacao);
                setbuf(stdin, NULL);
                break;
            case '7':
                clear_screen();
                setbuf(stdin, NULL);
                printf("Numero da conta a ser removida: ");
                scanf("%d", &num_conta);
                for(i = 0; i < quantidade_contas; i++){
                    if(num_conta == vetor_contas[i].numero_conta){
                        vetor_contas = remove_CONTA(vetor_contas, &quantidade_contas, num_conta);
                    }
                }
                printf("CONTA REMOVIDA COM SUCESSO!\n");
                new_operation(&operacao);
                setbuf(stdin, NULL);
                break;
            case '8':
                clear_screen();
                setbuf(stdin, NULL);
				for (i = 0; i < quantidade_contas; i++)
					printf("Nome: %s\nCPF: %s\nNumero da Conta: %d\nSenha:%d\n\n", vetor_contas[i].nome_cliente, vetor_contas[i].cpf_cliente, vetor_contas[i].numero_conta, vetor_contas[i].senha_cliente);
                new_operation(&operacao);
                setbuf(stdin, NULL);
				break;
            case '0':
                printf("BYE!\n");
    			break;
        	default:
                printf("\nOPERACAO INVALIDA!\n");
                new_operation(&operacao);
                break;
            }
    	}
    return 0;
}

