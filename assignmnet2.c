// code to run traffic signal
// SWE 660 - Fall 2023
// Programming RTES - 1 Group 6
//Venkata Sriharsha Perla, Reethika Muvva, Vaishnavi Kurelli,  Amulya Jaladi , Bharat Sai Likhit Gatti ,Sai Kumar Reddy Ambati

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
//#include <sys/utsname.h>

//struct utsname sysInfo;
#define GPIO_PATH "/sys/class/gpio"
#define redPin1 "gpio66"                                 //variable redPin1 for red light of the signal 1
#define yellowPin1 "gpio69"                                 //variable yellowPin1 for red light of the signal 1
#define greenPin1 "gpio45"                                 //variable greenPin1 for red light of the signal 1
#define redPin2 "gpio67"                                 //variable redPin2 for red light of the signal 2
#define yellowPin2 "gpio44"                                 //variable yellowPin2 for red light of the signal 2
#define greenPin2 "gpio68"                                 //variable greenPin2 for red light of the signal 2


#define RED1dir "/sys/class/gpio/gpio66/direction" //signal1 red light
#define RED1val "/sys/class/gpio/gpio66/value"
#define YELLOW1dir "/sys/class/gpio/gpio69/direction" //signal 1 yellow light
#define YELLOW1val "/sys/class/gpio/gpio69/value"
#define GREEN1dir "/sys/class/gpio/gpio45/direction" //signal 1  green light
#define GREEN1val "/sys/class/gpio/gpio45/value"
#define RED2dir "/sys/class/gpio/gpio67/direction" //signal 2 red light
#define RED2val "/sys/class/gpio/gpio67/value"
#define YELLOW2dir "/sys/class/gpio/gpio44/direction" //signal 2 yellow light
#define YELLOW2val "/sys/class/gpio/gpio44/value"
#define GREEN2dir "/sys/class/gpio/gpio68/direction" //signal 2 green light

#define ON 1
#define OFF 0

//struct  utsname sysInfo;

#define DELAY1 120000000 //2 min delay in microseconds
#define DELAY2 5000000 //5 sec delay in microseconds

int initialize_gpios(){
     int f=0;

     f=open(RED1dir, O_RDWR);
     if (f < 0){
        perror("Error opening Red1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(YELLOW1dir, O_RDWR);
     if (f < 0){
        perror("Error opening Yellow1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(GREEN1dir, O_RDWR);
     if (f < 0){
        perror("Error opening Green1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(RED2dir, O_RDWR);
     if (f < 0){
        perror("Error opening Red2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(YELLOW2dir, O_RDWR);
     if (f < 0){
        perror("Error opening Yellow2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(GREEN2dir, O_RDWR);
     if (f < 0){
        perror("Error opening Green2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);
     return 0;
}

int writeGPIO(char* light, int value){

     int f=0;

     f=open(light,O_WRONLY);

     value == ON ? write(f,"1",1) : write(f,"0",1);

    close(f);

}


int main (void)

{

     //uname(&sysInfo);
    //printf("Machine : %s \n",sysInfo.machine);

    /*if (initialize_gpios() == -1){
       printf("Error with GPIO initialization \n");
       return -1;
    }*/
while(1){
       //writeGPIO(RED1val,OFF);
       //writeGPIO(GREEN1val,ON);
       //writeGPIO(RED2val,ON);
        printf("\nSignal 1 : G ON  Y OFF R OFF\nSignal 2 : G OFF Y OFF R ON  \n");
        printf("\nWaitTime : 2mins\n");
        usleep(DELAY1);
       //writeGPIO(GREEN1val,OFF);
       //writeGPIO(YELLOW1val,ON);
        printf("\nSignal 1 : G OFF Y ON  R OFF\nSignal 2 : G OFF Y OFF R ON  \n");
        printf("\nWaitTime : 5sec\n");
        usleep(DELAY2);
       //writeGPIO(RED2val,OFF);
       //writeGPIO(YELLOW1val,OFF);
       //writeGPIO(RED1val,ON);
       //writeGPIO(GREEN2val,ON);
        printf("\nSignal 1 : G OFF Y OFF R ON \nSignal 2 : G ON  Y OFF R OFF \n");
        printf("\nWaitTime : 2mins\n");
        usleep(DELAY1);
       //writeGPIO(GREEN2val,OFF);
       //writeGPIO(YELLOW2val,ON);
        printf("\nSignal 1 : G OFF Y OFF R ON \nSignal 2 : G OFF Y ON  R OFF \n");
        printf("\nWaitTime : 5sec\n");
         usleep(DELAY2);
       //writeGPIO(YELLOW2val,OFF);
   }

   return 0;
}
