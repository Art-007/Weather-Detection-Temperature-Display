/*****************************************************************//**
 * @file main_video_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "vga_core.h"
#include "sseg_core.h"
#include "ps2_core.h"
#include "i2c_core.h"


void main_message(OsdCore *osd_p)
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, backg = black
	osd_p->bypass(0);

	// move the message text to a different x and y position
	int x = 8;
	int y = 5;
	int r= 1;

    // display the message "on the sprites click left for celisius or right for fahrenheit"
	static char main_message[64] = { 'O','n',' ','t','h','e',' ','S','p','r','i','t','e','s',' ',
			                         'c','l','i','c','k',' ','l','e','f','t',' ','f','o','r',' ',
									 'C','e','l','s','i','u','s',' ','a','n','d',' ','r','i','g','h','t',
									 ' ','f','o','r',' ','F','a','h','r','e','n','h','e','i','t'};


	for (int i = 0; i < 64; i++)
	{
		osd_p->wr_char(i + x, y, main_message[i], r);
	}

}

void nice_weather_message(OsdCore *osd_p)
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, back = black
	osd_p->bypass(0);
	// osd_p->clr_screen();

	// move the message text to a different x and y position
	int x = 8;
	int y = 21;
	int r= 1;

	 // main message for the user
	 main_message(osd_p);

    // display "The weather is sunny and nice."
	static char sunny_message[56] = {'T','h','e',' ','w','e','a','t','h','e','r',' ','i','s',' ',
			's','u','n','n','y',' ','a','n','d',' ','n','i','c','e', '.',' ', ' ',' ',' ',' ',' ',
			' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',};

	for (int i = 0; i < 56; i++)
	{
		osd_p->wr_char(i + x , y, sunny_message[i], r);
	}


}

void cold_weather_message(OsdCore *osd_p)
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, back = black
	osd_p->bypass(0);
	// osd_p->clr_screen();

	// move the message text to a different x and y position
    int x = 8;
	int y = 21;
	int r= 1;

	 // main message for the user
	main_message(osd_p);

	// write "The weather is a little cold, please wear a light jacket"

	static char lilcold_message[56] = {'T','h','e',' ','w','e','a','t','h','e','r',' ','i','s',' ','a',' ','l','i','t','t'
			,'l','e',' ','c','o','l','d', ' ','p','l','e','a','s','e',' ','w','e','a','r', ' ', 'a', ' ','l','i','g','h','t'
			,' ', 'j','a','c','k','e','t','.'};

	for (int i = 0; i < 56; i++)
	{
		osd_p->wr_char(i + x, y, lilcold_message[i], r);
	}


}


void very_cold_weather_message(OsdCore *osd_p)
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, backg = black
	osd_p->bypass(0);

	// move the message text to a different x and y position
	int x = 8;
	int y = 21;
	int r= 1;

	 // main message for the user
	main_message(osd_p);

	//  write "The weather is very cold, please wear a heavy jacket."
	static char verycold_message[56] = { 'T','h','e',' ','w','e','a','t','h','e','r',' ',
			'i','s',' ','v','e','r','y',' ','c','o','l','d','.',' ','W','e','a','r',' ',
			'a',' ','h','e','a','v','y',' ','j','a','c','k','e','t','.',' ',' ',' ',};

	for (int i = 0; i < 56; i++)
	{
		osd_p->wr_char(i + x, y, verycold_message[i], r);
	}


}

void very_hot_weather_message(OsdCore *osd_p)
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, backg = black
	osd_p->bypass(0);

	// move the message text to a different x and y position
	int x = 8;
	int y = 21;
	int r= 1;

	 // main message for the user
	main_message(osd_p);

	//  write "The weather is very hot. Wear light clothing."
	static char veryhot_message[56] = { 'T','h','e',' ','w','e','a','t','h','e','r',' ',
			'i','s',' ','v','e','r','y',' ','h','o','t','.',' ','W','e','a','r',' ',
			'l','i','g','h','t',' ','c','l','o','t','h','i','n','g','.',' ',' ',' ',' ',' ',
			' ',' ',' ',' ',' ',' ',};

	for (int i = 0; i < 56; i++)
	{
		osd_p->wr_char(i + x, y, veryhot_message[i], r);
	}

}


void current_temp_message(OsdCore *osd_p, float temp_reading, int temp_sel)//temp_sel = 1 for Celsius. 0 for Fahrenheit
{
	osd_p->set_color(0x001, 0xfc0); // front = yellow, backg = black
	osd_p->bypass(0);

	float frac, shift_left1, shift_left2;
	int i_part, tens, ones, tenths, hundredths;

	// move the message text to a different x and y position
	int x = 70;
	int y = 10;
	int r= 1;


	//integer portion
	i_part = (int) temp_reading; // integer part of reading
	frac = temp_reading - (float) i_part;

	//tens place
	tens = i_part/10;

	//ones place
	ones = i_part - (tens*10);

	//tenths place
	shift_left1 = frac*10.0;//shift tenths place number to ones place
	tenths = (int)shift_left1 ;

	//hundredths place
	shift_left2 = (shift_left1 - tenths)*10.0; //subtract shifted value with integer to isolate decimal part of number
	hundredths = (int)shift_left2 ;


	static char numbers[10] = { '0','1','2','3','4','5','6','7','8','9'};//numbers for OSD

	//OSD for Tens place
	osd_p->wr_char(0 + x, y, numbers[tens], r);

	//OSD for Ones place
	osd_p->wr_char(1 + x, y, numbers[ones], r);

	//OSD for decimal
	osd_p->wr_char(2 + x, y, '.', r);

	//OSD for tenths place
	osd_p->wr_char(3 + x, y, numbers[tenths], r);

	//OSD for hundredths place
	osd_p->wr_char(4 + x, y, numbers[hundredths], r);

	if(temp_sel==1)//celsius OSD
	{
		osd_p->wr_char(5 + x, y, 'C', r);
	}
	else if(temp_sel==0)//fahrenheit OSD
	{
		osd_p->wr_char(5 + x, y, 'F', r);
	}


}

void sun_display(SpriteCore *sun_p) { // display sun sprite
   int x, y;

   sun_p->bypass(0);
   sun_p->wr_ctrl(0x02);  //2= Orange color, 1= yellow, 3 = red
   x = 285;
   y = 200;
   sun_p->move_xy(x, y);  // sun dispay at the center of the screen

}

void snowflake_display(SpriteCore *snowflake_p) { // display snowflake sprite
   int x, y;

   snowflake_p->bypass(0);
   snowflake_p->wr_ctrl(0x02); //2= Orange color, 1= yellow, 3 = red
   x = 316;
   y = 200;
   snowflake_p->move_xy(x, y);  // snowflake display at the center of the screen

}


float noise_correction(float reading)//return temp if it has changed more than .002
{
	static float ini_temp = 0;

	float diff;
	diff = (ini_temp >= reading) ? ini_temp-reading : reading-ini_temp;
	if(diff > 0.002)//if temp changes more than .002 update new value
	{
		ini_temp = reading;
		return reading;
	}
	else
		return ini_temp;
}


float temp_check(I2cCore *adt7420_p, int select)//select=1:Celsius. select=0:Fahrenheit
{
   const uint8_t DEV_ADDR = 0x4b;
   uint8_t wbytes[2], bytes[2];
   uint16_t tmp;
   float tmpC, tmpF;

   wbytes[0] = 0x00;
   adt7420_p->write_transaction(DEV_ADDR, wbytes, 1, 1);
   adt7420_p->read_transaction(DEV_ADDR, bytes, 2, 0);

   // conversion
   tmp = (uint16_t) bytes[0];
   tmp = (tmp << 8) + (uint16_t) bytes[1];
   if (tmp & 0x8000) {
      tmp = tmp >> 3;
      tmpC = (float) ((int) tmp - 8192) / 16;
   } else {
      tmp = tmp >> 3;
      tmpC = (float) tmp / 16;
   }

   if(select)//Celsius
    {
       return tmpC;
    }

   if(!select)//Fahrenheit
    {
	   tmpF =  (float) ((tmpC * 9/5) + 32 );
	   return tmpF;
    }

   return 0;
}


void display_messages_based_temp_Celsius(I2cCore *adt7420_p, OsdCore *osd_p, SpriteCore *sun_p, SpriteCore *snowflake_p)
{
	  float Ctemp;
	  float static  temp=0;
	  Ctemp = temp_check(adt7420_p, 1);


	  Ctemp = noise_correction(Ctemp);



	  if(temp != Ctemp)//if Temp has changed display respective message
	  {
		 temp = Ctemp;


		 if (Ctemp >= 15  && Ctemp <20)// if very cold
		  {
			 sun_p->bypass(1);
			 snowflake_display(snowflake_p);   //  display snowflake if very cold
			 very_cold_weather_message(osd_p);  // display very cold message
		  }
		  if (Ctemp >= 20   && Ctemp <25)//if cold
		  {
			  sun_p->bypass(1);
			  snowflake_display(snowflake_p);   //  display snowflake if cold
			  cold_weather_message(osd_p);	// display cold message
		  }
		  if (Ctemp >= 25 && Ctemp <30)//if warm
		  {
			  snowflake_p->bypass(1);	// Turn snowflake off
			  sun_display(sun_p);	//  display sun if warm
			  nice_weather_message(osd_p);	// display warm message
		  }
		  if (Ctemp >= 30 && Ctemp <35) //if hot
		  {
			  snowflake_p->bypass(1); 	// Turn snowflake off
			  sun_display(sun_p);	//display sun if hot
			  very_hot_weather_message(osd_p); //display hot
		  }

		  current_temp_message(osd_p, temp, 1); //display current temp
	  }
}

void display_messages_based_temp_fahrenheit(I2cCore *adt7420_p, OsdCore *osd_p, SpriteCore *sun_p, SpriteCore *snowflake_p)
{
	float Ftemp;
	float static  temp=0;
	Ftemp = temp_check(adt7420_p, 0);


	Ftemp = noise_correction(Ftemp);


	if(temp != Ftemp)//if Temp has changed display respective message
	{
		temp = Ftemp;

		if (Ftemp >= 54  && Ftemp <63)
		{
			sun_p->bypass(1);
			snowflake_display(snowflake_p);   //  display snowflake if cold
			very_cold_weather_message(osd_p);
		}
		if (Ftemp >= 63   && Ftemp <72)
		{
			  sun_p->bypass(1);
			  snowflake_display(snowflake_p);	//  display snowflake if very cold
			  cold_weather_message(osd_p);
		  }
		  if (Ftemp >= 72 && Ftemp <81)
		  {
			  snowflake_p->bypass(1);
			  sun_display(sun_p);               //   display sun if warm weather
			  nice_weather_message(osd_p);
		  }
		  if (Ftemp >= 81 && Ftemp <90)
		  {
			  snowflake_p->bypass(1);
			  sun_display(sun_p);	//   display sun if hot
			  very_hot_weather_message(osd_p);
		  }

		  current_temp_message(osd_p, temp, 0);// display current temp
	  }

}

void click_sprites_change_temp(SpriteCore *mouse_p,  Ps2Core *ps2_p, I2cCore *adt7420_p, OsdCore *osd_p, SpriteCore *sun_p, SpriteCore *snowflake_p,  int lbtn, int rbtn,  int x, int y)
{
	//float Ctemp, Ftemp;
	bool static flag_l = false;//flag when left click has been pressed
	bool static flag_r= false;//flag when right click has been pressed

		if (lbtn == 1)
		 {
			if (x >= 280 && x <= 350 && y >= 190 && y <= 240)//if left click on middle sprites
				{
				   flag_l  = true;
				   flag_r = false;
			   }
		 }

		if(flag_l == true)//continue to redisplay Celsius temp messages if latest click was left click
		{
			  display_messages_based_temp_Celsius(adt7420_p, osd_p, sun_p, snowflake_p);//  display messages

		}


		if (rbtn == 1)
		 {
			if (x >= 280 && x <= 350 && y >= 190 && y <= 240 ) //if right click on middle sprites
				{
					 flag_l  = false;
					 flag_r = true;
				}
		 }

	     if (flag_r == true )//continue to redisplay Fahrenheit temp messages if latest click was right click
		 {
			 display_messages_based_temp_fahrenheit(adt7420_p, osd_p, sun_p, snowflake_p); //  display messages

		 }
}

void initialize_screen(SpriteCore *mouse_p, SpriteCore *sun_p, SpriteCore *snowflake_p, OsdCore *osd_p)
{
	// main message for the user
	 main_message(osd_p);

	 // diplay at the beginning both sprites in the center of the screen
	 sun_display(sun_p);
	 snowflake_display(snowflake_p);
}

void user_interface(SpriteCore *mouse_p, SpriteCore *sun_p, SpriteCore *snowflake_p,  Ps2Core *ps2_p, I2cCore *adt7420_p,  OsdCore *osd_p)
{
   int lbtn, rbtn, xmov, ymov;
   int  static x, y;//x-point & y-point on screen


   if(ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)){

	   x = x + xmov;//add mouse distance to current cursor location
	   y = y - ymov;

	   //reset cursor location if out reaching out bounds
	   if (x < 0)
	   {
		   x=0;
	   }
	   if (x > 639 )
	   {
		   x=639;
	   }
	   if (y < 0)
	   {
		   y=0;
	   }
	   if (y > 479)
	   {
		   y=479;
	   }

	   mouse_p->move_xy(x, y);//move within boundary

   }// if activity

   click_sprites_change_temp(mouse_p, ps2_p, adt7420_p, osd_p,  sun_p, snowflake_p, lbtn, rbtn, x, y);
   //click sprites to display temp messages

 }



// external core instantiation
GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
FrameCore frame(FRAME_BASE);
GpvCore bar(get_sprite_addr(BRIDGE_BASE, V7_BAR));
GpvCore gray(get_sprite_addr(BRIDGE_BASE, V6_GRAY));
SpriteCore sun(get_sprite_addr(BRIDGE_BASE, V4_SUN), 1024);
SpriteCore snowflake(get_sprite_addr(BRIDGE_BASE, V3_SNOWFLAKE), 1024);
SpriteCore mouse(get_sprite_addr(BRIDGE_BASE, V1_MOUSE), 1024);
OsdCore osd(get_sprite_addr(BRIDGE_BASE, V2_OSD));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));
Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));
I2cCore adt7420(get_slot_addr(BRIDGE_BASE, S10_I2C));

int main() {
	ps2.init();  // Initialize
	if(ps2.init() == 2)
	{
	   bar.bypass(1);
	   gray.bypass(1);
	   frame.bypass(1);
	   mouse.bypass(0);
	   initialize_screen(&mouse, &sun, &snowflake, &osd);

	   while (1)
	   {
		   user_interface(&mouse, &sun, &snowflake, &ps2, &adt7420, &osd); // call the main function
	   } // while

	} // if
} //main


