#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct{
	int codigo;
	char nome[100];
	int idade;
	int id;
	char admitido;
	int quali;
	int cargo; //Vai entrar número, em virtude pq fica mais fácil para parametrizar 
}Cadastro;

typedef struct{
	char nome[100];
	int teste;
}Teste;

typedef struct{
	char nomeu[100];
	char sexo;
	char conselheiroa[100];
	char conselheirob[100];
	Teste vetdeb[8];
}CadastroU;

typedef struct{
	char nome[100];
	int codigo;
	int elevacao;
	int dia;
	int mes;
	int ano;
}CadastroE;

int Menu(){
	int a;
	printf("\n=============================Menu===========================");
	printf("\n1-Cadastro de Pessoas");
	printf("\n2-Listar");
	printf("\n3-Cadastro de Unidade");
	printf("\n4-Eliminar");
	printf("\n6-Ordenar");
	printf("\n7-Cadastro de Elevacao");
	printf("\n8-Verificar se está criando o vetor");
	printf("\n9-Buscar");
	printf("\n10-Sair");
	printf("\n\nDigite a opcao: ");
	scanf(" %d",&a);
	return a;
}

int Cargo(){
	int x;
	printf("\nSomente Número:\n");
	printf("\n1-Diretor");
	printf("\n2-Conselheiro");
	printf("\n3-Desbravador");
	printf("\n\nDigite a opção: ");
	scanf(" %d",&x);
	return x;
}

int MostrarQualiD(){
	int a;
	printf("1-Amigo\n");
	printf("2-Companheiro\n");
	printf("3-Pesquisador\n");
	printf("4-Pioneiro\n");
	printf("5-Excurcionista\n");
	printf("6-Guia\n");
	printf("\nDigite:");
	scanf(" %d",&a);
	return a;
}

int MostrarQualiC(){
	int a;
	printf("1-Amigo\n");
	printf("2-Companheiro\n");
	printf("3-Pesquisador\n");
	printf("4-Pioneiro\n");
	printf("5-Excurcionista\n");
	printf("6-Guia\n");
	printf("7-Lider\n");
	printf("8-Lider Master\n");
	printf("9-Lider Master Avançado\n");
	printf("\nDigite:");
	scanf(" %d",&a);
	return a;
}

Cadastro CadPessoas(){
	Cadastro n;
	srand(time(NULL));
	n.codigo = rand()%100;
		printf("\n=============================Cadastro de Pessoas===========================");
		printf("\nDigite seu nome:");
		scanf(" %s",n.nome);
		printf("Digite sua idade:");
		scanf(" %d",&n.idade);
		printf("Digite sua identidade:");
		scanf(" %d",&n.id);
		printf("Voce e admitido(V/F):");
		scanf(" %c",&n.admitido);
		printf("Qual a sua qualificaçao:\n");
		if (n.idade >= 16){
			n.quali = MostrarQualiC();
		}else{
			n.quali = MostrarQualiD();
		}
		if(n.idade >= 16){
			printf("\nQual o seu cargo no clube:\n");
			n.cargo = Cargo();
		}else{
			n.cargo = 3;
		}
	
	return n;
}

void MandarProArqPe(){
	Cadastro a;
	a = CadPessoas();
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","ab");
	fwrite(&a,sizeof(Cadastro),1,file);
	fclose(file);
}

int VerificarTamanhoEl(){
	CadastroE a;
	int cont=1;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\elevado.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	while(fread(&a,sizeof(Cadastro),1,file)!=NULL){
		cont++;
	}
	fclose(file);
	return cont-1;
}

int VerificarTamanho(){
	Cadastro a;
	int cont=1;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	while(fread(&a,sizeof(Cadastro),1,file)!=NULL){
		cont++;
	}
	fclose(file);
	return cont-1;
}

int VerificarTamanhoUnidade(){
	CadastroU a;
	int cont=1;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\unidade.txt","rb");
	while(fread(&a,sizeof(CadastroU),1,file)!=NULL){
		cont++;
	}
	fclose(file);
	return cont-1;
}

void ListarMembros(){
	Cadastro a;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	
	printf("\n-----------------------Lista de Membros------------------------");
	
	while(fread(&a,sizeof(Cadastro),1,file)!=NULL){
		printf("\n%d-Cadastro/Codgo:",a.codigo);
		printf("\nNome: %s",a.nome);
		printf("\nIdade: %d\n",a.idade);
		printf("identidade: %d\n",a.id);
		printf("Admitido: %c\n",a.admitido);
		printf("Qualificação: %d\n",a.quali);
		printf("Cargo: %d\n",a.cargo);
	}
	fclose(file);
}

