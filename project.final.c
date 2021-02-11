#include <windows.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>


void mainmenu(void);
void Password(int);
void addusers();
void deleteusers();
void searchusers();
void viewusers();
void editusers();
int getdata();
int checkid();
void returnToMainMenu();
void gotoxy (int x,int y);


char password[10]={"project"};

COORD coord = {0, 0};

struct users
{
    int id;
    char name[50];
    char Adress[50];
    char phoneno[10];
    float Price;
    int count;
    char *cat;
};

struct users user;
FILE *fp, *ft;
int s;
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()

{
    Password(1);
    return 0;
}



void Password(int isFirstTime)
{

   system("cls");
   if(isFirstTime == 0)
   {
     gotoxy(15,16);
	 printf("Incorrect Password. Input the password again");
   }
   char d[19]="Password Protected";
   char ch,pass[10];
   int i=0,j;
    gotoxy(10,3);
    for(j=0;j<20;j++)
    {
        printf("*");
    }
    for(j=0;j<19;j++)
    {
        printf("%c",d[j]);
    }
   for(j=0;j<20;j++)
   {
        printf("*");
   }
   gotoxy(15,7);
   system("color 20");
   printf("Enter Password:");

   while(ch!=13)
   {
	ch=getch();

	if(ch!=13 && ch!=8){
	putch('*');
	pass[i] = ch;
	i++;
	}
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {

	gotoxy(15,9);
	printf("Password match");
	gotoxy(17,10);
	printf("Press any key to go to the main menu.");
	if(getch())
    {
     mainmenu();
    }
   }
   else
   {
	 Password(0);
   }
}



void mainmenu()
{
    char c;
    system("cls");
	gotoxy(20,3);
	system("color 17");
	printf("************** MAIN MENU ****************");
	gotoxy(28,5);
	printf(" 1. Add users   ");
	gotoxy(28,7);
	printf(" 2. Delete users");
	gotoxy(28,9);
	printf(" 3. Search users");
	gotoxy(28,11);
	printf(" 4. View user list");
	gotoxy(28,13);
	printf(" 5. Update user's information");
	gotoxy(28,15);
	printf(" 6. Exit");
	gotoxy(28,17);
	printf("******************************************");

	InputOptions:
	gotoxy(20,19);
	printf("Enter your choice:");
	c = getchar();
	switch(c)
	{
		case '1':
		addusers();
		break;
	case '2':
		deleteusers();
		break;
		case '3':
		searchusers();
	    break;
	    case '4':
		viewusers();
		break;
	    case '5':
		editusers();
		break;
		case '6':
		    system("cls");
            exit(0);
	    default:
		{
		gotoxy(20,23);

		goto InputOptions;
		}

    }
}


void addusers()
{
    system("cls");
	int i;
	fp=fopen("milton.txt","a+");
	if(getdata()==1)
	{

	fseek(fp,0,SEEK_END);
	fwrite(&user,sizeof(user),1,fp);
	fclose(fp);
	gotoxy(21,16);
	printf("The record is sucessfully saved");
	gotoxy(21,17);
	printf("Save any more?(Y / N):");
	if(getch()=='n')
	    mainmenu();
	else
	    system("cls");
	    addusers();
	}
}
int getdata()
{
    system("cls");
	int t;
	gotoxy(20,3);printf("Enter the Information Below");
	gotoxy(15,4);
	printf("********************************************");
	gotoxy(15,15);
	printf("********************************************");
	gotoxy(28,6);
	printf("Category:");
	gotoxy(38,6);
	gotoxy(21,8);
	printf("user ID:\t");
	InputData:
	gotoxy(31,8);
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		gotoxy(15,16);
		printf("\aThe user id already exists. Input again...\a");
		goto InputData;
		return 0;
	}
	user.id=t;
	gotoxy(21,9);
	printf("user Name:");
	gotoxy(33,9);
	scanf("%s",user.name);
	gotoxy(21,10);
	printf("User Adress:");
	gotoxy(35,10);
	scanf("%s",user.Adress);
	gotoxy(21,11);
	printf("Phone number:");
	gotoxy(35,11);
	scanf("%s",&user.phoneno);
	gotoxy(21,12);
	printf("Package Price:");
	gotoxy(35,12);
	scanf("%f",&user.Price);
	gotoxy(21,13);

	return 1;
}
int checkid(int t)
{
	rewind(fp);
	while(fread(&user,sizeof(user),1,fp)==1)
	if(user.id==t)
	return 0;
      return 1;
}


void deleteusers()
{
    char finduser;
    system("cls");
    int d;
    char another='y';
    while(another=='y')
    {
	system("cls");
	gotoxy(10,5);
	printf("Enter the user ID to  delete:");
	scanf("%d",&d);
	fp=fopen("milton.txt","r");
	rewind(fp);
	while(fread(&user,sizeof(user),1,fp)==1)
	{
	    if(user.id==d)
	    {
		gotoxy(10,7);
		printf("The user record is available");
		gotoxy(10,8);
		printf("user name is %s",user.name);
		gotoxy(10,9);
		finduser='t';
	    }
	}
	if(finduser=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("test.txt","w");
		rewind(fp);
		while(fread(&user,sizeof(user),1,fp)==1)
		{
		    if(user.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);
			fwrite(&user,sizeof(user),1,ft);
		    }
		}
		fclose(ft);
		fclose(fp);
		int a=1;

		a=remove("milton.txt");
		rename("test.txt","milton.txt");

		if(a==0)
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	    }
	else
	mainmenu();
	fflush(stdin);
	another=getch();
	}
	else
    {
        gotoxy(10,10);
	    printf("No record is found.");
	    if(getch())
	    mainmenu();
    }
	}
	mainmenu();
}




