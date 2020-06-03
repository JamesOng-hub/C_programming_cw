#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ENTER 1
#define UPDATE 2
#define SEARCH 3
#define PRODUCE 4
#define DELETE 5
#define SAVE 6
#define QUIT 7

#define INVENTORYSIZE 1000
#define MAXLINELENGTH 1000
//maybe we can add a function to expand inventory. 
void displayMenu();
int getMenuOption();
void doOptions(int option);
void enterNew();
void updateNum();
void searchItem();
void produceReport();
void delete();
void saveData();
void laodData();
void testing();
char* inputText();
void sortList();
void removeNewLine(char *buffer);

struct data

{
	char *name;
	char *barcode;
	char *price;
	char *number;
};

struct data products[INVENTORYSIZE];


void displayMenu()
//display options
{
	printf("Inventory\n");
	printf("%i. Enter an item\n", ENTER);
	printf("%i. Update the number in stock\n",UPDATE);
	printf("%i. Search for an item\n", SEARCH);
	printf("%i. Produce a report of all items\n", PRODUCE);
	printf("%i. Delete an item\n", DELETE);
	printf("%i. Save data to a file\n", SAVE);
	printf("%i. Quit\n", QUIT);
} 

//a func that takes the option. 
int getMenuOption()
{
	int option =0;
	printf("Enter Option: ");
	scanf("%d",&option);
	return option;
}//it works. 


void doOptions(int option)
//takes it from getMenuOption and carry out the func.
{
	switch(option)
	{
		case ENTER: enterNew(); break;
		case UPDATE: updateNum();break;
		case SEARCH: searchItem(); break;
		case PRODUCE: produceReport(); break;
		case DELETE: delete(); break;
		case SAVE: saveData(); break;
		default: printf("\nSorry, option is not recognised.\n");
	}
}

//a function that enters a new item into the structure. 
void enterNew()
{
	//b4, the user adds sth, you can tell how many items it has. 
	//run through the whole list
	int index = 0;
	for (index = 0; index < INVENTORYSIZE; index++)
	{
		if ((index == INVENTORYSIZE-2) && (products[index].name != NULL))//the last item is NULL
		{//If the second last item has sth, then the inventory is full
			printf("The inventory is full.\n");//proceed to resize the inven.
			break;
		}
		else if (products[index].name == NULL)

		{//so now we have the index of the null product
			products[index].name = inputText("Enter name: ");
			products[index].barcode = inputText("Enter barcode: ");
			products[index].price = inputText("Enter price: ");
			products[index].number = inputText("Enter number: ");

			products[index+1].name = NULL;
			products[index+1].barcode = NULL;
			products[index+1].price = NULL;
			products[index+1].number = NULL;
			break;
		}
	} 

}

//write a function that updates the number
void updateNum()
{
	int index =0;
	char* name = inputText("Enter the name of the item you want to search: ");
	/*while (products[index].name != NULL)
	{*/
	for (index = 0; index< INVENTORYSIZE; index++)
	{
		if (products[index].name == NULL)
		{ 
			printf("There is no such item in the inventory.\n");
			break;
		}

		else if (!strcmp(products[index].name,name))//if it matches 
		{
			char* number = inputText("Enter its new number: ");
			products[index].number = number;
			break;
		}
		
	}
	
	
}



//write a function that searches for an item. 
void searchItem()
{
	int index =0;
	char* name = inputText("Enter the name of the item you want to search: ");
	for (index = 0; index< INVENTORYSIZE; index++)
	{
		if (products[index].name == NULL)
		{ 
			printf("There is no such item in the inventory.\n");
			break;
		}

		else if (!strcmp(products[index].name, name)) //if it matches
		{
			printf("%s %s %s %s.\n", products[index].name, products[index].barcode, products[index].price, products[index].number);
			break;
		}
		
	}
}