void ListarUnidade(){
	CadastroU a;
	int cont;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\unidade.txt","rb");
	
	printf("\n-----------------------Lista de Unidades------------------------\n");
	while(fread(&a,sizeof(CadastroU),1,file)!=NULL){
		printf("\nUnidade: %s",a.nomeu);
		printf("\nSexo: %c",a.sexo);
		printf("\n1-Conselheiro(a): %s",a.conselheiroa);
		printf("\n2-Conselheiro(a): %s",a.conselheirob);
		
		for(int i=0;i<7;i++){
			if (a.vetdeb[i].teste == 1){
				cont = i+1;
				printf("\n%d-Desbravador: %s",cont,a.vetdeb[i].nome);
			}else{
				break;
			}
		}
		printf("\n");
	}
	fclose(file);
}

void ListarDbvEsp(){
	int tam = VerificarTamanho(),cont = 0;
	Cadastro a, vetor[tam];
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb");
	
	while( !feof(file) ){
		fread(&a,sizeof(Cadastro),1,file);
		vetor[cont] = a;
		printf("\nkkkkkpppp%s",vetor[cont].nome);
		cont++;
	}
	
	printf("\n==================================================================\n");
	printf("\nAmigo:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 1){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nCompanheiro:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 2){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nPesquisador:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 3){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nPioneiro:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 4){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nEscursionista:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 5){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nGuia:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 6){
			printf("%s, ",vetor[i].nome);
		}
	}
	printf("\nLider:");
	for(int i=0;i<tam;i++){
		if (vetor[i].quali == 7){
			printf("%s, ",vetor[i].nome);
		}
	}
	fclose(file);
}

void ListarElevacao(){
	CadastroE a;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\elevado.txt","rb");
	
	while(fread(&a,sizeof(CadastroE),1,file) != NULL){
		printf("\nCodigo: %d",a.codigo);
		printf("\nNome do Membro: %s",a.nome);
		printf("\nElevou da Classe: %d -> %d",(a.elevacao-1),a.elevacao);
		printf("\nData: %d/%d/%d",a.dia,a.mes,a.ano);
	}
	
	fclose(file);
}

void ListarTudo(){
	int y;
	
	printf("\n-----------------------Menu de Listagem------------------------");
	printf("\n1 - Listar os Membros");
	printf("\n2 - Listar as Unidades");
	printf("\n3 - Listar os Desbravdores por Especialidades");
	printf("\n4 - Listar todas as Elevacoes\n");
	printf("\nDigite a opcao: ");
	scanf(" %d",&y);
	
	switch(y){
		case 1: 
			ListarMembros();
			break;
		case 2:
			ListarUnidade();
			break;
		case 3:
			ListarDbvEsp();
			break;
		case 4:
			ListarElevacao();
			break;
	}	
}

int VerificarTamanhoDeb(){
	Cadastro a;
	int cont=1;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	while(fread(&a,sizeof(Cadastro),1,file)!=NULL){
		if(a.idade<16){
			cont++;
		}
	}
	fclose(file);
	return cont-1;
}

void CriarVdoarquivo(){
	int tam=VerificarTamanho();
	Cadastro vet[tam],t;
	int cont;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	
	while(!feof(file)){
		fread(&t,sizeof(Cadastro),1,file);
		vet[cont]=t;
		cont++;
	}
	
	for(int i=0;i<tam;i++){
		printf("\n%d",vet[i].codigo);
		printf("\nNome: %s",vet[i].nome);
		printf("\nIdade: %d\n",vet[i].idade);
		printf("identidade: %d\n",vet[i].id);
		printf("Admitido: %c\n",vet[i].admitido);
		printf("Qualificacao: %d\n",vet[i].quali);
		printf("Cargo: %d\n",vet[i].cargo);
	}
	
}

void EliminarMembro(){
	char nome[100];
	int cont=0,tam,teste = 0,loc = 0;
	tam = VerificarTamanho();
	Cadastro vet[tam],t,a;
	
	printf("\n----------------------------------------------------------------");
	printf("\nDigite o nome: ");
	scanf(" %s",nome);
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	printf("\nkkkkkkk0\n");
	while(!feof(file)){
		fread(&t,sizeof(Cadastro),1,file);
		vet[cont] = t;
		cont++;										//Oproblema está no fread
	}
	fclose(file);
	printf("\nkkkkkkk2\n");
	for(int i=0;i<tam;i++){
		if (strcmp(vet[i].nome,nome)==0){
			teste = 1;
			loc = i;
		}
	}
	
	if (teste == 1){
		printf("\nEncontrado!!!");
		FILE *filea;
		filea = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","w");
		for(int i=0;i<tam;i++){
			if (i != loc){
				a = vet[i];
				fwrite(&a,sizeof(Cadastro),1,filea);
				printf("\nkkkkkkk3\n");
			}
		}
		fclose(filea);
	}else{
		printf("\nNão está no arquivo");
	}
}