void searchusers()
{
    system("cls");
    int finduser = 0;
    gotoxy(20,6);
    int userId;
    printf("***************Search users****************");
    gotoxy(30,10);
    printf(" 1. Search By ID");
    gotoxy(30,12);
    printf(" 2. Search By Name");
    gotoxy( 20,14);
    printf("Enter Your Choice");
    fp=fopen("milton.txt","r");
    rewind(fp);
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    gotoxy(25,3);
	    printf("****Search users By Id****");
	    gotoxy(20,5);
	    printf("Enter the user id:");
	    scanf("%d",&userId);
	    while(fread(&user,sizeof(user),1,fp)==1)
	    {
		if(user.id==userId)
		{
		    gotoxy(20,7);
		    printf("The user is available");
		    gotoxy(20,8);
		    printf("*****************************");
		    gotoxy(20,9);
		    printf(" ID:%d",user.id);
		    gotoxy(20,10);
		    printf(" Name:%s",user.name);
		    gotoxy(20,11);
		    printf(" Adress:%s ",user.Adress);
		    gotoxy(20,12);
		    printf(" phoneno:%s ",user.phoneno);
		    gotoxy(20,13);
		    printf(" Price:Rs.%.2f",user.Price);

		    gotoxy(20,15);
		    printf("*****************************");
		    finduser=1;
		}
	    }
	    if(finduser!=1)
	    {
	    gotoxy(22,9);
	    printf("\aNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchusers();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char userNameFromUser[50];
	    system("cls");
	    gotoxy(25,3);
	    printf("****Search users By Name****");
	    gotoxy(20,5);
	    printf("Enter user Name:");
	    scanf("%s",userNameFromUser);
	    int d=0;
	    while(fread(&user,sizeof(user),1,fp)==1)
	    {
		if(strcmp(user.name, userNameFromUser)==0)
		{
		    gotoxy(20,7);
		    printf("The user is available");
		    gotoxy(20,8);
		    printf("******************************");
		    gotoxy(20,9);
		    printf(" ID:%d",user.id);
		    gotoxy(20,10);
		    printf(" Name:%s",user.name);
		    gotoxy(20,11);
		    printf(" Adress:%s ",user.Adress);
		    gotoxy(20,12);
		    printf(" phoneno:%s ",user.phoneno);
		    gotoxy(20,13);
		    printf(" Price:Rs.%.2f",user.Price);

		    gotoxy(20,15);
		    printf("******************************");
		    d++;
		}

	    }
	    if(d==0)
	    {
	    gotoxy(22,9);
	    printf("\aNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchusers();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchusers();
    }
    fclose(fp);
}



void viewusers()
{
    int i=0,j,count=0;
    system("cls");
    gotoxy(1,1);
     printf("*********************************User List*****************************");
    gotoxy(2,2);
    printf("          ID    USER NAME     ADRESS        PHONENO        PRICE     ");
    j=4;
    fp=fopen("milton.txt","r");
    while(fread(&user,sizeof(user),1,fp)==1)
    {
    gotoxy(12,j);
	printf("%d",user.id);
	gotoxy(20,j);
	printf("%s",user.name);
	gotoxy(32,j);
	printf("%s",user.Adress);
	gotoxy(45,j);
	printf("%s",user.phoneno);
	gotoxy(60,j);
	printf("%.2f",user.Price);

	printf("\n\n");
	j++;
	count++;
      }
      gotoxy(3,25);
      printf("Total users =%d",count);
      fclose(fp);
      gotoxy(35,25);
      returnToMainMenu();
}



void returnToMainMenu()
{
    {
	printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13)
    mainmenu();
    else
    goto a;
}



void editusers()
{
    system("cls");
	int c=0;
	int d,e;
	gotoxy(20,4);
	printf("****Edit users Section****");
	char another='y';
	while(another=='y')
	{
		system("cls");
		gotoxy(15,6);
		printf("Enter user Id to be edited:");
		scanf("%d",&d);
		fp=fopen("milton.txt","r+");
		while(fread(&user,sizeof(user),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				gotoxy(15,7);
				printf("The user is availble");
				gotoxy(15,8);
				printf("The user ID:%d",user.id);
				gotoxy(15,9);
				printf("Enter new name:");scanf("%s",&user.name);
				gotoxy(15,10);
				printf("Enter new adress:");scanf("%s",&user.Adress);
				gotoxy(15,11);
				printf("Enter new phone Number:");scanf("%s",&user.phoneno);
				gotoxy(15,12);
				printf("Enter new price:");scanf("%f",&user.Price);
				gotoxy(15,13);

				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(user),0);
				fwrite(&user,sizeof(user),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				printf("No record found");
			}
		}
		gotoxy(15,16);
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another=getch();
	}
		returnToMainMenu();
}






