# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<conio.h>
struct Bus{
    char name[30];
    int Bus_No;
    int total_seat;
    char Starting_Route[30];
    char Ending_Route[30];
} a;
struct Bus_seat{
    int bus_no;
    int Tseat;
    int Seat[120];
}seat;
void Menu();
void Add_Bus();
void View_All_Bus_Details();
void Search_bus();
void Booking_Ticket();
void Cencle_ticket();
void Update_Bus_details();
void Delete_bus_record();
void SEAT_STATUS();
int main(){
    printf("\n**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
    printf("**   *******-----*******-----******------*******     **\n");
    printf("**   **                                       **     **\n");
    printf("**   **   Welcome to Bus Management  System   **     **\n");
    printf("**   **                                       **     **\n");
    printf("**   *******-----*******-----******------*******     **\n");
    printf("**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**\n");
    printf("Enter any key to countinue: ");
    char c;
    c=getche();
    Menu();
    return 0;
}
void Menu(){
printf("\npress particular option\n");
printf("1: Add_Bus\n");
printf("2: Search_bus for your route\n");
printf("3: Check Seat Status\n");
printf("4: Booking_Ticket\n");
printf("5: Cencle_ticket\n");
printf("6: Update_Bus_details\n");
printf("7: View_All_Bus_details\n");
printf("8: Delete Bus Record\n");
printf("9: Exit\n");
int choice;
printf("Enter your choice:");
scanf("%d",&choice);
switch(choice){
    case 1:
        Add_Bus();
        break;
    case 2:
        Search_bus();
        break;
    case 3:
        SEAT_STATUS();
        break;    
    case 4:
        Booking_Ticket();
        break;
    case 5:
        Cencle_ticket();
        break;
    case 6:
        Update_Bus_details();
        break;
    case 7:
        View_All_Bus_Details();
        break;
    case 8:
        Delete_bus_record();
        break;        
    case 9:
        printf("\nYou are successfully exit\n");
        break;
    default:
        printf("INVALID INPUT TRY AGAIN");
        Menu();                        
}
}
/*      **************Adding Bus Details***************     */
void Add_Bus(){
	system("cls");
    printf("Enter the bus_number:");
    scanf("%d",&a.Bus_No);
    char name[30],Starting_Route[30],Ending_Route[30];
    int Bus_no,total_seat,flag=0;
    FILE *ptr,*ptr1;
    ptr=fopen("project.txt","a");
    if(ptr==NULL){
        printf("File can not be open");
        exit(1);
    }
    while(fscanf(ptr,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
    	if(Bus_no==a.Bus_No){
    		flag=1;
		}
	}
	fclose(ptr);
	if(flag==0){
	printf("Enter the bus name:");
    scanf("%s",a.name);
    printf("Enter the Totalseat number:");
    scanf("%d",&a.total_seat);
    printf("Enter the starting point:");
    scanf("%s",a.Starting_Route);
    printf("Enter the Ending point:");
    scanf("%s",a.Ending_Route);
    ptr=fopen("project.txt","a");
    fprintf(ptr,"%s\t\t%d\t\t%d\t  %s\t%s\n",a.name,a.Bus_No,a.total_seat,a.Starting_Route,a.Ending_Route);
    // fwrite(&a,sizeof(a),1,ptr);
    printf("Data successfully added\n");
	fclose(ptr);
    ptr1=fopen("seat.txt","a");
    
    int i;
    seat.bus_no=a.Bus_No;
    seat.Tseat=a.total_seat;
    for(i=0;i<a.total_seat;i++){
        if(i%3==0)
            seat.Seat[i]=1;
        else
            seat.Seat[i]=0;    
    }
    fwrite(&seat,sizeof(seat),1,ptr1);
    fclose(ptr1);
	}
	else{
		printf("\nThis bus number already exist\n");
	}
    char ch;
    printf("Press any key to continue:");
    ch=getche();
    Menu();
    return ;
}
/* *********************Search Bus Details***************************************** */
void Search_bus(){
    system("cls");
    char starting_point[40],ending_point[40];
    printf("Enter your starting_station and ending_station:");
    fflush(stdin);
    gets(starting_point);
    fflush(stdin);
    gets(ending_point);
    FILE* ptr=NULL;
    ptr=fopen("project.txt","r");
    if(ptr==NULL){
        printf("\nfile cannot open\n");
        exit(1);
    }
    char name[30],Starting_Route[30],Ending_Route[30];
    int Bus_no,total_seat,flag=0,serial_no=1;
    printf("\n   ****************Search Record **************\n");
    while(fscanf(ptr,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
    	if(strcmp(starting_point,Starting_Route)==0 && strcmp(ending_point,Ending_Route)==0){
             printf("Ser_No:%d Bus_name::%s\tBus_no.:%d\tTotalseat:%d\tStarting-point:%s\tEnding-point:%s\n\n",serial_no,name,Bus_no,total_seat,Starting_Route,Ending_Route);
    	    serial_no+=1;
            flag=1;
        }
    }
    fclose(ptr);
    if(flag==0){
        printf("Record not found");
    }
    char c;
    printf("\nPress any key to continue:");
    c=getche();
    Menu();
    return;
}
/* *********************Booking Ticket*****************************************  */
void Booking_Ticket(){
    FILE *ptr,*ptr1;
    ptr=fopen("seat.txt","r");
    system("cls");
    int n,m;
    printf("Enter bus number:");
    scanf("%d",&n);
    ptr1=fopen("seat1.txt","w");
    int flag=0;
    int i;
    while(fread(&seat,sizeof(seat),1,ptr)){
        if(n==seat.bus_no){
            printf("Enter the seat number:");
            scanf("%d",&m);
            if (seat.Seat[m-1]==0){
                seat.Seat[m-1]=1;
                flag=1;
                fwrite(&seat,sizeof(seat),1,ptr1);
            }
        }
        else{
        fwrite(&seat,sizeof(seat),1,ptr1);
        }
    }
    fclose(ptr1);
    fclose(ptr);
    ptr=fopen("seat.txt","w");
    ptr1=fopen("seat1.txt","r");
    while(fread(&seat,sizeof(seat),1,ptr1)){
        fwrite(&seat,sizeof(seat),1,ptr);
    }
    fclose(ptr1);
    fclose(ptr);
    ptr1=fopen("seat1.txt","w");
    fclose(ptr1);
    remove("seat1.txt");
    if(flag==1)
        printf("\nSeat booked and your seat number is %d\n",m);
    else
        printf("\nSEAT ALREADY BOOKED TRY AGAIN\n");        
    Menu();
    return ;

}
/* *********************Cencle Ticket***************************************** */
void Cencle_ticket(){
    FILE *ptr,*ptr1;
    ptr=fopen("seat.txt","r");
    system("cls");
    int n,m;
    printf("Enter bus number:");
    scanf("%d",&n);
    ptr1=fopen("seat1.txt","w");
    int flag=0;
    int i;
    while(fread(&seat,sizeof(seat),1,ptr)){
        if(n==seat.bus_no){
            printf("Enter the seat number:");
            scanf("%d",&m);
            if (seat.Seat[m-1]==1){
                seat.Seat[m-1]=0;
                flag=1;
                fwrite(&seat,sizeof(seat),1,ptr1);
            }
        }
        else{
        fwrite(&seat,sizeof(seat),1,ptr1);
        }
    }
    fclose(ptr1);
    fclose(ptr);
    ptr=fopen("seat.txt","w");
    ptr1=fopen("seat1.txt","r");
    while(fread(&seat,sizeof(seat),1,ptr1)){
        fwrite(&seat,sizeof(seat),1,ptr);
    }
    fclose(ptr1);
    fclose(ptr);
    ptr1=fopen("seat1.txt","w");
    fclose(ptr1);
    remove("seat1.txt");
    if(flag==1)
        printf("\nYour seat number %d cencle successfully \n",m);
    else
        printf("\nSEAT ALREADY BOOKED TRY AGAIN\n");        
    Menu();
    return ;
    
}
/* ***************************Update Bus Details****************************** */
void Update_Bus_details(){
    system("cls");
     FILE *ptr,*ptr1;
    ptr=fopen("project.txt","r");
    if(ptr==NULL){
        printf("\nFile cannot be open\n");
        exit(1);
    }
    int BUS_NO;
    printf("Enter the bus no. which you want to update:");
    scanf("%d",&BUS_NO);
    int flag=0;
    char name[30],Starting_Route[30],Ending_Route[30];
    int Bus_no,total_seat;

    int preseat;
    ptr1=fopen("Temp.txt","a");
    while(fscanf(ptr,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
        if(BUS_NO==Bus_no){
            preseat=total_seat;
            flag=1;
        }
        else{
            fprintf(ptr1,"%s\t\t%d\t\t%d\t  %s\t%s\n",name,Bus_no,total_seat,Starting_Route,Ending_Route);
        }    
    }
    fclose(ptr);
    fclose(ptr1);
    if(flag==1){
        printf("\nENTER THE NEW DATA THAT YOU WANT TO UPDATE IF SOME DATE YOU DON'T WANT TO UPDATE THEN ENTER OLD DATA\n");
        printf("Enter the new bus number:");
        scanf("%d",&a.Bus_No);
        printf("Enter the new bus name:");
        scanf("%s",a.name);
        printf("Enter the new Totalseat number:");
        scanf("%d",&a.total_seat);
        printf("Enter the starting point:");
        scanf("%s",a.Starting_Route);
        printf("Enter the Ending point:");
        scanf("%s",a.Ending_Route);
        ptr1=fopen("Temp.txt","r");
        ptr=fopen("project.txt","w");
        fprintf(ptr,"%s\t\t%d\t\t%d\t  %s\t%s\n",a.name,a.Bus_No,a.total_seat,a.Starting_Route,a.Ending_Route);
        while(fscanf(ptr1,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
            fprintf(ptr,"%s\t\t%d\t\t%d\t  %s\t%s\n",name,Bus_no,total_seat,Starting_Route,Ending_Route);
        }
        printf("\nSuccessfully Updated\n");
        fclose(ptr);
        fclose(ptr1);
        if(preseat!=a.total_seat){
            FILE *ptr2,*ptr3;
            ptr2=fopen("seat.txt","r");
            ptr3=fopen("seat1.txt","w");
            int i;
            while(fread(&seat,sizeof(seat),1,ptr2)){     
                if(seat.bus_no==BUS_NO){
                    seat.bus_no=a.Bus_No;
                    seat.Tseat=a.total_seat;
                    for(i=0;i<seat.Tseat;i++){
                        seat.Seat[i]=0;
                    }
                    fwrite(&seat,sizeof(seat),1,ptr3);
                }
                else{
                    fwrite(&seat,sizeof(seat),1,ptr3);
                }
                }
            fclose(ptr2);
            fclose(ptr3);
            ptr2=fopen("seat.txt","w");
            ptr3=fopen("seat1.txt","r");
            while(fread(&seat,sizeof(seat),1,ptr3)){
            fwrite(&seat,sizeof(seat),1,ptr2);
            }
            fclose(ptr3);
            fclose(ptr2);
            ptr3=fopen("seat1.txt","w");
            fclose(ptr3);
            remove("seat1.txt");
        }
    }

    else{
        printf("\nTHIS bus number to exist in system\n");
    }
    remove("Temp.txt");
    char ch;
    printf("\nPress any key to continue:");
    ch=getche();
    Menu();

    return ;
}
/* ****************************Delete Bus Record****************************** */
void Delete_bus_record(){
    system("cls");
    FILE *ptr,*ptr1;
    ptr=fopen("project.txt","r");
    if(ptr==NULL){
        printf("\nFile cannot be open\n");
        exit(1);
    }
    int bus_no;
    printf("Enter the bus no. which you want to delete:");
    scanf("%d",&bus_no);
    int flag=0;
    char name[30],Starting_Route[30],Ending_Route[30];
    int Bus_no,total_seat;
    ptr1=fopen("Temp.txt","a");
    while(fscanf(ptr,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
        if(bus_no==Bus_no)
            flag=1;
        else{
            fprintf(ptr1,"%s\t\t%d\t\t%d\t  %s\t%s\n",name,Bus_no,total_seat,Starting_Route,Ending_Route);
        }    
    }
    fclose(ptr);
    fclose(ptr1);
    if(flag==1){
        ptr1=fopen("Temp.txt","r");
        ptr=fopen("project.txt","w");
            while(fscanf(ptr1,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
                fprintf(ptr,"%s\t\t%d\t\t%d\t  %s\t%s\n",name,Bus_no,total_seat,Starting_Route,Ending_Route);
            }
       fclose(ptr1);
       fclose(ptr);
       ptr1=fopen("Temp.txt","w");
       fclose(ptr1);
       remove("Temp.txt"); 
       /*----------------------for seat detalis-----------------------*/
        FILE *ptr2,*ptr3;
        ptr2=fopen("seat.txt","r");
        ptr3=fopen("seat1.txt","w");
        while(fread(&seat,sizeof(seat),1,ptr2)){
            if(bus_no!=seat.bus_no){
            fwrite(&seat,sizeof(seat),1,ptr3);
            }
        }
        fclose(ptr2);
        fclose(ptr3);
        ptr2=fopen("seat.txt","w");
        ptr3=fopen("seat1.txt","r");
        while(fread(&seat,sizeof(seat),1,ptr3)){
            fwrite(&seat,sizeof(seat),1,ptr2);
        }
        fclose(ptr1);
        fclose(ptr);
        ptr1=fopen("seat1.txt","w");
        fclose(ptr1);
        remove("seat1.txt");
        printf("Delete successfully\n");      
    }
    else{
        printf("\nThis bus not exist\n");
    }
    char ch;
    printf("Press any key to continue:");
    ch=getche();
    Menu();

}
/* **************************To show all bus record ****************************** */
void View_All_Bus_Details(){
	system("cls");
    FILE *ptr=NULL;
    char str;
    char name[30],Starting_Route[30],Ending_Route[30];
    int Bus_no,total_seat;
    ptr=fopen("project.txt","r");
    if(ptr==NULL){
        printf("Error not found data");
        exit(1);
    }
	printf("           *********************   Bus   Record   *************************\n");
	int serial_no=1;
    while(fscanf(ptr,"%s  %d %d %s%s",name,&Bus_no,&total_seat,Starting_Route,Ending_Route)!=EOF){
        printf("Ser_No:%d   Bus_name::%s\tBus_no.:%d\tTotalseat:%d\tStarting-point:%s\t Ending-point:%s\n\n",serial_no,name,Bus_no,total_seat,Starting_Route,Ending_Route);
    	serial_no+=1;
	}
    fclose(ptr);
    char c;
    printf("\nPress any key to continue:");
    c=getche();
    Menu();
    return;
}
void SEAT_STATUS(){
    FILE *ptr;
    ptr=fopen("seat.txt","r");
    system("cls");
    int n;
    printf("Enter bus number:");
    scanf("%d",&n);
    system("cls");
    int flag=0;
    while(fread(&seat,sizeof(seat),1,ptr)){
        if(n==seat.bus_no){
            flag=1;
            printf("Bus_number:%d\n ",seat.bus_no);
            printf("************SEAT STATUS****************\n");
            for(int i=0;i<seat.Tseat;i++){
                if(seat.Seat[i]==1)
                    printf("%2d:booked  ",i+1);
                else
                    printf("%2d:Vacant  ",i+1);   
                if((i+1)%5==0)
                    printf("\n");
            }
        break;
        }
}
fclose(ptr);
if(flag==0){
    printf("\nThis bus number not exist\n");
}
    char c;
    printf("\nPress any key to continue:");
    c=getche();  
    Menu();
    return ;

}