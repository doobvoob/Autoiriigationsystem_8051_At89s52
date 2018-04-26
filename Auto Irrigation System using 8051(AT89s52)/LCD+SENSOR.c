# include <at89x51.h>
# define LCDPort P2
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
sbit sensor=P3^2;
sbit relay = P2^0;

void delay(int t)
     {
	        int i;
		while(t>0)
		  {
		    i=1275;
			while(i>0) i--;
			t--;
		  }
	 }
  void LCDCommand(unsigned char Value)
     {
	        RS=0;
		RW=0;
		LCDPort=Value;
		EN=1;
		delay(2);
		EN=0;
		return;
	}

 void LCDData(unsigned char Value)
     {
	        RS=1;
		RW=0;
		LCDPort=Value;
		EN=1;
		delay(2);
		EN=0;
		return;
	}
 void LCDInit()
    {
	  LCDCommand(0x38);
	  LCDCommand(0x06);
	  LCDCommand(0x0c);
	  LCDCommand(0x01);
	}
 LCDPuts(char *s)
    {
	   int i;
	   for(i=0;s[i];i++) LCDData(s[i]);
	}

void LCD_goto_XY(int x , int y)
{
	if(y == 1)
		LCDCommand(0x80 | x);
	else if(y == 2)
		LCDCommand(0xC0 | x);
	
}

void GPIO_INIT()
{
	sensor = 0xFF;
	sensor = 0;
	relay = 0x00;
}
void displayStatus(unsigned char status)
{
	LCDCommand(0x01);
	LCD_goto_XY(4,1);
	LCDPuts("Status");	
	LCD_goto_XY(0,2);
	LCDPuts(status);
}

 void main()
    {
	GPIO_INIT();
	LCDInit();
	LCDCommand(0x01);
	LCD_goto_XY(2,1);
	LCDPuts("Automatic");
	LCD_goto_XY(0,2);
	LCDPuts("Irrigation Sys.");
	delay(1000);
	while(1)
	{
		delay(100);
		if(sensor == 1)
		{
		LCDCommand(0xc0);
		displayStatus("Less Humidity");
		relay = 1;
		}
		else if(sensor == 0)
		{
		LCDCommand(0xc0);
		displayStatus("Enough Humidity");
		relay = 0;
		}
		delay(100);
	    }
    }
