/*
 * Sborka1.c
 *
 * Created: 23.09.2021 11:29:39
 * Author : Leo
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define F_CPU 1000000 UL;

	//план
	/*
	Инициализация
	принятие сигнала
	фильтровка
	обработка
	настройка яркости
	запоминание в EEPROM
	*/
	
	//Общие переменные////////////////////////////////////////////
	int MKID = 1;
	int AllMKID = 0;
	int MyADCOut;
	
	//Фильтр
	int Alfa1 = 0.25;
	int Beta1 = 0.75;
	int Alfa2 = 0.0625;
	int Beta2 = 0.9375;
	int FilterA;
	int FilterB;
	int margin; //Todo Настрой пороговое з8
	
	
	void Init()
	{
		//установка параметров
		
		//ADC
		//Порт А пин 3 на вход
		DDRA &= (0<<PINA0);
		//Настраиваем АЦП
		ADMUX=
		(0<<MUX0)|
		(0<<MUX1)|
		(0<<MUX2)|
		(0<<MUX3)|
		(0<<MUX4)|
		(0<<MUX5)| //выбираем пин 13 для ввода через мультиплексер
		(0<<REFS0)|
		(1<<REFS1)| //вибираем внутрений ИОН 1,1В
		(0<<ADLAR); //выравнивание справо
		ADCSRA|=
		(1<<ADEN)| //разрешаем работу АЦП
		(0<<ADPS2)|
		(1<<ADPS1)|
		(0<<ADPS0); //Устанавливаем прескейлер на 4
		
		ADCSRA|=(1<<ADSC);// Запуск АЦП
		
		//NOTE ADCH - значение АЦП
	}
	
	void Filter()
	{
		//фильтр
		FilterA = ADCH*Alfa1+FilterA*Beta1;	//быстро меняется
		FilterB = FilterA*Alfa2+FilterB*Beta2;	//медленно меняется
		if ((FilterB-FilterA)>margin)
		{
			FilterResultat = 1;
		}
		else
		{
			FilterResultat = 0;
		}
	}
	
	void Handler()
	//обработчик
	{
		_Bool StartBit = Filter();
		
	}
	
	void PWMControl(int Scavash)
	{
		//Настройка яркости
		OCR0A=Scavash;//TODO Сюда вставлять значения
		
	}
	
	void FlashSave(int Date, int Locat)
	{
		//EEPROM
		OCR0A=ADCH;
		eeprom_update_byte(Locat, Date);
	}

int main(void)
{
	Init();
    while (1) 
    {
		
    }
	
}

