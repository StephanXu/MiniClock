#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "24cxx.h" 
#include "myiic.h"
#include "touch.h" 
#include "rtc.h"

/*
_calendar_obj calendar;

u8 Hour;
u8 Minute;
u8 Sec;
u8 Day;
u32 totalM;
u8 LastMin;
u8 bRefresh;
u8 Per;
u8 PersentageFlag;

u8 TimeStr[0xf];
u8 DateStr[0xf];
u8 Min[0x3];
u8 Hou[0x3];
u8 SecS[0x3];
u8 PerS[0x3];

u32 TimeList []=
{
	0,
	360*60,//6
	380*60,//6.20
	400*60,//6.40
	435*60,//7.15
	475*60,//7.55
	480*60,//8
	525*60,//8.45
	535*60,//8.55
	580*60,//9.40
	605*60,//10.05
	650*60,//10.50
	660*60,//11.00
	705*60,//11.45
	750*60,//12.30
	830*60,//13.50
	850*60,//14.10
	895*60,//14.55
	905*60,//15.05
	950*60,//15.50
	960*60,//16
	1005*60,//16.45
	1015*60,//16.55
	1060*60,//17.40
	1125*60,//18.45
	1220*60,//20.20
	1235*60,//20.35
	1325*60,//22.05
	1440*60//24
};

void DrawWedgeCircle(u8 x0,u8 y0,u8 r,u8 wedge)
{
	u8 i;
	if (wedge>r)
		return;
	for (i=0;i<wedge;i++)
	{
		LCD_Draw_Circle(x0,y0,r-i);
	}
	return;
}

void Clock(void)
{
	u8 i;
	u32 NearestTime;
	u32 NearestTime2;
	u16 bColorTemp;
	Hour=calendar.hour;
	Minute=calendar.min;
	Sec=calendar.sec;
	Day=0;
	Per=0;
	LastMin=0;
	bRefresh=1;
	PersentageFlag=1;
	while(1)
	{
		if (bRefresh)
		{
			LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
			LCD_ShowString(lcddev.width/2-(20*16/2)/2,70,200,16,16,"Stephan's Tiny Clock");
			LCD_ShowString(lcddev.width/2-(4*16/2)/2,150,200,16,16,"20:00");
			LCD_ShowString(lcddev.width/2-(8*16/2)/2,250,200,16,16,"Settings");
			
			bColorTemp=POINT_COLOR;
			POINT_COLOR=LIGHTBLUE;
			Per=((NearestTime-totalM)*100/(NearestTime-NearestTime2))/100;
			DrawWedgeCircle(lcddev.width/2,172,50,2);
			POINT_COLOR=bColorTemp;
		}
			Hour=calendar.hour;
			Minute=calendar.min;
			Sec=calendar.sec;
		 if (Minute<10)
		 {
				sprintf((char*)Min,"0%d",Minute);
		 }
		 else
		 {
			 sprintf((char*)Min,"%d",Minute);
		 }
		 if (Hour<10)
		 {
				sprintf((char*)Hou,"0%d",Hour);
		 }
		 else
		 {
			 sprintf((char*)Hou,"%d",Hour);
		 }
		 if (Sec<10)
		 {
				sprintf((char*)SecS,"0%d",Sec);
		 }
		 else
		 {
			 sprintf((char*)SecS,"%d",Sec);
		 }
		 totalM=Hour*3600+Minute*60+Sec;
		 if (Minute!=LastMin||bRefresh)
		 {
			 for (i=0;i<29;i++)
		 {
			 if (TimeList[i]>totalM)
			 {
				 NearestTime=TimeList[i];
				 NearestTime2=TimeList[i-1];
				 break;
			 }
		 }
			 if (PersentageFlag)
			 {
				sprintf((char*)PerS,"%d%%",(totalM-NearestTime2)*100/(NearestTime-NearestTime2));
			 }
			 else
			 {
				 sprintf((char*)PerS,"%dm",(NearestTime-totalM)/60);
			 }
			 LCD_ShowString(lcddev.width/2-(3*16/2)/2,190,200,16,16,PerS);
			 sprintf((char*)TimeStr,"%s:%s:%s",Hou,Min,SecS);
			 LCD_ShowString(lcddev.width/2-(8*16/2)/2,150,200,16,16,TimeStr);
			 if (Day!=calendar.w_date||bRefresh)
			 {
				 sprintf((char*)DateStr,"%d-%d-%d",calendar.w_year,calendar.w_month,calendar.w_date);
				 LCD_ShowString(lcddev.width/2-(8*16/2)/2,170,200,16,16,DateStr);
				 Day=calendar.w_date;
			 }
			 bRefresh=0;
		}
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)
		{
			if (tp_dev.x[0]>lcddev.width/2-(8*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(8*16/2)/2+200 &&
				tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
			{
				LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
				LCD_ShowString(lcddev.width/2-(8*16/2)/2,70,200,16,16,"Settings");
				LCD_ShowString(lcddev.width/2-(12*16/2)/2,150,200,16,16,"Change theme");
				LCD_ShowString(lcddev.width/2-(8*16/2)/2,190,200,16,16,"Set Date");			
				LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Back");
				while (1)
				{
					tp_dev.scan(0);
					if (!(tp_dev.sta&TP_PRES_DOWN))
					{
						break;
					}
				}
				while (1)
				{
					tp_dev.scan(0); 		 
					if(tp_dev.sta&TP_PRES_DOWN)
					{
						if (tp_dev.x[0]>lcddev.width/2-(8*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(8*16/2)/2+200 &&
						tp_dev.y[0]>190-20 && tp_dev.y[0]<190+16+20)
						{
							u16 year,mon,day,h,m,s;
							u8 Str[0x20];
							year=calendar.w_year;
							mon=calendar.w_month;
							day=calendar.w_date;
							h=calendar.hour;
							m=calendar.min;
							s=calendar.sec;
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,100,200,16,16,"Year");
							sprintf((char*)Str,"%d",year);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(--year<=1970)year=1971;
										}
										else
										{
											if(++year>=2100)year=2099;
										}
										sprintf((char*)Str,"%d",year);											
										LCD_ShowString(lcddev.width/2-(4*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(5*16/2)/2,100,200,16,16,"Month");
							sprintf((char*)Str,"%d",mon);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(--mon<1)mon=12;
										}
										else
										{
											if(++mon>12)mon=1;
										}
										if (mon<10)
											sprintf((char*)Str,"0%d",mon);
										else
											sprintf((char*)Str,"%d",mon);
										LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(3*16/2)/2,100,200,16,16,"Day");
							sprintf((char*)Str,"%d",day);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(--day<1)day=31;
										}
										else
										{
											if(++day>31)day=1;
										}
										if (day<10)
											sprintf((char*)Str,"0%d",day);
										else
											sprintf((char*)Str,"%d",day);
										LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,100,200,16,16,"Hour");
							sprintf((char*)Str,"%d",h);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(h==0)h=23;else h--;
										}
										else
										{
											if(++h>23)h=0;
										}
										if (h<10)
											sprintf((char*)Str,"0%d",h);
										else
											sprintf((char*)Str,"%d",h);
										LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(6*16/2)/2,100,200,16,16,"Minute");
							sprintf((char*)Str,"%d",m);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(m==0)m=59;else m--;
										}
										else
										{
											if(++m>59)m=0;
										}
										if (m<10)
											sprintf((char*)Str,"0%d",m);
										else
											sprintf((char*)Str,"%d",m);
										LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(6*16/2)/2,100,200,16,16,"Second");
							sprintf((char*)Str,"%d",s);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(4*16/2)/2,250,200,16,16,"Next");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while (1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(4*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(4*16/2)/2+200 &&
										tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
									{
										break;
									}
									else
									{
										if (tp_dev.x[0]<lcddev.width/2 && tp_dev.y[0]<200)
										{
											if(s==0)s=59;else s--;
										}
										else
										{
											if(++s>59)s=0;
										}
										if (s<10)
											sprintf((char*)Str,"0%d",s);
										else
											sprintf((char*)Str,"%d",s);
										LCD_ShowString(lcddev.width/2-(2*16/2)/2,150,200,16,16,Str);
										delay_ms(100);
										continue;
									}
								}
								delay_ms(30);
							}
							
							LCD_Fill(0,0,lcddev.width,lcddev.height,BACK_COLOR);
							LCD_ShowString(lcddev.width/2-(5*16/2)/2,100,200,16,16,"Sure?");
							sprintf((char*)Str,"%d-%d-%d %d:%d:%d",year,mon,day,h,m,s);
							LCD_ShowString(lcddev.width/2-(17*16/2)/2,150,200,16,16,Str);
							LCD_ShowString(lcddev.width/2-(2*16/2)/2,230,200,16,16,"OK");
							LCD_ShowString(lcddev.width/2-(6*16/2)/2,270,200,16,16,"Cancel");
							while (1)
							{
								tp_dev.scan(0);
								if (!(tp_dev.sta&TP_PRES_DOWN))
								{
									break;
								}
							}
							while(1)
							{
								tp_dev.scan(0); 		 
								if(tp_dev.sta&TP_PRES_DOWN)
								{
									if (tp_dev.x[0]>lcddev.width/2-(2*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(2*16/2)/2+200 &&
										tp_dev.y[0]>230-10 && tp_dev.y[0]<230+16+10)
									{
										RTC_Set(year,mon,day,h,m,s);
										break;
									}
									if (tp_dev.x[0]>lcddev.width/2-(6*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(6*16/2)/2+200 &&
										tp_dev.y[0]>270-10 && tp_dev.y[0]<270+16+10)
									{
										break;
									}
								}
							}
							break;
						}
						
						if (tp_dev.x[0]>lcddev.width/2-(12*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(12*16/2)/2+200 &&
							tp_dev.y[0]>150-20 && tp_dev.y[0]<150+16+20)
						{
							if (POINT_COLOR==WHITE && BACK_COLOR==BLACK)
							{
								POINT_COLOR=BLACK;
								BACK_COLOR=WHITE;
							}
							else
							{
								POINT_COLOR=WHITE;
								BACK_COLOR=BLACK;
							}
							break;
						}
						if (tp_dev.x[0]>lcddev.width/2-(12*16/2)/2 && tp_dev.x[0]<lcddev.width/2-(12*16/2)/2+200 &&
							tp_dev.y[0]>250-20 && tp_dev.y[0]<250+16+20)
						{
							break;
						}
					}
					delay_ms(30);
				}
				bRefresh=1;
				continue;
			}
			if (tp_dev.x[0]>lcddev.width/2-50 && tp_dev.x[0]<lcddev.width/2+50 &&
				tp_dev.y[0]>172-50 && tp_dev.y[0]<172+50)
			{
				if (PersentageFlag)
					PersentageFlag=0;
				else
					PersentageFlag=1;
				bRefresh=1;
				continue;
			}
		}
		 delay_ms(1000);
	}
}
*/


int main(void)
 {
	delay_init();	//延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组设置	 
	uart_init(9600);//串口初始化为9600
	LCD_Init();		//初始化LCD 		 	
	TP_Init();		//初始化触摸屏  
	POINT_COLOR=WHITE;
	BACK_COLOR=BLACK;
	RTC_Init();
	RTC_Get();
	//Clock();
 }
