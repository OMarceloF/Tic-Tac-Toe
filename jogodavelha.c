/*
Marcelo Ferreira Santana
21.2.4016
Turma 33
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define Lado 3

char matriz[3][3]; /*Começa Declarando a Matriz do Jogo*/
char matriza[3][3];
char matrizb[3][3];
char jogador1[20];
char jogador2[20];
char comando[20];
int voltar = 0;
int salvar = 0;
char vitoria;
char nomeDoArquivo[20];
int jogadas = 0;

void init_matriz();
void imprime_matriz();
int jogador_joga(int a, int b);
int jogador_joga2(int a, int b);
void pega_valores(void);
void pega_valores2(void);
int checar(void);
int pc_joga();
void gera_rand();
int menu();
char resultado();


// Cria o menu do jogo
int menu(){
  int option;
  printf("Bem Vindo ao Jogo da Velha\n0. Sair do jogo\n1. Comecar um novo jogo\n2. Continuar um jogo salvo\n3. Continuar o jogo atual\n4. Exibir Ranking\nDurante o jogo digite 'voltar' para retornar ao menu.\n");
  scanf("%d", &option);
  return option;
}

/*Gera a semente randomica necessária para a função rand
e é executada no começo do programa*/
void gera_rand()
{
  int stime;
  int ltime;

  ltime=time(NULL);
  stime=(unsigned) ltime/2;
  srand(stime);

}

int pc_joga()
{
  int x,y,mx,my;
  int k,j,i;
  int erro=0;

  x=(rand()%3);
  y=(rand()%3);

  if(matriz[x][y]!=' ')
    {
      pc_joga();
      return(1);
    }
  else
    {
      for(i=0;i<3;i++)
   for(j=0;j<3;j++)
     matriza[i][j]=matriz[i][j];


      for(i=0;i<3;i++)
   for(j=0;j<3;j++)
     {
       if (matriz[i][j]==' ')
         {
      matriz[i][j]='O';
      if((checar()!=0))
        {
          mx=i;
          my=j;
          erro=2;
         }
      else
        {
          matriz[i][j]='X';
          if((checar()!=0)&&(erro!=2))
            {
         mx=i;
         my=j;
         erro=1;
            }

        }

         matriz[i][j]=' ';
              }
     }

      //Restaura Matriz 
      for(i=0;i<3;i++)
   for(j=0;j<3;j++)
     matriz[i][j]=matriza[i][j];
      
      if (erro==0)
    matriz[x][y]='O';
      if (erro!=0)
   matriz[mx][my]='O';
    }
}




/*Função que verifica se há vencedor*/
int checar()
{
  int erro=0;

  int i;
  //Caso a diagonal esteja vencida
  if ((matriz[0][0]==matriz[1][1])&&(matriz[1][1]==matriz[2][2])&&(matriz[0][0]!=' '))
   {
     erro=1;
     vitoria=matriz[0][0];
   }
  

  //Verifica Linhas e Colunas
  for(i=0;i<Lado;i++)
    {
      if ((matriz[i][0]==matriz[i][1])&&(matriz[i][1]==matriz[i][2])&&(matriz[i][0]!=' '))
   {
     erro=1;
     vitoria=matriz[i][0];
   }
      if ((matriz[0][i]==matriz[1][i])&&(matriz[1][i]==matriz[2][i])&&(matriz[0][i]!=' '))
   {
     erro=1;
     vitoria=matriz[0][i];
   }
    }
  //Verifica Diagonal Inversa
  if ((matriz[2][0]==matriz[1][1])&&(matriz[1][1]==matriz[0][2])&&(matriz[2][0]!=' '))
   {
     erro=1;
     vitoria=matriz[2][0];
   }


  return(erro);
}



