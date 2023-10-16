
// Code to run traffic signal multithread
// SWE 660 - Fall 2023
// Programming Multitasking  Group 6
//Venkata Sriharsha Perla, Reethika Muvva, Vaishnavi Kurelli,  Amulya Jaladi , Bharat Sai Likhit Gatti    Sai Kumar Reddy Ambati

//Importing Required libraries
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <pthread.h>

// Define GPIO file paths using the configured pins
#define RED1_DIR "/sys/class/gpio/gpio67/direction"
#define RED1_VAL "/sys/class/gpio/gpio67/value"
#define YELLOW1_DIR "/sys/class/gpio/gpio68/direction"
#define YELLOW1_VAL "/sys/class/gpio/gpio68/value"
#define GREEN1_DIR "/sys/class/gpio/gpio44/direction"
#define GREEN1_VAL "/sys/class/gpio/gpio44/value"
#define RED2_DIR "/sys/class/gpio/gpio66/direction"
#define RED2_VAL "/sys/class/gpio/gpio66/value"
#define YELLOW2_DIR "/sys/class/gpio/gpio69/direction"
#define YELLOW2_VAL "/sys/class/gpio/gpio69/value"
#define GREEN2_DIR "/sys/class/gpio/gpio45/direction"
#define GREEN2_VAL "/sys/class/gpio/gpio45/value"
#define BUTTON1_DIR "/sys/class/gpio/gpio47/direction"
#define BUTTON1_VAL "/sys/class/gpio/gpio47/value"
#define BUTTON2_DIR "/sys/class/gpio/gpio27/direction"
#define BUTTON2_VAL "/sys/class/gpio/gpio27/value"

#define ON 1
#define OFF 0

struct utsname sysInfo;


// Mutexes for synchronizing access to shared data
pthread_mutex_t waitTimerMutex = PTHREAD_MUTEX_INITIALIZER;

// Global variables to store timer , button states, traffic direction and print statements

int waitTimer = 0;
int buttonState1 = OFF;
int buttonState2 = OFF;
int trafficDirection = 1;
int bt1 = 0;
int bt2 = 0;
int TfGreen1=0;
int TfGreen2=0;
int green1printflag=0;
int yellow1printflag=0;
int red1printflag=0;
int green2printflag=0;
int yellow2printflag=0;
int red2printflag=0;

