# Final Project "Weather Detection / Temperature Display" 
## This Final involved the use of a mouse (ps2) to move a mouse pointer moving sprite to choose between celisus and fahrenheit, by clicking the mouse left for C and right for F. In additon, the OSD core was use to display diffrent messages on the screen monitor depeding on the temperature. The Temperature was taken using the I2cCore(adt7420) sensor.
### *This Final includes:*

1. - [x] The Hardware, with all the modify code from vivado to permform this lab. 
    * The sun sprite, has all the files need it to display a sun   
    * The snowflake sprite, has all the files need it to display a snowflake
    * The the change files in the mcs_top_complete system, has all the files to run this two sprites 

2. - [x] The driver.
    * The chu_io_map.h, was modfiy to run the sprites on the software  

3. - [x] Test Application.
    * The Final_Project_4305.cpp, has all the C++ code to implement the project functionality 

4. - [x] Project Images.
    * sprites images 
    
5. - [x] SOC additonal Sources.
    * This contains all the needed sources files in the hardware and software to run the project, which also needs to have ip components such as a MicroBlaze MCS (cpu), XADC configuration / instantiation and clock management (under vivado clocking wizard) for four clocks of 100, 25, 40 and 65 MHZ.

6. - [x] Video implemetation of the final project using the FPGA board and a monitor. **[Click here for the Final video ](https://youtu.be/wjzRvunuTA8)**