/*Função que pede as coordenadas ao usuário*/
void pega_valores(void)
{
  comando[20] = ' ';  
  int x,y;
  do
  {
    fflush(stdin);
    printf("\n\n%s, Digite o comando: ", jogador1);
    gets(comando);
    //printf("%s", comando);
    if(strncmp(comando, "marcar", 6) == 0){
      x = (comando[7]-48);
      y = (comando[8]-48);
      jogador_joga(x,y);
  } else if(strncmp(comando, "voltar", 6) == 0){
    voltar = 1;
    break;
  }
  else if(strncmp(comando, "salvar", 6) == 0){
    salvar = 1;
    int h = 0;
    for(int i = 7; i < strlen(comando); i++){
        nomeDoArquivo[h] = comando[i];
        h++;
    }
    nomeDoArquivo[h] = '\0';
    char extensao[5];
    int k = 4;
    for(int i=strlen(comando); i >= strlen(comando)-4; i--){
        extensao[k] = comando[i];
        k--;
    }
    extensao[4] = '\0';

    if(strcmp(extensao, ".txt") == 0){
        FILE *arquivo = fopen(nomeDoArquivo, "w");
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                fprintf(arquivo, "%c ", matriz[i][j]);
            }
            fclose(arquivo);
        }
    }
    break;
  } 
  else{
    printf("Comando invalido");
  }
  } while (strncmp(comando, "marcar", 6) != 0);
}

void pega_valores2(void)
{
  comando[20] = ' ';  
  int x,y;
  do
  {
    fflush(stdin);
    printf("\n\n%s, Digite o comando: ", jogador2);
    gets(comando);
    //printf("%s", comando);
    if(strncmp(comando, "marcar", 6) == 0){
      x = (comando[7]-48);
      y = (comando[8]-48);
      jogador_joga2(x,y);
  } else if(strncmp(comando, "voltar", 6) == 0){
    voltar = 1;
    break;
  }
  else if(strncmp(comando, "salvar", 6) == 0){
    salvar = 1;
    int h = 0;
    for(int i = 7; i < strlen(comando); i++){
        nomeDoArquivo[h] = comando[i];
        h++;
    }
    nomeDoArquivo[h] = '\0';
    char extensao[5];
    int k = 4;
    for(int i=strlen(comando); i >= strlen(comando)-4; i--){
        extensao[k] = comando[i];
        k--;
    }
    extensao[4] = '\0';

    if(strcmp(extensao, ".txt") == 0){
        FILE *arquivo = fopen(nomeDoArquivo, "w");
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                fprintf(arquivo, "%c ", matriz[i][j]);
            }
            fclose(arquivo);
        }
    }
    break;
  } 
  else{
    printf("Comando invalido");
  }
  } while (strncmp(comando, "marcar", 6) != 0);
}


/*Esta função recebe como argumento a coordenada onde deve-se marcar o X.
Faz as verificações necessárias, e marca X na matriz*/
int jogador_joga(int a, int b)

{
  if((a>Lado)||(b>Lado)||(a<1)||(b<1))
    {
      printf("Valores Invalidos %d,%d\n\n",a,b);
      imprime_matriz();
      pega_valores();
    }
  else if(matriz[a-1][b-1]!=' ')
    {
      printf("Casa ja foi preenchida %d,%d \n\n",a,b);
      imprime_matriz();
      pega_valores();
    }
  else
    matriz[a-1][b-1]='X';

}

// para o jogador 2
int jogador_joga2(int a, int b){
  {
  if((a>Lado)||(b>Lado)||(a<1)||(b<1))
    {
      printf("Valores Inválidos %d,%d\n\n",a,b);
      imprime_matriz();
      
      pega_valores();
    }
  else if(matriz[a-1][b-1]!=' ')
    {
      printf("Casa já foi preenchida %d,%d \n\n",a,b);
      imprime_matriz();
      pega_valores();
    }
  else
    matriz[a-1][b-1]='0';
}
}
/*Esa função simplismente gera um gráfico ASCII da Matriz na tela*/
void imprime_matriz()
{
  int i;
  printf("\n\n");
  for(i=0;i<Lado;i++)
    {
      printf(" %c | %c | %c\n",matriz[i][0],matriz[i][1],matriz[i][2]);
      if(i<Lado-1)
   printf("------------\n");
    }
}

