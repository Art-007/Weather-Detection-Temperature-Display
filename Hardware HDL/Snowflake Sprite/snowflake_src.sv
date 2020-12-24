`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/02/2020 08:53:17 PM
// Design Name: 
// Module Name: snowflake_src
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


module snowflake_src
  #(
    parameter CD = 12,      // color depth
              ADDR = 10,    // number of address bits
              KEY_COLOR =0  // chroma key
   )
   (
    input  logic clk,
    input  logic [10:0] x, y,   // x-and  y-coordinate    
    input  logic [10:0] x0, y0, // origin of sprite 
    input  logic [1:0] ctrl,    // sprite control 
    // sprite ram write 
    input  logic we ,
    input  logic [ADDR-1:0] addr_w,
    input  logic [1:0] pixel_in,
    // pixel output
    output logic [CD-1:0] sprite_rgb
   );
   
   // localparam declaration
   localparam H_SIZE = 32; // horizontal size of sprite
   localparam V_SIZE = 32; // vertical size of sprite
   // signal delaration
   logic signed [11:0] xr, yr;  // relative x/y position
   logic in_region;
   logic [ADDR-1:0] addr_r; 
   logic [CD-1:0] full_rgb, snowflake_rgb;
   logic [CD-1:0] out_rgb_d1_reg;
   
   logic [1:0] plt_code;
   logic [CD-1:0] out_rgb; 
   logic [1:0] gc_color_sel;                
   
   // body 
   assign gc_color_sel = ctrl[1:0];

   //******************************************************************
   // sprite RAM
   //******************************************************************
   // instantiate sprite RAM
   snowflake_ram_lut #(.ADDR_WIDTH(ADDR), .DATA_WIDTH(2)) ram_unit (
      .clk(clk), .we(we), .addr_w(addr_w), .din(pixel_in),
      .addr_r(addr_r), .dout(plt_code));
 
   //******************************************************************
   // snowflake color control 
   //******************************************************************
   // snowflake color selection
   always_comb
      case (gc_color_sel)
         2'b00:   snowflake_rgb = 12'h05c;  //  blue
         2'b01:   snowflake_rgb = 12'h0bf;  // light blue
         2'b10:   snowflake_rgb = 12'h00f;  // dark blue
         default: snowflake_rgb = 12'h06a;  // muddy blue
         // 05c blue , light blue 0bf
      endcase   
   // palette table
   always_comb
      case (plt_code)
         2'b00:   full_rgb = 12'h000;   // chrome key
         2'b01:   full_rgb = 12'h111;   // dark gray 
         2'b10:   full_rgb = snowflake_rgb; // snowflake body color
         default: full_rgb = 12'hfff;   // white
      endcase   
   //******************************************************************
   // in-region circuit
   //******************************************************************
   // relative coordinate calculation
   assign xr = $signed({1'b0, x}) - $signed({1'b0, x0});
   assign yr = $signed({1'b0, y}) - $signed({1'b0, y0});
   assign addr_r = { yr[4:0], xr[4:0]};
   // in-region comparison and multiplexing 
   assign in_region = ((0<= xr) && (xr<H_SIZE) && (0<=yr) && (yr<V_SIZE));
   assign out_rgb = in_region ? full_rgb : KEY_COLOR;
   
   //******************************************************************
   // output with a-stage delay line
   //******************************************************************
   always_ff @(posedge clk) 
      out_rgb_d1_reg <= out_rgb;
   assign sprite_rgb = out_rgb_d1_reg;
endmodule