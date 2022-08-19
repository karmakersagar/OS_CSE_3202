#include "../include/kstdio.h"
/**
* first argument define the type of string to kprintf and kscanf, 
* %c for charater
* %s for string, 
* %d for integer
* %x hexadecimal
* %f for floating point number
* 
*/

void kprintf(uint8_t *format,uint8_t* outvar);

void swap(char *x, char *y){
	char t = *x;
	*x = *y;
	*y = t;
}

char* reverse(char *x, uint8_t start, uint8_t end){
	while(start<end){
		swap(&x[start++],&x[end--]);
	}
	return x;
}
uint32_t stringToInt(char* str){
	uint32_t  result = 0;
	uint32_t  sign = 1;
	uint32_t i = 0;
	if(str[0] == '-'){
		sign = -1;
		i++;
	}

	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        result = result * 10 + (uint32_t)(str[i] - '0');
        // UART_SendChar(USART2,(uint8_t*)str[i]);
        i++;
    }
  return result;
}
// for floating point
float stof(const char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1; 
      continue;
    };
    uint32_t d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
}
char * _float_to_char(float x, char *p) {
    char s1[200];//= p + CHAR_BUFF_SIZE; // go to end of buffer
    char *s = p + 100;
    *--s = 0;
    
    uint32_t decimals;  // variable to store the decimals
    uint32_t units;  // variable to store the units (part to left of decimal place)
    if (x < 0) { // take care of negative numbers
        decimals = (uint32_t)(x * -100) % 100; // make 1000 for 3 decimals etc.
        units = (uint32_t)(-1 * x);
    } else { // positive numbers
        decimals = (uint32_t)(x * 100) % 100;
        units = (uint32_t)x;
    }
    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    while (units > 0) {
        *--s = (units % 10) + '0';
        units /= 10;
    }
    if (x < 0) *--s = '-'; // unary minus sign for negative numbers
    return s;
}

// end of floating point 


uint32_t stringHexToDec(char* str){
	uint32_t i = 0;
	uint32_t j;
	uint32_t res = 0;
	for(;str[i]!='\0';i++){
		//kprintf((uint8_t*)"%c",(uint8_t*)str[i]);
		if(str[i]>='0' && str[i]<='9')res = res*16+ (uint32_t) str[i] - '0';
		else if(str[i]>='A' && str[i] <='F' ) res = res*16 +(uint32_t) str[i] + 10 - 'A';

	}
	//kprintf((uint8_t*)"%d",(uint8_t*)&res);
	return res;
}

void numberToString(uint32_t value, char str[200] , uint32_t base){
	uint8_t isNegative = 0;
	// invalide base 
	if(base < 2)    str[0] = '\0';

	uint8_t i = 0;

	if(value == 0){
		str[i++] = '0';
		str[i] = '\0';
		//return str;

	}

	// negative number ha=andle 
	if(value < 0){
		value = -value;
		isNegative = 1;
	}

	while(value!=0){
		uint32_t rem = value%base;

		str[i++] = (rem > 9) ? (rem - 10) + 65 : rem + 48;
		//cout << str[i] << endl;
		value = value/base;
	}

	if(isNegative==1) str[i++] = '-';
	str[i] = '\0';

     reverse(str,0, i-1);

}

void intToHex(uint32_t value,char str[200]){
	uint32_t i = 0;
	uint32_t j;
	kprintf((uint8_t*)"%d",(uint8_t*)&value);
	//char str[200];
	while(value!=0){
		uint32_t temp = value%16;
		//kprintf((uint8_t*)"%d",(uint8_t*)&temp);
		if(temp <10) temp = temp+ 48;
		else temp = temp+55;
		str[i++] = temp;
		value = value/16;

	}
	str[i] = '\0';
	//kprintf((uint8_t*)"%s",(uint8_t*)str);
	reverse(str,0,i-1);
}

void kprintf(uint8_t *format,uint8_t* outvar)
{
//write your code here
	char p = format[1];
	if(p == 'c'){
		UART_SendChar(USART2,(uint8_t*)outvar);
	}
	if(p =='s'){
		_USART_WRITE(USART2,(uint8_t*)outvar);
	}
	if(p =='d'){
		uint32_t value = *((uint32_t*) outvar);
		char str[200];

		//char* pnt = 
		numberToString(value,str, 10);
		outvar = (uint8_t*) str;

		_USART_WRITE(USART2,(uint8_t*)outvar);

	}
	if(p =='x'){

		uint32_t value = *((uint32_t*) outvar);
		char str[200];

		//char* pnt = 
		numberToString(value,str, 16);
		//intToHex(outvar,str);
		//intToHex(value,str);
		outvar = (uint8_t*) str;
		//kprintf((uint8_t*)"%s",(uint8_t*)str);

		_USART_WRITE(USART2,(uint8_t*)outvar);

	}

	if(p == 'f'){
		float value = *((float*) outvar);
		char str[200];
		char* string = _float_to_char(value,str);

		outvar = (uint8_t*) string;
		//kprintf((uint8_t*)"%s",(uint8_t*)str);

		_USART_WRITE(USART2,(uint8_t*)outvar);

	}
}
void kscanf(uint8_t *format,uint8_t* invar)
{
//write your code here

	char type = format[1];
	if(type == 'c'){
		// _USART_GetChar(USART2);
		_USART_READ(USART2,invar,1);
		//kprintf((uint8_t*)"%s",(uint8_t*)invar);

	}

	if(type == 's'){
		_USART_READ(USART2,invar,200);
	}

	if(type == 'd'){
		char ch[200];
		_USART_READ(USART2,(uint8_t*) ch,200);
		//kprintf((uint8_t*)"%s",(uint8_t*)ch);
	   *(uint32_t*) invar = stringToInt((uint8_t*)ch);
	   

	}
	if(type == 'x'){
		char ch[200];
		_USART_READ(USART2,(uint8_t*) ch,200);
		//kprintf((uint8_t*)"%s",(uint8_t*)ch);
		*(uint32_t*)invar =  stringHexToDec((uint8_t*)ch);
		//kprintf((uint8_t*)"%d",(uint32_t*)invar);
		// *(uint32_t*) invar = stringToInt((uint8_t*)ch);
		//numberToString
	   

	}
	if(type == 'f'){
		char ch[200];
		_USART_READ(USART2,(uint8_t*) ch,200);
		kprintf((uint8_t*)"%s",(uint8_t*)ch);
		 *(float*)invar = stof((uint8_t*)ch);
	}



}




