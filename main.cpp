#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
int sysarm = 0;
int siren = 0;

// function for arming sequence

int armed ( int armpb, int frontdoor,  int backdoor, int numcount)
{
    numcount++;
    if (numcount > 29 && frontdoor == 1) {
        ::siren = 1; // siren going off if front door is opened after 30 secs
    }
    if (backdoor == 1 ){
        ::siren = 1; // siren going off if rare door is opened after 30 secs
    }

    if (numcount > 29){
        ::sysarm = 1; // arming the system after 30 secs
        numcount = 0;
   } else{
        ::sysarm = 0;
   }
    return numcount;
}

// function for disarming sequence
int disarm ( int armpb, int frontdoor,  int backdoor, int uncount)
{
    --uncount;
    if (uncount < 1) {
        ::siren = 1; // siren going off after disarming fails
    }
    if (backdoor == 1 ){
        ::siren = 1; // siren going off when we open rare door
    }
    if (uncount < 1){
        uncount = 30;
    }
    return uncount;
}

int main()
{
    // initializing variables
    int armpb = 0;
    int disarmpb = 1;
    int numcount = 0; // on timer
    int frontdoor = 0;
    int backdoor = 0;
    int uncount = 30; // off timer
    int flag = 0;
    int armpush = 0; // momentary arm push button
    int disarmpush = 0; // momentary disarm push button

while (true){
    clock_t start = clock(); // system clock

    // output display to user
    if (siren == 0){
            cout << "Current system status: \n";
        if (sysarm == 1)
            cout << "System is armed \n";
        else
            cout << "System is disarmed \n";
        system("Color F");
        cout << "Front door is ";
        if (frontdoor == 1){ cout << "opened";}else {cout <<"closed";} cout << "\n";
        cout << "Back door is ";
        if (backdoor == 1){ cout << "opened";}else {cout <<"closed";} cout << "\n \n";

        if (uncount < 30)
            cout <<"Siren will go off in "<< uncount << "secs\n";
        if (numcount > 0)
            cout <<"System will be armed in "<< 30 - numcount << "secs\n";

    } else {
        system("Color 4");
        cout << "Siren went off\n";
    }

    cout << "\n Press any keyboard button to change input variables";
    // pausing iteration for a sec each time
    while (true) {
        if (((clock () - start)/ CLOCKS_PER_SEC ) > 1)
        {
            start = clock();
            break;
        }
        // taking inputs from user if he hits keyboard
        if (kbhit()){
            cout << "\n To press arm button type 1 or else type 0:";
            cin >>  armpush;
            if (armpush ==1){ armpb = 1; disarmpb = 0; armpush = 0;}
            cout << "\n To press disarm button type 1 or else type 0:";
            cin >>  disarmpush;
            if (disarmpush ==1){ armpb = 0; disarmpb = 1; disarmpush = 0;}
            cout << "\n To open front door type 1 or else type 0:";
            cin >>  frontdoor;
            cout << "\n To open rear door type 1 or else type 0:";
            cin >>  backdoor;
            }
    }

    // process
    if (disarmpb == 0){
        if (armpb == 1 && sysarm == 0){
            numcount = armed (armpb, frontdoor, backdoor, numcount); // calling function for arming the system
        }
        if (sysarm == 1 && (frontdoor == 1 || flag == 1)){
            uncount = disarm (armpb, frontdoor, backdoor, uncount); // calling function for disarming the system
            flag = 1;
            if (uncount < 1){
                flag = 0;
            }
        }
    }else{
        ::sysarm = 0;
        ::siren = 0; // when system is disarmed setting siren to zero
        numcount = 0;
        uncount = 30;
        flag = 0;
    }

    if (sysarm == 1 && numcount == 0 && uncount == 30){
        if (frontdoor == 1 || backdoor == 1){
            siren = 1; // setting siren off when frontdoor and reardoor is opened when system is armed
        }
    }


    system("cls");
    }
}
