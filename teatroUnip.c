#include <stdio.h>
#include <stdlib.h>

// Limpa a tela
void clearScreen() {
  system("@cls||clear");
}

// Renderiza o cabeçalho
static void renderHeader() {
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
static int renderMenu(char* title, char* items[], int size) {
  int i;
  int option;
  
  printf("%s \n\n", title);

  for (i = 0; i < size; i++) {
    printf("%d) %s\n", i+1, items[i]);
  }

  printf("\nEscolha uma opção:\n");
  scanf("%d",&option); 

  if (option > size || option < 1) {
    clearScreen();
    renderHeader();
    return renderMenu(title, items, size);
  }

  return option;
}

// Venda de ingressos
static void sellTicket() {
  int selectedOption;
  char* menuOptions[] = {"O Fantasma da Ópera", "Romeu e Julieta", "Voltar ao menu principal"};

  clearScreen();
  renderHeader();

  selectedOption = renderMenu(
    "Selecione a peça que deseja vender ingressos:",
    menuOptions,
    sizeof(menuOptions) / sizeof(char*)
  );
}

// Menu principal
static void mainMenu() {
  int selectedOption;
  char* menuOptions[] = {"Vender ingressos"};

  clearScreen();
  renderHeader();
  selectedOption = renderMenu(
    "Seja bem vindo ao sistema de vendas de ingressos!",
    menuOptions,
    sizeof(menuOptions) / sizeof(char*)
  );

  if (selectedOption == 1) {
    sellTicket();
  }
}

int main(){
  mainMenu();
  return 0;
}
