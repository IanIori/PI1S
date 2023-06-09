#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>   
#include <unistd.h>
FILE *fp;
FILE *fp1; //temp
char data[100];
int code;
char name[32];
char amount[4];
char supplier[64];

void report() {
    fp = fopen("Warehouse.txt", "r");
 
    if (!fp) {
        printf("Can't open file\n");
	} else {
 		
        int line=1, i=0;
        int size = 0;
 
        while (fgets(data, 100, fp) != NULL) {
            //printf("%d ", line);
			size = strlen(data);
			
            for(i = 0; i < size; i++){
			data[i] == ',' ? data[i] = '\t' : data[i];
			}
 			printf("%s", data);
			line++;
		}
        fclose(fp);
        printf("\n");
    }
}

void registerProduct() {
    fp = fopen("Warehouse.txt", "a+");
 
    if (!fp) {
        printf("Can't open file\n");
	} else {
		
		int line = 0;
		while (fgets(data, 104, fp) != NULL) {
			line++;
		}
		
    	printf("This product code is: %d\n", line);
	    printf("\nEnter product name: ");
		scanf(" %[^\n]s", name);
	    printf("\nEnter quantity in stock: ");
	    scanf(" %[^\n]s", amount);
	    printf("\nEnter supplier name: ");
	    scanf(" %[^\n]s", supplier);
	    
	    fprintf(fp,"%d,%s,%s,%s\n", line, name, amount, supplier);
	 
	    printf("\nNew product added to stock!\n");
	}
	fclose(fp);
}

void editProduct() {
	int id;
	int reg = 1;
	char ans;
	int  size = 0, i = 0, j = 0, k;
	char fields[4][64];
	
	report();
	
	printf("Enter the product code you wish to edit: ");
	scanf("%d",&id);
	
	fp = fopen("Warehouse.txt","r");
	fp1 = fopen("temp.txt","w");
	
	while(fgets(data, 100 , fp) != NULL){
		if(reg == id+1){
			size = strlen(data);
			for(k=0; k < size; k++){
					if(data[k] != ','){
						fields[i][j] = data[k];
						j++;
					}else{
						fields[i][j] = '\0';
						i++;
						j=0;
					}
			}
			
			printf("Name: %s \nChange (y/n)?",fields[1]);
			scanf(" %c",&ans);
			if(ans == 'y'){
				printf("Updated name: ");
				fflush(stdin);
				gets(fields[1]);
			}
			
			printf("Amount: %s \nChange (y/n)?",fields[2]);
			scanf(" %c",&ans);
			if(ans == 'y'){
				printf("Updated aumount: ");
				fflush(stdin);
				gets(fields[2]);
			}
			
			printf("Supplier: %sChange (y/n)?",fields[3]);
			scanf(" %c",&ans);
			if(ans == 'y'){
				printf("Updated supplier: ");
				fflush(stdin);
				gets(fields[3]);
			}
			
			fprintf(fp1,"%s,%s,%s,%s",fields[0], fields[1], fields[2], fields[3]);		
		} else{
			fprintf(fp1,"%s",data);
		} 
		reg++;
	}
	fclose(fp);
	fclose(fp1);
	remove("Warehouse.txt");
	rename("temp.txt","Warehouse.txt");
	printf("\n\nProduct updated!\n\n");
}

void deleteProduct() {
	int id;
	int reg = 1;
	int  size = 0;
	char fields[4][64];
	
	report();
	
	printf("Enter the product code you wish to delete: ");
	scanf("%d",&id);
	
	fp = fopen("Warehouse.txt","r");
	fp1 = fopen("temp.txt","w");
	
	while(fgets(data, 100 , fp) != NULL){
		if(reg != id+1){
			fprintf(fp1,"%s",data);	
		} 
		reg++;
	}
	fclose(fp);
	fclose(fp1);
	remove("Warehouse.txt");
	rename("temp.txt","Warehouse.txt");
	printf("\n\nProduct updated!\n\n");
}

void header() {
	system("cls");	
	printf("////////////////////////////////////////////\n");
	printf("/                                          /\n");
	printf("/  Warehouse                               /\n");
	printf("/                              By LockTech /\n");
	printf("////////////////////////////////////////////\n");
	printf("\n");	
}

void mainMenu() {
	printf("1 - STOCK REPORT\n");
	printf("2 - REGISTER ITEM\n");
	printf("3 - EDIT ITEM\n");
	printf("4 - DELETE ITEM\n");
	printf("0 - EXIT\n\n");
	printf("Choose: ");
}

void exception() {
	printf ("Opção inválida, tente novamente!\n");
	fflush(stdout);
	sleep(1);
}

void pause() {
		printf("\nPress Any Key to Continue");
		getch();
}

main() {
	setlocale(LC_ALL, "Portuguese");
	char option = '.';
	while (option != '0') {
		
	header();
	mainMenu();
	scanf(" %c", &option);
	
	switch (option) {
		case '1':
			header();	
			report();	
			pause();
			break;
						
		case '2':
			header();
			registerProduct();
			pause();
			break;
			
		case '3':
			header();
			editProduct();
			pause();
			break;
			
		case '4':
			header();	
			deleteProduct();
			pause();
			break;
			
		case '0':
			printf("\nThanks for using our system!");
			printf("\nOur team is composed by: Guilherme, Vinícius and Ian\n");
			exit(0);
		default:
			exception();	
		}
		
	}
	
}