//write a funciton that list all the items in the inventory. 
void produceReport()
{
	int index =0, index1 =0; //while loop, it will do it unitl NULL. 
	for (index = 0; index <INVENTORYSIZE; index++)
	{
		sortList(); 
	}//at here the index will be INVENTORYSIZE-1
	//so need to reset the index or set a new index1.

	while (products[index1].name != NULL)
	{
		printf("\n");
		printf("Name: %s\n", products[index1].name);
		printf("Barcode: %s\n", products[index1].barcode);
		printf("Price: %s\n", products[index1].price);
		printf("Number: %s\n\n", products[index1].number);
		index1++;
	}
}

//write a function that deletes an item from the inventory. 
void delete()
{
	int index = 0; 
	char* name = inputText("Enter the name of the item you want to delete: ");
	for (index = 0; index< INVENTORYSIZE; index++)
	{
		printf("%d\n", index);
		if (products[index].name == NULL)
		{ 
			printf("null%d\n", index);
			printf("There is no such item in the inventory.\n");
			break;
		}

		else if (!strcmp(products[index].name, name)) //if it matches
		{
			for (int x = index; x< INVENTORYSIZE; x++)
			{	
			printf("yay%d\n", x);
			products[x].name = products[x+1].name;
			
			}
			break;
		}
	
	}
	
}

//write a function that save the data to a file. 
void saveData()
{
	char* fileName = inputText("Enter the name of the file: ");
	FILE* outputFile = fopen(fileName,"w");
	if (outputFile == NULL)
  	{
   		printf("\nUnable to write to file - phone book not saved.\n");
    	free(fileName);
    	return;
  	}
  	int index = 0;
  	while (products[index].name != NULL)
  	{
  		fprintf(outputFile, "%s\n", products[index].name); 
  		fprintf(outputFile, "%s\n", products[index].barcode);
  		fprintf(outputFile, "%s\n", products[index].price);
  		fprintf(outputFile, "%s\n", products[index].number);
  		index++;
  	}
  	fclose(outputFile);
  	free(fileName);

}





int main()
{
	testing();
	while (true)
  	{
  		displayMenu();
  		int option = getMenuOption();
  		if (option == QUIT) {break;}
  		else {doOptions(option);}
  	}
  	return 0;

}

void testing()
{
products[0].name = "belt";
products[0].barcode = "33977045743";
products[0].price = "12.99";
products[0].number = "5";

products[1].name = "shoes";
products[1].barcode = "91053008129";
products[1].price = "13.99";
products[1].number = "8";

products[2].name = "bag";
products[2].barcode = "97256259795";
products[2].price = "19.99";
products[2].number = "10";

products[3].name = NULL;
products[3].barcode = NULL;
products[3].price = NULL;
products[3].number = NULL;


}

//a function that takes in text. 
char* inputText(char* msg)
{
	int size =1000; //1000 bytes 
	char* text = NULL;

	text = (char* )malloc(size * sizeof(char));
	if (text != NULL) //meaning that memory was successfully allocated
	{
		printf("%s", msg);
		scanf(" "); //this is important somehow. why? 
		gets(text); //get as reads from the stdin		
	}
	return text;
}

void sortList()
{
	
	for (int index = 0; index < INVENTORYSIZE; index++)
	{
	if (products[index+1].name == NULL) //first condition to check is whether i am at the end. 
		{break;}

	else if (products[index].name[0] < products[index+1].name[0]) //c can compare alphabets 
		{;}
	
	else
		{
		//swap sides. 
		char* name, * barcode,* price, * number; 
		name = products[index].name;
		products[index].name = products[index+1].name;
		products[index+1].name = name;

		barcode =products[index].barcode;
		products[index].barcode = products[index+1].barcode;
		products[index+1].barcode = barcode;

		price =products[index].price;
		products[index].price = products[index+1].price;
		products[index+1].price = price;

		number =products[index].number;
		products[index].number = products[index+1].number;
		products[index+1].number = number;
		}
	}
}