// Function to initialize GPIO pins
int initialize_gpios() {
    int f=0;

     f=open(RED1_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Red1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(YELLOW1_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Yellow1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(GREEN1_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Green1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(RED2_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Red2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(YELLOW2_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Yellow2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);

     f=open(GREEN2_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Green2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);
     return 0;

     f=open(BUTTON1_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Button1 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);
     return 0;

     f=open(BUTTON2_DIR, O_RDWR);
     if (f < 0){
        perror("Error opening Button2 Direction");
        return -1;
     }

     write(f,"out",3);
     close(f);
     return 0;
}

// Function to write a value to a GPIO pin
int writeGPIO(char* light, int value) {
    int f=0;
    f=open(light,O_WRONLY);
    value == ON ? write(f,"1",1) : write(f,"0",1);
    close(f);
}

//Function track timer and set traffic direction
void timerTrafficSignal(){

   waitTimer++;
   sleep(1);
   if(waitTimer > 240+10){
    waitTimer = 0;
    if(trafficDirection == 1){
        trafficDirection = 2;
    }else{
        trafficDirection = 1;
        green1printflag=0;
        yellow1printflag=0;
        red1printflag=0;
        green2printflag=0;
        yellow2printflag=0;
        red2printflag=0;
    }
   }
}

//Function read the button pressed event
int pressed(const char* GPIOval) {
    char strVal[50];

    FILE* fp = fopen(GPIOval, "r");
    if (fp == NULL) {
        perror("Error opening GPIO value file");
        return -1;
    }

    fscanf(fp, "%s", strVal);
    int buttonState = atoi(strVal);

    fclose(fp);

    return buttonState;
}

// Function for the traffic signal 1 thread
void* trafficSignal1(void* arg) {
    while (1) {
        //sleep(1);
       timerTrafficSignal();

       if(waitTimer<=240 && trafficDirection == 1){

            writeGPIO(YELLOW1_VAL,OFF);
            writeGPIO(RED1_VAL, OFF);
            writeGPIO(GREEN1_VAL, ON);

            TfGreen1=ON;
            if(green1printflag==0){
                printf("\nSignal 1 : G ON  Y OFF R OFF\n");
                printf("\nWaitTime signal1 : 2mins\n");
                green1printflag=1;
            }
        }

        if(waitTimer > 240 && waitTimer < 240+10 && trafficDirection == 1){

            writeGPIO(GREEN1_VAL,OFF);
            writeGPIO(YELLOW1_VAL,ON);
            writeGPIO(RED1_VAL, OFF);
            TfGreen1=OFF;
            if(yellow1printflag==0){
                printf("\nSignal 1 : G OFF  Y ON R OFF\n");
                printf("\nWaitTime signal1 : 5secs\n");
                yellow1printflag=1;
            }
        }

        if(waitTimer <=240 && trafficDirection == 2){
            writeGPIO(GREEN1_VAL,OFF);
            writeGPIO(RED1_VAL,ON);
            writeGPIO(YELLOW1_VAL,OFF);
            TfGreen1=OFF;
            if(red1printflag==0){
                printf("\nSignal 1 : G OFF  Y OFF R ON\n");
                printf("\nWaitTime signal1 : 2mins5secs\n");
                red1printflag=1;
            }

        }
    }
    return NULL;
}

// Function for the traffic signal 2 thread (similar to trafficSignal1)
void* trafficSignal2(void* arg) {
    while (1) {

        timerTrafficSignal();

        if(waitTimer <=240 && trafficDirection == 1){
            writeGPIO(GREEN2_VAL,OFF);
            writeGPIO(YELLOW2_VAL,OFF);
            writeGPIO(RED2_VAL,ON);

            TfGreen2=OFF;
            if(red2printflag==0){
                printf("\nSignal 2 : G OFF  Y OFF R ON\n");
                printf("\nWaitTime signal2 : 2mins5secs\n");
                red2printflag=1;
            }

        }

        if(waitTimer > 240 && waitTimer < 240+10 && trafficDirection == 2){
            writeGPIO(RED2_VAL,OFF);
            writeGPIO(YELLOW2_VAL,ON);
            writeGPIO(GREEN2_VAL,OFF);
            TfGreen2=OFF;
            if(yellow2printflag==0){
                printf("\nSignal 2 : G OFF  Y ON R OFF\n");
                printf("\nWaitTime signal2 : 5secs\n");
                yellow2printflag=1;

            }

        }

        if(waitTimer <= 240 && trafficDirection == 2){
            writeGPIO(RED2_VAL,OFF);
            writeGPIO(GREEN2_VAL, ON);
            writeGPIO(YELLOW2_VAL, OFF);
            TfGreen2=ON;
            if(green2printflag==0){
                printf("\nSignal 2 : G ON  Y OFF R OFF\n");
                printf("\nWaitTime signal2 : 2mins\n");
                green2printflag=1;
            }

        }
    }
    return NULL;
}

//Function to change the direction
void swapDirection(){
    waitTimer = 0;
    bt1=0;
    bt2=0;
    if(trafficDirection == 1){
        trafficDirection = 2;

        green1printflag=0;
        yellow1printflag=0;
        red1printflag=0;
        green2printflag=0;
        yellow2printflag=0;
        red2printflag=0;
    }else{
        trafficDirection = 1;

        green1printflag=0;
        yellow1printflag=0;
        red1printflag=0;
        green2printflag=0;
        yellow2printflag=0;
        red2printflag=0;
    }
}

// Function for the button 1 thread
void* button1(void* arg) {
    while (1) {

        int buttonState = pressed(BUTTON1_VAL);

        if (buttonState != -1) {
                pthread_mutex_lock(&waitTimerMutex);
                buttonState1 = buttonState;
                pthread_mutex_unlock(&waitTimerMutex);

                if (buttonState1 == ON) {
                    sleep(1);
                    bt1++;
                }
                else{
                    bt1 = 0;
                }
                pthread_mutex_lock(&waitTimerMutex);
                if(buttonState1 == ON && bt1>5 && TfGreen2==ON){
                        swapDirection();
                        printf("\nButton 1 Triggred\n");
                    }
                pthread_mutex_unlock(&waitTimerMutex);
            }
    }
    return NULL;
}

// Function for the button 2 thread
void* button2(void* arg) {
    while (1) {

            int buttonState = pressed(BUTTON2_VAL);

            if (buttonState != -1) {
                pthread_mutex_lock(&waitTimerMutex);
                buttonState2 = buttonState;
                pthread_mutex_unlock(&waitTimerMutex);

                if (buttonState2 == ON) {
                    sleep(1);
                    bt2++;
                }
                else{
                    bt2 = 0;
                }
                pthread_mutex_lock(&waitTimerMutex);
                if(buttonState2 == ON && bt2>5 && TfGreen1==ON){
                        swapDirection();
                        printf("\nButton 2 Triggred\n");
                    }
                pthread_mutex_unlock(&waitTimerMutex);
                }
        }
        return NULL;
}

int main(void) {
    // Printing Machine name
    uname(&sysInfo);
    printf("Machine : %s \n", sysInfo.machine);

    // Initialize GPIO pins
    if (initialize_gpios() == -1) {
        printf("Error with GPIO initialization \n");
        return -1;
    }

    // Create threads for traffic signals and buttons
    pthread_t signalThread1, signalThread2, buttonThread1, buttonThread2;

    pthread_create(&signalThread1, NULL, trafficSignal1, NULL);
    pthread_create(&signalThread2, NULL, trafficSignal2, NULL);
    pthread_create(&buttonThread1, NULL, button1, NULL);
    pthread_create(&buttonThread2, NULL, button2, NULL);

    // Wait for threads to finish
    pthread_join(signalThread1, NULL);
    pthread_join(signalThread2, NULL);
    pthread_join(buttonThread1, NULL);
    pthread_join(buttonThread2, NULL);

    return 0;
}
