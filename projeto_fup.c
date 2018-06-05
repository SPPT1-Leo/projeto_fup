#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char nome_cliente[52];
	char cpf_cliente[13];
	int numero_conta;
	char senha[10];
	double saldo;

} CONTA;

typedef struct
{
	int numero_conta;
	double valor_da_conta;

} MOVIMENTACAO;

CONTA criaConta(){

    CONTA c;
    fgets(c.nome_cliente, sizeof(c.nome_cliente), stdin);
    fgets(c.cpf_cliente, sizeof(c.cpf_cliente), stdin);
    scanf("%d\n", &c.numero_conta);
    fgets(c.senha, sizeof(c.senha), stdin);
    scanf("%lf\n", &c.saldo);

    return c;

}

MOVIMENTACAO criaMovimentacao(){

    MOVIMENTACAO m;

    scanf("%d", m.numero_conta);
    scanf("%f", m.valor_da_conta);

    return m;

}

CONTA* insereConta(CONTA *c, int *n, CONTA nova_conta){

    if(*n > 0){
        c = (CONTA*)realloc(c, (*n)*sizeof(CONTA));
        c[*n] = nova_conta;
        (*n++);
    }else{
        c = (CONTA*)malloc(sizeof(CONTA));
        c[*n] = nova_conta;
        //return c;
    }
    if(!c){
        printf("ERRO: Nao foi possivel alocar memoria!\n");
        return 0;
    }

    return c;

}

CONTA* removeConta(CONTA *c, int *n, int numero_da_conta){



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
	printf("\n\t8 - MOSTRAR CONTAS\n");
	printf("\n\t0 - FINALIZAR\n");
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

void clear_screen()
{
	system("cls");
}

void new_operation(char *operacao)
{
	int new_operation;
	printf("DESEJA REALIZAR UMA NOVA OPERACAO ? \n(1 - sim | 2 - nao)\n");
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
		printf("BYE!\n");
	}
	else
	{
		printf("OPERACAO INVALIDA!\n");
	}
}

int main(int argc, char *argv[])
{
    int qtd = 0, i = 0, n = 0;
    CONTA *c = 0;
    CONTA nova_conta;
	char operacao;

	menu();

	while(operacao != '0')
	{
		scanf("\n%c", &operacao);

		switch(operacao)
		{
			case '1':
				//sacar();
				printf("SAQUE\n");
				new_operation(&operacao);
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
                //printf("Insira quantas contas ir� criar: ");
                //scanf("%d", &qtd);
                //for(i = 0; i < qtd; i++){
                    nova_conta = criaConta();
                    c = insereConta(c, &n, nova_conta);
                //}
                fflush(stdin);
                new_operation(&operacao);
                break;
            case '8':
                clear_screen();
                for(i = 0; i < n; i++){
                    printf("%s%s%d\n%s%.1f\n", c[i].nome_cliente, c[i].cpf_cliente, c[i].numero_conta, c[i].senha, c[i].saldo);
                }
                new_operation(&operacao);
                break;
			case '0':
			    clear_screen();
				printf("BYE!\n");
				break;
			default:
				printf("OPERAÇAO INVALIDA!\n");
				break;
		}
	}

	return 0;
}