/*Inicia a Matriz*/
void init_matriz()
{
  int k,j;
  for (k=0;k < Lado;k++)
    for(j=0;j < Lado;j++)
      matriz[k][j]=' ';
}


int main(void)
{
  char filename[20]; // nome do arquivo
  int playersSalvos = 0;
  int player[10];
  int option;
  int jogadores = 0;
  jogadas = 0;
  int sair = 0;
  gera_rand();                       // Coloca semente randomica no sistema

  do
  {
    //Exibe Menu
    option = menu();
    switch (option)
  {
  case 0:
    printf("Saindo do jogo...\n");
    sair = 1;
    break;
  case 1:
    printf("Digite o numero de jogadores (1 ou 2): ");
    scanf("%d",&jogadores);
    switch (jogadores)
    {
    case 1:
      printf("\nDigite o nome do jogador 1: ");
      scanf("%s", &jogador1);
      init_matriz();
      jogadas = 0;                    //Zera o numero de jogadas.
      destinoa:
      do
      {      
      imprime_matriz();
      pega_valores();
      if(salvar == 1){
        salvar = 2;
        printf("Jogo salvo com sucesso!\n");
        break;
      }
      if(voltar == 1){
        break;
      }
      jogadas++;
      if((checar()==0)&&(jogadas<9)) // Verifica se não houve vitórias ou se acabaram
      {                            // ou se acabaram o numero de jogadas.
      pc_joga();                 // Caso contrário, o computador joga e numero de jogadas
      jogadas++;                 // Aumenta um
      }
      }while((checar()==0)&&(jogadas<9)); //Repere a verificação
      if(salvar == 0){
        imprime_matriz();
      }                 // Imprime matriz final na tela
      break;
    case 2:
      printf("\nDigite o nome do jogador 1: ");
      scanf("%s", &jogador1);
      printf("\nDigite o nome do jogador 2: ");
      scanf("%s", &jogador2);
      init_matriz();
      jogadas = 0;
      destinob:
      do
      {
      imprime_matriz();
      pega_valores();
      jogadas++;
      if((checar()==0)&&(jogadas < 9)){
        imprime_matriz();
        pega_valores2();
        jogadas++;
      }
      }while((checar()==0)&&(jogadas<9));
      if(salvar == 0){
        imprime_matriz();
      }
      break;
    }
    break;
  case 2:
    printf("Qual arquivo voce deseja carregar? ");
    scanf("%s", &filename);
    printf("Carregando jogo...\n");
    FILE *arquivo = fopen(strcat(filename, ".txt"), "r");
    if(arquivo == NULL){
      printf("Erro ao abrir o arquivo!\n");
    }
    else{
      //fscanf(arquivo, "%d", &jogadores);
      //fscanf(arquivo, "%d", &jogadas);
      //fscanf(arquivo, "%d", &jogador1);
      fscanf(arquivo, "%c ", &matriz);
    fclose(arquivo);
    }
    do
    {      
    imprime_matriz();
    pega_valores();
    if(salvar == 1){
      printf("Impossivel salvar novamente!");
    }
      if(voltar == 1){
        break;
      }
      jogadas++;
      if((checar()==0)&&(jogadas<9)) // Verifica se não houve vitórias ou se acabaram
      {                            // ou se acabaram o numero de jogadas.
      pc_joga();                 // Caso contrário, o computador joga e numero de jogadas
      jogadas++;                 // Aumenta um
      }
      }while((checar()==0)&&(jogadas<9)); //Repere a verificação

    break;
  case 3:
    voltar = 0;
    if(jogadas > 0){
    switch (jogadores)
    {
    case 1:
      goto destinoa;
      break;
    case 2:
      goto destinob;
      break;
    default:
      printf("%d", jogadores);
    }
    } else {
      printf("Nao ha jogo em andamento\n");
    }
    break;
  case 4:
    printf("RANKING\n");
  default:
    break;
  }
  } while (sair == 0);  
  return(0);
}