void EliminarUnidade(){
	char nome[100];
	int cont=0,tam,teste = 0,loc = 0;
	tam = VerificarTamanhoUnidade();
	CadastroU vet[tam],t,a;
	
	printf("\n----------------------------------------------------------------");
	printf("\nDigite o nome da unidade: ");
	scanf(" %s",nome);
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\unidade.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	printf("\nkkkkkkk0\n");
	while(!feof(file)){
		fread(&t,sizeof(CadastroU),1,file);
		vet[cont] = t;
		cont++;										//Oproblema está no fread
	}
	fclose(file);
	printf("\nkkkkkkk2\n");
	for(int i=0;i<tam;i++){
		if (strcmp(vet[i].nomeu,nome)==0){
			teste = 1;
			loc = i;
		}
	}
	
	if (teste == 1){
		printf("\nEncontrado!!!");
		FILE *filea;
		filea = fopen("C:\\Users\\Diego\\Desktop\\unidade.txt","w");
		for(int i=0;i<tam;i++){
			if (i != loc){
				a = vet[i];
				fwrite(&a,sizeof(CadastroU),1,filea);
				printf("\nkkkkkkk3\n");
			}
		}
		fclose(filea);
	}else{
		printf("\nNão está no arquivo");
	}
}

void EliminarElevacao(){;
	int cont=0,tam,teste = 0,loc = 0,codigo;
	tam = VerificarTamanhoEl();
	CadastroE vet[tam],t,a;
	
	printf("\n----------------------------------------------------------------");
	printf("\nDigite o código: ");
	scanf(" %d",&codigo);
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\elevado.txt","rb"); //aqui tem que mudar de 'a' para 'r'
	
	while(fread(&t,sizeof(CadastroE),1,file) != NULL){
		vet[cont] = t;
		if (vet[cont].codigo == codigo){
			teste = 1;
			loc = cont;
		}
		printf("\n%s",vet[cont].nome);
		cont++;										//Oproblema está no fread
	}
	fclose(file);
	printf("\nkkkkkkk2\n");
	
	if (teste == 1){
		printf("\nEncontrado!!!");
		FILE *filea;
		filea = fopen("C:\\Users\\Diego\\Desktop\\elevado.txt","w");
		for(int i=0;i<tam;i++){
			if (i != loc){
				a = vet[i];
				fwrite(&a,sizeof(CadastroE),1,filea);
				printf("\nkkkkkkk3\n");
			}
		}
		fclose(filea);
	}else{
		printf("\nNão está no arquivo");
	}
}


void EliminarMenu(){
	int x;
	printf("\n-----------------------Menu de Eliminacao------------------------");
	printf("\n1-Membro");
	printf("\n2-Unidade");
	printf("\n3-Classificação");
	printf("\nDigite: ");
	scanf(" %d",&x);
	
	if (x == 1){
		EliminarMembro();
	}
	if (x == 2){
		EliminarUnidade();
	}
	if (x == 3){
		EliminarElevacao();
	}
}

CadastroU CadUnidade(){
	CadastroU a;
	int testar;
	
	printf("\n=============================Cadastro de Unidade===========================\n");
	printf("1-Digite o nome da Unidade: ");
	scanf(" %s",a.nomeu);
	printf("2-Digite qual o sexo da unidade(M/F): ");
	scanf(" %c",&a.sexo);
	printf("3-Digite o nome do Primeiro Conselheiro:");
	scanf(" %s",a.conselheiroa);
	printf("4-Digite o nome do Segundo Conselheiro:");
	scanf(" %s",a.conselheirob);
	
	
	for(int i=0;i<7;i++){
		printf("Deseja digitar os desbravadores(1-s,0-n): ");
		scanf(" %d",&testar);
		if(testar == 1){
			printf("Digite o nome: ");
			scanf(" %s",a.vetdeb[i].nome);
			a.vetdeb[i].teste = 1;
		}else{
			break;
		}
	}
	return a;
}

