`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/02/2020 08:54:57 PM
// Design Name: 
// Module Name: snowflake_ram_lut
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module snowflake_ram_lut
   #(
    parameter ADDR_WIDTH = 10,  // number of address bits
              DATA_WIDTH = 2    // color depth
   )
   (
    input  logic clk,
    input  logic we,
    input  logic [ADDR_WIDTH-1:0] addr_r,
    input  logic [ADDR_WIDTH-1:0] addr_w,
    input  logic [DATA_WIDTH-1:0] din,
    output logic [DATA_WIDTH-1:0] dout
   );

   // signal declaration
   logic [DATA_WIDTH-1:0] ram [0:2**ADDR_WIDTH-1];
   logic [DATA_WIDTH-1:0] data_reg;
   
   // snowflake.mem specifies the initial values of ram 
   initial 
      $readmemb("snowflake.mem", ram);
      
   // body
   always_ff @(posedge clk)
   begin
      if (we)
         ram[addr_w] <= din;
      data_reg <= ram[addr_r];
   end
   assign dout = data_reg;
endmodule