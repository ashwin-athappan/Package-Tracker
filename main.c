#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define MaxWeight 10
#define Size 50

struct product{
    char productname[40];
    int count;
    struct product *next;
};

struct package{
    char deliveryguyname[20];
    int contact[10];
    struct product *pro;
    int weight;
    bool dispatchstatus;
    bool deliverystatus;
    char ID[11];
    char otp[7];
};

struct previousOrders{
    struct package *pack;
    int top;
    struct previousOrders *next;
};

struct orderQueue{
    struct package *p[50];
    int front,rear;
};

struct Cart{
    struct product *pro;
};

struct Customer{
    char name[30];
    char email[50];
    int age;
    int itemstop;//Maintain Stacks Top
    char address[50];
    struct previousOrders *previousOrders;
    struct Customer *next;
    char password[20];
    struct Cart *cart;
    char otp[7];
};

struct Customer *c,*cback;

void login();

void ID_generator(struct package *pack){
    int length = 10;
    int key;
    int temp,i=0;
    char *otp;
    char *string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // Seed number for rand()

    srand((unsigned int) time(0));

    temp = length;
    printf("\n");

    while(temp--) {
        key = rand() % strlen(string);
        pack->ID[i] = string[key];
        srand(rand());
        i++;
    }
    pack->ID[i] = '\0';
}

void otp_generator(struct Customer *customer){

    int length = 6;
    int key;
    int temp,i=0;
    char *otp;
    char *string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    /* Seed number for rand() */

    srand((unsigned int) time(0));

    temp = length;
    printf("\n");

    while(temp--) {
        key = rand() % strlen(string);
        customer->otp[i] = string[key];
        srand(rand());
        i++;
    }
    customer->otp[i] = '\0';
    strcpy(customer->previousOrders->pack->otp,customer->otp);
}

void push(struct Customer* cus,struct package *pack){
    struct previousOrders *new = (struct previousOrders*)malloc(sizeof(struct previousOrders));
    new->pack = pack;
    new->next = NULL;
    if(cus->previousOrders == NULL){
        cus->previousOrders = new;
    }else{
        new->next = cus->previousOrders;
        cus->previousOrders = new;
    }
    cus->previousOrders->top = cus->itemstop;
    cus->previousOrders->top++;
    cus->itemstop++;
}

void displayPreviousOrders(struct Customer* cus){
     system("cls");

     struct previousOrders *tmp=cus->previousOrders;
     int i=cus->previousOrders->top;
     while(tmp!=NULL){
         struct product *p = tmp->pack->pro;
         printf("Package %d\n",i+1);
         while(p!=NULL) {
             printf("%s \t %d\n", p->productname, p->count);
             p=p->next;
         }
         tmp=tmp->next;
         i--;
     }
    printf("\n\n");
}

void trackPackage(struct Customer *cust){
    int i;
    char ID[15];
    printf("Enter the order ID");
    scanf("%s",ID);
    i = cust->itemstop;
    if(strcasecmp(cust->previousOrders->pack->ID,ID)==0){
        if(cust->previousOrders->pack->dispatchstatus == TRUE){
            printf("\n\n\nThe product is dispatched \n\n\n");
        }
    }else{
            printf("\n\n\nThe product is not dispatched \n\n\n");
    }
}



void placeOrder(struct Customer *cust){
    struct product *new,*temp;
    int n;
    int ch = 1;
    printf("\n\n\n\n\nSelect from a variety of items in our store:");
    while(ch!=0) {
        new = (struct product*)malloc(sizeof(struct product));
        new->next = NULL;
        printf("\nEnter the name of the product (Note: no spaces in between words instead use '_'):");
        scanf("%s",new->productname);
        printf("\nEnter the quantity:");
        scanf("%d",&n);
        new->count = n;
        temp = cust->cart->pro;
        if(cust->cart->pro == NULL){
            cust->cart->pro = new;
        }else{
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = new;
        }


        printf("Enter '0' to proceed to checkout or '1'  to continue shopping");
        scanf("%d",&ch);
        if(ch==0){
            struct package *pack = (struct package*)malloc(sizeof(struct package));
            pack->weight = 0;
            struct product *point = cust->cart->pro;
            while(point!=NULL) {
                n = point->count;
                pack->weight += n;
                point=point->next;
            }
                pack->dispatchstatus = true;
                ID_generator(pack);
                pack->pro=cust->cart->pro;
            push(cust,pack);
            struct product *tmp;
            tmp = cust->cart->pro;
            cust->cart->pro = NULL;
            otp_generator(cust);
            break;
        }
    }
    printf("\nYour OTP is : %s \nand your Package ID is %s\n\n\n\n",cust->otp,cust->previousOrders->pack->ID);
    printf("Please remember it\n\n\n\n");
}

void UserMenu(struct Customer *p){
    int ch,n;
    printf("\n\n\n\nWelcome %s \n",p->name);
    do {
        printf("1.Place an order\n2.View previous orders\n3.Track a package\n4.Back\n");
        scanf("%d",&ch);
        switch (ch){
            case 1:
                placeOrder(p);
                break;
            case 2:displayPreviousOrders(p);
                break;
            case 3:trackPackage(p);
                break;
            case 4:system("cls");
                return;
            default:printf("Invalid option.");
        }
    }while(ch!=4);
}

