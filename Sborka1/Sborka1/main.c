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

	//����
	/*
	�������������
	�������� �������
	����������
	���������
	��������� �������
	����������� � EEPROM
	*/
	
	//����� ����������////////////////////////////////////////////
	int MKID = 1;
	int AllMKID = 0;
	int MyADCOut;
	
	//������
	int Alfa1 = 0.25;
	int Beta1 = 0.75;
	int Alfa2 = 0.0625;
	int Beta2 = 0.9375;
	int FilterA;
	int FilterB;
	int margin; //Todo ������� ��������� �8
	
	
	void Init()
	{
		//��������� ����������
		
		//ADC
		//���� � ��� 3 �� ����
		DDRA &= (0<<PINA0);
		//����������� ���
		ADMUX=
		(0<<MUX0)|
		(0<<MUX1)|
		(0<<MUX2)|
		(0<<MUX3)|
		(0<<MUX4)|
		(0<<MUX5)| //�������� ��� 13 ��� ����� ����� �������������
		(0<<REFS0)|
		(1<<REFS1)| //�������� ��������� ��� 1,1�
		(0<<ADLAR); //������������ ������
		ADCSRA|=
		(1<<ADEN)| //��������� ������ ���
		(0<<ADPS2)|
		(1<<ADPS1)|
		(0<<ADPS0); //������������� ���������� �� 4
		
		ADCSRA|=(1<<ADSC);// ������ ���
		
		//NOTE ADCH - �������� ���
	}
	
	void Filter()
	{
		//������
		FilterA = ADCH*Alfa1+FilterA*Beta1;	//������ ��������
		FilterB = FilterA*Alfa2+FilterB*Beta2;	//�������� ��������
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
	//����������
	{
		_Bool StartBit = Filter();
		
	}
	
	void PWMControl(int Scavash)
	{
		//��������� �������
		OCR0A=Scavash;//TODO ���� ��������� ��������
		
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

