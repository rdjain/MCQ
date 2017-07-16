//Code by rishabh jain
//email :- rishabhhasanemail@gmail.com
#include "msp430g2553.h"
#include"lcdLib.h"
#include<math.h>

static unsigned short int q=1;
static unsigned short int marks=0;
static unsigned short int answ=0;
static unsigned short int r=0;
static unsigned short int w=0;
int data_q(int);
//void data_a();
//void marks(int,int);
//volatile int quest;



/*
 * main.c
 */
void main(void) {
  WDTCTL = WDTPW | WDTHOLD;
    lcdInit();
    lcdClear();
    P1DIR=0x00;

    P1IE|=BIT1+BIT2+BIT4+BIT3+BIT7;
    P1IES|=BIT1+BIT2+BIT4+BIT3+BIT7;//hi to low
    P1REN|=0xff;//pulls up to vcc
    P1IFG=0X00;


  while(1){
          P1IE|=BIT1+BIT2+BIT4+BIT3+BIT7;
          P1IES|=BIT1+BIT2+BIT4+BIT3+BIT7;//hi to low
     if (q>5) {
      lcdClear();
      lcdSetText("You Scored", 0, 0);
      lcdSetInt(marks, 11, 0);
      lcdSetText("Have a nice day", 0, 1);
      delay_ms(3000);
      lcdClear();
      lcdSetText("By Rishabh,", 0, 0);
      lcdSetText("Sambhav,Vijetha", 0, 1);
      break;
  }
     else if(q<5){
           //delay_ms(1000);
             P1IFG=0x00;
             answ=data_q(q);
           __enable_interrupt();
           //lcdSetInt(q, 11, 1);
           _BIS_SR(LPM4 + GIE);
           // enable all interrupts
         }
}
 _BIS_SR(LPM4 + GIE);


}
    #pragma vector = PORT1_VECTOR
   __interrupt void Port_1(void)
   {
       switch(P1IFG)
       {
           P1IE=0x00;
           case 0x02:
                   if (q==1 |q==5){
                      lcdClear();
                      lcdSetText("Correct Ans :)", 0, 0);
                      marks+=5;
                      q++;
                      r++;
                      delay_ms(2000);
                      answ=data_q(q);
                      P1IFG=0x00;
                      break;
                    }
                    else if ((q==2|q==3|q==4)) {
                      lcdClear();
                      lcdSetText("Wrong ans :( ", 0, 0);
                      lcdSetText("Answer-Opt ", 0, 1);
                      lcdSetInt(answ, 11, 1);
                      marks-=2;
                      q++;w++;delay_ms(2000);
                      answ=data_q(q);
                      P1IFG=0x00;
                      break; //similarly for other questions and bits
                    }


       case 0x04:       if (q==2){
                          lcdClear();
                          lcdSetText("Correct Ans :)", 0, 0);
                          marks+=5;
                          q++;
                          r++;
                          delay_ms(2000);
                          answ=data_q(q);
                          P1IFG=0x00;
                          break;
         }


                           if((q==1 |q==3| q==4| q==5))
                       {
                                 lcdClear();
                                 lcdSetText("Wrong ans :(", 0, 0);
                                 lcdSetText("Answer-Opt ", 0, 1);
                                 lcdSetInt(answ, 11, 1);
                                 marks -= 2;
                                 q ++;
                                 w++;
                                 delay_ms(2000);
                                 answ=data_q(q);
                                 P1IFG = 0x00;
                                 break; //similarly for other questions and bits;
                    }
                    

       case 0x08:
                       if(q==3 |q==4){
                      lcdClear();
                      lcdSetText("Correct Ans :)", 0, 0);
                      marks+=5;
                      q++;
                      r++;
                      delay_ms(2000);
                      answ=data_q(q);
                      P1IFG=0x00;
                      break;
                    }
                    else if((q==1|q==2|q==5)){
                      lcdClear();
                      lcdSetText("Wrong ans :(", 0, 0);
                      lcdSetText("Answer-Opt ", 0, 1);
                      lcdSetInt(answ, 11, 1);
                      marks -= 2;
                      q ++;
                      w++;
                      delay_ms(2000);
                      answ=data_q(q);
                      P1IFG = 0x00;
                      break; //similarly for other questions and bits
                    }  



       case 0x10:
           if((q==1 |q==2| q==3| q==4| q==5))
                                  {
                                            lcdClear();
                                            lcdSetText("Wrong ans :(", 0, 0);
                                            lcdSetText("Answer-Opt ", 0, 1);
                                            lcdSetInt(answ, 11, 1);
                                            marks -= 2;
                                            q ++;
                                            w++;
                                            delay_ms(2000);
                                            answ=data_q(q);
                                            P1IFG = 0x00;
                                            break; //similarly for other questions and bits;
                               }

                    
       default:      if(q==6){
           lcdClear();
                 lcdSetText("Summary", 0, 0);
                 lcdSetText("Right-", 0, 1);
                 lcdSetInt(r, 6, 1);
                 lcdSetText("Wrong-", 8, 1);
                 lcdSetInt(w, 14, 1);
                 delay_ms(2500);
                 lcdClear();
                 lcdSetText("You Scored", 0, 0);
                 lcdSetInt(marks, 11, 0);
                 lcdSetText("Have a nice day", 0, 1);
                 delay_ms(2500);
                 lcdClear();
                 lcdSetText("By Rishabh,", 0, 0);
                 lcdSetText("Sambhav,Vijetha", 0, 1);
                 delay_ms(2500);
                 lcdClear();
                 lcdSetText("Enter Password", 0, 0);
                 lcdSetText("to RESET", 0, 1);

                 //if(P1IFG==0x01){WDTCTL = 0x0A + WDTHOLD;}
                 delay_ms(3500);
                 P1IFG=0x00;
                 lcdClear();
                 lcdSetText("This Feature", 0, 0);
                 lcdSetText("Coming Soon ;)", 0, 1);
                 break;
       }

       }

   }


 int data_q( int q)
 {
     int ans=0;
     if(q==1)
     {
         lcdClear();
        lcdSetText("1st Alphabet is?", 0, 0);
        lcdSetText("a.A b.B c.C d.D", 0, 1);
        ans=1;

     }
     if(q==2)
          {
              lcdClear();
             lcdSetText("First Number is?", 0, 0);
             lcdSetText("a.1 b.0 c.2 d.3", 0, 1);
             ans=1;

          }
     if(q==3)
               {
                   lcdClear();
                  lcdSetText("EIE dept floor?", 0, 0);
                  lcdSetText("a.1 b.3 c.5 d.4", 0, 1);
                  ans=3;

               }
     if(q==4)
               {
                   lcdClear();
                  lcdSetText("No of Planets?", 0, 0);
                  lcdSetText("a.3 b.0 c.8 d.9", 0, 1);
                  ans=3;

               }
     if(q==5)
                  {
                      lcdClear();
                     lcdSetText("Smallest Odd No?", 0, 0);
                     lcdSetText("a.1 b.4 c.6 d.-2", 0, 1);
                     ans=1;
                  }
      return ans;

     }

 /*void marks(int q, int flag)
 {
     if(q==1)
     {
           if(flag==1)
           {

               lcdClear();
             lcdSetText("Correct :)", 0, 0);
             quest=q;

             quest++;


           }
           else
           {

                 lcdClear();
               lcdSetText("Wrong :(", 0, 0);
               quest=q;

               quest++;

           }
     }

 }*/