void MandarProArqUn(){
	CadastroU a;
	a = CadUnidade();
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\unidade.txt","ab");
	fwrite(&a,sizeof(CadastroU),1,file);
	fclose(file);
}

void TrocarPosiHeap(Cadastro *dados, int i, int j){
	Cadastro temporario = dados[i];
	dados[i] = dados[j];
	dados[j] = temporario;
}

void ConstruirHeap(Cadastro *dados, int n){
	int i, pai, filho;	
	for(i = 0; i < (n - 1); i++){		
		filho = i + 1;
		pai = (filho - 1) / 2;
		while(filho > 0 && dados[pai].idade < dados[filho].idade){
			TrocarPosiHeap(dados, pai, filho);
			filho = pai;
			pai = (filho - 1) / 2;
		}		
	}
}

void ConstruirHeapString(Cadastro *dados, int n){
	int i, pai, filho;
	for(i = 0; i < (n - 1); i++){
		filho = i + 1;
		pai = (filho - 1) / 2;
		while(filho > 0 && (strcmp(dados[pai].nome,dados[filho].nome) < 0)){
			 TrocarPosiHeap(dados, pai, filho);
			 filho = pai;
			 pai = (filho - 1) / 2;
		}
	}
}

void RescontruirHeap(Cadastro *dados, int n){
	int pai, filhoEsquerdo, filhoDireito, filhoMaior;	
	pai = 0;	
	while(pai <= (n / 2 - 1)){	
		filhoEsquerdo = 2 * pai + 1;
		filhoDireito = 2 * pai + 2;
		
		filhoMaior = filhoEsquerdo;
		if(filhoDireito < n && dados[filhoDireito].idade > dados[filhoEsquerdo].idade){
			filhoMaior = filhoDireito;
		}
		
		if(dados[filhoMaior].idade > dados[pai].idade){
			TrocarPosiHeap(dados, pai, filhoMaior);
			pai = filhoMaior;			
		}else{
			break;
		}
	}
}

void RescontruirHeapString(Cadastro *dados, int n){
	int pai, filhoEsquerdo, filhoDireito, filhoMaior;
	pai = 0;
	while(pai <= (n / 2 - 1)){
		filhoEsquerdo = 2 * pai +1;
		filhoDireito = 2 * pai + 2;
		
		filhoMaior = filhoEsquerdo;
		if((filhoDireito < n) && (strcmp(dados[filhoDireito].nome,dados[filhoEsquerdo].nome) > 0)){
			filhoMaior = filhoDireito;
		}
		
		if(strcmp(dados[filhoMaior].nome,dados[pai].nome) > 0){
			TrocarPosiHeap(dados,pai,filhoMaior);
			pai = filhoMaior;
		}else{
			break;
		}
	}
}

void RetirarRaizHeap(Cadastro *dados, int n){ 
	TrocarPosiHeap(dados, 0, n - 1);	
}

void HeapSort(Cadastro *dados, int n){
	ConstruirHeap(dados, n);
	while(n > 1){							
		RetirarRaizHeap(dados, n);
		n--;			
		RescontruirHeap(dados, n);		
	}
}

void HeapSortString(Cadastro *dados, int n){
	ConstruirHeapString(dados, n);
	while(n > 1){
		RetirarRaizHeap(dados, n);
		n--;
		RescontruirHeapString(dados, n);
	}
}

void ImprimirTela(Cadastro *dados, int n){
	printf("\n-----------------------Resultado------------------------\n");
	for (int i = 0; i < n; i++)
		printf("\t %d \t (%s) \n", dados[i].idade, dados[i].nome);			
}

void OrdenarHeap(int x){
	int tam,cont=0;
	Cadastro t;
	if ((x == 1) || (x == 4)){
		tam=VerificarTamanho();
	}else{
		tam=VerificarTamanhoDeb();
	}
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb");
	Cadastro dados[tam];
	
	if ((x == 2) || (x == 3)){
		while(!feof(file)){
			fread(&t,sizeof(Cadastro),1,file);
			if (t.idade < 16){
				dados[cont] = t;
				cont++;
			}	
		}						
	}else{
		while(!feof(file)){
			fread(&t,sizeof(Cadastro),1,file);
			dados[cont] = t;
			cont++;							
		}
	}
	
	if ((x == 1) || (x == 2)){
		HeapSort(dados,tam);
	}
	
	if ((x == 3) || (x == 4)){
		HeapSortString(dados,tam);
	}
	fclose(file);
	ImprimirTela(dados,tam);
}