void SignUp(){  //Sign Up page
    struct Customer *p = c,*q = c,*new;

    int age,flag=0;
    char password[20],password2[20],name[30],email[50],address[50];

    printf("\n\n\n\nEnter your name:");
    scanf("%s",name);
    while(q!=NULL){
       if(strcasecmp(q->name,name)==0){
           printf("\nUsername already exists. Try again\n\n\n\n\n");
           flag = 1;
       }
       q=q->next;
    }
    if(flag == 1){
        return;
    }
    printf("\nEnter your age:");
    scanf("%d",&age);
    printf("\nEnter your address:");
    scanf("%s",address);
    printf("\nEnter your Email id:");
    scanf("%s",email);
    printf("\nEnter your password:");
    scanf("%s",password);
    printf("\nEnter your password again:");
    scanf("%s",password2);
    while(1){
        if(strcasecmp(password,password2)==0){
            break;
        }else{
            printf("\nThe passwords you Entered do not match please enter the again:");
            printf("\nEnter your password:");
            scanf("%s",password);
            printf("\nEnter your password again:");
            scanf("%s",password2);
        }
    }

    new = (struct Customer*)malloc(sizeof(struct Customer));
    new->next = NULL;
    strcpy(new->name,name);
    strcpy(new->email,email);
    strcpy(new->password,password);
    new->age = age;
    strcpy(new->address,address);
    new->itemstop = -1;
    new->cart = (struct Cart*)malloc(sizeof(struct Cart));
    new->cart->pro = NULL;
    p = c;
    if(p->next == NULL){
        p->next = new;
    }else {
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = new;
    }
    cback = new;
    printf("\n\n\n\n");
}

void adminView(){
    struct Customer *p;
    printf("\n\n\n");
    for(p=c;p!=NULL;p=p->next){
        printf("\n");
        printf("%s \t%s \t%s",p->name,p->email,p->password);
        printf("\n");
    }
}

void removeUser(){
    char name[30];
    int flag=0;
    printf("Enter the name of the user:");
    scanf("%s",name);

    struct Customer *p = c,*q;
    if(strcasecmp(name,c->name)==0){
        printf("Cannot remove admin:");
        return;
    }

        while (p != NULL) {
            if (strcasecmp(p->name, name) == 0) {
                flag = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        if (flag == 1) {
            printf("%s was removed", p->name);
            q->next = p->next;
            free(p);
        }

}

void adminPage(){
    struct Customer *p;
    int ch,flag=0;
    char name[30];
  do {
      printf("\n\n\n\n1.View User Accounts\n2.Add User\n3.Remove User\n4.View Transactions of a User\n5.Back\n");
      scanf("%d", &ch);
      switch (ch){
          case 1:adminView();
              break;
          case 2:SignUp();
              break;
          case 3:removeUser();
              break;
          case 4:printf("Enter the user name you want to view transactions of:");
                 scanf("%s",name);
              struct Customer *p = c;
              while(p!=NULL){
                if(strcasecmp(name,p->name)==0){
                    flag = 1;
                    break;
                }
              }
              if(flag == 1){
                  displayPreviousOrders(p);
              }else{
                  printf("\nNo such user exists\n");
              }
              flag = 0;
              break;
          case 5:system("cls");
              return;
          default: printf("\nInvalid option\n");
      }
  }while (ch!=5);

}

void login(){   //Login Page
    printf("\n\n\n");
    system("cls");
    char email[50],pass[20],ch;
    struct Customer *p=c;
    printf("Enter your email:");
    scanf("%s",email);
    while(1){
        if(p!=NULL){
            if(strcasecmp(p->email,email)==0){
                if(strcasecmp(email,"admin@packagetracker.com")==0){
                    printf("Enter your password:");
                    scanf("%s",pass);
                    if(strcasecmp(pass,"4265")==0){
                        adminPage();
                        return;
                    }else{
                        printf("Incorrect Password\n This activity will be reported");
                    }
                }else {
                    printf("Enter your password:");
                    scanf("%s", pass);
                    if (strcasecmp(p->password, pass) == 0) {
                        UserMenu(p);
                        return;
                    } else {
                        printf("Incorrect Password");
                    }
                }
            }
        }else{
            printf("No account found please sign up");
            printf("\nEnter 'y' if you want to signup or 'r' to return");
            scanf("%c",&ch);
            if(ch == 'y'|| ch == 'Y'){
                SignUp();
            }else if(ch == 'r'|| ch == 'R'){
                return;
            }
            break;
        }
        p=p->next;
    }
}

void createJunkAccount(char *name, int age, char *add, char *email, char *pass){
    struct Customer *new,*p;
    new = (struct Customer*)malloc(sizeof(struct Customer));
    new->next = NULL;
    strcpy(new->name,name);
    strcpy(new->email,email);
    strcpy(new->password,pass);
    new->age = age;
    new->previousOrders = NULL;
    strcpy(new->address,add);
    new->itemstop = -1;
    new->cart = (struct Cart*)malloc(sizeof(struct Cart));
    new->cart->pro = NULL;
    p = c;
    if(p->next == NULL){
        p->next = new;
    }else {
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = new;
    }
    cback = new;
}

void menu(){ //Main Menu
    int ch,n;
    do{ printf("1.Login\n2.Sign up\n3.Exit");
        printf("\nEnter your choice:");
        scanf("%d",&ch);
        switch (ch){
            case 1:system("cls");
                login();
                break;
            case 2:system("cls");
                SignUp();
                break;
            case 3: exit(0);
            default: printf("Wrong Input");
        }
    }while (ch!=3);
}

int main() {
    c = (struct Customer*)malloc(sizeof(struct Customer));
    c->next=NULL;
    strcpy(c->name,"admin");
    strcpy(c->email,"admin@packagetracker.com");
    strcpy(c->address,"CONFIDENTIAL");
    strcpy(c->password,"4265");
    c->age = 19;
    createJunkAccount("Ashwin", 19, "abc", "a@g", "1234");
    menu();
    return 0;
}