

/*-----------------
PIN     USE
-------------------
PB6     USART1_TX
PB7     USART1_RX
-------------------*/

/* IMPORTANT
 * Create project for using Keil for ARM (C:\Keil_v5\ARM)
*/

#include <stm32f10x.h>
#include <stdio.h> 
#include <stdlib.h>

// Function prototypes
void usartSetup (void);
void sendChar (char ch);
char getChar (void);
void sendString (char *ptr);
void getString (char *ptr);
void clearString (char *ptr);
void delaybyms (uint32_t j);

// Global variables 
char characterRx;
char message[100]= "Bonjour les enfants!";
float n;

int main(void) {
  usartSetup();
  while(1) {
    n = (float) rand()/(float) RAND_MAX*100.0;
    sprintf(message, "Temperature = %2.2f degrees\r\n",n);
    sendString(message);
    delaybyms(100);
  }
}

void usartSetup (void) {

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  // Put PB6 (TX) to alternate function output push-pull at 50 MHz
  // Put PB7 (RX) to floating input
  GPIOB->CRL = (GPIOB->CRL & 0x00FFFFFF) | 0x4B000000;

  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;            // enable AFIO  
  AFIO->MAPR   |= AFIO_MAPR_USART1_REMAP;        // 1: Remap (TX/PB6, RX/PB7)
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;          // enable clock for USART1
  USART1->BRR   = 0x1D4C;                        // set baudrate (9600)
  USART1->CR1  |= (USART_CR1_RE | USART_CR1_TE); // RX, TX enable
  USART1->CR1  |= USART_CR1_UE;                  // USART enable
}

void sendChar (char ch) {
  USART1->DR = ch;
  while (!(USART1->SR & USART_SR_TXE));
}

char getChar (void) {
  while (!(USART1->SR & USART_SR_RXNE));
  return USART1->DR;
}

void sendString(char *ptr) {
  while (*ptr !=0) {
    sendChar(*ptr++);
  } 
}

void getString (char *ptr) {
  do  {
    *ptr = getChar();
  } while (*ptr++ != 0); 
}

void clearString(char *ptr) {
  char i;
  for (i=0;i<50;i++)
    *ptr++ = 0;
}

void delaybyms(uint32_t j) {
  uint32_t k;
  while(j--)
    for(k=4800;k!=0;k--); 
}

  