void OrdenarTotal(){
	int x;
	
	printf("\n-----------------------Ordenacao------------------------");
	printf("\n1-Os membros pela idade:");
	printf("\n2-Os desbravadores pela idade:");
	printf("\n3-Os desbravadores por ordem alfabeticas:");
	printf("\n4-Os membros por ordem alfabéticas:");
	printf("\nDiegite: ");
	scanf(" %d",&x);
	
	switch (x){
		case 1:
			OrdenarHeap(x);
			break;
		case 2:
			OrdenarHeap(x);
			break;
		case 3:
			OrdenarHeap(x);
			break;
		case 4:
			OrdenarHeap(x);
			break;
		break;
	}
}

void MandarProArqEl(CadastroE y){
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\elevado.txt","ab");
	
	fwrite(&y,sizeof(CadastroE),1,file);
	fclose(file);
}

void CadElevacao(){
	int tam = VerificarTamanho(),codigo = 0,loc = -1,teste = 0;
	Cadastro vetor[tam],a;
	CadastroE y;
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb");
	
	printf("\nDigite o codigo da pessoa: ");
	scanf(" %d",&codigo);
	
	for(int i=0;i<tam;i++){
		fread(&a,sizeof(Cadastro),1,file);
		if(a.codigo == codigo){
			loc = i;
		}
		printf("\n%d-%d",a.codigo,loc);
		vetor[i] = a;
	}
	
	if (loc > -1){
		printf("\nEncontrado!!!");
		printf("\nDesbravador %s",vetor[loc].nome);
		printf("\nNivel: %d",vetor[loc].quali);
		printf("\nDeseja elevar(s=1,n=0)? ");
		scanf(" %d",&teste);
		if(teste == 1){
			y.elevacao = vetor[loc].quali + 1;
			strcpy(y.nome,vetor[loc].nome);
			printf("Digite o código:");
			scanf(" %d",&y.codigo);
			printf("Digite o ano:");
			scanf(" %d",&y.ano);
			printf("Digite o mes:");
			scanf(" %d",&y.mes);
			printf("Digite o dia:");
			scanf(" %d",&y.dia);
			MandarProArqEl(y);
			vetor[loc].quali = vetor[loc].quali + 1;
		}
	}
	
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","wb");
	
	for(int i=0;i<tam;i++){
		a = vetor[i];
		fwrite(&a,sizeof(Cadastro),1,file);
	}
	
	fclose(file);
	//CadElevacao(vetor,tam,loc,codigo);
}

int BuscarEncontrar (int x, int n, int v[]) { 
   int e = -1, d = n; // atenção!
   while (e < d-1) {  
      int m = (e + d)/2;
      if (v[m] < x) e = m;
      else d = m; 
   }
   return d;
}

void BuscarUsuario(){
	int cont = 0, x = 0, tam = VerificarTamanho(),loc = 0;
	int vet[tam];
	Cadastro vetor[tam],a;
	
	FILE *file;
	file = fopen("C:\\Users\\Diego\\Desktop\\pessoa.txt","rb");
	
	printf("Digite o código do membro: ");
	scanf(" %d",&x);
	
	while(fread(&a,sizeof(Cadastro),1,file) != NULL){
		vetor[cont] = a;
		cont++;
	}
	HeapSort(vetor,tam);
	for(int i=0;i<tam;i++){
		vet[i] = vetor[i].codigo;
	}
	loc = BuscarEncontrar(x,tam,vet);
	
	printf("\nA pessoa %s",vetor[loc].nome);
	printf("\nEstá na posicao %d", loc);
}

void BuscaBinaria(){
	int x;
	
	printf("\n1- Buscar Usuário ");
	printf("\n2- Buscar Elevacao ");
	printf("\n3- Buscar Unidade ");
	printf("\nDigite: ");
	scanf(" %d",&x);
	
	if (x == 1){
		BuscarUsuario();
	}
}

int main()
{	
	int y;
	do{
		y=Menu();
		switch(y){
			case 1:
				MandarProArqPe();
				break;
			
			case 2:
				ListarTudo();
				break;
			
			case 3:
				MandarProArqUn();
				break;
			
			case 4:
				EliminarMenu();
				break;
				
			case 6:
				OrdenarTotal();
				break;
				
			case 7:
				CadElevacao();
				break;
				
			case 8:
				CriarVdoarquivo();
				break;
				
			case 9: 
				BuscaBinaria();
				break;
				
			default : printf("Opcao errada:");
				break;
		}
	}while(y <= 10);
	
	return 0;
}
