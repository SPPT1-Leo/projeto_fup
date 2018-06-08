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
    system("cls");
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
    a.saldo = 0.0;

    return a;
    
    clear_screen();
    
    }

    MOVIMENTACAO le_movimentacao(int num_conta, double valor)
    {
    MOVIMENTACAO m;
    m.numero_conta = num_conta;
    m.movimento = valor;

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

    MOVIMENTACAO* remove_Movimentacao(MOVIMENTACAO *vetor_movi, int *qtd_movi, int numero_conta){


    int i;
    for(i = 0; i < *qtd_movi; i++){
        if(vetor_movi[i].numero_conta == numero_conta){
            vetor_movi[i] = vetor_movi[*qtd_movi - 1];
            vetor_movi = (MOVIMENTACAO*) realloc(vetor_movi, (*qtd_movi - 1) * sizeof(MOVIMENTACAO));
            (*qtd_movi)--;
        }
        if(!vetor_movi){
            printf("ERRO NA ALOCACAO");
        }
    }
        return vetor_movi;
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
        printf("OPERAÇAO INVALIDA!\n");
    }
    }

    int main()
    {
    char operacao;
    int quantidade_contas = 0, i, j, num_conta = 0, num_conta2 = 0,senha = 0, qtd_movi = 0;
    double valor;
    CONTA *vetor_contas = 0;
    CONTA a;
    MOVIMENTACAO *vetor_movi = 0;
    MOVIMENTACAO nova_movi;

    menu();

    while(operacao != '0')
    {
        scanf("\n%c", &operacao);

        switch(operacao)
        {
            case '1':
                clear_screen();
                printf("\tSAQUE\n");
                printf("Digite o numero da conta: ");
                scanf("%d", &num_conta);
                printf("Digite a senha: ");
                scanf("%d", &senha);
                fflush(stdin);
                clear_screen();
                for(i = 0; i < quantidade_contas; i++){
                    if(vetor_contas[i].numero_conta == num_conta && vetor_contas[i].senha_cliente == senha){
                        printf("Digite o valor do saque: ");
                        scanf("%lf", &valor);
                        if(valor < 0){
                            clear_screen();
                            printf("Valor não suportado!\n");
                            new_operation(&operacao);
                        }else{
                            if(valor > 0 && vetor_contas[i].saldo < valor){
                                clear_screen();
                                printf("Saldo indisponível!\n");
                                new_operation(&operacao);
                            }else{
                                vetor_contas[i].saldo = vetor_contas[i].saldo - valor;

                                nova_movi = le_movimentacao(num_conta, (-valor));
                                vetor_movi = insere_Movimentacao(vetor_movi, &qtd_movi, nova_movi);
                                clear_screen();
                                printf("SAQUE REALIZADO COM SUCESSO!\n");
                                new_operation(&operacao);
                            }
                        }
                    }
                }
                clear_screen();
                printf("Numero da conta e/ou senha incorretos!\n");
                new_operation(&operacao);
                break;
            case '2'://DEPOSITA NA CONTA
                clear_screen();
                printf("\tDEPOSITO\n");
                printf("Digite o numero da conta: ");
                scanf("%d", &num_conta);
                printf("Digite a senha: ");
                scanf("%d", &senha);
                fflush(stdin);
                clear_screen();
                for(i = 0; i < quantidade_contas; i++){
                    if(vetor_contas[i].numero_conta == num_conta && vetor_contas[i].senha_cliente == senha){
                        printf("Digite o valor do deposito: ");
                        scanf("%lf", &valor);
                        if(valor < 0){
                            clear_screen();
                            printf("Valor invalido!\n");
                            new_operation(&operacao);
                        }else{
                            vetor_contas[i].saldo = vetor_contas[i].saldo + valor;

                            nova_movi = le_movimentacao(num_conta, valor);
                            vetor_movi = insere_Movimentacao(vetor_movi, &qtd_movi, nova_movi);

                            clear_screen();
                            printf("DEPOSITO REALIZADO!!!\n");
                            new_operation(&operacao);
                        }
                    }
                }
                clear_screen();
                printf("Numero da conta e/ou senha incorretos!\n");
                new_operation(&operacao);
                break;
            case '3'://REALIZA TRANSFERENCIA
                clear_screen();
                printf("\tTRANSFERENCIA\n");
                printf("Digite o numero da conta: ");
                scanf("%d", &num_conta);
                printf("Digite a senha: ");
                scanf("%d", &senha);
                fflush(stdin);
                clear_screen();
                for(i = 0; i < quantidade_contas; i++){
                    if(vetor_contas[i].numero_conta == num_conta && vetor_contas[i].senha_cliente == senha){
                        printf("Digite a conta que sera transferido o valor: ");
                        scanf("%d", &num_conta2);
                        for(j = 0; j < quantidade_contas; j++){
                            if(num_conta2 == vetor_contas[j].numero_conta){
                                printf("Digite o valor da transferencia: ");
                                scanf("%lf", &valor);
                                if(valor < 0){
                                    clear_screen();
                                    printf("Erro: Valor nao suportado!\n");
                                    new_operation(&operacao);
                                }else{
                                    clear_screen();
                                    vetor_contas[j].saldo = vetor_contas[j].saldo + valor;
                                    vetor_contas[i].saldo = vetor_contas[i].saldo - valor;

                                    nova_movi = le_movimentacao(num_conta, (-valor));
                                    vetor_movi = insere_Movimentacao(vetor_movi, &qtd_movi, nova_movi);
                                    nova_movi = le_movimentacao(num_conta2, valor);
                                    vetor_movi = insere_Movimentacao(vetor_movi, &qtd_movi, nova_movi);

                                    clear_screen();
                                    printf("TRANSFERENCIA REALIZADA\n");
                                    new_operation(&operacao);

                                }
                            }
                        }
                    }
                }
                clear_screen();
                printf("Numero da conta e/ou senha incorretos!\n");
                new_operation(&operacao);
                break;
            case '4'://VE O SALDO DA CONTA
                clear_screen();
                printf("Digite o numero da conta: ");
                scanf("%d", &num_conta);
                printf("Digite a senha: ");
                scanf("%d", &senha);
                fflush(stdin);
                clear_screen();
                for(i = 0; i < quantidade_contas; i++){
                    if(vetor_contas[i].numero_conta == num_conta && vetor_contas[i].senha_cliente == senha){
                        printf("Saldo: %.2f\n", vetor_contas[i].saldo);
                        new_operation(&operacao);
                    }
                }
                clear_screen();
                printf("Numero da conta e/ou senha incorretos!\n");
                new_operation(&operacao);
                break;
            case '5'://LISTA TODAS AS MOVIMENTAÇÕES DE UMA CONTA!!!
                clear_screen();
                printf("\tEXTRATO\n");
                printf("Digite o numero da conta: ");
                scanf("%d", &num_conta);
                printf("Digite a senha: ");
                scanf("%d", &senha);
                fflush(stdin);
                clear_screen();
                for(i = 0; i < quantidade_contas; i++){
                    if(vetor_contas[i].numero_conta == num_conta && vetor_contas[i].senha_cliente == senha){
                        for(j = 0; j < qtd_movi; j++){
                            if(num_conta == vetor_movi[j].numero_conta){
                                printf("Numero da Conta: %d\nValor: R$%.2f\n\n", vetor_movi[j].numero_conta, vetor_movi[j].movimento);
                            }
                        }
                    }
                }
                clear_screen();
                printf("Numero da conta e/ou senha incorretos!\n");
                new_operation(&operacao);
                break;
            case '6'://CRIA E ALOCA UMA NOVA CONTA!!!
                clear_screen();
                setbuf(stdin, NULL);
                a = le_CONTA();
                vetor_contas = inserir_CONTA(vetor_contas, &quantidade_contas, a);
                new_operation(&operacao);
                setbuf(stdin, NULL);
                break;
            case '7'://REMOVE UMA CONTA!!!
                clear_screen();
                setbuf(stdin, NULL);
                printf("Numero da conta a ser removida: ");
                scanf("%d", &num_conta);
                for(i = 0; i < quantidade_contas; i++){
                    if(num_conta == vetor_contas[i].numero_conta){
                        vetor_contas = remove_CONTA(vetor_contas, &quantidade_contas, num_conta);
                        vetor_movi = remove_Movimentacao(vetor_movi, &qtd_movi, num_conta);
                    }
                }
                clear_screen();
                printf("CONTA REMOVIDA COM SUCESSO!\n");
                new_operation(&operacao);
                setbuf(stdin, NULL);
                break;
            case '8'://LISTA TODAS AS CONTAS CADASTRADAS!!!
                clear_screen();
                setbuf(stdin, NULL);
                for (i = 0; i < quantidade_contas; i++)
                    printf("Nome: %s\nCPF: %s\nNumero da Conta: %d\nSenha: %d\nSaldo: %.2f\n\n", vetor_contas[i].nome_cliente, vetor_contas[i].cpf_cliente, vetor_contas[i].numero_conta, vetor_contas[i].senha_cliente, vetor_contas[i].saldo);
                new_operation(&operacao);
                setbuf(stdin, NULL);
                break;
            case '0':
                clear_screen();
                printf("BYE!\n");
                break;
            default:
                clear_screen();
                printf("\nOPERACAO INVALIDA!\n");
                new_operation(&operacao);
                break;
            }
        }
        return 0;
    }
