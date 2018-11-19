#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das funções para referência nas funções
void mainMenu();
void sellTicketMenu();

// Definição das sessões
struct TheaterSession  {
  char title[50];
  int soldPlaces;
  int totalPlaces;
  int soldValues[30];
};

struct TheaterSession session1 = {.title = "O Fantasma da Ópera", .soldPlaces = 0, .totalPlaces = 30};
struct TheaterSession session2 = {.title = "Romeu e Julieta", .soldPlaces = 0, .totalPlaces = 30};

// Função para limpar a tela
void clearScreen() {
  system("@cls||clear");
}

// Função que exibe "pressione qualquer tecla para continuar..."
void pressAnyKey () {
  printf("Pressione qualquer tecla para continuar...");
  while (getchar() != '\n');
  getchar();
}

// Renderiza o cabeçalho
void renderHeader() {
  clearScreen();
  printf("\n\n  _______         _               _    _       _       \n");
  printf(" |__   __|       | |             | |  | |     (_)      \n");
  printf("    | | ___  __ _| |_ _ __ ___   | |  | |_ __  _ _ __  \n");
  printf("    | |/ _ \\/ _` | __| '__/ _ \\  | |  | | '_ \\| | '_ \\ \n");
  printf("    | |  __/ (_| | |_| | | (_) | | |__| | | | | | |_) |\n");
  printf("    |_|\\___|\\__,_|\\__|_|  \\___/   \\____/|_| |_|_| .__/ \n");
  printf("                                                | |    \n");
  printf("                                                |_|    \n\n");
  printf("*******************************************************\n\n");
};

// Renderiza menus e retorna a opção escolhida
int renderMenu(char* title, char* items[], int size) {
  int i;
  int option;
  
  printf("%s \n\n", title);

  for (i = 0; i < size; i++) {
    printf("%d) %s\n", i+1, items[i]);
  }

  printf("\nEscolha uma opção:\n");
  scanf("%d",&option); 

  if (option > size || option < 1) {
    renderHeader();
    return renderMenu(title, items, size);
  }

  return option;
}

// Função que gera um ticket, recebe como parâmetros a sessão e o assento
void generateTicket(struct TheaterSession *session, int place) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  printf("Ticket: \n\n");
  printf("Peça: %s\n", session->title);
  printf("Assento: %d\n", place);
  printf("Data: %d/%d/%d - 21:00\n\n", tm.tm_mday, tm.tm_mon,tm.tm_year+1900);
}

/*
 Executa a venda do ingresso, recebe um ponteiro para um struct do tipo session
 verifica se a propriedade soldPlaces não atingiu 30 e executa a venda, caso contrário
 exibe uma mensagem de sessão esgotada.
 */
void finishTicket(struct TheaterSession *session) {
  int selectedOption;
  char* menuOptions[] = {"Inteira (R$30,00)", "Meia (R$15,00)", "Gratuita", "Voltar para seleção da peça"};

  renderHeader();

  if (session->soldPlaces < session->totalPlaces) {
    selectedOption = renderMenu(
      "Selecione o tipo de ingresso:",
      menuOptions,
      sizeof(menuOptions) / sizeof(char*)
    );

    session->soldPlaces = session->soldPlaces + 1;
    switch(selectedOption) {
    case 1:
      session->soldValues[session->soldPlaces - 1] = 30;
      break;
    case 2:
      session->soldValues[session->soldPlaces - 1] = 15;
      break;
    case 3:
      session->soldValues[session->soldPlaces - 1] = 0;
      break;
    case 4:
      sellTicketMenu();
      return;
    }

    renderHeader();
    printf(
      "Venda efetuada com sucesso, lugares disponíveis: %d\n\n",
      session->totalPlaces - session->soldPlaces
    );
    generateTicket(session, session->soldPlaces);
    pressAnyKey();
    mainMenu();
  } else {
    printf("Sessão esgotada, escolha outra sessão. \n\n");
    pressAnyKey();
    sellTicketMenu();
  }
}

// Menu de venda de ingressos
void sellTicketMenu() {
  int selectedOption;
  char* menuOptions[] = {session1.title, session2.title, "Voltar ao menu principal"};

  renderHeader();
  selectedOption = renderMenu(
    "Sessões para hoje às 21:00, \nselecione a peça que deseja vender ingressos:",
    menuOptions,
    sizeof(menuOptions) / sizeof(char*)
  );

  switch(selectedOption) {
  case 1:
    finishTicket(&session1);
    break;
  case 2:
    finishTicket(&session2);
    break;
  case 3:
    mainMenu();
    break;
  }
}

void cashClosing() {
  int totalSoldTickets = 0;
  int totalSoldValue = 0;
  int i;

  totalSoldTickets = session1.soldPlaces + session2.soldPlaces;

  for (i = 0; i < session1.soldPlaces; i++) {
    totalSoldValue = totalSoldValue + session1.soldValues[i];
  }

  for (i = 0; i < session2.soldPlaces; i++) {
    totalSoldValue = totalSoldValue + session2.soldValues[i];
  }

  renderHeader();
  printf("Total de ingressos vendidos: %d\n", totalSoldTickets);
  printf("Valor total: R$%d,00\n\n", totalSoldValue);
  pressAnyKey();
  mainMenu();
}

// Menu principal
void mainMenu() {
  int selectedOption;
  char* menuOptions[] = {"Vender ingressos", "Fechar caixa", "Sair"};

  renderHeader();
  selectedOption = renderMenu(
    "Seja bem vindo ao sistema de vendas de ingressos!",
    menuOptions,
    sizeof(menuOptions) / sizeof(char*)
  );

  switch(selectedOption) {
  case 1:
    sellTicketMenu();
    break;
  case 2:
    cashClosing();
    break;
  case 3:
    exit(0);
    break;
  }
}

// Função principal
int main(){
  mainMenu();
  return 0;
}
