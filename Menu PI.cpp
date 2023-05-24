#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>   
#include <unistd.h>

void report() {
    FILE* fp = fopen("C:\\Users\\1050482313014\\Desktop\\Warehouse\\Warehouse.txt", "r");
 
    if (!fp) {
        printf("Can't open file\n");
        
	} else {
        char buffer[64];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,64, fp)) {
            column = 0;
            row++;
        
            if (row == 1) {
            	continue;
			}
                
            char* value = strtok(buffer, ",");
 
            while (value) {
                if (column == 0) {
                    printf("Code: ");
                }
 
                if (column == 1) {
                    printf("\tName: ");
                }
 
                if (column == 2) {
                    printf("\nQuantity: ");
                }
                
                if (column == 3) {
                    printf("\tSupplier: ");
                }
 
                printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }
            printf("\n");
        }
        fclose(fp);
    }
}

void registerProduct() {
    FILE* fp = fopen("C:\\Users\\1050482313014\\Desktop\\Warehouse\\Warehouse.txt", "a+");
 
 	char name[64], supplier[64];
 	int code, quantity;
 
    if (!fp) {
        printf("Can't open file\n");
	} else {
		
		char buffer[128];
		char *value1;
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer, 128, fp)) {
            column = 0;
            row++;
        
            if (row == 1) {
            	continue;
			}
                
            char* value = strtok(buffer, ",");
 			
            while (value) {
            	if (column == 0) {
                    code = strtol(buffer, &value1, 10);
                }
                value = strtok(NULL, ",");
            	column++;
			}	
    	}
    
    	printf("This product code is: %d", code+1);
	    printf("\nEnter product name: ");
		scanf(" %[^\n]s", &name);
	    printf("\nEnter quantity in stock: ");
	    scanf("%d", &quantity);
	    printf("\nEnter supplier name: ");
	    scanf(" %[^\n]s", supplier);
	    
	    fprintf(fp,"%d,%s,%d,%s\n",code+1,name,quantity,supplier);
	 
	    printf("\nNew product added to stock!\n");
	}
	fclose(fp);
}

void editProduct() {
	
} 

void deleteProduct() {
	int lno, ctr = 0;
	char ch;
    char fname[128];
    char str[128], temp[] = "temp.txt";
    FILE *fp = fopen("C:\\Users\\1050482313014\\Desktop\\Warehouse\\Warehouse.txt", "r");
 	FILE *fp1 = fopen(temp, "w") ;
 
    if (!fp) {
        printf("Can't open file\n");
	} else {
		if (!fp1) {
			printf("Can't open temporary file\n");
		}
		
		printf("Input the line you want to remove: ");
		scanf("%d", &lno);
		lno++;

		while (!feof(fp)) 
        {
            strcpy(str, "\0");
            fgets(str, 128, fp);
            if (!feof(fp)) {
                ctr++;
                if (ctr != lno) {
                    fprintf(fp1, "%s", str);
                }
            }
        }
        fclose(fp);
        fclose(fp1);
        remove("C:\\Users\\1050482313014\\Desktop\\Warehouse\\Warehouse.txt");  
        rename(temp, "C:\\Users\\1050482313014\\Desktop\\Warehouse\\Warehouse.txt"); 
    }
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
		printf("Press Any Key to Continue");
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
			break;
			
		case '4':
			header();	
			deleteProduct();
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
